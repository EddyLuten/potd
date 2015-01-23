// 2015.01.19 - http://www.problemotd.com/problem/popular-letters/
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define DICTIONARY_FILE "/usr/share/dict/words"
#define LETTERS_IN_ALPHABET 26
#define IS_LETTER(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
#define LETTER_INDEX(c) (c >= 'a' ? c - 'a' : c - 'A')

int letter_count[LETTERS_IN_ALPHABET] = { 0 };
int repeat_count[LETTERS_IN_ALPHABET] = { 0 };

int main(void)
{
  FILE* dict;
  int i, character, previous = 0;
  unsigned most_letters_pos = 0, most_repeat_pos = 0;

  setlocale(LC_ALL, "");

  if (!(dict = fopen(DICTIONARY_FILE, "r")))
  {
    printf("Could not open the dictionary file.\n");
    return EXIT_FAILURE;
  }

  while (EOF != (character = fgetc(dict)))
  {
    if (IS_LETTER(character))
    {
      ++letter_count[LETTER_INDEX(character)];

      if (IS_LETTER(previous) && character == previous)
        ++repeat_count[LETTER_INDEX(character)];
    }

    previous = character;
  }

  fclose(dict);

  for (i = 0; i < LETTERS_IN_ALPHABET; ++i)
  {
    if (letter_count[i] >= letter_count[most_letters_pos])
      most_letters_pos = i;
    if (repeat_count[i] >= repeat_count[most_repeat_pos])
      most_repeat_pos = i;

    printf(
      "%c: %'10i | repeated: %'8i\n",
      i + 'A',
      letter_count[i],
      repeat_count[i]
    );
  }

  printf("Most frequent letter: %c\n", most_letters_pos + 'A');
  printf("Most repeating letter: %c\n", most_repeat_pos + 'A');

  return 0;
}
