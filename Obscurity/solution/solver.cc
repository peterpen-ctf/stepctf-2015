#include <set>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

#include <stdint.h>
#include <unistd.h>
#include <assert.h>

#include "cipher.h"
using namespace std;

void split_bits(uint64_t from, uint32_t *even, uint32_t *odd, int n) {
  uint32_t ans_even, ans_odd;
  ans_even = ans_odd = 0;
  for (int i = 0; i < n; ++i)
    if (i & 1)
      ans_odd = bassign(ans_odd, i >> 1, from >> i);
    else
      ans_even = bassign(ans_even, i >> 1, from >> i);  
  if (even)
    *even = ans_even;
  if (odd)
    *odd = ans_odd;
}

uint64_t merge_bits(uint32_t even, uint32_t odd, int n) {
  uint64_t result = 0;
  for (int i = 0; i < n; ++i) {
    if (i & 1)
      result = bassign(result, i, odd >> (i >> 1));
    else
      result = bassign(result, i, even >> (i >> 1));
  }
  return result;
}

vector<uint64_t> reverse_filter_function(uint16_t keystream) {
  vector<uint64_t> result;
  for (uint32_t sequence = 0; sequence < (1 << 20); ++sequence)
    if (f20(sequence) == bit(keystream, 0))
      result.push_back(sequence);

  for (int i = 1; i < 16; ++i) {
    bool bit_to_match = bit(keystream, i);
    fprintf(stderr, "[%2d/16] result.size() = %d ~> %d\n", i, result.size(), bit_to_match);
    int place = 19 + i;
    vector<uint64_t> tmp;
    for (int j = 0; j < result.size(); ++j) {
      uint64_t sequence = result[j];
      sequence = bunset(sequence, place);
      if (f20(sequence >> i) == bit_to_match)
	tmp.push_back(sequence);
      sequence = bset(sequence, place);
      if (f20(sequence >> i) == bit_to_match)
	tmp.push_back(sequence);
    }
    result.swap(tmp);
  }
  fprintf(stderr, "\n");
  return result;
}

uint16_t g(uint64_t x) {
  uint16_t result = 0;
  const int glen = 11;
  for (int i = 0; i < glen; ++i) {
    uint8_t value = 
      (x >>  0) ^ (x >>  5) ^ (x >>  6) ^ (x >> 7) ^
      (x >> 12) ^ (x >> 21) ^ (x >> 24);
    result = bassign(result, i, value);
    x >>= 1;
  }
  return result;
}

uint16_t h(uint64_t x) {
  uint16_t result = 0;
  const int hlen = 11;
  for (int i = 0; i < hlen; ++i) {
    uint8_t value = 
      (x >>  2) ^ (x >>  4) ^ (x >>  7) ^ (x >>  8) ^
      (x >>  9) ^ (x >> 12) ^ (x >> 13) ^ (x >> 14) ^
      (x >> 17) ^ (x >> 19) ^ (x >> 20) ^ (x >> 21);
    result = bassign(result, i, value);
    x >>= 1;
  }
  return result;  
}

// Функция выбирает 70 битные пары значений odd -- even,
// которые могли находиться с сдвиговом регистре, но
// возвращает только 48 из них, т.к остальные можно однозначно определить.
vector<uint64_t> choose_matching_for_lfsr(vector<uint64_t> even, vector<uint64_t> odd) {
  vector<uint64_t> result;
  map<pair<uint16_t, uint16_t>, vector<uint64_t> > even_table;

  for (int i = 0; i < even.size(); ++i) {
    uint64_t value = even[i];
    pair<uint16_t, uint16_t> key = make_pair(g(value), h(value >> 1));
    even_table[key].push_back(value);
  }

  for (int i = 0; i < odd.size(); ++i) {
    uint64_t value = odd[i];
    pair<uint16_t, uint16_t> key = make_pair(h(value), g(value));
    if (!even_table.count(key))
      continue;

    vector<uint64_t> &vect = even_table[key];
    for (int j = 0; j < vect.size(); ++j) {
      uint64_t found_state = merge_bits(vect[j], value, 64);
      assert(matches_lfsr(found_state, 64));
      result.push_back(found_state & ((1ll << 48) - 1));
      if (result.size() % 100000 == 0)
	fprintf(stderr, "result.size() = %d\n", result.size());
    }
  }
  return result;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage %s 0x32-bit-keystream bits_to_skip flag_length\n", argv[0]);
    return 0;
  }

  int bits_to_skip = atoi(argv[2]);
  int flag_length = atoi(argv[3]);

  uint32_t keystream;
  sscanf(argv[1], "0x%x", &keystream);
  fprintf(stderr, "keystream = 0x%x\nbits_to_skip = %d\nflag_len = %d\n", keystream, bits_to_skip, flag_length);
  uint32_t even, odd;

  // Делим keystream на четные и нечетные биты
  split_bits(keystream, &even, &odd, 32);
  fprintf(stderr, "even = 0x%x, odd = 0x%x\n", even, odd);

  // Находим все последовательности 70-бит(35 - odd, 35 - even), создающие данный keystream
  vector<uint64_t> possible_odd, possible_even;
  cerr << "reversing odd...\n";
  possible_odd  = reverse_filter_function(odd);
  cerr << "reversing even...\n";
  possible_even = reverse_filter_function(even);

  vector<uint64_t> answer = choose_matching_for_lfsr(possible_even, possible_odd);
  fprintf(stderr, "answer.size() = %d\n", answer.size());
  for (int i = 0; i < answer.size(); ++i) {
    for (int j = 0; j < bits_to_skip; ++j)
      lfsr_shift_bit(&(answer[i]), 0);
    char buf[flag_length * 2 + 1];
    for (int j = 0; j < flag_length; ++j)
      snprintf(buf + j * 2, 3, "%.2hhx", lfsr_keystream_byte(&answer[i], 0));
    printf("%s\n", buf);
  }
  fprintf(stderr, "Bye!\n");
  return 0;
}
