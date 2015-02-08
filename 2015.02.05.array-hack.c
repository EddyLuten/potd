// 2015.02.05 - http://problemotd.com/problem/array-hack/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct ArrayHack {
  size_t elem_size;
  size_t capacity;
  size_t cursor;
  void* block;
} ArrayHack;

ArrayHack* ah_create(const size_t elem_size, const size_t capacity) {
  if (0 == elem_size || 0 == capacity) {
    return NULL;
  }

  ArrayHack* ah = malloc(sizeof(ArrayHack));
  ah->block = malloc(elem_size * capacity);
  ah->elem_size = elem_size;
  ah->capacity = capacity;
  ah->cursor = 0;

  return ah;
}

void ah_destroy(ArrayHack** ah) {
  if (ah && *ah) {
    free((*ah)->block);
    free(*ah);
  }
}

size_t ah_push(ArrayHack* ah, const void* data) {
  if (ah->cursor >= ah->capacity) {
    ah->capacity *= 2;
    ah->block = realloc(ah->block, ah->elem_size * ah->capacity);
  }

  memcpy(ah->block + (ah->elem_size * ah->cursor), data, ah->elem_size);
  return ah->cursor++;
}

void* ah_get(ArrayHack* ah, const size_t index) {
  if (!ah || index >= ah->cursor) {
    return NULL;
  }

  return ah->block + (index * ah->elem_size);
}

int main(void) {
  int data;
  size_t ix;
  ArrayHack* ah = ah_create(sizeof(int), 2); // initially stores 2 ints
  assert(NULL != ah);

  data = 123;
  assert(0 == ah_push(ah, (void*)&data));
  assert(123 == *(int*)ah_get(ah, 0));

  data = 456;
  assert(1 == ah_push(ah, (void*)&data));
  assert(456 == *(int*)ah_get(ah, 1));

  data = 789;
  assert(2 == ah_push(ah, (void*)&data)); // causes resize
  assert(123 == *(int*)ah_get(ah, 0));
  assert(456 == *(int*)ah_get(ah, 1));
  assert(789 == *(int*)ah_get(ah, 2));
  assert(NULL == ah_get(ah, 3)); //out of array bounds

  ah_destroy(&ah);
  return EXIT_SUCCESS;
}
