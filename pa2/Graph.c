/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA1
* Graph.c
* This is my graph ADT where we use BFS to find the shortest path possible.
*********************************************************************************/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{	
	int *color;
	int *parent;
	int *distance;
	List *neighbors;
	int order;
	int size;
	int start;
}GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->color = (int *)calloc(n+1,sizeof(int));
	G->parent = (int *)calloc(n+1,sizeof(int));
	G->distance = (int *)calloc(n+1,sizeof(int));
	G->neighbors = (List *) calloc(n+1,sizeof(List));
	G->order = n;
	G->size = 0;
	G->start = -1;
	for(uint32_t i = 1; i < n+1; i++){
		G->neighbors[i]= newList();
	}
	return G;

}

void freeGraph(Graph *pG){
	if(pG!= NULL && *pG != NULL){
		for(uint32_t i = 1; i <= (*pG)->order; i++){
            		freeList(&(*pG)->neighbors[i]);
        	}
        	free((*pG)->color);
        	free((*pG)->parent);
        	free((*pG)->distance);
        	free((*pG)->neighbors);
		free(*pG);
		*pG = NULL;
	}	
}

int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}

int getSource(Graph G){
	if(G->start >0){
		return G->start;
	}
	else{
		return NIL;
	}
}


int getParent(Graph G, int u){
	if( u >= 1 && u <= getOrder(G)){		
		return G->parent[u];
	}
	else{
		return NIL;
	}
}

int getDist(Graph G, int u){
	if(u>= 1 && u <= getOrder(G)){
		return G->distance[u];
	}
	else{
		return INF;
	}
}

void getPath(List L, Graph G, int u){
	if(getDist(G,u) >= 0 && getSource(G) != NIL){
		List bla = newList();
		moveFront(bla);
		append(bla,getSource(G));
		append(L,get(bla));
		moveNext(bla);
		while(u!= getSource(G)){
			append(bla,u);
			append(L,get(bla));
			moveNext(bla);
			u = getParent(G,u);
		}
		freeList(&bla);
	}
	else{
		List non = newList();
		append(non,NIL);
		append(L,get(non));
		freeList(&non);
	}
}

void makeNull(Graph G){
	for(uint32_t i = 0; i < G->order+1; i++){
		clear(G->neighbors[i]);
	}
	G->size = 0;
	G->start = -1;
}


void addEdge(Graph G, int u , int v){
	if ( u>=1 && u <= getOrder(G)&& v>=1 && v<=getOrder(G) ){
		addArc(G,u,v);
		addArc(G,v,u);
		G->size = G->size -1;
	}
}

void addArc(Graph G, int u , int v){
	if ( u >=1 && u<= getOrder(G)&& v>=1 && v<= getOrder(G)){
			 moveBack(G->neighbors[u]);
	   		while(index(G->neighbors[u])>=0  && get(G->neighbors[u])>v){
		   		movePrev(G->neighbors[u]);
			}
			if(index(G->neighbors[u]) != -1){
	  			insertAfter(G->neighbors[u],v);
	 		}
			else{
				prepend(G->neighbors[u],v);
			}
		G->size = G->size +1;
	}
}

void BFS(Graph G, int s){
	for(uint32_t i = 0; i < G->order+1; i ++){
		if(i != s){
			G->color[i] = 0;
			G->distance[i]= INF;
			G->parent[i]= NIL;
		}
	}
	G->color[s] = 1;
	G->distance[s]= 0;
	G->parent[s] = NIL;

	List temp = newList();
	append(temp,s);
	moveFront(temp);
	G->start = s;

	while( length(temp) > 0){
		uint32_t x = front(temp);
		deleteFront(temp);
		moveFront(G->neighbors[x]);
		for( int i = 0; i < length(G->neighbors[x]) ; i++){
			uint32_t bla = get(G->neighbors[x]);
			if(G->color[bla] == 0){
				G->color[bla] = 1;
				G->distance[bla] = G->distance[bla] + 1;
				G->parent[bla] = x;
				append(temp,bla);
			}
			moveNext(G->neighbors[x]);
		}
		G->color[x]= 2;
	}
	freeList(&temp);
}
void printGraph(FILE* out, Graph G){
    for(uint32_t i = 1; i < G->order+1; i++){
        fprintf(out, "%u: ", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}




	

