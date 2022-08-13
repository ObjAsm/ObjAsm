; ==================================================================================================
; Title:      DbgShowObjectHeader.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
% include &ObjMemPath&ObjMemWin.cop

ProcName textequ <DbgShowObjectHeader>

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  DbgShowObjectHeader
; Purpose:    Output heading object information.
; Arguments:  Arg1: -> Object Name.
;             Arg2: -> Instance.
;             Arg3: Text RGB color.
;             Arg3: -> Destination Window WIDE name.
; Return:     Nothing.

% include &ObjMemPath&Common\\DbgShowObjectHeader_XP.inc

end
