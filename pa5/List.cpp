#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "List.h"

List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

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


List::~List(){
	Node *temp = frontDummy;
	while(temp != backDummy){
		Node *neww = temp->next;
		delete(temp);
		temp = neww;
	}
	delete(backDummy);
}

int List::length() const{
	return num_elements;
}

ListElement List::front() const{
	if(num_elements <= 0){
		throw std::length_error("List: front(): empty list");
	}	
	return frontDummy->next->data;
	
}

ListElement List::back() const{
	if(num_elements <= 0){
		throw std::length_error("List: back(): empty list");
	}	
	return backDummy->prev->data;
	
}

int List::position() const{
	//if( pos_cursor >= 0 && pos_cursor <= num_elements){
	return pos_cursor;
}

ListElement List::peekNext() const{
	if(pos_cursor >= num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

ListElement List::peekPrev() const{
	if(pos_cursor < 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}	
	return beforeCursor->data;
	
}

void List::clear(){
	moveBack();
	while(beforeCursor != frontDummy){
		eraseBefore();
	}
}

void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

void List::moveBack(){
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;
}

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

void List::insertAfter(ListElement x){
	Node *rawr = new Node(x);
	rawr->next = afterCursor;
	rawr->prev = beforeCursor;
	beforeCursor->next = rawr;
	afterCursor->prev = rawr;
	afterCursor = rawr;
	num_elements = num_elements +1;
}

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

void List::setAfter(ListElement x){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
	
}


void List::setBefore(ListElement x){
	if(pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}	
	beforeCursor->data = x;
}

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


int List::findNext(ListElement x){
	while(pos_cursor < num_elements){
		int meow = moveNext();
		if(meow == x){
			return position();
		}
	}
	return -1;
}

int List::findPrev(ListElement x){
	while(pos_cursor > 0){
		int meow = movePrev();
		if(meow == x){
			return position();
		}
	}
	return -1;
}


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
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}




