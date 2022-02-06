/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA1
 * List.c
 * This is my List ADT where we have a cursor used for iteration.
 *********************************************************************************/

#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeObj {
  void *data;
  struct NodeObj *pre;
  struct NodeObj *next;
} NodeObj;

typedef NodeObj *Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

Node newNode(int *node_data) {
  Node N = malloc(sizeof(NodeObj));
  N->data = node_data;
  N->pre = NULL;
  N->next = NULL;
  return N;
}

void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Creates and returns a new empty List.

List newList(void) {
  List L = malloc(sizeof(ListObj));
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return L;
}
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.

void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    Node temp = (*pL)->front;
    while (temp != NULL) {
      Node new = temp->next;
      freeNode(&temp);
      temp = new;
    }
    free(*pL);
    *pL = NULL;
  }
}
// Returns the number of elements in L.

int length(List L) { return L->length; }
// Returns index of cursor element if defined, -1 otherwise.

int index(List L) {
  if (L->index >= 0) {
    return L->index;
  } 
  else {
    return -1;
  }
}
// Returns front element of L. Pre: length()>0

void *front(List L) {
  if (L->length > 0) {
    return L->front->data;
  }
  fprintf(stderr, "tried to call back() but empty list\n");
  exit(EXIT_FAILURE);
}
// Returns back element of L. Pre: length()>0

void *back(List L) {
  if (L->length > 0) {
    return L->back->data;
  }
  fprintf(stderr, "tried to call back() but empty list\n");
  exit(EXIT_FAILURE);
}
// Returns cursor element of L. Pre: length()>0, index()>=0
void *get(List L) {
  if (L->length > 0 && L->index >= 0) {
    return L->cursor->data;
  }
  fprintf(stderr, "tried to call back() but empty list\n");
  exit(EXIT_FAILURE);
}

// Resets L to its original empty state.

void clear(List L) {
  while (L->front != NULL) {
    Node temp = L->front->next;
    freeNode(&L->front);
    L->front = temp;
  }
  L->length = 0;
  L->index = -1;
  L->cursor = NULL;
}
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void *x) {
  if (L->length > 0 && L->index >= 0) {
    L->cursor->data = x;
  }
}
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
  if (L->length > 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.

void moveBack(List L) {
  if (L->length > 0) {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
  if (L->cursor != NULL && L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (L->cursor != NULL) {
    L->cursor = L->cursor->pre;
    L->index = L->index - 1;
  }
}
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
  if (L->index >= 0) {
    if (L->cursor != NULL && L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
    }
    if (L->cursor != NULL) {
      L->cursor = L->cursor->next;
      L->index = L->index + 1;
    }
  }
}
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.

void prepend(List L, void *x) {
  Node temp = newNode(x);
  if (L->front != NULL) {
    temp->next = L->front;
    L->front->pre = temp;
    L->front = temp;
    L->length = L->length + 1;
    L->index = L->index + 1;
  } 
  else {
    L->front = temp;
    L->back = temp;
    L->length = L->length + 1;
    L->index = 0;
  }
}
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void *x) {
  Node temp = newNode(x);
  if (L->length > 0) {
    Node rawr = L->front;
    while (rawr->next != NULL) {
      rawr = rawr->next;
    }
    rawr->next = temp;
    L->back = temp;
    temp->pre = rawr;
    L->length = L->length + 1;
  } 
  else {
    L->front = temp;
    L->back = temp;
    L->length = L->length + 1;
    L->index = 0;
  }
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0

void insertBefore(List L, void *x) {
  if (L->length > 0 && L->index >= 0) {
    Node temp = newNode(x);
    if (index(L) == 0) {
      temp->pre = NULL;
      L->front = temp;
    } 
    else {
      temp->pre = L->cursor->pre;
    }
    L->cursor->pre = temp;
    temp->next = L->cursor;
    if (temp->pre != NULL) {
      temp->pre->next = temp;
    }
    L->index = L->index + 1;
    L->length = L->length + 1;
  }
}
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void *x) {
  if (L->length > 0 && L->index >= 0) {
    Node temp = newNode(x);
    temp->next = L->cursor->next;
    temp->pre = L->cursor;
    L->cursor->next = temp;
    if (temp->next != NULL) {
      temp->next->pre = temp;
    } 
    else {
      L->back = temp;
    }
    L->length = L->length + 1;
  }
}
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if (L->length > 0) {
    if (L->length != 1) {
      Node temp = L->front->next;
      L->front = temp;
      freeNode(&L->front->pre);
      L->length = L->length - 1;
      L->index = L->index - 1;
    } 
    else {
      freeNode(&L->front);
      L->front = NULL;
      L->back = NULL;
      L->cursor = NULL;
      L->length = L->length - 1;
      L->index = -1;
    }
  }
}
// Delete the back element. Pre: length()>0

void deleteBack(List L) {
  if (L->length > 0) {
    if (L->length != 1) {
      Node temp = L->back->pre;
      L->back = temp;
      freeNode(&L->back->next);
      L->length = L->length - 1;
      if (L->index == L->length) {
        L->cursor = NULL;
        L->index = -1;
      }
    } 
    else {
      freeNode(&L->back);
      L->front = NULL;
      L->back = NULL;
      L->cursor = NULL;
      L->length = L->length - 1;
      L->index = -1;
    }
  }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0

void delete (List L) {
  if (L->length > 0 && L->index >= 0) {
    if (L->cursor == L->front) {
      deleteFront(L);
    } 
    else if (L->cursor == L->back) {
      deleteBack(L);
    }
    else {
      if (L->cursor->pre != NULL) {
        L->cursor->pre->next = L->cursor->next;
      }
      if (L->cursor->next != NULL) {
        L->cursor->next->pre = L->cursor->pre;
      }
      freeNode(&L->cursor);
      L->cursor = NULL;
      L->index = -1;
      L->length = L->length - 1;
    }
  }
}
