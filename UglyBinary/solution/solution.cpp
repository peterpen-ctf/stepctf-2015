#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
char flagg [] ={92,119,33,133,29,67,61,152,200,235,211,84,239,183,203,170,0};
unsigned char S[ 256 ];
unsigned int i, j;
/* ключевое расписание */
void rc4_init( char* key, int key_length ){
	unsigned char temp;

	for( i = 0; i != 256; ++i )
	S[ i ] = i;

	for( i = j = 0; i != 256; ++i )
	{
	j = ( j + key[ i % key_length ] + S[ i ] ) % 256;
	temp = S[ i ];
	S[ i ] = S[ j ];
	S[ j ] = temp;
	}
	i = j = 0;
}
unsigned char rc4_output(){
	unsigned char temp;
	i = ( i + 1 ) % 256;
	j = ( j + S[ i ] ) % 256;
	temp = S[ j ];
	S[ j ] = S[ i ];
	S[ i ] = temp;
	return S[ ( temp + S[ j ] ) % 256 ];
}

int main (){
	char key[32];
	char out[17];
	out[16]=0;
	for (int i=40; i<1000; i++){
		sprintf(&(key[0]),"%d",i);
		rc4_init((char *)&(key[0]),strlen((char *)&(key[0])));
		int pos = 0;
		bool is_valid=true;
		for (int i=0; i<strlen((char*)flagg); i++){
			char a = flagg[i];
			char b = a ^ rc4_output();
			if (b >= '0' && b <= 'z'){
				out[pos++]=b;
			}
			else{
				is_valid = false;
				break;
			}
		}
		if (is_valid){
			printf("%s\n",out);
		}
	}
	return 0;
}
