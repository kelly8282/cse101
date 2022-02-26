/********************************************************************************
* Kelly Liu, kliu80
* 2022 Winter CSE101 PA5
* BigIntegerTest.cpp
* This is my custom test functions that I use to debug my BigInteger.cpp file
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
	string a = "100001";
	string b = "3";

	BigInteger meow = BigInteger(a);
	BigInteger gr = BigInteger(b);

	BigInteger p = meow + gr;
	BigInteger o = meow - gr;
	BigInteger i = gr - meow;
	BigInteger u = meow * meow;
	
	cout << p << endl;
	cout << o << endl;
	cout << i << endl;
	cout << u << endl;

	p.negate();
	cout << p << endl;
	p.makeZero();
	cout << p << endl;

	cout << i.compare(p) << end1;
	
	string c = "0";
	cout << p.compare(c) << endl;
}
