/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA3
* GraphTest.c
* This is my custom test functions that I use to debug my Graph.c file.
*********************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){
	int n = 7;	
	Graph G = newGraph(n); //create Graph
   for(int i=1; i<n; i++){ //add edges from 1 to 7
	   addArc(G,i,i+2);
   }
   addEdge(G, 1, 4); //test addEdge
  
	int u = 2;
	int v = 6;
	addArc(G,u,v); //test addArc
	printGraph(stdout,G);
	fprintf(stdout,"\n");
	List L = newList();
	for(int i = 1; i< n; i++){
            append(L, i);
        }

	DFS(G,L); //Run BFS from source 2
	Graph Transpose = transpose(G);
	DFS(Transpose,L);
	printGraph(stdout,Transpose);
        fprintf(stdout,"\n");	
	//print out everything to test if my functions are working
   printf("Order %d\n", getOrder(G));
   printf("Size %d\n", getSize(G));
	printf("Discover %d\n", getDiscover(G,u));
	printf("Parent %d\n", getParent(G,u));
	printf("Finish %d\n", getFinish(G,u));
	
	//test copyGraph
	Graph new = copyGraph(G);
	printGraph(stdout,new);
	fprintf(stdout,"\n");

	//freeing everything
	freeGraph(&G);
	freeGraph(&new);	
}


