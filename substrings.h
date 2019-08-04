#pragma once
#include <stdint.h>
#include <stddef.h>

struct hashmap_entry;
struct substring;

struct hashmap_entry {
  uint32_t offset;
  uint32_t length;
  uint32_t count;
  struct hashmap_entry *next;
};

struct substrings {
  const char *string;
  size_t string_length;
  size_t hashmap_length;
  struct hashmap_entry *hashmap;
};

void substrings_init(struct substrings *data);

void substrings_find(struct substrings *data);

void substrings_show_unique(struct substrings *data);

void substrings_free(struct substrings *data);
