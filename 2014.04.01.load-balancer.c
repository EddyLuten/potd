// 2014-04-01 - http://www.problemotd.com/problem/load-balancer/
#include <stdlib.h>
#include <stdio.h>

unsigned SERVERS[] = {
  357, 651, 101, 230
};
#define SERVER_COUNT (sizeof(SERVERS) / sizeof(unsigned))

void remove_random(void)
{
  --SERVERS[rand() % (SERVER_COUNT - 1)];
}

void balance_request(void)
{
  int min = 0, i = 0;
  for (; i < SERVER_COUNT; ++i)
    min = SERVERS[i] < min ? i : min;
  --SERVERS[min];
}

unsigned servers_left(void)
{
  unsigned c = 0, i = 0;
  for (; i < SERVER_COUNT; c += SERVERS[i], ++i);
  return c;
}

int main(void)
{
  unsigned requests = 0;
  
  srand(time());
  
  while (0 != servers_left())
  {
    if (0 == ++requests % 10)
      remove_random();
    balance_request();
  }
  
  printf("Happy April Fools!\n");
  printf("%i requests handled\n", requests);
  return 0;
}
