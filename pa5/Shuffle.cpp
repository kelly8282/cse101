/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA5
 * Shuffle.cpp
 * Main function written by me
 *********************************************************************************/
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "List.h"
using namespace std;

void shuffle(List& D){
        int n = D.length();
        if(n <= 1){
                return;
        }
        List r = List();
        List l = List();
        List result = List();
        D.moveFront();
        if(n %2 == 0){
                for(int i = 0; i < n/2; i++){
                        l.insertBefore(D.moveNext());
                }
                for(int i = 0; i < n/2;i++){
                        r.insertBefore(D.moveNext());
                }
                r.moveFront();
                l.moveFront();
                while(r.position() < r.length()){
                        result.insertBefore(r.moveNext());
                        result.insertBefore(l.moveNext());
                }
                D = result;
                result.clear();
        }
        else{
                for(int i = 0; i< n/2; i++){
                        l.insertBefore(D.moveNext());
                }
                for(int i = 0; i <= n/2; i++){
                        r.insertBefore(D.moveNext());
                }
                r.moveFront();
                l.moveFront();
                while(l.position() < l.length()){
                        result.insertBefore(r.moveNext());
                        result.insertBefore(l.moveNext());
                }
                result.insertBefore(r.moveNext());
                D = result;
                result.clear();
        }
}
int main(int argc, char * argv[]){

    // check command line for correct number of arguments
    if( argc != 2 ){
      cerr << "Incorrect Input" << endl;
      return(-1);
    }

    // oheck card range
    if( atoi(argv[1]) <= 0){
      cerr << "Card range out of bounds" << endl;
      return(-1);
    }

	cout << "deck size       shuffle count\n------------------------------" << endl;
	//check deck size
	int end = atoi(argv[1]);
	
	for(int i = 1; i < end+1; i++){
	       fprintf(stdout, " %d\t\t", i);
       		int count2= 1;
		List meow = List();
		//creating our list
		while(count2< i+1){
			meow.insertBefore(count2);
			count2 = count2 + 1;
		}
		//create another list to tell how many shuffles it takes for it to return to original state
		List comp = List(meow);
		int shuf = 1;
		shuffle(comp);
		while(comp.equals(meow) == false){
			shuffle(comp);
			shuf = shuf +1;	
		}
		fprintf(stdout, "%d\n", shuf);
	}
}

