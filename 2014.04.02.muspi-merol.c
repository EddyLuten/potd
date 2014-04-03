// 2014-04-02 - http://www.problemotd.com/problem/muspi-merol/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MIN_WORD_LENGHT 1
#define MAX_WORD_LENGTH 10
#define MIN_SENTENCE_WORDS 3
#define MAX_SENTENCE_WORDS 14
#define MAX_SENTENCE_LENGTH 80
#define MIN_PARAGRAPH_SENTENCES 3
#define MAX_PARAGRAPH_SENTENCES 6
#define NUM_PARAGRAPHS 10

const char VOWELS[] = { 'a', 'e', 'i', 'o', 'u' };
const char CONSONANTS[] = {
  'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
  'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y',
  'z'
};
const char MUSPI[] = {
  'M', 'u', 's', 'p', 'i', ' ', 'M', 'e', 'r', 'o', 'l', ' '
};

const unsigned VOWELS_COUNT = sizeof(VOWELS) / sizeof(char);
const unsigned CONSONANTS_COUNT = sizeof(CONSONANTS) / sizeof(char);
const unsigned MUSPI_LENGTH = sizeof(MUSPI) / sizeof(char);

unsigned dice_roll(unsigned chance)
{
  return 0 == rand() % chance;
}

char get_vowel()
{
  return VOWELS[ rand() % (VOWELS_COUNT - 1) ];
}

char get_consonant()
{
  return CONSONANTS[ rand() % (CONSONANTS_COUNT - 1) ];
}

char* generate_word(const unsigned max_word_length)
{
  unsigned i,
           word_length = rand() % max_word_length + MIN_WORD_LENGHT,
           is_consonant = dice_roll(2);
  char* word = calloc(word_length + 2, sizeof(char)); // 2 = space + null

  for (i = 0; i < word_length; ++i)
  {
    if ((!is_consonant && dice_roll(5)) || is_consonant || 1 == word_length)
    {
      word[i] = get_vowel();
      is_consonant = 0;
      continue;
    }

    word[i] = get_consonant();
    is_consonant = 1;
  }

  word[word_length] = ' ';
  return word;
}

char* generate_sentence(const unsigned max_words,
                        const unsigned capitalize)
{
  unsigned i,
           word_len;
  unsigned sentence_words = rand() % max_words + MIN_SENTENCE_WORDS,
           cur_len = 0;
  char *word = NULL,
       *sentence = calloc(1, sizeof(char));

  for (i = 0; i < sentence_words; ++i)
  {
    word = generate_word(MAX_WORD_LENGTH);
    word_len = strlen(word);

    if (capitalize && 0 == i) word[i] -= 32;

    sentence = realloc(
      sentence,
      ((cur_len += word_len) + 1) * sizeof(char)
    );
    sentence[cur_len - word_len] = '\0';
    strcat(&sentence[cur_len - word_len], word);
    free(word);
  }

  sentence = realloc(sentence, (cur_len + 2) * sizeof(char));
  sentence[cur_len - 1] = '.';
  sentence[cur_len    ] = ' ';
  sentence[cur_len + 1] = '\0';
  return sentence;
}

char* generate_paragraph(const unsigned add_muspi)
{
  unsigned i,
           max_words,
           sentence_len,
           is_muspi,
           paragraph_sentences,
           cur_len = 0;
  char *sentence = NULL,
       *paragraph = calloc(1, sizeof(char));

  paragraph_sentences =
    rand() % MAX_PARAGRAPH_SENTENCES + MIN_PARAGRAPH_SENTENCES;
  
  for (i = 0; i < paragraph_sentences; ++i)
  {
    is_muspi = add_muspi && 0 == i;
    max_words = rand() % MAX_SENTENCE_WORDS + 1;
    max_words = is_muspi && max_words > 2 ? max_words - 2 : max_words;

    sentence = generate_sentence(max_words, !is_muspi);
    sentence_len = strlen(sentence);

    if (is_muspi)
    {
      sentence = realloc(sentence, (sentence_len += MUSPI_LENGTH) + 1);
      memcpy(&sentence[MUSPI_LENGTH],
        sentence,
        (sentence_len - MUSPI_LENGTH) / sizeof(char)
      );
      memcpy(sentence, MUSPI, MUSPI_LENGTH / sizeof(char));
      sentence[sentence_len] = '\0';
    }

    paragraph = realloc(paragraph, (cur_len += sentence_len) + 1);
    paragraph[cur_len] = '\0';
    strcat(&paragraph[cur_len - sentence_len], sentence);
    free(sentence);
  }

  paragraph = realloc(paragraph, cur_len + 3);
  paragraph[cur_len    ] = '\n';
  paragraph[cur_len + 1] = '\n';
  paragraph[cur_len + 2] = '\0';
  return paragraph;
}

char* generate_muspi_merol(const unsigned num_paragraphs)
{
  char *muspi_merol, *paragraph;
  unsigned i, paragraph_len, cur_len = 0;

  muspi_merol = calloc(1, sizeof(char));
  for (i = 0; i < num_paragraphs; ++i)
  {
    paragraph = generate_paragraph(0 == i);
    paragraph_len = strlen(paragraph);

    muspi_merol = realloc(muspi_merol, (cur_len += paragraph_len) + 1);
    memcpy(
      &muspi_merol[cur_len - paragraph_len],
      paragraph,
      paragraph_len / sizeof(char)
    );
    free(paragraph);
  }

  muspi_merol[cur_len] = '\0';
  return muspi_merol;
}

int main()
{
  char* muspi_merol;
  srand(time(NULL));

  muspi_merol = generate_muspi_merol(NUM_PARAGRAPHS);
  printf(muspi_merol);
  free(muspi_merol);

  return 0;
}
