#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cipher.h"

#ifdef __flag__
char flag[] = __flag__;
#else
char flag[] = "The Flag";
#endif

/* random 32-bit nonce generator */
uint32_t get_nonce() {
  uint32_t result;
  FILE *urand = fopen("/dev/urandom", "rb");
  fread(&result, 4, 1, urand);
  fclose(urand);
  return result;
}

main(int argc, char **argv) {
  int i;

  uint32_t nonce = get_nonce();
  fwrite(&nonce, 4, 1, stdout);    
  fflush(stdout);

  uint64_t lfsr = key;

  for (i = 0; i < 32; ++i)
    lfsr_shift_bit(&lfsr, nonce >> i);
  
  uint32_t nonce_enc = 0;
  for (i = 0; i < 32; ++i)
    nonce_enc |= lfsr_keystream_bit(&lfsr, 0) << i;
  nonce_enc ^= nonce;

  uint32_t reader_reply = 0;
  fread(&reader_reply, 4, 1, stdin);
  if (reader_reply != nonce_enc) {
    fprintf(stderr, "A hacking attempt detected!\n");
    exit(0);
  }
  
  uint32_t n = strlen(flag);
  fwrite(&n, 4, 1, stdout);
  fflush(stdout);
  for (i = 0; i < n; ++i)
    flag[i] ^= lfsr_keystream_byte(&lfsr, 0);

  fwrite(flag, 1, n, stdout);
  fflush(stdout);
  fprintf(stderr, "Flag sent!\n");

  return 0;
}
