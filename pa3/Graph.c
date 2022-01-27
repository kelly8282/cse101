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

typedef struct GraphObj{	
	int *color;
	int *parent;
	int *discover;
	int *finish;
	List *neighbors;
	int order;
	int size;
	int time;
}GraphObj;

//allocating all my memory and return my Graph
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->color = (int *)calloc(n+1,sizeof(int));
	G->parent = (int *)calloc(n+1,sizeof(int));
	G->discover = (int *)calloc(n+1,sizeof(int));
	G->finish =  (int *)calloc(n+1, sizeof(int));
	G->neighbors = (List *) calloc(n+1,sizeof(List));
	G->order = n;
	G->size = 0;
	G->time = 0;
	for(uint32_t i = 1; i < n+1; i++){
		G->neighbors[i]= newList();
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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
        	free((*pG)->discover);
		free((*pG)->finish);
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

//return my parent vertex to my u if it exists, else return NIL
int getParent(Graph G, int u){
	if (u>=1 && u<= getOrder(G)){	
		return G->parent[u];
	}
	else{
		return NIL;
	}
}

int getDiscover(Graph G, int u){
        if (u>=1 && u<= getOrder(G)){
                return G->discover[u];
        }
        else{
                return NIL;
        }
}

int getFinish(Graph G, int u){
        if (u>=1 && u<= getOrder(G)){
                return G->finish[u];
        }
        else{
                return NIL;
        }
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

void Visit(Graph G, int x, List s){
        G->discover[x] = ++(G->time);
        G->color[x] = 1;
        moveFront(G->neighbors[x]);
        for (int i = 0; i< length(G->neighbors[x]); i++){
                int bla = get(G->neighbors[x]);
                if(G->color[bla] == 0){
                        G->parent[bla] = x;
                        Visit(G,bla,s);
                }
                moveNext(G->neighbors[x]);
        }
        G->color[x] = 2;
        prepend(s,x);
        G->finish[x] = ++(G->time);
}

void DFS(Graph G, List s){
	if(length(s) == G->order){
		List old = copyList(s);
		moveFront(old);
		clear(s);
		for ( int i = 1; i < G->order + 1; i++){
			G->color[get(old)] = 0;
			G->parent[get(old)] = NIL;
			moveNext(old);
		}
		G->time = 0;
		moveFront(old);
		for (int i = 1; i < G->order + 1; i++){
			if(G->color[get(old)] == 0){
				Visit(G,get(old),s);
			}
			moveNext(old);
		}
		freeList(&old);
	}
}


Graph transpose(Graph G){
	Graph rawr = newGraph(G->order);
	for(int i = 1; i <G->order + 1; i++){
		moveFront(G->neighbors[i]);
		for(int j = 0; j < length(G->neighbors[i]); j++){
			int bla = get(G->neighbors[i]);
			addArc(rawr,bla,i);
			moveNext(G->neighbors[i]);
		}
	}
	return rawr;
}

Graph copyGraph(Graph G){
	Graph rawr = newGraph(G->order);
	for(int i = 1; i <G->order + 1; i++){
        	rawr->neighbors[i] = copyList(G->neighbors[i]); 
		rawr->discover[i] = (G->discover[i]);
		rawr->color[i] = (G->color[i]);
		rawr->parent[i] = (G->parent[i]);
	}
	rawr->order = G->order;
	rawr->size = G->size;
	rawr->time = G->time;
        return rawr;
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

