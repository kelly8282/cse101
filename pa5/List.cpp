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

	Node dog = L.frontDummy;
	while(dog.next != nullptr){
		insertAfter(dog);
		moveNext();
		dog = dog->next;
	}
	pos_cursor = 0;
	moveFront();
}

List::~List(){
	     clear();
}

int List::length() const{
	return num_elements;
{

ListElement List::front() const{
	if(num_elements > 0){
		return frontDummy->next->data;
	}
}

ListElement List::back() const{
	if(num_elements > 0){
		return backDummy->prev->data;
	}
}

int List::position() const{
	if( pos_cursor >= 0 && pos_cursor <= num_elements){
		return pos_cursor;
	}
}

ListElement List::peekNext() const{
	if(pos_cursor < num_elements){
		return afterCursor->data;
	}
}

ListElement List::peekPrev() const{
	if(pos_cursor > 0){
		return beforeCursor->data;
	}
}

void List::clear(){
	Node temp = frontDummy;
	while(temp.next != nullptr){
		Node rawr = temp;
		temp = temp->next;
		delete(rawr);
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

void List::moveNext(){
	if(pos_cursor < num_elements){
		Node temp = afterCursor;
		afterCursor = afterCursor->next;
		beforeCursor = temp;
		delete(temp);
	}
}

void List::movePrev(){
	if(pos_cursor > 0){
		Node temp = beforeCursor;
		beforeCursor = beforeCursor->pre;
		afterCursor = temp;
		delete(temp);
	}
}

void List::insertAfter(ListElement x) const{
	Node rawr = new Node(x);
	rawr->next = afterCursor;
	rawr->prev = beforeCursor;
	beforeCursor->next = rawr;
	afterCursor->prev = rawr;
	afterCursor = rawr;
	num_elements = num_elements +1;
}

void List::insertBefore(ListElement x) const{
	Node rawr = new Node(x);
	rawr->next = afterCursor;
	rawr->prev = beforeCursor;
	beforeCursor->next = rawr;
	afterCursor->prev = rawr;
	beforeCursor = rawr;
	num_elements = num_elements + 1;
	pos_cursor = pos_cursor + 1;
}

void List::setAfter(ListElement x) const{
	if(pos_cursor < num_elements){
		afterCursor->data = x;
	}
}


void List::setBefore(ListElement x) const{
	if(pos_cursor > 0){
		beforeCursor->data = x;
	}
}

void List::eraseAfter(){
	if(pos_cursor < num_elements){
		afterCursor->prev->next = afterCursor->next;
		afterCursor->next->prev = afterCursor->prev;
		delete(afterCursor);
		afterCursor = beforeCursor->next;
		num_elements = num_elements - 1;
	}
}

void List::eraseBefore(){
	if(pos_cursor> 0){
		beforeCursor->next->prev = beforeCursor->prev;
		beforeCursor->prev->next = beforeCursor->next;
		delete(afterCursor);
		beforeCursor = afterCursor->prev;
		num_elements = num_elements -1;
		pos_cursor = pos_cursor-1;
	}
}


int List::findNext(ListElement x) const{
	while(pos_cursor < num_elements){
		int meow = moveNext();
		if(meow == x)
			return position();
		}
	}
	return -1;
}

int List::findPrev(ListElement x) const{
	while(pos_cursor > 0){
		int meow = movePrev();
		if(meow == x){
			return position();
		}
	}
	return -1;
}

List List::concat(const List& L) const{
	List bla = L;
	moveFront();
	while(pos_cursor < num_elements){
		int meow = moveNext();
		bla.insertBefore(meow);
	}
	bla.moveFront();
	return bla;
}

std::ostream& operator<< ( std::ostream& stream,  const List& L ) {
	return stream << L.List::to_string();
}


bool List::equals(const List& R) const{
	if(R.num_elements != num_elements){
		return false;
	}
	List temp1 =this;
	List temp2 =R;
	temp1.moveFront();
	temp2.moveFront();
	bool result = true;
	while(temp1.position() < num_elements){
		int rawr = temp1.moveNext();
		int dog = temp2.moveNext();
		if(rawr != dog){
			pot = false;
		}
	}
	clear(temp1);
	clear(temp2);
	return result;
}






