; ==================================================================================================
; Title:      DbgOutFPU_UEFI.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, June 2022.
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup32.inc
% include &ObjMemPath&ObjMemUefi.cop

ProcName textequ <DbgOutFPU_UEFI>

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  DbgOutFPU_UEFI
; Purpose:    Display the content of the FPU.
; Arguments:  Arg1: -> Destination Window WIDE name.
;             Arg2: Text RGB color.
; Return:     Nothing.

% include &ObjMemPath&Common\\DbgOutFPU_XP.inc

end
