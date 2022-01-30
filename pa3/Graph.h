/*********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA3
* Graph.h
* A header file that specifies the interface for graog.c
*********************************************************************************/


#pragma once
#include <stdbool.h>
#include "List.h" //include List.h so we can access List functions

#define NIL 0  //create macro for infinity
#define UNDEF -2 //create macro for undefined vertex label

typedef struct GraphObj* Graph; //create GraphObj
// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);
// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
// Other Functions
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

