// 2014-03-31 - http://www.problemotd.com/problem/sort-times/
#include <stdio.h>
#define SORT_COMPARE(t) (t < 12 ? t + 24 : t)
#define AMPM(t) (t < 12 ? "AM" : "PM")
#define PRINT_ENGLISH_TIME(t) printf("%i%s ", (t > 12 ? t - 12 : t), AMPM(t))

void gym_sort(int* times, const int length)
{
  int i = 1, temp;
  while (i < length)
  {
    if (SORT_COMPARE(times[i]) < SORT_COMPARE(times[i - 1]))
    {
      temp = times[i - 1];
      times[i - 1] = times[i];
      times[i] = temp;
      i = 0;
      continue;
    }
    ++i;
  }
}

int main(void)
{
  int i;
  int times[] = { 2, 1, 12, 3, 16, 19, 23 };
  const int length = sizeof(times) / sizeof(int);
  
  gym_sort(times, length);
  
  for (i = 0; i < length; ++i)
    PRINT_ENGLISH_TIME(times[i]);
  printf("\n");
  return 0;
}
