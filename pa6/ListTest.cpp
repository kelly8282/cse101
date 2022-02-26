/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA6
* ListTest.cpp
* This is my custom test functions that I use to debug my List.c file
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
	List A;

	//test insertAfter and insertBefore
	for(long i=0; i< 5; i++){
		A.insertAfter(i);
	}
	A.insertBefore(4);
	A.insertAfter(2);
	cout << endl;
   	cout << "A = " << A << endl;

	//test cursor position manipulation functions
	A.moveFront();
	cout << "A.position() = " << A.position() << endl;
	long meow = A.moveNext();
	cout << meow << endl;
	cout << "A.position() = " << A.position() << endl;
	A.moveBack();
	cout << "A.position() = " << A.position() << endl;
	long woof = A.movePrev();
	cout << woof << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << endl;

	//test access functions
	cout << "A.length() = " << A.length() << endl;
	cout << "A.front() = " << A.front() << endl;
	cout << "A.back() = " << A.back() << endl;
	
	//test peek functions
	cout << "Peek Next = " << A.peekNext() << endl;
	cout << "Peek Prev = " << A.peekPrev() << endl;
	
	//test set functions
	A.setAfter(12);
	A.setBefore(15);
	cout<< "A = " << A << endl;
	cout << endl;
	
	//test findNext and findPrev functions
	A.moveFront();
	cout << "findNext() = " << A.findNext(4) <<endl;
	A.moveBack();
	cout << "findPrev() = " << A.findPrev(4) << endl;
	A.cleanup();
	cout << "A = " << A << endl;
	cout << endl;

	//check concat functions
	List B;
	B.insertBefore(3);
	B.insertBefore(3);
	List C = B.concat(A);
	cout << "C (B concat A) = " << C << endl;
	cout << endl;

	//test equal function
	if(A == B){
		printf("Error, equals doesn't work\n");
	}
	else{
		printf("Equals works as expected\n");
	}

	//test clear
	A.clear();
	B.clear();
	C.clear();
}

