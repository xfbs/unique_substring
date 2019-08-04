#include <stdio.h>
#include <string.h>
#include "substrings.h"
#include <stdlib.h>

void help(const char *name);

int main(int argc, char *argv[]) {
  if(argc < 2) {
    help(argv[0]);
    exit(-1);
  }

  const char *string = argv[1];

  struct substrings sub = {
    .string = string,
    .string_length = strlen(string),
    .hashmap_length = 0
  };

  substrings_init(&sub);

  substrings_find(&sub);

  substrings_show_unique(&sub);

  substrings_free(&sub);

  return 0;
}

void help(const char *name) {
  fprintf(
      stderr,
      "Usage: %s <string>\n"
      "\n"
      "Finds and lists all unique substrings of the string along with their\n"
      "index and offset in the string. Uses a hash table to improve efficiency\n"
      "with Bernstein and Aumasson's SipHash.\n",
      name);
}
