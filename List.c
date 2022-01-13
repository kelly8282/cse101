#include <stdbool.h>
#include <stdio.h>

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
	return n;
}

void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

List newList(void){
	List L;
	L= malloc(sizeof(ListObj));
	L->front = NULL;
	L->back=NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = 0;
	return L;
}

void freeList(List* pL){
	Node* temp = pL->front;
	while( temp != NULL){
		Node *new = temp->next;
		free(temp);
		temp = new;
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
		return L->front;
	}
	else{
		return -1;
	}
}

int back(List L){
	if(L->length > 0){
		return L->back;
	}
	else{
		return -1;
	}
}

int get(List L){
	if(L->length > 0 && L->index >= 0){
		return L->cursor;
	}
	else{
		return -1;
	}
}

bool equals(List A, List B){
	bool final = true;
	if(A->length == B->length){
		Node* a = A->front;
                Node* b = B->front;
		for(int i = 0; i < A->length; i ++){
			if(a->data != b->data){
				final = false;
			}
			a = a->next;
			b = b->next;
		}
	}
	return final;
}


			

