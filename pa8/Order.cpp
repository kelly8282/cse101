/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA8
 * Order.cpp
 * My main function for Dictionary ADT in C++
 *********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;

   //checking arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(-1);
   }

   in.open(argv[1]);
   if( in.is_open() == false ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(-1);
   }

   out.open(argv[2]);
   if( out.is_open() == false ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(-1);
   }
   Dictionary cat = Dictionary();
   std::string meow = "";
   int i = 1;
   while(getline(in,meow)){
       if(meow != ""){
	       cat.setValue(meow, i);
       } else if(meow == ""){
	       break;
       }
       i = i +1;
   }
   out << cat << endl;

   out << cat.pre_string() << endl;

   // close files 
   in.close();
   out.close();

   return(1);
}


