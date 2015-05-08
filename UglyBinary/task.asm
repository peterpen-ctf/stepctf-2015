.686
.model flat,stdcall
option casemap:none

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
includelib c:\masm32\lib\kernel32.lib
STD_INPUT_HANDLE                     equ -10
STD_OUTPUT_HANDLE                    equ -11
STD_ERROR_HANDLE                     equ -12

ASSUME FS:NOTHING
CSEG segment  READ  WRITE EXECUTE 
conptr	dd 0
inptr	dd 0
LENS	dd 0
buf	db 17 dup(0)
res	db 64 dup(0)
errmes	db "Oh, no ",10,0
hThread	dd 0
start:
	invoke GetStdHandle,STD_OUTPUT_HANDLE
	mov conptr,EAX
	invoke GetStdHandle,STD_INPUT_HANDLE
	mov inptr,eax
	
	invoke NtCreateThread, addr hThread,THREAD_ALL_ACCESS_VISTA, 0,
	
	; invoke ReadFile, inptr, addr buf, 17, addr LENS, 0
	; lea eax, res
	; push eax
	; lea eax, buf
	; push dword ptr [eax+4]
	; push dword ptr [eax]
	; call real_testkey	
	; invoke WriteFile, conptr, addr res, 64, addr LENS, 0
	; xor eax,eax
	ret
real_testkey proc, key_val_1:DWORD, key_val_2:DWORD, resbuf:DWORD
	
	ret
real_testkey endp
CSEG ends

end start
