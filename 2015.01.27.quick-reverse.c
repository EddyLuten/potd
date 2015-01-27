// 2015.01.27 - http://problemotd.com/problem/quick-reverse/
#include <stdio.h>
#include <string.h>

char* str_reverse(char* s) {
  // strlen is "free" with a high level language, since it's pre-calculated in
  // the string's constructor, but this is C... I'm going to assume that it's ok
  // to call strlen.
  const size_t len = strlen(s);

  for (size_t i = 0; i < len / 2; ++i, s[len] = 0) {
    s[len] = s[i]; // magic!
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = s[len];
  }

  return s;
}

int main(int argc, char* argv[]) {
  if (1 == argc) {
    printf("Please provide a string to reverse!\n");
    return 1;
  }

  printf("Reversed: \"%s\"\n", str_reverse(argv[1]));

  return 0;
}
