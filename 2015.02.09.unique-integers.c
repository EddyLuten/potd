// 2015.02.09 - http://www.problemotd.com/problem/unique-integers/
#include <stdio.h>

unsigned is_unique(unsigned num) {
  unsigned flag, flags = 0;
  do {
    flag = 1u << num % 10;
    if (flag & flags) return 0;
    flags |= flag;
  } while (num /= 10);
  return 1;
}

unsigned unique_integers(const unsigned limit) {
  unsigned result = 0;
  for (unsigned i = 0; i <= limit; ++i) result += is_unique(i);
  return result;
}

int main(void) {
  printf("Unique integers: %u\n", unique_integers(1000000));
  return 0;
}
