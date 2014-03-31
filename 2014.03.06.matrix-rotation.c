// 2014-03-07 - http://www.problemotd.com/problem/matrix-rotation/
#include <stdlib.h>
#include <stdio.h>

// Matrix from example, plus the size of one matrix dimension
#define MATRIX_SIZE 5
const static int INPUT_MATRIX[MATRIX_SIZE * MATRIX_SIZE] = {
  1 , 2 , 3 , 4 , 5 ,
  6 , 7 , 8 , 9 , 10,
  11, 12, 13, 14, 15,
  16, 17, 18, 19, 20,
  21, 22, 23, 24, 25
};

void rotate_square_matrix(const int* input, const int n, int* result)
{
  int row = 0, i = 0;
  for (; row < n; ++row, i = 0)
    for (; i < n; ++i)
      result[ (row * n) + i ] = input[ (n - i - 1) * n + row ];
}
  
int main()
{
  int i = 0, j = 0;
  int result[MATRIX_SIZE * MATRIX_SIZE] = { 0 };
  rotate_square_matrix(INPUT_MATRIX, MATRIX_SIZE, result);
  
  for (; i < MATRIX_SIZE; ++i, j = 0)
  {
    for (; j < MATRIX_SIZE; ++j)
      printf("%i ", result[i * MATRIX_SIZE + j]);
    printf("\n");
  }
   
  return 0;
}
