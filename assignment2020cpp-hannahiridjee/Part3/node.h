#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists

/*In the file node.h implement a template class Node that represents a node in a doubly-linked list. 
It should have three public member variables:

The data stored in that Node. The type of this should be a template argument.
A pointer to the next Node in the list
A pointer to the previous Node in the list
Make a constructor that takes an item of data, stores it in the node, and sets the two pointers to nullptr*/

template<typename T>
class Node{

private:

public: 

    //next is ptr to Node, *next is node
    T data;
    Node * next;
    Node * previous;

    //check assigning it to null pointer
    Node(const T & dataIn)
        :data(dataIn), next(nullptr), previous(nullptr){}

    Node(){}

};



template<typename T>
class NodeIterator {
  
private:
 //CHECK IF HAS TO BE PRIVATE   
    //Node<T>* current;
    
public:
    Node<T>* current;

    
    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here

    //should return type be NodeIterator<T> &
    NodeIterator<T> operator++(){
        current = current->next;
        return *this;
    }

    //operator ==
    bool operator==(const NodeIterator<T> other) const{
        return(current == other.current);
    }

    //operator !=
    bool operator!=(const NodeIterator<T> other) const{
        return(current != other.current);
    } 
    
};

// do not edit below this line

#endif
