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
double getTemp (){
	int s, error;
    struct sockaddr_in addr;
    if((s = socket(AF_INET,SOCK_STREAM,0))<0){
        //cout<<"Error 01: creating socket failed!\n";
        close(s);
        return 0;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_aton("146.185.151.176",&addr.sin_addr);

    error = connect(s,(sockaddr*)&addr,sizeof(addr));
    if(error!=0)    {
        //cout<<"Error 02: conecting to server failed!\n";
        close(s);
        return 0;
    }

    char msg[] = "GET /data/2.5/weather?q=Saint-Petersburg&units=metric http/1.1\nHOST: api.openweathermap.org\n\n";
    char answ[1024];
    //cin.getline(&msg[0],256);
	
    send(s,msg,sizeof(msg),0);

    if (recv(s,answ,1024,0)!=0){
		close(s);
		char * pos1 = strstr(answ,"temp");
		if (pos1 !=0){
			char * pos2 = strstr(pos1,",");
			if (pos2 !=0){
				char * res = new char [10];
				memcpy(res,pos1+6,pos2-pos1-6);
				float resd;
				sscanf(res,"%f",&resd);
				return resd-273.15;
			}
			else 
				return 0;
		}
		else
			return 0;
	}
	else{
		close(s);
		return 0;
	}
}
long long int GetTime(){
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
	long long int rrr = time_in_mill;
	return time_in_mill;
}
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
	double temp = round(getTemp());
	if (temp < 40){
		printf("It's too cold for me :(\n");
		return 0;
	}
	int proc_count = sysconf(_SC_NPROCESSORS_ONLN);
	if (proc_count < 32){
		printf("Too slow machine :(\n");
		return 0;
	}
	char buf[17];
	buf[16]=0;
	
	printf("Okay, enter you name:");
	system("/bin/stty raw");
	unsigned int ttt=0;
	for(int i=0; i<16; i++){
		long long int start = GetTime();
		buf[i] = getchar();
		long long int elaps =  GetTime()-start;
		if (elaps < 10)
			ttt = ttt | 1;
		ttt << 1;
	}
	system("/bin/stty cooked");
	if (ttt ==0){
		printf("%s is invalid name\n Oh ... you are too slow :(\n",buf);
		return 0;
	}
	puts("");
	char key [32];
	//unsigned char flag[]={"AUDACTY7H32DHAPY"};// 42 911
	// STCTF#AUDACTY7H32DHAPY#
	sprintf(&(key[0]),"%d",42+911);//temp+proc_count
	rc4_init((char *)&(key[0]),strlen((char *)&(key[0])));
	for (int i=0; i<strlen((char*)buf); i++){
		char a = flagg[i];
		char b = buf[i] ^ rc4_output();
		if (a != b){
			printf("Invalid key :(\n");
			return 0;
		}
	}
	printf("Okay your flag is STCTF#%s#\n",buf);
	
	
	return 0;
}
