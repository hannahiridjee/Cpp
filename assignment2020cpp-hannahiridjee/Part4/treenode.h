#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:

template<typename T>
class TreeNode{

public:
    T data;
    unique_ptr<TreeNode<T>> leftChild;
    unique_ptr<TreeNode<T>> rightChild;
    TreeNode * parent;

    TreeNode(const T & dataIn)
        :data(dataIn), parent(nullptr) {}

    void setLeftChild(TreeNode<T> * child){
        leftChild = unique_ptr<TreeNode>(child);
        if(leftChild != nullptr){
            leftChild->parent = this;
        }
    }
    
    void setRightChild(TreeNode<T> * child){
        rightChild = unique_ptr<TreeNode>(child);
        if(rightChild != nullptr){
            rightChild->parent = this;
        }
    }

    void write(ostream & o) const{
        if (leftChild) {
            leftChild->write(o);
        }
        o << " ";
        o << data;
        o << " ";
        if (rightChild) {
            rightChild->write(o);
        }

    }


    int maxDepth(){

        auto lc = this->leftChild.get();
        auto rc = this->rightChild.get();

        int max = 0;
        int depthL = 0;
        int depthR = 0;

        if(lc == nullptr && rc == nullptr){
            max = 1;
            return max;
        }
        if(lc != nullptr){
            depthL = lc->maxDepth();
        }
        if(rc != nullptr){
            depthR = rc->maxDepth();
        }

        if(depthL>depthR){
            max = depthL+1;
            return max;
        }
        else{
            max = depthR+1;
            return max;
        }
        
    }
    
    
};

template<typename T>
class TreeNodeIterator{

private:

    //Should it be private??
    TreeNode<T>* current;
public:

    //TreeNode<T>* treeNode;

    TreeNodeIterator(TreeNode<T>* currentIn)
        :current(currentIn){}

//check this
    T & operator*(){
        //return treeNode->data
        return current->data;
    }

    bool operator==(const TreeNodeIterator<T> & other) const {
        return current == other.current;
    }

    bool operator!=(const TreeNodeIterator<T> & other) const{
        return current != other.current;
    }

    TreeNodeIterator<T>  operator++(){

        TreeNode<T> * prevParent;
        if(current->rightChild != nullptr){
            current = current ->rightChild.get();

            while(current->leftChild != nullptr){
                current = current -> leftChild.get();
            }
        }

        else{
            prevParent=current->parent;
            while(prevParent != nullptr && current == prevParent->rightChild.get()){
                    current = prevParent;
                    prevParent = prevParent->parent;
            }
            current = prevParent;
        }
        return current;
    }




};

// do not edit below this line

#endif
