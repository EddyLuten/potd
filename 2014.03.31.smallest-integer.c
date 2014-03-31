// 2014-03-31 - http://www.problemotd.com/problem/smallest-integer/
#include <stdio.h>
#include <math.h>

int smallest_2(int a, int b)
{
  return ((a + b) - abs(a - b)) / 2;
}

int smallest(int* ints, unsigned int len)
{
  int c = ints[len - 1];
  while (len--)
    c = smallest_2(c, ints[len]);
  return c;
}

int main(void)
{
  int ints[] = { -67, 100, -2, 0, 1, 2, 3, -66, 2, 68 };

  printf("%i\n", smallest(ints, sizeof(ints) / sizeof(int)));
  return 0;
}
