#include <stdio.h>
#include <assert.h>
#include "cipher.h"

main(){
  int i;
  uint32_t nonce;
  fread(&nonce, 4, 1, stdin);
  
  uint64_t lfsr = key;
  
  for (i = 0; i < 32; ++i)
    lfsr_shift_bit(&lfsr, nonce >> i);
  
  uint32_t nonce_enc = 0;
  for (i = 0; i < 32; ++i)
    nonce_enc |= lfsr_keystream_bit(&lfsr, 0) << i;
  nonce_enc ^= nonce;
  fwrite(&nonce_enc, 4, 1, stdout);
  fflush(stdout);

  uint32_t n;
  fread(&n, 4, 1, stdin);
  assert(n < 0xff);

  char flag[n+1];
  fread(flag, 1, n, stdin);
  for (i = 0; i < n; ++i) 
    flag[i] ^= lfsr_keystream_byte(&lfsr, 0);
  flag[n] = 0;

  fprintf(stderr, "the flag is: %s\n", flag);
  return 0;
}
