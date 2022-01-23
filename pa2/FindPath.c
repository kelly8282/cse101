/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA1
* FindPath.c
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
   	
	int meow;
	fscanf(in,"%d",&meow);
	Graph G = newGraph(meow);
	int bla;
	int blaa;

	//read line by line setting the first int to line and the second int to line2 until end of file
	//Break if I hit 0
	while(fscanf(in, "%d %d", &bla,&blaa)!= EOF ){ 
		if(!bla){
		       	break;
		}
		addEdge(G,bla,blaa);
	}

	//print Graph
	printGraph(out,G);
	fprintf(out,"\n");

//read line by line setting the first int to line and the second int to line2 until end of file
        //Break if I hit 0
	
	while(fscanf(in,"%d %d", &bla,&blaa)!=EOF){
		if(!bla){
		       	break;
		}

		//run BFS from source of the second int read in the particular line
		BFS(G,bla);
		if(getDist(G,blaa) <0){ //If the distance doesn't exist print these statements
			 fprintf(out, "The distance from %d to %d is %s\n", bla, blaa, "infinity");
                         fprintf(out, "No %d-%d path exists\n\n", bla, blaa);

		}
		else{ //else print these statements
                        fprintf(out, "The distance from %d to %d is %d\n", bla, blaa, getDist(G, blaa));
                        fprintf(out, "A shortest %d-%d path is: ", bla, blaa);
                        List L = newList();
                        getPath(L, G, blaa);
                        printList(out, L);
                        freeList(&L);
                        fprintf(out, "\n\n");
		}
	}

	//close everything
	freeGraph(&G);
	fclose(in);
	fclose(out);
}
	


