/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA3
* FindComponents.c
* This is my main function that incorporates my Graph.h files.
*********************************************************************************/




#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"


int main(int argc, char* argv[]){
   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   // open files for reading and writing
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      fclose(in);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      fclose(out);
      exit(1);


   }
	//getting how many vertexes there are and then initializing my graph
	int meow;
	fscanf(in,"%d",&meow);
	Graph G = newGraph(meow);

	//read line by line setting the first int to line and the second int to line2 until end of file
	//Break if I hit 0
	int bla;
	int blaa;
	while(fscanf(in, "%d %d", &bla,&blaa)!= EOF ){ 
		if(!bla){
		       	break;
		}
		addArc(G,bla,blaa);
	}
	//some print statements
	fprintf(out,"Adjacency list representation of G:\n");
	printGraph(out,G);
	fprintf(out,"\n");

	//creating my lis
	List L = newList();
        for(int i = 1; i< meow+1; i++){
            append(L, i);
        }
	DFS(G,L);
	Graph Transpose = transpose(G);	
	DFS(Transpose,L);

	//finding the number of strongly connected components
	int counter = 0;
	for(int i = 1; i < getOrder(G)+1; i++){
            if(getParent(Transpose, i) == NIL){
                counter = counter + 1;
            }
        }
	fprintf(out, "G contains %d strongly connected components:\n", counter);
	counter = 0;

	//printing out my strongly connected components by iterating through my vertexes
	moveBack(L);
	List grr = newList();
	for(int i = 1; i < getOrder(G) + 1; i++){
            prepend(grr,get(L));
	    if(getParent(Transpose, get(L)) == NIL){
		    counter = counter + 1;
		    fprintf(out, "Component %d: ", counter);
		    printList(out, grr);
		    fprintf(out, "\n");
		    clear(grr);
	    }
	    movePrev(L);
	}

	//freeing everything
	fclose(in);
	fclose(out);
	freeList(&L);
	freeList(&grr);
	freeGraph(&G);
	freeGraph(&Transpose);
	}
	


