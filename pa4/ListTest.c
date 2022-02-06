/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA4
* ListTest.c
* This is my custom test functions that I use to debug my List.c file
*********************************************************************************/


#include "Matrix.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  //initialize
  List A = newList();
  List B = newList();
  List C = newList();
  int X[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
             11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int i, u = -1, v = -2, w = -3;
  bool equal = false;

  //create List
  for (i = 1; i <= 20; i++) {
    append(A, &X[i]);
    prepend(B, &X[i]);
  }

  //print lists going forward
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
    printf("%d ", *(int *)get(B));
  }
  printf("\n");

  //print lists going backwards
  for (moveBack(A); index(A) >= 0; movePrev(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");
  for (moveBack(B); index(B) >= 0; movePrev(B)) {
    printf("%d ", *(int *)get(B));
  }
  printf("\n");

  //copy A
  moveFront(A);
  while (index(A) >= 0) {
    append(C, get(A));
    moveNext(A);
  }
  //print copy going forward
  for (moveFront(C); index(C) >= 0; moveNext(C)) {
    printf("%d ", *(int *)get(C));
  }
  printf("\n");

  // check equal
  if(length(A) == length(C)){
	  equal = true;
	}
  else{
	  equal = false;
	 }

  moveFront(A);
  moveFront(C);
  while (index(A) >= 0 && equal) {
    equal = (get(A) == get(C));
    moveNext(A);
    moveNext(C);
  }
  printf("A equals C is %s\n", (equal ? "true" : "false"));


  //test insertion deletions and sets
  moveFront(A);
  for (i = 0; i < 5; i++){
    moveNext(A); 
   }
  printf("index(A)=%d\n", index(A));
  insertBefore(A, &u); 
  printf("index(A)=%d\n", index(A));
  for (i = 0; i < 9; i++){
    moveNext(A); 
 }
  printf("index(A)=%d\n", index(A));
  insertAfter(A, &v); 
  printf("index(A)=%d\n", index(A));
  for (i = 0; i < 5; i++){
    movePrev(A); 
   }
  printf("index(A)=%d\n", index(A));
  delete (A); 
  printf("index(A)=%d\n", index(A));
  moveBack(A); 
  printf("index(A)=%d\n", index(A));
  for (i = 0; i < 10; i++){
    movePrev(A); 
   }
  printf("index(A)=%d\n", index(A));
  set(A, &w);

  // print A
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");
  for (moveBack(A); index(A) >= 0; movePrev(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");

  //length checks
  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));


  //free everything
  freeList(&A);
  freeList(&B);
  freeList(&C);

  return 0;
}
