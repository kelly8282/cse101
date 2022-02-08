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
  fprintf(stdout, "NNZ: %d\n", NNZ(M));
  printMatrix(stdout, M);
  fprintf(stdout,"\n");
  
  //test copy
  Matrix B = copy(M);
  Matrix C = transpose(B);
  printMatrix(stdout, C);
fprintf(stdout,"\n");

   //test sum and diff
  Matrix summ = sum(M,C);
  Matrix difff = diff(M,C);
  printMatrix(stdout,summ);
fprintf(stdout,"\n");

  printMatrix(stdout,difff);
fprintf(stdout,"\n");

  //test scalar multiplication
  Matrix D = scalarMult(1.5, C);
  printMatrix(stdout, D);
fprintf(stdout,"\n");

  //test product
  Matrix F = product(M, B);
  printMatrix(stdout, F);
fprintf(stdout,"\n");

  //free everything
  freeMatrix(&M);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&F);
  freeMatrix(&summ);
  freeMatrix(&difff);

  return 0;
}
