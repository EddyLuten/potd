// 2014-03-06 - http://www.problemotd.com/problem/vigenere-cipher/
#include <stdio.h>
#include <string.h>
static const char MESSAGE[] = "TODAYISMYBIRTHDAY";
static const char CIPHER[]  = "REDDIT";

int main()
{
  int i, j;
  const size_t msglen  = strlen(MESSAGE),
               ciphlen = strlen(CIPHER);
  char* result = (char*)calloc(msglen + 1, sizeof(char));

  for (i = 0, j = 0; i < msglen; ++i, j = (i % ciphlen))
    result[i] = ((MESSAGE[i] - 'A' + CIPHER[j] - 'A') % 26) + 'A';

  printf("%s", result);
  return 0;
}
