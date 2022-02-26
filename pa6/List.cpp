/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA6
 * List.cpp
 * My list ADT in C++
 *********************************************************************************/

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "List.h"

//Node constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

//constructor
List::List(){
	frontDummy = new Node(0);
	backDummy = new Node(7);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

//copy constructor
List::List(const List& L){
	frontDummy = new Node(0);
	backDummy = new Node(7);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	Node *dog = L.frontDummy->next;
	while(length() < L.length()){
		insertBefore(dog->data);
		dog = dog->next;
	}
	
	//watpos_cursor = 0;
	//moveFront();
}

//deconstructor
List::~List(){
	Node *temp = frontDummy;
	while(temp != backDummy){
		Node *neww = temp->next;
		delete(temp);
		temp = neww;
	}
	delete(backDummy);
}


//returning num_elements
int List::length() const{
	return num_elements;
}

//return first element
ListElement List::front() const{
	if(num_elements <= 0){
		throw std::length_error("List: front(): empty list");
	}	
	return frontDummy->next->data;
	
}

//return back element
ListElement List::back() const{
	if(num_elements <= 0){
		throw std::length_error("List: back(): empty list");
	}	
	return backDummy->prev->data;
	
}

//return position of cursor
int List::position() const{
	//if( pos_cursor >= 0 && pos_cursor <= num_elements){
	return pos_cursor;
}

//return what the next element is
ListElement List::peekNext() const{
	if(pos_cursor >= num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}


//return what the previous element is
ListElement List::peekPrev() const{
	if(pos_cursor < 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}	
	return beforeCursor->data;
	
}

//clear list
void List::clear(){
	moveBack();
	while(beforeCursor != frontDummy){
		eraseBefore();
	}
}

//move cursor to front
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

//move cursor to back
void List::moveBack(){
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;
}


//move cursor next one and return element skipping over
ListElement List::moveNext(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	Node *temp = afterCursor;
	afterCursor = afterCursor->next;
	beforeCursor = temp;
	pos_cursor = pos_cursor + 1;
	//delete(temp)
	return beforeCursor->data;
}


//move cursor one previous and return element skipping voer
ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
	Node *temp = beforeCursor;
	beforeCursor = beforeCursor->prev;
	afterCursor = temp;
	pos_cursor = pos_cursor -1;
	//delete(temp);
	return afterCursor->data;
}


//insert after cursor
void List::insertAfter(ListElement x){
	Node *rawr = new Node(x);
	rawr->next = afterCursor;
	rawr->prev = beforeCursor;
	beforeCursor->next = rawr;
	afterCursor->prev = rawr;
	afterCursor = rawr;
	num_elements = num_elements +1;
}

//insert before cursor
void List::insertBefore(ListElement x){
	Node *rawr = new Node(x);
	rawr->next = afterCursor;
	rawr->prev = beforeCursor;
	beforeCursor->next = rawr;
	afterCursor->prev = rawr;
	beforeCursor = rawr;
	num_elements = num_elements + 1;
	pos_cursor = pos_cursor + 1;
}

//overwrite element after cursor
void List::setAfter(ListElement x){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
	
}

//overwrite element before cursor
void List::setBefore(ListElement x){
	if(pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}	
	beforeCursor->data = x;
}

//erase element after cursor
void List::eraseAfter(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	afterCursor->prev->next = afterCursor->next;
	afterCursor->next->prev = afterCursor->prev;
	delete(afterCursor);
	afterCursor = beforeCursor->next;
	num_elements = num_elements - 1;

}

//erase element before cursor
void List::eraseBefore(){
	if(pos_cursor <= 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
	beforeCursor->next->prev = beforeCursor->prev;
	beforeCursor->prev->next = beforeCursor->next;
	delete(beforeCursor);
	beforeCursor = afterCursor->prev;
	num_elements = num_elements -1;
	pos_cursor = pos_cursor-1;
}


//find next element of x if it exists
int List::findNext(ListElement x){
	while(pos_cursor < num_elements){
		int meow = moveNext();
		if(meow == x){
			return position();
		}
	}
	return -1;
}

//find previous element of x if it exists
int List::findPrev(ListElement x){
	while(pos_cursor > 0){
		int meow = movePrev();
		if(meow == x){
			return position();
		}
	}
	return -1;
}

//join two lists together
List List::concat(const List &L) const{
	List bla = L;
	List dog = *this;
	bla.moveFront();
	dog.moveFront();
	while(dog.position() < num_elements){
		int meow = dog.moveNext();
		bla.insertBefore(meow);
	}
	bla.moveFront();
	dog.clear();
	return bla;
}


   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    List bla = *this;
    std::string s = "(";
    bla.moveFront();
    bool last = false;
    while(bla.position() < num_elements-1){
	int meow = bla.moveNext();
        s += std::to_string(meow) + ", ";
	last = true;
    }
    if(last == true){
    	int meow = bla.moveNext();
    	s += std::to_string(meow);
	}
    bla.clear();
    s += ")";
    return s;
}

//check if two lists are equal
bool List::equals(const List &R) const{
	if(R.num_elements != num_elements){
		return false;
	}
	List temp1 =*this;
	List temp2 =R;
	temp1.moveFront();
	temp2.moveFront();
	bool result = true;
	while(temp1.position() <  num_elements ){
		int rawr = temp1.moveNext();
		int dog = temp2.moveNext();
		if(rawr != dog){
			result = false;
		}
	}
	temp1.clear();
	temp2.clear();
	return result;
}


   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost
   // occurrance of each element, and removing all other occurances. The cursor
   // is not moved with respect to the retained elements, i.e. it lies between
   // the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node *p1, *p2, *dup;
    p1 = frontDummy->next;
    int i = 0, k = 0;
    while(p1 != backDummy && p1->next != backDummy){
        p2 = p1;
        k = i;
        while(p2->next != backDummy){
            if(p1->data == p2->next->data){
                if(p2->next == afterCursor){
                    dup = p2->next;
                    p2->next->next->prev = p2;
                    p2->next = p2->next->next;
                    afterCursor = p2->next;
                    num_elements--;
                    delete dup; 
                } else if(p2->next == beforeCursor){
                    dup = p2->next;
                    p2->next->next->prev = p2;
                    p2->next = p2->next->next;
                    beforeCursor = beforeCursor->prev;
                    num_elements--;
                    delete dup;
                } else {
                    dup = p2->next;
                    p2->next->next->prev = p2;
                    p2->next = p2->next->next;
                    num_elements--;
                    delete dup;
                }
                if(k+1 < pos_cursor){
                    pos_cursor--;
                }
            }
            else{
                p2 = p2->next;
                k++;
            }
        }
        p1 = p1->next;
        i++;
    }
}

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in boOAth Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if(this != &L){
        List a = L;
        std::swap(afterCursor, a.afterCursor);
        std::swap(beforeCursor, a.beforeCursor);
        std::swap(frontDummy, a.frontDummy);
        std::swap(backDummy, a.backDummy);
        std::swap(pos_cursor, a.pos_cursor);
        std::swap(num_elements, a.num_elements);
    }
    return *this;
}




