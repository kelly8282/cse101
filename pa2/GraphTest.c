/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA2
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
	   addEdge(G,i,i+2);
   }
   addEdge(G, 1, 4); //test addEdge
  
	int u = 2;
	int v = 6;
	addArc(G,u,v); //test addArc
	printGraph(stdout,G);
	BFS(G,u); //Run BFS from source 2

	//print out everything to test if my functions are working
   printf("Order %d\n", getOrder(G));
   printf("Size %d\n", getSize(G));
	printf("Source %d\n", getSource(G));
	printf("Parent %d\n", getParent(G,u));
	printf("Distance %d\n", getDist(G,u));
	
	//test for getPath
	List meow = newList();
	getPath(meow,G,u);
	printList(stdout,meow);
	fprintf(stdout,"\n");
	

	//test to see if my makeNull works
	makeNull(G);
	printGraph(stdout,G);
}

