/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA3
* Matrix.c
* This is my matrix ADT where we do alot of calculations and manipulations of Matrix's
 *********************************************************************************/

#include "Matrix.h"
#include "List.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct EntryObj *Entry;

//create obj
typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

//create obj
typedef struct MatrixObj {
  List *entries; 
  int size;
  int NNZ;
} MatrixObj;

//allocating all my memory and returning my Entry
Entry newEntry(int col, double val) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = col;
  E->val = val;
  return E;
}

//allocating all my memory and returning my Matrix
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  M->entries = calloc(n + 1, sizeof(List));
  for (int i = 1; i < n+1; i++) { 
    M->entries[i] = newList();
  }
  M->size = n;
  M->NNZ = 0;
  return M;
}

//free all heap memory associated with *pE and sets *pE to NULL
void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    (*pE) = NULL;
  }
}

//frees all heap memory associated with *pM and sets 8pM to NULL
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i < size(*pM)+1; i++) {
      List L = (*pM)->entries[i];
      freeList(&L);
    }
    free((*pM)->entries);
    free(*pM);
    *pM = NULL;
  }
}


//return size
int size(Matrix M) {
       	return M->size;
}

// Return the number of non-zero elements in M
int NNZ(Matrix M) {
  int e = 0;
  for (int i = 1; i <= size(M); i++) {
    List L = M->entries[i];
    e = e + length(L);
  }
  return e;
}
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  bool meow = false;
  if(size(A) == size(B)){
	  meow = true;
  }
  if (meow == false) {
    return 0;
  }
  bool istrue = true;
  for (int i = 1; i < size(A)+1; i++) {
    List AList = A->entries[i];
    List BList = B->entries[i];
    bool meow;
    if(length(AList) == length(BList)){
	    meow = true;
	   }
    else{
	    meow = false;
	   }
    if (meow == false) { 
      return 0;
    }
    if (length(AList) > 0 && length(BList) > 0 &&
        meow == true) {
      moveFront(AList);
      moveFront(BList);
      while (index(AList) >0) {
        if (((Entry)get(AList))->col != ((Entry)get(BList))->col) {
          istrue = false;
          break;
        }
        if (((Entry)get(AList))->val != ((Entry)get(BList))->val) {
          istrue = false;
          break;
        }
        moveNext(AList);
        moveNext(BList);
      }
    }
  }
  if (istrue == true) {
    return 1;
  }
  else {
    return 0;
  }
}

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  for (int i = 1; i <= size(M); i++) {
    List L = M->entries[i];
    while (length(L) > 0) {
      moveFront(L);
      Entry E = (Entry)get(L);
      freeEntry(&E);
      deleteFront(L); 
    }
  }
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if( i<1 || i > size(M) || j <1 || j >size(M)){
	  return;
  }
  List L = M->entries[i];
  if (length(L) == 0) { 
    if (x != 0){
      Entry E = newEntry(j,x);
      append(L,E);
      return;
     }
    return;
  }
  moveFront(L);
  while (index(L) >= 0) {
    if (((Entry)get(L))->col == j) {
      if (x == 0) {
        Entry E = (Entry)get(L);
        freeEntry(&E);
        delete (L);
      }
      else {
        ((Entry)get(L))->val = x;
      }
      return;
    } 
    else if (j < ((Entry)get(L))->col) {
      if (x != 0){
        Entry E = newEntry(j,x);
	insertBefore(L,E);
	      return;
	}
      return;
    } 
    else{
      if (index(L) + 1 == length(L)) {
        if (x == 0){
          return;
	 }
        Entry E = newEntry(j, x);
        insertAfter(L, E);
        return;
      }
      moveNext(L);   
    }
  }
     
  exit(-1);
}
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  Matrix C = newMatrix(size(A));
  for (int a = 1; a < size(A)+1; a++) {
    List L = A->entries[a];
    moveFront(L);
    if (length(L) > 0) {
      for (int j = 0; j<length(L); j++) {
        Entry e = get(L);
        changeEntry(C, a, e->col, e->val);
	moveNext(L);
      }
    }
  }
  return C;
}
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
  Matrix B = newMatrix(size(A));
  for (int i = 1; i <size(A)+1; i++) {
    List L = A->entries[i];
    moveFront(L);
    if (length(L) > 0) {
      for (int j = 0; j<length(L); j++) {
        changeEntry(B, ((Entry)get(L))->col, i, ((Entry)get(L))->val);
	moveNext(L);
      }
    }
  }
  return B;
}

// Returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A) {
  Matrix B = newMatrix(size(A));
  for (int i = 1; i < size(A)+1; i++) {
    List L = A->entries[i];
    moveFront(L);
    if (length(L) > 0) {
      for (int j = 0; j < length(L); j++) {
        changeEntry(B, i, ((Entry)get(L))->col, ((Entry)get(L))->val * x);
	moveNext(L);
      }
    }
  }
  return B;
}


//helper function for sum()
Matrix sum_helper(Matrix A, Matrix B, bool add) {
  bool meow = false;
  if(size(A) == size(B)){
	  meow = true;
  }
  if (meow == false) {
    exit(-1);
  }
  Matrix m = newMatrix(size(B));
  for (int i = 1; i < size(A)+1; i++) {
    List LA = A->entries[i];
    List LB = B->entries[i];
    moveFront(LA);
    moveFront(LB);
    while (index(LA) >= 0 || index(LB) >= 0) {
      Entry a = NULL;
      Entry b = NULL;
      if (index(LA) >= 0){
        a = get(LA);
	}
      if (index(LB) >= 0){
        b = get(LB);
	}
      if (b == NULL || (index(LA) >= 0 && a->col < b->col)) {
        changeEntry(m, i, a->col, a->val);
        moveNext(LA);
        continue;
      }
      if (a == NULL || (index(LB) >= 0 && a->col > b->col)) {
        if(add== true){
        changeEntry(m, i, b->col, b->val);
        }
	else{
        changeEntry(m, i, b->col, -b->val);
        }
        moveNext(LB);
        continue;
      }
      if (a == NULL || b == NULL)
        continue;
      if (add==true) {
        changeEntry(m, i, a->col, a->val + b->val); // sum
      } 
      else {
        changeEntry(m, i, a->col, a->val - b->val); // diff
      }
      moveNext(LA);
      if (A != B) {
        moveNext(LB);
      }
    }
  }
  return m;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) { 
	return sum_helper(A, B, true);
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
        return sum_helper(A,B, false);
}

// helper function for product()
double vectorDot(List P, List Q) {
  double dot = 0;
  if (length(P) >0) {
    moveFront(P);
  }
  if (length(Q) > 0) {
    moveFront(Q);
  }
  while (index(P) >=0 && index(Q) >=0) {
    if (((Entry)get(P))->col == ((Entry)get(Q))->col) {
	double temp = (((Entry)get(P))->val*((Entry)get(Q))->val);
      dot = dot +temp;
      moveNext(P);
      moveNext(Q);
    } 
    else if(((Entry)get(P))->col > ((Entry)get(Q))->col) {
      moveNext(Q);
    }
    else {
      moveNext(P);
    }
  }
  return dot;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  bool meow = false;
  if(size(A) == size(B)){
		  meow = true;
  }
  if (meow == false) {
    exit(-1);
  }
  Matrix C = newMatrix(size(A));
  Matrix TB = transpose(B);
  for (int i = 1; i < size(A)+1; i++) { 
    List LA = A->entries[i];
    if (length(LA) > 0) {
      for (int j = 1; j < size(TB)+1; j++) { 
        List LTB = TB->entries[j];
        if (length(LTB) > 0) {
          double dot = vectorDot(LA, LTB);
          changeEntry(C, i, j, dot);
        }
      }
    }
  }
  freeMatrix(&TB);
  return C;
}


// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point
void printMatrix(FILE *out, Matrix M) {
  for (int i = 1; i <= size(M); i++) {
    List L = M->entries[i];
    if (length(L) > 0) {
      fprintf(out, "%d: ", i);
      moveFront(L);
      for (int j = 1; j <= length(L); j++) {
        fprintf(out, "(%d, %.1f) ", ((Entry)get(L))->col, ((Entry)get(L))->val);
        moveNext(L);
      }
      fprintf(out, "\n");
    }
  }
}
