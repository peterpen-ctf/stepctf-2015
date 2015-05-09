#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795
unsigned int hash1 (char * key_val_ref){
	//a[0:3] ^ a[4:7] ^ 0xcafebabe ^ 0x5cf7fC7f5 ^ 0x83965013
	__asm{
		push ecx
		push esi
		mov esi, key_val_ref
		
		xor ecx,ecx
		mov eax, dword ptr [esi]
		xor ecx, eax
		xor cl, 0xFE
		xor ch, 0xCA
		ror ecx,8
		xor cl, 0xBE
		xor ch, 0xBA
		ror ecx,8
		
		mov eax, dword ptr [esi+4]
		xor ecx, eax
		xor cl, 0x7F
		xor ch, 0x5C
		ror ecx,8
		xor cl, 0xF5
		xor ch, 0xC7
		ror ecx,8
		
		xor cl, 0x96
		xor ch, 0x83
		ror ecx,8
		xor cl, 0x13
		xor ch, 0x50
		ror ecx,8
		
		mov eax, ecx
		pop esi
		pop ecx
	}
}
unsigned int hash2 (char * key_val_ref){
	//a[0,1,2,3] ^ a[7,4,5,6] ^ 0xFAACCAAF ^ 0x5EEFFCAC ^ 0x65452465
	__asm{
		push ecx
		push esi
		mov esi, key_val_ref
		
		xor ecx,ecx
		mov eax, dword ptr [esi]
		xor ecx, eax
		xor cl, 0xAC
		xor ch, 0xFA
		ror ecx,8
		xor cl, 0xAF
		nop
		xor ch, 0xCA
		ror ecx,8
		
		mov eax, dword ptr [esi+4]
		rol eax, 8
		xor ecx, eax
		xor cl, 0xEF
		nop
		xor ch, 0x5E
		ror ecx,8
		xor cl, 0xAC
		xor ch, 0xFC
		ror ecx,8
		
		xor cl, 0x45
		xor ch, 0x65
		ror ecx,8
		xor cl, 0x65
		xor ch, 0x24
		ror ecx,8
		
		mov eax, ecx
		pop esi
		pop ecx
	}
}


int main (int argc, char * argv[] ){
	if (argc>1){
		printf("%x %x\n",hash1(argv[1]),hash2(argv[1]));
		
	}
	return 0;
}
