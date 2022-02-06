/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA4
 * Sparse.c
 * Main function written by me
 *********************************************************************************/

#include "List.h"
#include "Matrix.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   // open files for reading and writing
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      fclose(in);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      fclose(out);
      exit(1);


   }

  int n, a, b;
  if (!feof(in)) { // read n, a, and b
    fscanf(in, "%d %d %d\n\n", &n, &a, &b);
  }

  Matrix A = newMatrix(n);
  int i, j;
  double x;
  for (int k = 0; k < a; k++) { // read entries for A
    fscanf(in, "%d %d %lf\n", &i, &j, &x);
    changeEntry(A, i, j, x);
  }

  fscanf(in, "\n");

  Matrix B = newMatrix(n);
  for (int k = 0; k < b; k++) { // read entries for B
    fscanf(in, "%d %d %lf\n", &i, &j, &x);
    changeEntry(B, i, j, x);
  }

  // print statements
  fprintf(out, "A has %d non-zero entries:\n", a);
  printMatrix(out, A);
  fprintf(out, "\nB has %d non-zero entries:\n", b);
  printMatrix(out, B);

  // scalar multiplication by 1.5
  Matrix Ascalar = scalarMult(1.5, A);
  fprintf(out, "\n(1.5)*A =\n");
  printMatrix(out, Ascalar);

  // adding A and B
  Matrix AplusB = sum(A, B);
  fprintf(out, "\nA+B =\n");
  printMatrix(out, AplusB);

  // adding A by itself
  Matrix AsumA = sum(A, A);
  fprintf(out, "\nA+A =\n");
  printMatrix(out, AsumA);

  // Subtracting B by A
  Matrix BdiffA = diff(B, A);
  fprintf(out, "\nB-A =\n");
  printMatrix(out, BdiffA);

  // Subtracting A by A
  Matrix AdiffA = diff(A, A);
  fprintf(out, "\nA-A =\n");
  printMatrix(out, AdiffA);

  // Transpose
  Matrix Atrans = transpose(A);
  fprintf(out, "\nTranspose(A) =\n");
  printMatrix(out, Atrans);

  // Multiplcation of A and B
  Matrix AproB = product(A, B);
  fprintf(out, "\nA*B =\n");
  printMatrix(out, AproB);

  // Multiplication of B and B
  Matrix BproB = product(B, B);
  fprintf(out, "\nB*B =\n");
  printMatrix(out, BproB);

  // free everything
  freeMatrix(&Ascalar);
  freeMatrix(&AplusB);
  freeMatrix(&AsumA);
  freeMatrix(&BdiffA);
  freeMatrix(&AdiffA);
  freeMatrix(&Atrans);
  freeMatrix(&AproB);
  freeMatrix(&BproB);
  freeMatrix(&A);
  freeMatrix(&B);

  //close files
  fclose(in);
  fclose(out);

  return 0;
}

