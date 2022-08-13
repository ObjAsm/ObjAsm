; ==================================================================================================
; Title:      sdword2decW.asm
; Author:     G. Friedrich
; Version:    C.1.1
; Notes:      Version C.1.1, May 2022
;               - First release.
; ==================================================================================================


% include @Environ(OBJASM_PATH)\\Code\\OA_Setup64.inc
TARGET_STR_TYPE = STR_TYPE_WIDE
% include &ObjMemPath&ObjMemWin.cop

externdef TwoDecDigitTableW:WORD
ProcName textequ <sdword2decW>

.code
; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  sdword2decW
; Purpose:    Convert a signed DWORD to its decimal WIDE string representation.
; Arguments:  Arg1: -> Destination WIDE string buffer.
;             Arg2: SDWORD value.
; Return:     eax = Number of BYTEs copied to the destination buffer, including the ZTC.
; Note:       The destination buffer must be at least 24 BYTEs large to allocate the output string
;             (Sign + 10 WIDE characters + ZTC = 24 BYTEs).

% include &ObjMemPath&Common\sdword2decT64.inc

end
