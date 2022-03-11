/*********************************************************************************
 * Kelly Liu, kliu80
 * 2022 Winter CSE101 PA8
 * Dictionary.cpp
 * My Dictionary ADT in C++
 *********************************************************************************/

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "Dictionary.h"

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0;
}

Dictionary::Dictionary(){
    nil = new Node("", -4);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D){
    nil = new Node("", -4);
    num_pairs = 0;
    root = nil;
    current = nil;
    preOrderCopy(D.root,D.nil);
}

Dictionary::~Dictionary(){
	postOrderDelete(root);
	delete(nil);
}

   // Helper Functions (Optional) ---------------------------------------------
void Dictionary::inOrderString(std::string& s, Node *R) const{
	if( R != nil && R != NULL){
		inOrderString(s,R->left);
		s.append(R->key);
		s.append(" : ");
		s.append(std::to_string(R->val));
		s.append("\n");
		inOrderString(s,R->right);
	}
}

void Dictionary::preOrderString(std::string &s, Node *R) const{
	if( R != nil && R!= NULL){
		s.append(R->key + "\n");
		preOrderString(s,R->left);
		preOrderString(s,R->right);
	}
}

void Dictionary::preOrderCopy(Node *R, Node *N){
	if( R != N){
		if(R != nil && R!= NULL){
			setValue(R->key, R->val);
        		preOrderCopy(R->left, N);
        		preOrderCopy(R->right, N);
		}
	}
}

void Dictionary::postOrderDelete(Node *R){
	if(R == nil || R == NULL){
		return;
	}
	else if(R == root){
		root = nil;
		current = nil;
	}
	postOrderDelete(R->left);
	postOrderDelete(R->right);
	delete(R);
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const{
    if(R == nil || R->key == k){
        return R;
    } else if(k < R->key){
        return search(R->left, k);
    } else{
      return search(R->right, k);  
    }
}

Dictionary::Node *Dictionary::findMin(Node *R){
	if(size() != 0){
		Node *cat = R;
		while(cat->left != nil){
			cat = cat->left;
		}
		return cat;
	}
	return nil;
}

Dictionary::Node *Dictionary::findMax(Node *R){
	if(size() != 0){
		Node *cat = R;
		while(cat->right != nil){
			cat = cat->right;
		}
		return cat;
	}
	return nil;
}

Dictionary::Node *Dictionary::findNext(Node *N){
	Node *cat = N;
	if(cat->right != nil){
		return findMin(cat->right);
	}
	Node *dog = N->parent;
	while(dog != nil && cat == dog->right){
		cat = dog;
		dog = dog->parent;
	}
	return dog;
}

Dictionary::Node *Dictionary::findPrev(Node *N){
	Node *cat = N;
	if(cat->left != nil){
		return findMax(cat->left);
	}
	Node *dog = N->parent;
	while(dog != nil && cat == dog->left){
		cat = dog;
		dog = dog->parent;
	}
	return dog;
}

void Dictionary::LeftRotate(Node *N)
{
    Node *y = N->right;

    N->right = y->left;
    if (y->left != nil){
        y->left->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil){
        root = y;
    }
    else if (N == N->parent->left){
        N->parent->left = y;
    }
    else{
        N->parent->right = y;
    }

    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node *N)
{
    Node *y = N->left;

    N->left = y->right;
    if (y->right != nil){
        y->right->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil){
        root = y;
    }
    else if (N == N->parent->right){
        N->parent->right = y;
    }
    else{
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node *N)
{
    while (N->parent->color == 1)
    {
        if (N->parent == N->parent->parent->left)
        {
            Node *y = N->parent->parent->right;
            if (y->color == 1){
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            }
            else{
                if (N == N->parent->right)
                {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        }
        else{
            Node *y = N->parent->parent->left;
            if (y->color == 1){
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            }
            else{
                if (N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node *u, Node *v)
{
    if (u->parent == nil){
        root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node *N)
{
    while (N != root and N->color == 0)
    {
        if (N == N->parent->left){
            Node *w = N->parent->right;
            if (w->color == 1){
                w->color = 0;        
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 and w->right->color == 0){
                w->color = 1;
                N = N->parent;
            }
            else{
                if (w->right->color == 0)
                {
                    w->left->color = 0;
                    w->color = 1;     
                    RightRotate(w);      
                    w = N->parent->right;
                }
                w->color = N->parent->color; 
                N->parent->color = 0;        
                w->right->color = 0;        
                LeftRotate(N->parent);       
                N = root;                   
            }
        }
        else{
            Node *w = N->parent->left;
            if (w->color == 1){
                w->color = 0;          
                N->parent->color = 1;   
                RightRotate(N->parent); 
                w = N->parent->left;    
            }
            if (w->right->color == 0 and w->left->color == 0){
                w->color = 1; 
                N = N->parent; 
            }
            else{
                if (w->left->color == 0){
                    w->right->color = 0;
                    w->color = 1;        
                    LeftRotate(w);      
                    w = N->parent->left; 
                }
                w->color = N->parent->color; 
                N->parent->color = 0;        
                w->left->color = 0;          
                RightRotate(N->parent);      
                N = root;                    
            }
        }
    }
    N->color = 0;
}

// RB_Delete()
void Dictionary::RB_Delete(Node *N)
{
    Node *y = N;
    Node *x;
    int y_original_color = y->color;
    if (N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil){
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else{
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N){
            x->parent = y;
        }
        else{
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == 0){
        RB_DeleteFixUp(x);
    }
}
   // Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}


   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
bool Dictionary::contains(keyType k) const{
	if( search(root,k) != nil){
		return true;
	}
	else{
		return false;
	}
}


   // Returns a reference to the value corresponding to key k.
valType &Dictionary::getValue(keyType k) const{
	Node *meow = search(root,k);
	if(meow != nil){
		return meow->val;
	}
	else{
		throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
	}
	return nil->val;
}

   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
bool Dictionary::hasCurrent() const{
	if (current != nil){
		return true;
	}
	else{
		return false;
	}
}

   // Returns the current key.
keyType Dictionary::currentKey() const{
    if( hasCurrent() == true){
        return current->key;
    }
    else if( hasCurrent() == false){
	    throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return nil->key;
}

   // Returns a reference to the current value.
valType &Dictionary::currentVal() const{
    if(hasCurrent() == true){
        return current->val;
    }
    else if(hasCurrent() == false){
	    throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return nil->val;
}

   // Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    num_pairs = 0;
    root = nil;
    current = nil;
}

//pseudocode provided
void Dictionary::setValue(keyType k, valType v){
		Node *meow = nil;
        	Node *grr = root;
        	Node *cat = new Node(k,v);
       		cat->left = nil;
        	cat->right = nil;
        	cat->parent = nil;
        	while(grr != nil){
            		meow = grr;
			if(k == grr->key){
				grr->val = v;
				return;
			}
			else if(k < grr->key){
                		grr = grr->left;
            		} 
			else{
                		grr = grr->right;
            		}
        	}
        	cat->parent = meow;
        	if(meow == nil){
            		root = cat;
        	} 
		else if(cat->key < meow->key){
            		meow->left = cat;
        	}
	       	else {
            		meow->right = cat;
        	}
            cat->color = 1;
            RB_InsertFixUp(cat);
       		num_pairs = num_pairs + 1;
}

//pseudocode provided
void Dictionary::remove(keyType k){
    if(contains(k) == false){
	    throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    else{
        Node *cat = search(root, k);
        if(current == cat){
	        current = nil;
        }
        RB_Delete(cat);
        num_pairs--;
    }
}

  // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin(){
    if(size() > 0){
        current = findMin(root);
    }
}

   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end(){
    if(size() > 0){
        current = findMax(root);
    }
}


   // If the current iterator is not at the last pair, advances current
   // to the next pair (as defined by the order operator < on keys). If
   // the current iterator is at the last pair, makes current undefined.
void Dictionary::next(){
    if(hasCurrent() == false){
	    throw std::logic_error("Dictionary: next(): current undefined");
    }
    if(current == findMax(root)){
	    current = nil;
    }
    else if(hasCurrent() != false){
        current = findNext(current);
    }
}


   // If the current iterator is not at the first pair, moves current to
   // the previous pair (as defined by the order operator < on keys). If
   // the current iterator is at the first pair, makes current undefined.
void Dictionary::prev(){
    if(hasCurrent() == false){
	    throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if(current == findMin(root)){
	    current = nil;
    }
    else if(hasCurrent() != false){
        current = findPrev(current);
    }
}

   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value
   // are separated by the sequence space-colon-space " : ". The pairs are arranged
   // in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}


   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const{
    Dictionary meow = *this;
    Dictionary gr = D;
    int meow_size = meow.size();
    int gr_size = gr.size();
    std::string cat = meow.to_string();
    std::string dog = gr.to_string();

    if(meow_size != gr_size){
        return false;
    }

    if(cat != dog){
        return false;
    }
    return true;
}


   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.Dictionary::equals(B);
}

   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){ 
    if(this != &D){
        if(num_pairs > 0){
            postOrderDelete(root);
        }
        preOrderCopy(D.root, D.nil);
    }
    return *this;
}

