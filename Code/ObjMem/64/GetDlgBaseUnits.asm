; ==================================================================================================
; Title:      GetDlgBaseUnits.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, October 2017
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemWin.cop

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  GetDlgBaseUnits
; Purpose:    Return the Dialog Base Units.
; Arguments:  Arg1: Dialog DC.
; Return:     eax = X DBU.
;             ecx = Y DBU.

% include &ObjMemPath&Common\GetDlgBaseUnits_X.inc

end
