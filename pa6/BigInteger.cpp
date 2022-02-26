/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA6
 * BigInteger.cpp
 * My BigInteger ADT in C++
 *********************************************************************************/

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "BigInteger.h"
#include "List.h"


int power = 9;
long base = 1000000000;

   // Constructor that creates a new BigInteger in the zero state:
   // signum=0, digits=().
BigInteger::BigInteger(){
        signum = 0;
        digits = List();
}

   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
        int length = s.length();
        if(length == 0){
                throw std::invalid_argument("BigInteger: Constructor: empty string");
        }
        std::string sign = s.substr(0,1);
        if(sign == "-"){
                signum = -1;
                s.erase(0,1);
        }
        else if(sign == "+"){
                signum = 1;
                s.erase(0,1);
        }
        else{
                if(s.find_first_not_of("0") != std::string::npos){
                        signum = 1;
                }
        }
        std::string meow = s;
        int purr = meow.length() % power;
        if(purr != 0){
                std::string woof = meow.substr(0,purr);
                long arf = std::stol(woof, NULL, 10);
                digits.insertBefore(arf);
                meow.erase(0,purr);
        }
        int counter = 0;
        std::string cat = "";
        while(meow.length() > 0){
                if (counter == power) {
                    digits.insertBefore(std::stoi(cat));
                    cat = "";
                    counter = 0;
                }
                cat.insert(0, 1, meow[0]);
                counter++;
                meow.erase(0, 1);
        }
}


// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	this->digits = List(N.digits);
	this->signum = N.signum;
}


   // Returns -1, 1 or 0 according to whether this BigInteger is positive,
   // negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}


   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	BigInteger meow = *this;
	BigInteger gr = N;
	meow.digits.moveFront();
	gr.digits.moveFront();
	if( meow.sign() >=0 && gr.sign() == -1){
		return 1;
	}
	if(meow.sign() == -1 && gr.sign() >=0){
		return -1;
	}
	if(meow.sign() == 0 && gr.sign() == 0){
		return 0;
	}
	else{
		if( meow.digits.length() > gr.digits.length() && meow.sign() == 1){
				return 1;
		}
		if(meow.digits.length() < gr.digits.length() && meow.sign() == 1){
				return -1;
		}
		if(meow.digits.length() > gr.digits.length() && meow.sign() == -1){	
				return -1;
		}
		if(meow.digits.length() < gr.digits.length() && meow.sign() == -1){
				return 1;
		}
		else{
			for(int i = 0; i < meow.digits.length(); i++){
				long meow_num = meow.digits.moveNext();
				long gr_num = gr.digits.moveNext();
				if(meow_num > gr_num && meow.sign() == 1){
					return 1;
				}
				if(meow_num > gr_num && meow.sign() ==-1){
					return -1;
				}
				if(meow_num < gr_num && meow.sign() == 1){
					return -1;
				}
				if(meow_num < gr_num && meow.sign() == -1){
					return 1;
				}
			}
		}
	}
	return 0;
}
    // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0;
}
   
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
void BigInteger::negate(){
	if(signum !=0){
		signum = signum*-1;
	}
}

   // Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger meow = *this;
	BigInteger gr = N;
	meow.digits.moveFront();
	gr.digits.moveFront();
	BigInteger result = BigInteger();
	result.digits.moveFront();
	int differ = 0;
	int cat = 0;
	int dog = 0;
	if(meow.sign() == 0 && gr.sign() == 0){
		result.signum = 0;
		result.digits.insertAfter(0);
		return result;
	}
	meow.negate();
	if(meow.sign() == gr.sign()){
		if(meow.compare(gr) ==  0){
			meow.negate();
			result.signum = 0;
			result.digits.insertAfter(0);
			return result;
		}
	}
	meow.negate();
	
	if(meow.digits.length() > gr.digits.length()){
		differ = meow.digits.length() - gr.digits.length();
		for(int i = 0; i < differ; i++){
			gr.digits.insertAfter(0);
		}
	}
	if(meow.digits.length() < gr.digits.length()){
		differ = gr.digits.length() - meow.digits.length();
		for(int i = 0; i < differ; i++){
			meow.digits.insertAfter(0);
		}
	}
	
	meow.digits.moveBack();	
	gr.digits.moveBack();
	for(int i = 0; i < meow.digits.length(); i++){
        	long s = 0;
		long a = meow.digits.movePrev();
		long b = gr.digits.movePrev();
        if(meow.sign() == 1 && gr.sign() == 1){
        	s = s +(a + b);
        }
       	if(meow.sign() == 1 && gr.sign() == -1){
        	s = s + (a - b);
	} 
	if(meow.sign() == -1 && gr.sign() == 1){
        	s = s + (b -a);
	}
       	if(meow.sign() == -1 && gr.sign() == -1){
       		s = s + (a + b);
       	}
        if( dog != -1){
        	s = s + dog;
        }

        if(s >= base){ 
   		cat = s / base;
        	s = s- (cat * base);
        } 
	else if(s <= (-1 * base)){
        	cat = s / (-1 * base);
        	s = s + (cat * (-1 * base));
        }
       	else if(s < 0 && s > (-1 * base)){ 
        	cat = -1;
        }
       	else if(s + dog== 0  || s > 0){
        	cat = 0;
        }
        else{
        	cat = -1;
        }
        if(dog == -1){
        	s = s + dog;
        }

        if(s < 0){
		if(i != meow.digits.length()){
            		result.digits.insertAfter(-s);
	    	}
	    	else{ 
			result.digits.insertAfter(s +base);
	    	}	
            	result.signum = -1;
            
        } 
        else{
            	result.digits.insertAfter(s);
	    	if(meow.sign() == -1 && gr.sign()== -1){
			    result.signum = -1;
	    	}
	    	else{
            		result.signum = 1;
	    	}
        }
        dog = cat;

    }
    return result;
}



   // Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
        BigInteger meow = *this;
        BigInteger gr = N;
        gr.negate();
        return gr.add(meow);
}

   // Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger result = BigInteger();
    BigInteger meow = BigInteger();
    BigInteger gr = *this;
    BigInteger rawr = N;
    gr.digits.moveFront();
    rawr.digits.moveFront();
    long cat = 0;
    long dog = 0;
    if(gr.sign() == 0 || rawr.sign() == 0){
        result.digits.insertAfter(0);
        result.signum = 0;
        return result;
    }
    gr.digits.moveBack();
    rawr.digits.moveBack();
    
    for(int i = 0; i < gr.digits.length(); i++){
        long l = gr.digits.movePrev();
        for(int j = 0; j < rawr.digits.length(); j++){
            long p = 0;
            long r = rawr.digits.movePrev();
            if(gr.sign() == 1 && rawr.sign() == 1){
                p = (l * r);
                result.signum = 1;
                meow.signum = 1;
            } else if(gr.sign() == 1 && rawr.sign() == -1){
                p = (l * r);
                result.signum = -1;
                meow.signum = -1;
            } else if(gr.sign() == -1 && rawr.sign() == 1){
                p = (l * r);
                result.signum = -1;
                meow.signum = -1;
            } else if(gr.sign() == -1 && rawr.sign() == -1){
                p = (l * r);
                result.signum = 1;
                meow.signum = 1;
            }
            p = p + cat;
            if(p >= base){
                    dog = p / base;
                    p = p -  (dog * base);
            } else if(p <= (-1 * base)){
                    dog = p / (-1 * base);
                    p = p + (dog * (base));
            }
            meow.digits.insertAfter(p);
            cat = dog;
        }
        if(dog > 0 && i != gr.digits.length() -1){
            meow.digits.insertAfter(dog);
            dog = 0;
            cat = dog;
        }
        meow.digits.moveBack();
        for(int k = 0; k < i; k++){
            meow.digits.insertAfter(0);
        }
        result = result.add(meow);
        rawr.digits.moveBack();
        meow.digits.clear();
    }
        return result;
}

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.

std::string BigInteger::to_string(){
	std::string str = "";
	BigInteger gr = *this;
        List meow = digits;
        if(gr.sign() == 0){
            return "0";
        }
        meow.moveFront();
	int bla = 0;
        for(int i = 0; i < meow.length(); i++){
            long cat = meow.moveNext();
	    uint len = std::to_string(cat).length();
            if(bla == 0){
		bla = 1;
                str = str + std::to_string(cat);
            } 
	    else if(len != power){
                for(uint i = 0; i < power - len; i++){
                    str = str+ "0";
                }
                str = str + std::to_string(cat);
            } 
	    else if(len == power){
                str = str + std::to_string(cat);
            }
        }
        if(gr.sign() == -1){
            str.insert(0, "-");
        }
        return str;
}


   // operator<<()
   // Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
        return stream << N.BigInteger::to_string();
}

    // operator==()
    // Returns true if and only if A equals B.
bool operator==( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) == 0;
}

    // operator<()
    // Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) == -1;
}

    // operator<=()
    // Returns true if and only if A is less than or equal to B.
bool operator<=( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) <= 0;
}

    // operator>()
    // Returns true if and only if A is greater than B.
bool operator>( const BigInteger& A, const BigInteger& B ){
        return A.compare(B) == 1;
}

    // operator>=()
    // Returns true if and only if A is greater than or equal to B.
bool operator>=( const BigInteger& A, const BigInteger& B ){
       return (A.compare(B) >= 0);
}

    // operator+()
    // Returns the sum A+B.
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
        return A.add(B);
}

    // operator+=()
    // Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
        A = A.add(B);
        return A;
}

    // operator-()
    // Returns the difference A-B.
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
        return A.sub(B);
}

    // operator-=()
    // Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
        return A;
}

    // operator*()
    // Returns the product A*B.
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
        return A.mult(B);
}

      // operator*=()
      // Overwrites A with the product A*B.
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
        A = A.mult(B);
        return A;
}

