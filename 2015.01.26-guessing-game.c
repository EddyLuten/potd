// 2015.01.26 - http://problemotd.com/problem/guessing-game/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_QUESTIONS 6

typedef int(*num_gen_t)(unsigned min, unsigned max);

int get_single_char() {
  int c = getchar(); getchar();
  return c;
}

int rand_between(unsigned min, unsigned max) {
  srand(time(NULL));
  return rand() % (max - min) + min;
}

int halving(unsigned min, unsigned max) {
  return (max + min) / 2;
}

int xkcd_random(unsigned min, unsigned max) {
  return 4;
}

num_gen_t pick_numgen() {
  printf(
    "Pick a number-generating algorithm:\n"\
    "1. random\n"\
    "2. halving (best)\n"\
    "3. xkcd random\n"
  );

  switch(get_single_char()) {
    case '1': return rand_between;
    case '2': return halving;
    case '3': return xkcd_random;
    default: return rand_between;
  }
}

int main(void) {
  char response;
  unsigned question = 0,
           lower    = 1,
           upper    = 100;

  num_gen_t generator = pick_numgen();
  printf("Think of a number 1-100\n");

  while (question < MAX_QUESTIONS && upper != lower) {
    unsigned ask = generator(lower, upper);

    printf("Is it greater than %u? ", ask);
    response = get_single_char();

    switch(response) {
      case 'y': lower = ask + 1; break;
      case 'n': upper = ask; break;

      default:
        printf("Please enter y or n.\n");
        continue;
    }

    ++question;
  }

  printf("Is your number %u? ", generator(lower, upper));
  response = get_single_char();

  switch(response) {
    case 'y': printf("Yay! :)\n"); break;
    case 'n': printf("Aww. :(\n"); break;
    default:
      printf("I guess you didn't know either.\n");
      break;
  }

  return 0;
}
