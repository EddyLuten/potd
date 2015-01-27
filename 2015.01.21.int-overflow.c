#include <stdio.h>

int main(void)
{
  int num = 1;

  while (num > 0) // overflow wraps around
  {
    printf("%i\n", num);
    num += num;
  }

  printf("Overflown: %i\n", num);
  return 0;
}
