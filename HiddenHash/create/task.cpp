#include <stdio.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535897932384626433832795
double q1 [] = {255037122.0,21228535.6118,-31222210.0099,32787438.909,-67417641.7612,-74270237.8351,-20427819.8469,-6292819.17092,-16225114.2612,-20437144.9698,-28156796.7643,-34376782.6837,11241782.3525,115468022.912,4863824.80768,26436635.1965,62538224.0342,-33011432.1142,-39764910.7944,-8608542.09469,-3089987.61241,-11055025.7609,1304209.85595,-15692216.0};
unsigned int q1_len = 24;
double q2 [] = {254612100.0,14027280.6281,-18784685.5744,35210085.7106,-60778878.333,-54393839.4879,-31986439.8741,-28616874.5518,-15757295.0602,2670129.26556,-79931500.0356,-6838426.50206,68760875.0765,16732018.0,582881.752764,51517017.2399,4467959.98166,17323759.1217,29756440.1578,-33108393.768,52029323.5888,-23700083.7673,-108993287.426,-36736303.4412,29052879.7462,45939111.5525,11178756.0};
unsigned int q2_len = 27;


double MakeMagic (double * x,int k,int N){
	/*
                                   N-2
y[k] = x[0] + (-1)**k x[N-1] + 2 * sum x[n]*cos(pi*k*n/(N-1))
                                   n=1
	*/
	double res = 0.0f;
	res = x[0];
	double oone=1.0;
	for (int i=0;i<k; i++)
		oone = oone * (-1.0);
	res = res + oone * x[N-1];
	for (int n=1; n<N-1;n++){
		res = res + 2.0*x[n] * cos(PI * k * 1.0 * n * 1.0 / (1.0*(N-1.0)));
	}
	res = res /(2*(N-1.0));
	return res;
}
void fix (long long int &cmd){
	if ((cmd & 0xFF00) == 0){
		cmd = cmd | 0xC300;
		
	}
	else if ((cmd & 0xFF0000L) == 0){
		cmd = cmd | 0xC30000L;
		
	}
	else if ((cmd & 0xFF000000L) == 0){
		cmd = cmd | 0xC3000000L;
		
	}
	else if ((cmd & 0xFF00000000L) == 0){
		cmd = cmd | 0xC300000000L;
		
	}
	else if ((cmd & 0xFF0000000000L) == 0){
		cmd = cmd | 0xC30000000000L;	
	}
}
unsigned int getHash(double *data,unsigned int data_len,char * st){
	long long int cmd;
	void * ccmd = &cmd;
	unsigned int s_eax,s_ecx;
	for (int i=0; i<data_len; i++){
		double qw = MakeMagic(data,i,data_len);
		//printf("%f\n",qw);
		cmd = round(qw);
		//printf("%llx \n", cmd);
		fix(cmd);
		__asm__ __volatile__ ("mov %0,%%esi"::"m"(st));
		__asm__ __volatile__ ("mov %0,%%ecx"::"m"(s_ecx));
		__asm__ __volatile__ ("mov %0,%%eax"::"m"(s_eax));
		__asm__ __volatile__ ("lea %0,%%edi"::"m"(ccmd));
		__asm__ __volatile__ ("call *0x0(%edi)");
		__asm__ __volatile__ ("movl %%esi,%0":"=m"(st));
		__asm__ __volatile__ ("movl %%ecx,%0":"=m"(s_ecx));
		__asm__ __volatile__ ("movl %%eax,%0":"=m"(s_eax));
		
	}
	return s_eax;
}
int main (int argc, char * argv[] ){
	if (argc <2){
		printf("Usage: <progname> <key>\n");
		return 0;
	}
	unsigned int hash1 = getHash(q1,q1_len,argv[1]);
	unsigned int hash2 = getHash(q2,q2_len,argv[1]);
	//printf("%x %x\n",hash1,hash2);	bffeefac 213f522
	if (hash1 == 0xbffeefac && hash2 == 0x213f522){//53Kur3dh
		printf("Correct key: STCTF#%s#\n",argv[1]);
	}
	else{
		printf("Incorrect key\n");
	}
	return 0;
}
