
// 2014-04-20 - http://www.problemotd.com/problem/stacks-queues/
#include <stdlib.h>
#include <stdio.h>

typedef struct _stackqueue
{
  unsigned* elements;
  unsigned count;
  unsigned capacity;
} StackQueue;

void sq_resize(StackQueue* stackqueue, unsigned capacity)
{
  stackqueue->capacity = capacity;
  stackqueue->elements = realloc(stackqueue->elements,
                                 sizeof(unsigned) * capacity);
}

void sq_grow(StackQueue* stackqueue)
{
  if (stackqueue->count + 1 > stackqueue->capacity)
    sq_resize(stackqueue, stackqueue->capacity * 2);
}

StackQueue* sq_create(unsigned capacity)
{
  StackQueue* result = malloc(sizeof(StackQueue));
  result->elements = NULL;
  result->count = 0;
  sq_resize(result, !capacity ? 5 : capacity);
  return result;
}

void sq_destroy(StackQueue* stackqueue)
{
  free(stackqueue->elements);
  free(stackqueue);
}

void sq_push(StackQueue* stackqueue, unsigned num)
{
  unsigned i, next;
  sq_grow(stackqueue);
  for (i = stackqueue->count; i != 0; --i)
    stackqueue->elements[i] = stackqueue->elements[i - 1];
  stackqueue->elements[0] = num;
  ++stackqueue->count;
}

unsigned sq_pop(StackQueue* stackqueue)
{
  unsigned i, result = 0;
  if (stackqueue->count > 0)
  {
    result = stackqueue->elements[0];
    --stackqueue->count;
    for (i = 0; i < stackqueue->count; ++i)
      stackqueue->elements[i] = stackqueue->elements[i + 1];
  }
  return result;
}

#define sq_dequeue sq_pop

void sq_enqueue(StackQueue* stackqueue, unsigned num)
{
  sq_grow(stackqueue);
  stackqueue->elements[stackqueue->count++] = num;
}

void sq_print(StackQueue* stackqueue)
{
  unsigned i;
  printf("[ ");
  for (i = 0; i < stackqueue->count; ++i)
    printf("%u%s",
           stackqueue->elements[i],
           i == stackqueue->count - 1 ? "" : ", ");
  printf(" ]\n");
}

int main(void)
{
  StackQueue* sq = sq_create(10);
  printf("Create: "); sq_print(sq);
  printf("Push: "); sq_push(sq, 5); sq_print(sq);
  printf("Enqueue: "); sq_enqueue(sq, 6); sq_print(sq);
  printf("Push: "); sq_push(sq, 7); sq_print(sq);
  printf("Popped: %u ", sq_pop(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);

  // Extra
  printf("Push: "); sq_push(sq, 1); sq_print(sq);
  printf("Push: "); sq_push(sq, 2); sq_print(sq);
  printf("Push: "); sq_push(sq, 3); sq_print(sq);
  printf("Push: "); sq_push(sq, 4); sq_print(sq);
  printf("Push: "); sq_push(sq, 5); sq_print(sq);
  printf("Push: "); sq_push(sq, 6); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);
  printf("Dequeued: %u ", sq_dequeue(sq)); sq_print(sq);

  sq_destroy(sq);

  return EXIT_SUCCESS;
}
