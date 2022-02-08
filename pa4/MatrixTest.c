/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA4
* MatrixTest.c
* This is my custom test functions that I use to debug my Matrix.c file
*********************************************************************************/


#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>

int main() {

//initialize matrix and set values
  Matrix M = newMatrix(3);
  changeEntry(M, 1, 2, 1);
  changeEntry(M, 1, 1, 3);
  changeEntry(M, 1, 3, 3);
  changeEntry(M, 2, 2, 4);
  changeEntry(M, 2, 2, 1);
  changeEntry(M, 2, 3, 6);
  changeEntry(M, 3, 1, 3);
  changeEntry(M, 3, 1, 5);
  changeEntry(M, 3, 3, 9);

  //check non zero entries
  fprintf(stdout, "%d\n", NNZ(M));
  printMatrix(stdout, M);


  //test copy
  Matrix B = copy(M);
  Matrix C = transpose(B);
  fprintf(stdout, "%d\n", NNZ(C));
  printMatrix(stdout, C);


  //test scalar multiplication
  Matrix D = scalarMult(1.5, C);
  fprintf(stdout, "%d\n", NNZ(D));
  printMatrix(stdout, D);

  //test product
  Matrix F = product(M, B);
  fprintf(stdout, "%d\n", NNZ(F));
  printMatrix(stdout, F);

  //free everything
  freeMatrix(&M);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&F);

  return 0;
}
