#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <inttypes.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 300
#define BLOCK 4096

int main(int argc, char * argv[]){
   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   // open files for reading and writing
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;

   }
   char readline[BLOCK];
   char **rawr;
   rawr = (char **) calloc(line_count,sizeof(char *));
   rewind(in);
   for (uint32_t i = 0; i < line_count; i++) { //loops through c_count
        fgets(readline, BLOCK, in); //reads the next line
        readline[strlen(readline) - 1] = '\0'; //remove the new line at the end of the line
	rawr[i] = malloc((strlen(readline) +1)*sizeof(char*));
        strcpy(rawr[i],readline); //duplicate the line into cities so it doesn't get overwritten
    }
   List L = newList();
   append(L,0);
   for(uint32_t i = 1; i <line_count; i ++){
	   moveBack(L);
	   while(index(L)>=0  && strcmp(rawr[get(L)],rawr[i])>0){
		   movePrev(L);
	}
	if(index(L) != -1){ 
	  insertAfter(L,i);
	 }
	else{
		prepend(L,i);
	}

   }
  for(moveFront(L); index(L) >= 0; moveNext(L)){
	  fprintf(out,"%s\n", rawr[get(L)]);
}

 for (uint32_t i = 0; i < line_count; i++) {
        free(rawr[i]);
    }
 free(rawr);
  if (in != stdin) {
        fclose(in);
    }
    if (out != stdout) {
        fclose(out);
    }
 freeList(&L);
}	
	


