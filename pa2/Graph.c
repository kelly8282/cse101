/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA2
* Graph.c
* This is my graph ADT where we use BFS to find the shortest path possible.
*********************************************************************************/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "List.h"
#include "Graph.h"


//creates my GraphObj
typedef struct GraphObj{	
	int *color;
	int *parent;
	int *distance;
	List *neighbors;
	int order;
	int size;
	int start;
}GraphObj;


//allocating all my memory and return my Graph
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


//frees all heap memory associated with *pG and sets *pG to  NULL
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
//return Order
int getOrder(Graph G){
	return G->order;
}


//return size
int getSize(Graph G){
	return G->size;
}


//return my source function if it exists, else return NIL
int getSource(Graph G){
	if(G->start >= 0){
		return G->start;
	}
	else{
		return NIL;
	}
}

//return my parent vertex to my u if it exists, else return NIL
int getParent(Graph G, int u){
	if(G->start >= 0 && (u>=1 && u<= getOrder(G))){	
		return G->parent[u];
	}
	else{
		return NIL;
	}
}

//returns my distance from my soruce to my u if exists, else return INF
int getDist(Graph G, int u){
	if(G->start >= 0 && (u >= 1 && u <= getOrder(G))){
		return G->distance[u];
	}
	else{
		return INF;
	}
}


//appends to the List L the vertices of a shortest path in G from source to u, or appends to L the
//value NIL if no such path exists
void getPath(List L, Graph G, int u){
	int empty = 0;
	if(length(L) != 0){
		empty = 1;
	}
	if(getDist(G,u) >= 0 && getSource(G) != NIL){
		List bla = newList();
		while(u!= getSource(G)){
			prepend(bla,u);
			moveFront(bla);
			prepend(L,get(bla));
			movePrev(bla);
			u = getParent(G,u);
		}
		if(getSource(G) == u && empty != 0){
			append(bla,getSource(G));
			moveBack(bla);
			append(L,get(bla));
		}
		else{
			prepend(bla,getSource(G));
                	moveFront(bla);
                	prepend(L,get(bla));
		}
		freeList(&bla);
	}
	else{
		List non = newList();
		append(non,NIL);
		moveFront(non);
		append(L,get(non));
		freeList(&non);
	}
}


//deletes all edges of G, restoring it to its
//original (no edge) state
void makeNull(Graph G){
	for(uint32_t i = 1; i < G->order+1; i++){
		clear(G->neighbors[i]);
	}
	G->size = 0;
	G->start = -1;
}

//inserts a new
//edge joining u to v, i.e. u is added to the adjacency List of v, 
//and v to the adjacency List of u.
void addEdge(Graph G, int u , int v){
	if ( u>=1 && u <= getOrder(G)&& v>=1 && v<=getOrder(G) ){
		addArc(G,u,v);
		addArc(G,v,u);
		G->size = G->size -1;
	}
}


//inserts a new directed
//edge from u to v, i.e. v is added to the adjacency List of u 
//(but not u to the adjacency List of v)
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


//runs the BFS algorithm on the Graph G with source s, setting the color,
//distance, parent, and source fields of G accordingly
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
				G->distance[bla] = G->distance[x] + 1;
				G->parent[bla] = x;
				append(temp,bla);
			}
			moveNext(G->neighbors[x]);
		}
		G->color[x]= 2;
	}
	freeList(&temp);
}


//prints the adjacency
//list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
    for(uint32_t i = 1; i < G->order+1; i++){
        fprintf(out, "%u: ", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}




	

