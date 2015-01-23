#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

size_t real_len(const char* str)
{
  return strchr(str, '\n') - str;
}

bool is_one_letter_off(const char* w1, const char* w2)
{
  bool found_inconsistency = false;
  size_t len = strlen(w1), i = 0;

  if (len != real_len(w2))
    return false;

  for (; i < len; ++i)
    if (w1[i] != w2[i])
    {
      if (found_inconsistency)
        return false;
      found_inconsistency = true;
    }

  return found_inconsistency;
}

int main(int argc, char* argv[])
{
  const char* word;
  FILE* dict;
  char* line;
  size_t len,
         words = 0;

  if (argc != 2)
  {
    printf("please provide a word to check\n");
    return EXIT_FAILURE;
  }

  word = argv[1];

  if (!(dict = fopen("/usr/share/dict/words", "r")))
  {
    printf("could not open the dictionary file\n");
    return EXIT_FAILURE;
  }

  while (-1 != getline(&line, &len, dict))
  {
    if (is_one_letter_off(word, line))
    {
      printf("%s", line);
      ++words;
    }
  }

  free(line);
  fclose(dict);

  if (0 == words)
    printf("no words found\n");

  return EXIT_SUCCESS;
}
