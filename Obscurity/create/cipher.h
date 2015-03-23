#include <stdint.h>

#ifdef __key__
const uint64_t key = __key__;
#else
const uint64_t key = 0xdeadbeefll;
#endif

uint8_t fa(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3) {
  uint8_t result;
  result = ((x0 | x1) ^ (x0 & x3)) ^ (x2 & ((x0 ^ x1) ^ x3));
  result &= 1;
  return result;
}

uint8_t fb(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3) {
  uint8_t result;
  result = ((x0 & x1) | x2) ^ ((x0 ^ x1) & (x2 | x3));
  result &= 1;
  return result;
}

uint8_t fc(uint8_t x0, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4) {
  uint8_t result;
  result = (x0 | ((x1 | x4) & (x3 ^ x4))) ^ ((x0 ^ (x1 & x3)) ^ ((x2 ^ x3) | (x1 & x4)));
  result &= 1;
  return result;
}

/* The filter function, x - 48bit LFSR internal state */
uint8_t f(uint64_t x) {
  uint8_t val0, val1, val2, val3, val4;
  val0 = fa(x >>  9, x >> 11, x >> 13, x >> 15);
  val1 = fb(x >> 17, x >> 19, x >> 21, x >> 23);
  val2 = fb(x >> 25, x >> 27, x >> 29, x >> 31);
  val3 = fa(x >> 33, x >> 35, x >> 37, x >> 39);
  val4 = fb(x >> 41, x >> 43, x >> 45, x >> 47);
  return fc(val0, val1, val2, val3, val4);
}


/* L(lfsr) - linear feedback function */
uint8_t L(uint64_t lfsr) {
  int i;
  uint8_t result = 0;
  const int lags[] = {0, 5, 9, 10, 12, 14, 15, 17, 19, 24, 25, 27, 29, 35, 39, 41, 42, 43};
  for (i = 0; i < sizeof(lags)/sizeof(int); ++i) 
    result ^= lfsr >> lags[i];
  result &= 1;
  return result;
}

/* Shift bit `in` into lfsr */
void lfsr_shift_bit(uint64_t *lfsr, uint8_t in) {
  uint64_t feedback;
  feedback = L(*lfsr);
  feedback ^= in;
  feedback &= 1;
  *lfsr = (*lfsr >> 1) | (feedback << 47);
}

/* Get new keystream bit and shift `in` into lfsr */
uint8_t lfsr_keystream_bit(uint64_t *lfsr, uint8_t in) {
  uint8_t result = f(*lfsr);
  lfsr_shift_bit(lfsr, in);
  return result;
}

uint8_t lfsr_keystream_byte(uint64_t *lfsr, uint8_t in) {
  int i;
  uint8_t result = 0;
  for (i = 0; i < 8; ++i) {
    result |= lfsr_keystream_bit(lfsr, in) << i;
    in >>= 1;
  }
  return result;
}
