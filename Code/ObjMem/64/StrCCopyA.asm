; ==================================================================================================
; Title:      StrCCopyA.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  StrCCopyA
; Purpose:    Copy the the source ANSI string with length limitation.
;             The destination buffer should be large enough to hold the maximum number of
;             characters + 1.
; Arguments:  Arg1: -> Destination buffer.
;             Arg2: -> Source ANSI string.
;             Arg3: Maximal number of charachters to copy, excluding the ZTC.
; Return:     rax = Number of copied BYTEs, including the ZTC.

align ALIGN_CODE
StrCCopyA proc uses rdi pBuffer:POINTER, pSrcStringA:POINTER, dMaxChars:DWORD
  mov rdi, rcx                                          ;rdi = pBuffer
  invoke StrCLengthA, rdx, r8d                          ;pSrcStr, dMaxChars
  m2z CHRA ptr [rax + rdi]                              ;Set ZTC
  invoke MemShift, rdi, pSrcStringA, eax
  add rax, sizeof(CHRA)                                 ;ZTC size
  ret
StrCCopyA endp

end
