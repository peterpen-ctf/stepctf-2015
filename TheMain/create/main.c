#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int super_secure_call(void *func, ...);
extern void super_secure_return(int status);

#define call super_secure_call
#define ret  super_secure_return

int main()
{
  // break your logic here
  // this code will never be executed

  printf("passphrase: ");
  char c[100];
  scanf("%s", c);
  if ( (char *)c != "lolol" )
    return;
  if ( (int) c[1] != (int) "azaza")
    return;
  printf("wrong!\n");
  ret(0);
}

unsigned int hash(const char *s)
{
  unsigned int result = 0xdeadbeef;
  while(*s) {
    result = result * 33 + *(s++);
  } 
  ret(result);
}

void xor(char *s, const char *k, int n)
{
  register int i = 0;
  for (i = 0; i < n; ++i) {
    s[i] ^= k[i % 4];
  }
  ret(0);
}

char flag[] = 
  "\x52\xfe\xf0\x5d\x35\x8a\xe5\x2a\x1b"
  "\xbf\xca\x67\x29\xb7\xd0\x56\x18\xb1"
  "\xd7\x56\x17\xb2\xd4\x68\x0f\xad\xfc"
  "\x64\x17\xb7\xcd\x2a";

int solve()
{
  char pass[1000];
  printf("password: ");
  scanf("%s", pass);
  
  unsigned int key = call(hash, pass);
  call(xor, flag, &key, strlen(flag));

  printf("here is your flag:\n%s\n", flag);
  ret(0);
}
