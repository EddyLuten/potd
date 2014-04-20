// 2014-04-20 - http://www.problemotd.com/problem/the-lone-survivor/
#include <stdlib.h>
#include <stdio.h>
#define KNIGHT_COUNT 1500

unsigned lone_survivor(unsigned* knights, const unsigned count)
{
  unsigned kill_next = 0, i = 0, murderer = 0;

  for (;; i = (i == (count - 1)) ? 0 : i + 1)
  {
    if (0 == knights[i])
      continue; // he's dead, Jim.

    if (kill_next)
    {
      if (murderer == i)
        break; // found the lone survivor!
      knights[i] = 0; // sorry, buddy.
    }
    else
      murderer = i;

    kill_next = !kill_next;
  }

  return i + 1; // index to position
}

int main(void)
{
  unsigned knights[KNIGHT_COUNT] = { [0 ... 1499] = 1 };
  unsigned last = lone_survivor(knights, KNIGHT_COUNT);

  printf("Out of %u knights, the lone survivor is %u!\n", KNIGHT_COUNT, last);

  return EXIT_SUCCESS;
}
