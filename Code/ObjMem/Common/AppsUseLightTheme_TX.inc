; ==================================================================================================
; Title:      AppsUseLightTheme_TX.inc
; Author:     G. Friedrich
; Version:    C.1.0
; Notes:      Version C.1.0, December 2022.
;               - First release.
;               - Bitness independent code.
; ==================================================================================================


; 覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧
; Procedure:  AppsUseLightTheme
; Purpose:    Determine of Light Mode for Apps is enabled.
; Arguments:  None
; Return:     eax = TRUE or FALSE.

align ALIGN_CODE
AppsUseLightTheme proc
  local hKey:HKEY, dValueType:DWORD, dValue:DWORD, dValueSize:DWORD

  mov dValue, TRUE
  mov dValueSize, sizeof(dValue)
  invoke RegOpenKeyExW, HKEY_CURRENT_USER, \
                       $OfsCStrW("Software\Microsoft\Windows\CurrentVersion\Themes\Personalize"), \
                       0, KEY_ALL_ACCESS, addr hKey
  invoke RegQueryValueExW, hKey, $OfsCStrW("AppsUseLightTheme"), NULL, addr dValueType, \
                          addr dValue, addr dValueSize
  mov eax, dValue
  ret
AppsUseLightTheme endp

