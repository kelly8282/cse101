/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA7
 * DictionaryTest.cpp
 * My test for Dictionary ADT in C++
 *********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
	string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

	Dictionary A = Dictionary();
	Dictionary B = Dictionary();

	//setting value
	for(int i=0; i<8; i++){
     		A.setValue(S[i], i+1);
   	}

	B = A;

	//test size
	cout << A.size() << endl << A << endl;
	cout << B.size() << endl << B << endl << endl;

	cout << "A one value: " << A.getValue("one") << endl;

	B.setValue("bar", 9);

	cout << "B bar value: " << B.getValue("bar") << endl;

	//test equals
	cout << (A==B?"true":"false") << endl;

	cout << endl;

	cout << A.pre_string() << endl;

	cout << B.to_string() << endl;

	return(EXIT_SUCCESS);
}

