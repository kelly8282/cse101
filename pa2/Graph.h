/*********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA2
* Graph.h
* A header file that specifies the interface for graog.c
*********************************************************************************/


#pragma once
#include <stdbool.h>
#include "List.h" //include List.h so we can access List functions

#define INF -1  //create macro for infinity
#define NIL -2 //create macro for undefined vertex label

typedef struct GraphObj* Graph; //create GraphObj
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

