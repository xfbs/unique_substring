#include "hash.h"
#include "siphash.h"
#include <string.h>

uint8_t key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 16, 15, 14, 13, 12, 11, 10, 9};

size_t string_hash(const char *begin, size_t length) {
  uint8_t out[8];
  siphash((const uint8_t *) begin, length, key, out, sizeof(out));
  size_t ret;
  memcpy(&ret, out, sizeof(ret));

  return ret;
}
