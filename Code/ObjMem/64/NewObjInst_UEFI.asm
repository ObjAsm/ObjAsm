; ==================================================================================================
; Title:      NewObjInst_UEFI.asm
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, June 2022
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
% include &ObjMemPath&ObjMemUefi.cop

ProcName equ <NewObjInst_UEFI>

; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  NewObjInst_UEFI
; Purpose:    Creates an object instance from an object ID.
; Arguments:  Arg1: Object ID.
; Return:     rax -> New object instance or NULL if failed.

% include &ObjMemPath&X\NewObjInst.asm

end
