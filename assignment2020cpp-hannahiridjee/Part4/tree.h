#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree{

private:

    //check this
    unique_ptr<TreeNode<T>> root;

public:

    BinarySearchTree(){}

    BinarySearchTree(const BinarySearchTree<T> & treeToCopy)
    {
        root = nullptr;
        copy(treeToCopy.root.get());
    }

    void copy(const TreeNode<T>* toCopy){
        if(toCopy){
           insert(toCopy->data);
           copy(toCopy->leftChild.get());
           copy(toCopy->rightChild.get());
        }
    }



    BinarySearchTree<T> & operator=(const BinarySearchTree<T> & treeToCopy){
        
        assign(treeToCopy.root.get());
        return *this;
    }
    
    void assign(TreeNode<T> * toAssign){
        
        this->insert(toAssign->data);
    
        if(toAssign->leftChild != nullptr){
            assign(toAssign->leftChild.get());
        }
        
        if(toAssign->rightChild != nullptr){
            assign(toAssign->rightChild.get());
        }
    }


    void write(ostream & o) const{
        root->write(o);
    }



    void leftRotation(TreeNode<T> * gp){
        //cout << "left rotation \n \n";
        TreeNode<T> * p = gp->rightChild.get();
        TreeNode<T> * temp = nullptr;
        //cout << "Parent " << p->data << "\n";
        //cout << "Grandarent " << gp->data << "\n";

        if(root.get() == gp){
            temp = root.release();
            root.reset(p);
            root->parent = nullptr;
        }
        else{
            TreeNode<T> * ggp = gp->parent;
            //cout << "Greatrandarent " << ggp->data << "\n";
            if(gp == ggp->rightChild.get()){
                //cout << "grandparent is right child of ggp \n";
                temp = ggp->rightChild.release();
                ggp->setRightChild(p);
                //cout << "greatgrandparent's right child is now " << ggp->rightChild.get()->data << "\n" ;
            }
            else if(gp == ggp->leftChild.get()){
                //cout << "grandparent is left child of ggp \n";
                temp = ggp->leftChild.release();
                ggp->setLeftChild(p);
            }
        }
        temp = gp->rightChild.release();
        gp->setRightChild(p->leftChild.get());
        p->setLeftChild(gp);
    }

    void rightRotation(TreeNode<T> * gp){

        TreeNode<T> * p = gp->leftChild.get();
        TreeNode<T> * temp = nullptr;

        if(root.get() == gp){
            temp = root.release();
            root.reset(p);
            root->parent = nullptr;
        }
        else{
            TreeNode<T> * ggp = gp->parent;
  
          if(gp == ggp->rightChild.get()){
                temp = ggp->rightChild.release();
                ggp->setRightChild(p);
            }
            else if(gp == ggp->leftChild.get()){
                temp = ggp->leftChild.release();
                ggp->setLeftChild(p);
            }
        }
        //check next two lines
        temp = gp->leftChild.release();
        gp->setLeftChild(p->rightChild.get());
        p->setRightChild(gp);
    }

    void leftRightRotation(TreeNode<T> * gp){
 
        //cout << "LR rot \n \n";

        TreeNode<T> * p = gp->leftChild.get();
        leftRotation(p);
        rightRotation(gp);
    }

    void rightLeftRotation(TreeNode<T> * gp){
        //cout << "RL rot \n \n";

        TreeNode<T> * p = gp->rightChild.get();
        rightRotation(p);
        leftRotation(gp);

    }

    int balanceFactor(TreeNode<T> * node){
        //cout << "inside balance factor \n";
        int leftside = 0;
        int rightside = 0;

        int balance = 0;
        if(node == nullptr){
            return 0;
        }
        if(node->leftChild.get()){
            leftside = node->leftChild.get()->maxDepth();
        }
        if(node->rightChild.get()){
            rightside = node->rightChild.get()->maxDepth();
        }
        balance = leftside-rightside;
        return balance;
    }
    
    void isBalanced(TreeNode<T> * toInsert){
            TreeNode<T> * gp = toInsert->parent->parent;
            int balance = balanceFactor(gp);
            
            if(balance > 1 && (toInsert->data < gp->leftChild.get()->data) ){
                rightRotation(gp);
            }
            else if(balance < -1 && (gp->rightChild.get()->data < toInsert->data)){
                leftRotation(gp);
            }
            else if(balance < -1 && (toInsert->data < gp->rightChild.get()->data)){
                rightLeftRotation(gp);
            } 
            else if(balance > 1 && (gp->leftChild.get()->data < toInsert->data)){
                leftRightRotation(gp);
            }
    }


//check inserting same value
    TreeNode<T> * insert(const T dataIn){

        TreeNode<T>* current = root.get();
        TreeNode<T>* pos = nullptr;
        
        while(current != nullptr){
            pos = current;
            if(dataIn < current->data){
                current = current -> leftChild.get();
            }
            else if(current->data < dataIn){
                current = current -> rightChild.get();
            }
            else{
                return pos;
            }
        }
        
        TreeNode<T> * toInsert = new TreeNode<T>(dataIn);
        //cout << "Inserting node " << toInsert->data << "\n";
        if(pos == nullptr){
            toInsert->setLeftChild(nullptr);
            toInsert->setRightChild(nullptr);
            root = unique_ptr<TreeNode<T>>(toInsert);
        }
        else{
            if(dataIn < pos->data){
    
                toInsert->leftChild = nullptr;
                toInsert->rightChild = nullptr;
                pos->setLeftChild(toInsert);
                isBalanced(toInsert);
    
            }
            else if(pos->data < dataIn){
    
                toInsert->setLeftChild(nullptr);
                toInsert->setRightChild(nullptr);
                pos->setRightChild(toInsert);
                isBalanced(toInsert);
    
            }
        }


        return toInsert;
    }


    TreeNode<T> * find(const T & item)const{

        TreeNode<T> * pos = root.get();

        while(pos != nullptr){

            if(item < pos->data){
                //check left
                pos = pos ->leftChild.get();
            }
            else if(pos->data < item){
                //check right
                pos = pos ->rightChild.get();
            }
            else{
                return pos;
            }
        }

        return nullptr;

    }

    TreeNodeIterator<T> begin() const{
        auto currentNode = root.get();

        if(currentNode == nullptr){
            //return nullptr;
            currentNode = nullptr;
        }
        else{
            while(currentNode->leftChild != nullptr){
                currentNode = currentNode->leftChild.get();
            }
        }
        return TreeNodeIterator<T>(currentNode);

    }


    TreeNodeIterator<T> end() const{
        return TreeNodeIterator<T>(nullptr);
    }


    int maxDepth(){
        if(root.get() == nullptr){
            return 0;
        }
        else{
            return this->root.get()->maxDepth();
        }
        
    }

    
};



// do not edit below this line

#endif
