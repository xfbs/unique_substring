#include "substrings.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void substrings_init(struct substrings *data) {
  if(!data->hashmap_length) {
    data->hashmap_length = data->string_length;
  }

  data->hashmap = calloc(data->hashmap_length, sizeof(struct hashmap_entry));
}

void substring_add(struct substrings *data, size_t offset, size_t length) {
  // find the hash of this substring.
  size_t hash = string_hash(data->string + offset, length);

  // find where in the hash map it should be.
  size_t pos = hash % data->hashmap_length;

  struct hashmap_entry *entry = &data->hashmap[pos];
  struct hashmap_entry *last = NULL;

  // if this entry is empty, we skip straight to adding.
  if(!entry->length) {
    goto adding;
  }

  // try to find the matching substring.
  do {
    if(length == entry->length && 0 == strncmp(data->string + offset, data->string + entry->offset, length)) {
      goto match;
    }
    last = entry;
    entry = entry->next;
  } while(entry);

  // if we got here, it means we didn't find anything, so
  // we create a new node.
  entry = malloc(sizeof(struct hashmap_entry));
  entry->next = NULL;
  last->next = entry;

adding:
  entry->offset = offset;
  entry->length = length;
  entry->count = 1;
  return;

match:
  entry->count++;
  return;
}

void substrings_find(struct substrings *data) {
  // go through the substring lengths, starting at the longest.
  for(size_t length = data->string_length; length >= 1; length--) {
    // go through the offsets, starting at the lowest.
    for(size_t offset = 0; (offset + length) <= data->string_length; offset++) {
      substring_add(data, offset, length);
    }
  }
}

void substrings_show_unique(struct substrings *data) {
  for(size_t i = 0; i < data->hashmap_length; i++) {
    struct hashmap_entry *cur = &data->hashmap[i];

    while(cur) {
      if(cur->count == 1) {
        printf("%u+%u: %.*s\n", cur->offset, cur->length, cur->length, data->string + cur->offset);
      }

      cur = cur->next;
    }
  }
}

void substrings_free(struct substrings *data) {
  for(size_t i = 0; i < data->hashmap_length; i++) {
    struct hashmap_entry *cur = data->hashmap[i].next;

    while(cur) {
      struct hashmap_entry *next = cur->next;
      free(cur);
      cur = next;
    }
  }

  free(data->hashmap);
}
