#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
#include <initializer_list>
using std::initializer_list;

template<typename T>
class LinkedList{

private:

    Node<T> * head;
    Node<T> * tail;
    int sizeLL;


public: 

    LinkedList()
        : head(nullptr), tail(nullptr), sizeLL(0) {}
    
//check 
    LinkedList(const initializer_list<T> & initList )
        :head(nullptr), tail(nullptr),sizeLL(0)
        {
            for(const auto element: initList){
                push_back(element);
            }
        }

    ~LinkedList(){
 
        while(head != nullptr){
            Node<T>* nextNode = head->next;
            delete head;
            head = nextNode;
        }
    }

//CHECK REF A front() function, that returns a reference to the data inside the head node
    T front(){
        return head->data;
    }

//CHECK REF A back() function, that returns a reference to the data inside the tail node
    T back(){
        return tail->data;
    }

    int size(){
        return sizeLL;
    }

//CHECK 
    NodeIterator<T> begin(){
        return NodeIterator<T>(head);
    }

    NodeIterator<T> begin() const{
        return NodeIterator<T>(head);
    }

//CHECK 
    NodeIterator<T> end(){
        return NodeIterator<T>(nullptr);

    }

//CHECK 
    NodeIterator<T> end() const{
        return NodeIterator<T>(nullptr);

    }


    void push_front(const T & item){

        sizeLL++;

        Node<T> * newNode = new Node<T>(item);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            newNode->next = head;
            head = newNode;
        }

    }


    void push_back(const T & item){

        sizeLL++;

        Node<T> * newNode = new Node<T>(item);
        newNode->next = nullptr;

        //if head is null
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode -> previous = tail;
            tail = newNode;
        }

    }

//DOUBLY LINKED LIST?
    void reverse(){
        Node<T> * prev = nullptr;
        Node<T> * next = nullptr;
        Node<T> * curr= head;

        while(curr != nullptr){
            next = curr -> next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    NodeIterator<T> insert(const NodeIterator<T> & insertPlace, T element){

        Node<T>* toAdd = new Node<T>(element);
        Node<T> * currentNode = insertPlace.current; 
        
        //insert at head
        if(currentNode == head){
            push_front(element);
            return head;
        }
        
        //insert after tail
        if(currentNode == nullptr){
            push_back(element);
            return tail;
        }
        
        //insert at other positions
        Node<T> * beforeNode = currentNode->previous;   

        beforeNode->next = toAdd;
        toAdd->previous = beforeNode;
        toAdd->next = currentNode;
        currentNode->previous = toAdd;

        return NodeIterator<T>(toAdd);

    }

//CHECK ERASE AFTER TAIL
    NodeIterator<T> erase(const NodeIterator<T> & erasePlace){

        Node<T> * toErase = erasePlace.current;

        //erasing the tail
        if(toErase == tail){
            delete toErase;
            return NodeIterator<T>(nullptr);
        }

        //erasing the head
        else if(toErase == head){
            Node<T> * afterNode = toErase->next;   
            head -> next = nullptr;
            afterNode ->previous = nullptr;
            delete head;
            head = afterNode;
            return NodeIterator<T>(head);
        }
        //erasing non head and non tail 
        else{
            Node<T> * afterNode = toErase->next;   
            Node<T> * beforeNode = toErase->previous; 

            beforeNode->next = afterNode;
            afterNode->previous = beforeNode;
            toErase->next = nullptr;
            toErase->previous = nullptr;
            delete toErase;

            return NodeIterator<T>(afterNode);

        }


        
    }



};

// do not edit below this line

#endif
