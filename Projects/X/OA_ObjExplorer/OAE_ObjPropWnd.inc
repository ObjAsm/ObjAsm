; ==================================================================================================
; Title:      OAE_ObjPropWnd.inc
; Author:     G. Friedrich
; Version:    Check OA_ObjExplorer.asm
; Purpose:    ObjPropWnd implementation for OA_ObjBrowser.
; ==================================================================================================


;Method Types: static, dynamic, virtual, interface, inline
;Method Implementation: abstract,  




; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.CreateMarkupText
; Purpose:    Emits the HTML render code in a file located in the user temp folder.
; Arguments:  None.
; Return:     Nothing.

Method ObjPropWnd.CreateMarkupText, uses xbx xdi xsi
  local cBuffer[1024]:CHR
  local LastWriteTimeDef:FILETIME, LastWriteTimeAsm:FILETIME, LastWriteTime:FILETIME
  local cAsmFile[MAX_PATH]:CHR, cLibFile[MAX_PATH]:CHR

  SetObject xsi

  ;Reset Stream
  OCall [xsi].MarkupStream::MemoryStream.Seek, QWORD ptr 0, STM_BEGIN

  ;Reset LinkInfos
  OCall [xsi].LinkInfos::DataCollection.DisposeAll

  ;Write header information to the stream
  mov xbx, [xsi].pInfo
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_NAME)
  OCall xsi.WriteString, [xbx].OBJECTINFORMATION.pName
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

  ;Show description (if available)
;  mov xbx, [xbx].OBJECTINFORMATION.pHelpData
;  .if xdi != NULL
;    OCall xsi.WriteString, xdi
;    OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)
;  .endif

  ;Show main files
  mov xdx, [xbx].OBJECTINFORMATION.pFileInfo
  mov xdi, [xdx].FILEINFORMATION.pFileName

  invoke StrCopy, addr cAsmFile, xdi
  invoke PathFindExtension, addr cAsmFile
  FillString [xax], <.asm>

  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILES)
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_INC)
  OCall xsi.ShowFileInfo, xdi, TRUE, addr LastWriteTimeDef, NULL, NULL
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_ASM)
  OCall xsi.ShowFileInfo, addr cAsmFile, TRUE, addr LastWriteTimeAsm, NULL, NULL
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  invoke ExpandEnvironmentStrings, $OfsCStr("%OBJASM_PATH%\Code\Objects\Lib\32A\"), \
                                   addr cLibFile, lengthof(cLibFile)
  invoke PathFindFileName, xdi
  lea xcx, cLibFile
  invoke StrCat, xcx, xax
  invoke PathFindExtension, addr cLibFile
  FillString [xax], <.lib>
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_LIB32A)
  OCall xsi.ShowFileInfo, addr cLibFile, FALSE, addr LastWriteTime, addr LastWriteTimeDef, addr LastWriteTimeAsm
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)

  invoke ExpandEnvironmentStrings, $OfsCStr("%OBJASM_PATH%\Code\Objects\Lib\32W\"), \
                                   addr cLibFile, lengthof(cLibFile)
  invoke PathFindFileName, xdi
  lea xcx, cLibFile
  invoke StrCat, xcx, xax
  invoke PathFindExtension, addr cLibFile
  FillString [xax], <.lib>
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_LIB32W)
  OCall xsi.ShowFileInfo, addr cLibFile, FALSE, addr LastWriteTime, addr LastWriteTimeDef, addr LastWriteTimeAsm
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  invoke ExpandEnvironmentStrings, $OfsCStr("%OBJASM_PATH%\Code\Objects\Lib\64A\"), \
                                   addr cLibFile, lengthof(cLibFile)
  invoke PathFindFileName, xdi
  lea xcx, cLibFile
  invoke StrCat, xcx, xax
  invoke PathFindExtension, addr cLibFile
  FillString [xax], <.lib>
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_LIB64A)
  OCall xsi.ShowFileInfo, addr cLibFile, FALSE, addr LastWriteTime, addr LastWriteTimeDef, addr LastWriteTimeAsm
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)

  invoke ExpandEnvironmentStrings, $OfsCStr("%OBJASM_PATH%\Code\Objects\Lib\64W\"), \
                                   addr cLibFile, lengthof(cLibFile)
  invoke PathFindFileName, xdi
  lea xcx, cLibFile
  invoke StrCat, xcx, xax
  invoke PathFindExtension, addr cLibFile
  FillString [xax], <.lib>
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_FILE_LIB64W)
  OCall xsi.ShowFileInfo, addr cLibFile, FALSE, addr LastWriteTime, addr LastWriteTimeDef, addr LastWriteTimeAsm
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  ;Show inheritance path
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_INHER)
  OCall xsi.ShowInheritance, [xsi].pInfo, FALSE         ;Don't show a link for this final object
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  ;Show method information
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_MTDS)
  OCall [xsi].Methods::DataCollection.ForEach, offset ShowObjMtd, xsi, NULL
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  ;Show variable information
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_VARS)
  OCall [xsi].Variables::DataCollection.ForEach, offset ShowObjVar, xsi, NULL
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_PARA)

  ;Finalize markup text
  OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_END)
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.Done
; Purpose:    Finalizes the ObjPropWnd object and disposes the MDI child window.
; Arguments:  None.
; Return:     Nothing.

Method ObjPropWnd.Done, uses xsi
  SetObject xsi

  ;Release internal data
  OCall [xsi].Variables::DataCollection.Done
  OCall [xsi].Methods::DataCollection.Done

  ;Final object cleanup
  ACall xsi.Done
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.Init
; Purpose:    Initalizes the ObjPropWnd object.
; Arguments:  Arg1: -> Owner object (ClientWnd).
;             Arg2: -> Window Class name.
;             Arg2: -> POBJECTINFORMATION.
; Return:     Nothing.

Method ObjPropWnd.Init, uses xsi, pOwner:$ObjPtr(ClientWnd), pWndClassName:PSTRING, \
                                  pInfo:POBJECTINFORMATION
  SetObject xsi
  OCall [xsi].Methods::DataCollection.Init, xsi, 50, 50, COL_MAX_CAPACITY
  OCall [xsi].Variables::DataCollection.Init, xsi, 50, 50, COL_MAX_CAPACITY
  ACall xsi.Init, pOwner, pWndClassName, pInfo
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Procedure:  MatchObjectImpMethod
; Purpose:    Perform a match test.
; Arguments:  Arg1: -> IMPMTDINFORMATION.
;             Arg2: -> Object name.
;             Arg2: -> Method name.
; Return:     eax = zero if a match was found.

MatchObjectImpMethod proc pImpMtdInfo:PIMPMTDINFORMATION, pObjectName:POINTER, pMethodName:POINTER
  mov xcx, pImpMtdInfo
  invoke StrCompA, [xcx].IMPMTDINFORMATION.pObjectName, pObjectName
  .if eax == 0
    mov xcx, pImpMtdInfo
    invoke StrCompA, [xcx].IMPMTDINFORMATION.pName, pMethodName
  .endif
  ret
MatchObjectImpMethod endp

; ��������������������������������������������������������������������������������������������������
; Procedure:  ShowObjMtd
; Purpose:    Emits HTML codes to render object method member information.
; Arguments:  Arg1: -> MEMBERDATA.
;             Arg2: -> ObjPropWnd.
;             Arg3: Dummy.
; Return:     Nothing.

ShowObjMtd proc uses xbx xdi xsi pMemberData:PMEMBERDATA, pSelf:$ObjPtr(ObjPropWnd), xDummy:XWORD
  local cBuffer[20]:CHR, pMarkupStream:$ObjPtr(MemoryStream), pText:POINTER
  local pImpMtdInfo:PIMPMTDINFORMATION

  mov xcx, pSelf
  lea xdx, [xcx].$Obj(ObjPropWnd).MarkupStream
  mov pMarkupStream, xdx
  mov xsi, pMemberData
  mov xbx, [xsi].MEMBERDATA.pMemberInfo                 ;xbx -> OBJMTDINFORMATION
  .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_UNKNOWN
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
    ;Attention: in this case xbx -> OBJECTINFORMATION
    OCall pSelf::PropWnd.WriteString, [xbx].OBJECTINFORMATION.pAncestorName
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
  .else
    ;Exit if dShowRedefMtds == FALSE
    mov xcx, pSelf
    .if [xcx].$Obj(ObjPropWnd).dShowRedefMtds == FALSE
      .ifBitClr [xsi].MEMBERDATA.dFlags, MDT_FINAL
        ret
      .endif
    .endif

    ;Get the method implementation info
    mov xdx, pSelf
    mov xcx, [xdx].$Obj(ObjPropWnd).pOwner              ;xcx -> ClientWnd
    mov xdx, [xcx].$Obj(ClientWnd).pOwner               ;xdx -> Application
    mov xcx, [xdx].$Obj(Application).pObjDB
    OCall [xcx].$Obj(OA_ObjDB).ImpMethodColl::Collection.FirstThatNot, offset MatchObjectImpMethod, \
                           [xbx].OBJMTDINFORMATION.pObjectName, [xbx].OBJMTDINFORMATION.pName
    mov pImpMtdInfo, xax

;    ;Setup (+)/(-) button
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_SHOWDETAIL
;      invoke WriteFile, hHtmlFile, offset HTML_HIDE, sizeof HTML_HIDE, xdi, NULL
    .else
;      invoke WriteFile, hHtmlFile, offset HTML_SHOW, sizeof HTML_SHOW, xdi, NULL
    .endif

    ;Display object and method names
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
    .endif
    OCall pSelf::PropWnd.WriteString, [xbx].OBJMTDINFORMATION.pObjectName
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_DOT)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_BOLD)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_NONE)
    .endif
    mov ecx, [xbx].OBJMTDINFORMATION.dFlags
    .if ecx == METHODTYPE_VIRTUAL_ABSTRACT || ecx == METHODTYPE_DYNAMIC_ABSTRACT
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_ITALIC)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_NONE)
    .endif
    OCall pSelf::PropWnd.WriteString, [xbx].OBJMTDINFORMATION.pName
    mov ecx, [xbx].OBJMTDINFORMATION.dFlags
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Display method type
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    mov eax, [xbx].OBJMTDINFORMATION.dFlags
    .if eax == METHODTYPE_REDEFINED && [xsi].MEMBERDATA.pDefinition == NULL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_RED)
    .else
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
      .endif
    .endif
    mov eax, [xbx].OBJMTDINFORMATION.dFlags
    .if eax != METHODTYPE_REDEFINED
      lea xcx, SOM_TEXT_TABLE
      mov xcx, PSTRING ptr [xcx + sizeof(PSTRING)*xax]
      mov pText, xcx
      OCall pSelf::PropWnd.WriteString, pText
    .else
      mov xdx, [xsi].MEMBERDATA.pDefinition
      .if xdx != NULL
        mov eax, [xdx].OBJMTDINFORMATION.dFlags
        lea xcx, SOM_TEXT_TABLE
        mov xdx, PSTRING ptr [xcx + sizeof(PSTRING)*xax]
        OCall pSelf::PropWnd.WriteString, xdx
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_UNKNOWN)
      .endif
    .endif
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Display Definition
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      .if pImpMtdInfo == NULL
        ;Draw in red also if it is abstract and final!
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_RED)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .endif
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
    .endif
    mov ecx, [xbx].OBJMTDINFORMATION.dFlags
    .if ecx ==  METHODTYPE_VIRTUAL_ABSTRACT || ecx == METHODTYPE_DYNAMIC_ABSTRACT
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_ABSTRACT)
    .elseif pImpMtdInfo == NULL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_UNKNOWN)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_REGULAR)
    .endif
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Display method status
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
    .endif
    .ifBitClr [xsi].MEMBERDATA.dFlags, MDT_FINAL
      mov xdx, PSTRING ptr SOM_TEXT_TABLE[sizeof(PSTRING)*METHODTYPE_REDEFINED]
      OCall pSelf::PropWnd.WriteString, xdx
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_CHECK)
    .endif
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Close row
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)

    ;Display method comments
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_SHOWDETAIL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
      .endif
      mov xax, pImpMtdInfo
      .if xax != NULL
        mov xsi, [xax].IMPMTDINFORMATION.pHelpData
        .while xsi != NULL
          lea xdx, [xsi + sizeof(POINTER)]
          OCall pSelf::PropWnd.WriteString, xdx
          OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
          mov esi, [xsi]                              ;Move to next string
        .endw
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_NO_INFO)
      .endif
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
    .endif
  .endif
  ret
ShowObjMtd endp

; ��������������������������������������������������������������������������������������������������
; Procedure:  ShowObjVar
; Purpose:    Emits HTML codes to render variable member information.
; Arguments:  Arg1: -> MEMBERDATA.
;             Arg2: -> ObjPropWnd.
;             Arg3: Dummy.
; Return:     Nothing.

ShowObjVar proc uses xbx xdi xsi pMemberData:PMEMBERDATA, pSelf:$ObjPtr(ObjPropWnd), xDummy:XWORD
  local pMarkupStream:$ObjPtr(MemoryStream), pText:POINTER
  local dLength:DWORD, dLength1:DWORD, dLength2:DWORD
  local cBuffer1[1024]:CHR, cBuffer2[1024]:CHR, cHexBuffer[12]:CHR
  local cNumBuffer[20]:CHR

  mov xcx, pSelf
  lea xdx, [xcx].$Obj(ObjPropWnd).MarkupStream
  mov pMarkupStream, xdx
  mov xsi, pMemberData
  mov xbx, [xsi].MEMBERDATA.pMemberInfo                 ;xbx -> OBJVARINFORMATION
  .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_UNKNOWN
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
    ;Attention: In this case xbx -> OBJECTINFORMATION
    OCall pSelf::PropWnd.WriteString, [xbx].OBJECTINFORMATION.pAncestorName
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
  .else
    mov xcx, pSelf
    .if [xcx].$Obj(ObjPropWnd).dShowRedefVars == FALSE
      .ifBitClr [xsi].MEMBERDATA.dFlags, MDT_FINAL
        ret
      .endif
    .endif

    ;Display icon
    .if [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_OBJECT
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_ICON_VAR_OBJ)
    .else
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_ICON_VAR_REG)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_ICON_VAR_RED)
      .endif
    .endif

    ;Display Data name
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
    .endif
    OCall pSelf::PropWnd.WriteString, [xbx].OBJVARINFORMATION.pObjectName
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_DOT)
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_BOLD)
    OCall pSelf::PropWnd.WriteString, [xbx].OBJVARINFORMATION.pName
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Display Variable Type
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .if [xbx].OBJMTDINFORMATION.dFlags == VARIABLETYPE_REDEFINED && \
        [xsi].MEMBERDATA.pDefinition == NULL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_RED)
    .else
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
      .endif
    .endif

    ;Extract Type and Value into cBuffer1 & cBuffer2
    m2z pText                                           ;Position of the colon
    m2z CHR ptr cBuffer1
    m2z CHR ptr cBuffer2
    m2z dLength1
    m2z dLength2
    .if xbx != NULL && [xbx].OBJVARINFORMATION.pArgType != NULL
      .if [xbx].OBJVARINFORMATION.dFlags != VARIABLETYPE_OBJECT     ;Handled separately
        invoke StrLScan, [xbx].OBJVARINFORMATION.pArgType, ","
        mov pText, xax
        .if xax != NULL
          add xax, sizeof CHR
          invoke StrLRTrim, addr cBuffer2, xax
          ;Handle this special case "{...}
          .if CHR ptr cBuffer2[0] == TVTAG_CMD_OPEN
            FillString cBuffer2, <{#7B}}>
          .endif
        .else
          FillString cBuffer2, <[I]Not Declared[~]>
        .endif
        invoke StrLength, addr cBuffer2
        if TARGET_STR_TYPE eq STR_TYPE_WIDE
          add eax, eax
        endif
        mov dLength2, eax
        .if [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_REDEFINED
          invoke StrLRTrim, addr cBuffer2, [xbx].OBJVARINFORMATION.pArgType
          invoke StrLength, addr cBuffer2
          if TARGET_STR_TYPE eq STR_TYPE_WIDE
            add eax, eax
          endif
          mov dLength2, eax
          mov xbx, [xsi].MEMBERDATA.pDefinition
          .if xbx != NULL
            mov pText, $invoke(StrLScan, [xbx].OBJVARINFORMATION.pArgType, ",")
          .endif
        .endif

        .if pText != NULL
          mov xax, pText
          sub xax, [xbx].OBJVARINFORMATION.pArgType
        .else
          invoke StrLength, [xbx].OBJVARINFORMATION.pArgType
          if TARGET_STR_TYPE eq STR_TYPE_WIDE
            add eax, eax
          endif
        .endif
        mov dLength1, eax
        invoke StrCCopy, addr cBuffer1, [xbx].OBJVARINFORMATION.pArgType, eax
      .endif
    .endif

    ;Display them
    .if xbx == NULL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_UNKNOWN)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_UNKNOWN)

    .elseif [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_UNKNOWN
      ;Show the name
      OCall pMarkupStream::MemoryStream.BinWrite, addr cBuffer1, dLength1
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
      ;Show the type
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
      .endif
      OCall pMarkupStream::MemoryStream.BinWrite, addr cBuffer2, dLength2
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    .elseif [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_REGULAR
      ;Show the name
      OCall pMarkupStream::MemoryStream.BinWrite, addr cBuffer1, dLength1
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
      ;Show the type
      .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
      .endif
      OCall pMarkupStream::MemoryStream.BinWrite, addr cBuffer2, dLength2
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    .elseif [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_OBJECT
      invoke StrLength, [xbx].OBJVARINFORMATION.pArgType
      if TARGET_STR_TYPE eq STR_TYPE_WIDE
        add eax, eax
      endif
      mov dLength, eax
      mov xcx, pSelf
      mov xdx, [xcx].$Obj(ObjPropWnd).pOwner            ;xdx -> ClientWnd
      OCall [xdx].$Obj(ClientWnd).pOwner::Application.FindObjInfo, [xbx].OBJVARINFORMATION.pArgType
      .if xax != NULL
        ;Show the link
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_LINK_BEG)
        ;Create a new entry in LinkInfos
        OCall pSelf::ObjPropWnd.CreateLinkInfo, LIA_GOTO_OBJECT, [xbx].OBJVARINFORMATION.pArgType, 0
        invoke dword2dec, addr cNumBuffer, eax
        OCall pSelf::PropWnd.WriteString, addr cNumBuffer
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_LINK_END)
        OCall pMarkupStream::MemoryStream.BinWrite, [xbx].OBJVARINFORMATION.pArgType, dLength
        OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
      .else
        OCall pMarkupStream::MemoryStream.BinWrite, [xbx].OBJVARINFORMATION.pArgType, dLength
      .endif
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TPL_DEFAULTS)
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
    .else
      DbgWarning "Unknown Variable Type"
      DbgStr [xbx].OBJVARINFORMATION.pName
      DbgHex [xbx].OBJVARINFORMATION.dFlags
    .endif
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    ;Display Variable status
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_TAB)
    .ifBitSet [xsi].MEMBERDATA.dFlags, MDT_FINAL
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_BLACK)
    .else
      OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_COLOR_GRAY)
    .endif
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_CHECK)
    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)

    OCall pMarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_BREAK)
  .endif
  ret
ShowObjVar endp

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.Gather
; Purpose:    Collect all informations of this object.
; Arguments:  None.
; Return:     Nothing.

Method ObjPropWnd.Gather, uses xsi
  SetObject xsi
  OCall xsi.GatherMethods, [xsi].pInfo
  OCall xsi.GatherVariables, [xsi].pInfo
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Procedure:  GatherObjMtds
; Purpose:    Recursion procedure used to collect object method information.
; Arguments:  Arg1: -> OBJECTINFORMATION.
;             Arg2: -> Object name.
;             Arg3: -> ObjPropWnd.
; Return:     Nothing.

GatherObjMtds proc uses xbx xdi xsi pObjMtdInfo:POBJMTDINFORMATION, pObjName:PSTRING, pSelf:$ObjPtr(ObjPropWnd)
  SetObject xsi, ObjPropWnd
  mov xbx, pObjMtdInfo
  .if $invoke(StrCompA, [xbx].OBJMTDINFORMATION.pObjectName, pObjName) == 0
    mov xdi, $MemAlloc(MEMBERDATA)
    mov [xdi].MEMBERDATA.pMemberInfo, xbx
    mov [xdi].MEMBERDATA.dFlags, MDT_FINAL
    m2z [xdi].MEMBERDATA.pDefinition
    .if [xbx].OBJMTDINFORMATION.dFlags == METHODTYPE_REDEFINED
      OCall [xsi].Methods::DataCollection.LastThatNot, offset FindFinalMember, xdi, NULL
    .endif
    OCall [xsi].Methods::DataCollection.Insert, xdi
  .endif
  ret
GatherObjMtds endp

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.GatherMethods
; Purpose:    Collect all method information of this object.
; Arguments:  Arg1: -> OBJECTINFORMATION.
; Return:     Nothing.

Method ObjPropWnd.GatherMethods, uses xsi, pInfo:POBJECTINFORMATION
  SetObject xsi
  OCall [xsi].Methods::DataCollection.DisposeAll

  mov xcx, pInfo
  mov xdx, [xcx].OBJECTINFORMATION.pAncestorName
  .if xdx != NULL
    mov xcx, [xsi].pOwner                               ;xcx -> ClientWnd
    OCall [xcx].$Obj(ClientWnd).pOwner::Application.FindObjInfo, xdx
    .if xax != NULL
      OCall xsi.GatherMethods, xax
    .else
      ;Stop recursion
      MemAlloc MEMBERDATA
      OCall [xsi].Methods::DataCollection.Insert, xax
      m2m [xax].MEMBERDATA.pMemberInfo, pInfo, xdx
      mov [xax].MEMBERDATA.dFlags, MDT_UNKNOWN
      m2z [xax].MEMBERDATA.pDefinition
    .endif
  .endif

  mov xax, pInfo
  mov xcx, [xsi].pOwner                                 ;xcx -> ClientWnd
  mov xdx, [xcx].$Obj(ClientWnd).pOwner                 ;xax -> Application
  mov xcx, [xdx].$Obj(Application).pObjDB
  OCall [xcx].$Obj(OA_ObjDB).ObjMethodColl::ObjMtdInfoCollection.ForEach, \
                                            offset GatherObjMtds, [xax].OBJECTINFORMATION.pName, xsi
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Procedure:  GatherObjVars
; Purpose:    Recursion procedure used to collect variable information.
; Arguments:  Arg1: -> OBJVARINFORMATION.
;             Arg2: -> Object name.
;             Arg3: -> ObjPropWnd.
; Return:     Nothing.

GatherObjVars proc uses xbx xdi xsi pObjVarInfo:POBJVARINFORMATION, pObjName:PSTRING, pSelf:$ObjPtr(ObjPropWnd)
  SetObject xsi, ObjPropWnd
  mov xbx, pObjVarInfo
  .if $invoke(StrCompA, [xbx].OBJVARINFORMATION.pObjectName, pObjName) == 0
    mov xdi, $MemAlloc(MEMBERDATA)
    mov [xdi].MEMBERDATA.pMemberInfo, xbx
    mov [xdi].MEMBERDATA.dFlags, MDT_FINAL
    m2z [xdi].MEMBERDATA.pDefinition
    .if [xbx].OBJVARINFORMATION.dFlags == VARIABLETYPE_REDEFINED
      OCall [xsi].Variables::DataCollection.LastThatNot, offset FindFinalMember, xdi, NULL
    .endif
    OCall [xsi].Variables::DataCollection.Insert, xdi
  .endif
  ret
GatherObjVars endp

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.GatherVariables
; Purpose:    Collect all method information of this object.
; Arguments:  Arg1: -> OBJECTINFORMATION.
; Return:     Nothing.

Method ObjPropWnd.GatherVariables, uses xsi, pInfo:POBJECTINFORMATION
  SetObject xsi
  OCall [xsi].Variables::DataCollection.DeleteAll

  mov xcx, pInfo
  mov xdx, [xcx].OBJECTINFORMATION.pAncestorName
  .if xdx != NULL
    mov xcx, [xsi].pOwner                               ;xcx -> ClientWnd
    OCall [xcx].$Obj(ClientWnd).pOwner::Application.FindObjInfo, xdx
    .if xax != NULL
      OCall xsi.GatherVariables, xax
    .else
      ;Stop recursion
      MemAlloc MEMBERDATA
      OCall [xsi].Variables::DataCollection.Insert, xax
      m2m [xax].MEMBERDATA.pMemberInfo, pInfo, xdx
      mov [xax].MEMBERDATA.dFlags, MDT_UNKNOWN
      m2z [xax].MEMBERDATA.pDefinition
    .endif
  .endif

  mov xax, pInfo
  mov xcx, [xsi].pOwner                                 ;xcx -> ClientWnd
  mov xdx, [xcx].$Obj(ClientWnd).pOwner                 ;xax -> Application
  mov xcx, [xdx].$Obj(Application).pObjDB
  OCall [xcx].$Obj(OA_ObjDB).ObjVariableColl::ObjVarInfoCollection.ForEach, \
                offset GatherObjVars, [xax].OBJECTINFORMATION.pName, xsi
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Method:   	ObjPropWnd.ShowInheritance
; Purpose:  	Method that is called recursively to output an inheritance path.
; Arguments:	Arg1: -> OBJECTINFORMATION.
;           	Arg2: Flag to signal if the current item should generate a link.
; Return:   	Nothing.

Method ObjPropWnd.ShowInheritance, uses xbx xsi, pObjectInfo:POBJECTINFORMATION, dLink:DWORD
  local cNumBuffer[20]:CHR, pLinkInfo:PLINK_INFO, cHexBuffer[12]:CHR

  SetObject xsi
  mov xcx, pObjectInfo
  mov xbx, [xcx].OBJECTINFORMATION.pAncestorName
  .if xbx != NULL
    mov xcx, [xsi].pOwner                               ;xcx -> ClientWnd
    OCall [xcx].$Obj(ClientWnd).pOwner::Application.FindObjInfo, xbx
    .if xax != NULL
      OCall xsi::ObjPropWnd.ShowInheritance, xax, TRUE  ;Show a link for this object
      OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_ARROW)
    .endif
  .endif

  mov xcx, pObjectInfo
  mov xbx, [xcx].OBJECTINFORMATION.pName
  .if dLink != FALSE
    ;Show the link
    OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_LINK_BEG)
    ;Create a new entry in LinkInfos
    OCall xsi::ObjPropWnd.CreateLinkInfo, LIA_GOTO_OBJECT, xbx, 0
    invoke dword2dec, addr cNumBuffer, eax
    OCall xsi::PropWnd.WriteString, addr cNumBuffer
    OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_LINK_END)
    OCall xsi::PropWnd.WriteString, xbx
    OCall [xsi].MarkupStream::MemoryStream.BinWrite, $OfsSze(MTXT_STYLE_CLOSE)
  .else
    OCall xsi::PropWnd.WriteString, xbx
  .endif
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.OnNotify
; Purpose:    Event procedure for WM_NOTIFY message.
; Arguments:  Arg1: First message parameter.
;             Arg2: Second message parameter.
; Return:     Nothing.

Method ObjPropWnd.OnNotify, uses xbx xdi xsi, wParam:WPARAM, lParam:LPARAM
  local dCheckBoxIndex:DWORD, Img:$Obj(Image), DstRect:RECT
  local StartupInfo:STARTUPINFO, ProcessInfo:PROCESS_INFORMATION
  local cFileName[MAX_PATH]:CHR, cFormat[2*MAX_PATH]:CHR, cCommand[2*MAX_PATH]:CHR

  SetObject xsi
  mov xax, wParam
  .if xax == VIEW_CTRL_ID
    mov xdi, lParam
    .if [xdi].NMHDR.code == TVNMC_APP_MOUSEUP
      OCall [xsi].LinkInfos::DataCollection.ItemAt, [xdi].TVNM_APP.dID
      .if xax != NULL
        .if [xax].LINK_INFO.dAction == LIA_GOTO_OBJECT
          mov xcx, [xsi].pOwner                         ;xcx -> ClientWnd
          OCall [xcx].$Obj(ClientWnd).pOwner::Application.Navigate, [xax].LINK_INFO.pParam, INFO_TYPE_OBJECT

        .elseif [xax].LINK_INFO.dAction == LIA_OPEN_FILE
          mov xbx, xax
          mov xcx, $ObjTmpl(Application).pViewerApp
          .if xcx == NULL || CHR ptr [xcx] == 0
            invoke ShellExecute, 0, offset cOpen, [xax].LINK_INFO.pParam, NULL, NULL, SW_SHOW
          .else
            invoke ExpandEnvironmentStrings, xcx, addr cFormat, lengthof cFormat
            invoke wsprintf, addr cCommand, addr cFormat, [xbx].LINK_INFO.pParam, [xbx].LINK_INFO.dParam
            DbgStr cCommand

            mov StartupInfo.cb, sizeof STARTUPINFO
            invoke GetStartupInfo, addr StartupInfo
            mov StartupInfo.dwFlags, STARTF_USESHOWWINDOW
            mov StartupInfo.wShowWindow, SW_SHOW
            invoke CreateProcess, NULL, addr cCommand, NULL, NULL, TRUE, NULL, NULL, NULL, \
                                  addr StartupInfo, addr ProcessInfo
          .endif
        .endif
      .endif

    .elseif [xdi].NMHDR.code == TVNMC_TIP
      .if [xdi].TVNM_TIP.dID == INFO_BUILD
        c2m [xdi].TVNM_TIP.pText, $OfsCStr("BuildInfo"), xax

      .elseif [xdi].TVNM_TIP.dID == INFO_UPDATE
        c2m [xdi].TVNM_TIP.pText, $OfsCStr("UpdateInfo"), xax
      .endif

    .elseif [xdi].NMHDR.code == TVNMC_TXT
      .if [xdi].TVNM_TXT.dID == 0

      .endif

    .elseif [xdi].NMHDR.code == TVNMC_DRAW
      New Img::Image
      OCall Img::Image.Init, xsi

      .if [xdi].TVNM_DRAW.dID == VARIABLETYPE_UNKNOWN
        OCall Img::Image.%LoadFromRes, $OfsCStr("PngVarUnk")
      .elseif [xdi].TVNM_DRAW.dID == VARIABLETYPE_REGULAR
        OCall Img::Image.%LoadFromRes, $OfsCStr("PngVarReg")
      .elseif [xdi].TVNM_DRAW.dID == VARIABLETYPE_REDEFINED
        OCall Img::Image.%LoadFromRes, $OfsCStr("PngVarRed")
      .elseif [xdi].TVNM_DRAW.dID == VARIABLETYPE_OBJECT
        OCall Img::Image.%LoadFromRes, $OfsCStr("PngVarObj")
      .endif
      m2m DstRect.left, [xdi].TVNM_DRAW.Position.x, eax
      m2m DstRect.top, [xdi].TVNM_DRAW.Position.y, ecx
      invoke MulDiv, Img.$Obj(Image).Dim.x, [xdi].TVNM_DRAW.dZoomFactor, TVZOOM_BASE
      mov DstRect.right, eax
      invoke MulDiv, Img.$Obj(Image).Dim.y, [xdi].TVNM_DRAW.dZoomFactor, TVZOOM_BASE
      mov DstRect.bottom, eax
      OCall Img::Image.AlphaDraw, [xdi].TVNM_DRAW.hDC, 255, addr DstRect
      OCall Img::Image.Done
    .endif
  .endif
MethodEnd

; ��������������������������������������������������������������������������������������������������
; Method:     ObjPropWnd.Startup
; Purpose:    Registers the object with the OS.
; Arguments:  None.
; Return:     Nothing.

Method ObjPropWnd.Startup
  local WC:WNDCLASSEX

  mov WC.cbSize, sizeof WNDCLASSEX
  m2z WC.style
  m2m WC.lpfnWndProc, $MethodAddr(ObjPropWnd.WndProc), xdx
  mov WC.cbClsExtra, 0
  mov WC.cbWndExtra, 0
  m2m WC.hInstance, hInstance, xdx
  mov WC.hbrBackground, 0
  mov WC.lpszMenuName, NULL
  m2m WC.lpszClassName, offset cObjPropClass, xax
  mov WC.hIcon, $invoke(LoadIcon, hInstance, $OfsCStr("ICON_OBJ_STD"))
  mov WC.hIconSm, 0
  mov WC.hCursor, $invoke(LoadCursor, NULL, IDC_ARROW)

  invoke RegisterClassEx, addr WC
MethodEnd
