#include <stdint.h>

#define bset(n, p)    ((n) | (1ll << (p)))
#define bunset(n, p)  ((n) & (~(1ll << (p))))
#define bit(n, p)     ((n >> p) & 1)
#define bassign(n, p, val) (((val) & 1) ? bset(n, p) : bunset(n, p))

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


uint8_t f20(uint32_t x) {
  uint8_t val[5];
  val[0] = fa(x >> 0, x >> 1, x >> 2, x >> 3);
  val[1] = fb(x >> 4, x >> 5, x >> 6, x >> 7);
  val[2] = fb(x >>  8, x >>  9, x >> 10, x >> 11);
  val[3] = fa(x >> 12, x >> 13, x >> 14, x >> 15);
  val[4] = fb(x >> 16, x >> 17, x >> 18, x >> 19);
  return fc(val[0], val[1], val[2], val[3], val[4]);
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

int matches_lfsr(uint64_t x, int n) {
  for (int i = 48; i < n; ++i) {
    uint64_t to_check = x >> (i - 48);
    if (L(to_check) != bit(x, i))
      return 0;
  }
  return 1;
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
