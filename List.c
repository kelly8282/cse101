#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj{
	int data;
	struct NodeObj* pre;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
}ListObj;


Node newNode(int node_data){
	Node N = malloc(sizeof(NodeObj));
	N->data=node_data;
	N->pre = NULL;
	N->next = NULL;
	return N;
}

void freeNode(Node *pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

List newList(void){
	List L= malloc(sizeof(ListObj));
	L->front = NULL;
	L->back=NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}

void freeList(List *pL){
	if(pL!=NULL && *pL!=NULL){
	Node temp = (*pL)->front;
	while( temp != NULL){
		Node new = temp->next;
		freeNode(&temp);
		temp = new;
	}
	free(*pL);
	*pL = NULL;
	}
}

int length(List L){
	return L->length;
}

int index(List L){
	if(L->index >= 0 ){
		return L->index;
	}
	else{
		return -1;
	}
}

int front(List L){
	if(L->length > 0){
		return L->front->data;
	}
	else{
		return -1;
	}
}

int back(List L){
	if(L->length > 0){
		return L->back->data;
	}
	else{
		return -1;
	}
}

int get(List L){
	if(L->length > 0 && L->index >= 0){
		return L->cursor->data;
	}
	else{
		return -1;
	}
}

bool equals(List A, List B){
	bool final = true;
	if(A->length == B->length){
		Node a = A->front;
                Node b = B->front;
		for(int i = 0; i < A->length; i ++){
			if(a->data != b->data){
				final = false;
			}
			a = a->next;
			b = b->next;
		}
	}
	else{
		final = false;
	}
	return final;
}

void clear(List L){
	while(L->front != NULL){
		Node temp = L->front->next;
		freeNode(&L->front);
		L->front = temp;
	}
	L->length = 0;
	L->index = -1;
	L->cursor = NULL;
}

void set(List L, int x){
	if(L->length > 0 && L->index >= 0){
		L->cursor->data = x;
	}
}

void moveFront(List L){
	if(L->length >0){
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L->length > 0 ){
		L->cursor = L->back;
		L->index = L->length-1;
	}
}

void movePrev(List L){
	if(L->cursor != NULL && L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	if(L->cursor != NULL){
		L->cursor = L->cursor->pre;
		L->index= L->index -1;
	}	
}

void moveNext(List L){
	if(L->index >= 0){
        	if(L->cursor != NULL && L->cursor == L->back ){
                	L->cursor = NULL;
			L->index = -1;
		}
		if(L->cursor != NULL){
			L->cursor = L->cursor->next;
			L->index = L->index +1;
		}
	}
}

void prepend(List L, int x){
	Node temp = newNode(x);
	if( L->front != NULL){	
		temp->next = L->front;
		L->front->pre = temp;
		L->front = temp;
		L->length = L->length + 1;
		L->index = L->index + 1;
	}
	else{
		L->front = temp;
		L->back = temp;
		L->length = L->length + 1;
		L->index = 0;
	}
}

void append(List L, int x){
	Node temp = newNode(x);
	if(L->length > 0){
		Node rawr = L->front;
		while(rawr->next != NULL){
			rawr = rawr->next;
		}
		rawr->next = temp;
		L->back = temp;
		temp->pre = rawr;
		L->length = L->length + 1;
	}
	else{
		L->front = temp;
		L->back = temp;
		L->length = L->length + 1;
		L->index = 0;
	}
}


void insertBefore(List L, int x){
	if(L->length >0 && L->index >= 0){
		Node temp = newNode(x);
		if(index(L) == 0){
			temp->pre = NULL;
			L->front = temp;
		}
		else{
			temp->pre = L->cursor->pre;
		}
		L->cursor->pre = temp;
		temp->next = L->cursor;
		if(temp->pre != NULL){
			temp->pre->next = temp;
		}
		L->index = L->index + 1;
		L->length = L->length + 1;
	}
}

void insertAfter(List L, int x){
	if(L->length > 0 && L->index >=0){
		Node temp = newNode(x);
		temp->next = L->cursor->next;
		temp->pre = L->cursor;
		L->cursor->next = temp;
		if(temp->next != NULL){
			temp->next->pre = temp;
		}
		else{
			L->back = temp;
		}	
		L->length = L->length + 1;

	}
}

void deleteFront(List L){
	if(L->length > 0 ){
                Node temp= L->front->next;
                freeNode(&L->front);
		L->front = temp;
                L->length = L->length -1;
		if(L->index != 0){
			L->index = L->index -1;
		}
		else{
			L->index = -1;
		}
	}
}

void deleteBack(List L){
	if(L->length > 0){
		Node temp = L->back->pre;
		freeNode(&L->back);
		L->back = temp;
		L->length = L->length -1;
		if(L->index == L->length){
			L->cursor = NULL;
                        L->index = -1;
		}
	}

}

void delete(List L){
	if(L->length >0 && L->index >= 0){
		if(L->cursor == L->front){
			L->front = L->cursor->next;
		}
		if(L->cursor == L->back){
			L->back = L->cursor->pre;
		}
		else{
			if(L->cursor->pre != NULL){
				L->cursor->pre->next = L->cursor->next;
			}
			if(L->cursor->next != NULL){
				L->cursor->next->pre = L->cursor->pre;
			}
			L->cursor = NULL;
		}
		L->index = -1;
		L->length = L->length -1;
	}
}


void printList(FILE *out, List L){
	Node temp = L->front;
	while(temp != NULL){
		fprintf(out,"%d ",temp->data);
		temp = temp->next;
	}
}

List copyList(List L){
	List new = newList();
	Node temp = L->front;
	while(temp != NULL){
		append(new,temp->data);
		temp= temp->next;
	}
	return new;
}



