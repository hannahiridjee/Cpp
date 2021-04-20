#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

// Do not add any #include statements to this file

class SudokuSquareSet {

    // TODO: write your code here

#include <iterator>
//using std::iterator;

private:

    unsigned int bits;

    int numOfValues;

public:

    /*SudokuSquareSet(){

    }

    int size(){
        return numOfValues;
    }

    bool empty(){
        return numOfValues == 0;
    }

    void clear(){
        //remove all values from the set
    }

    bool operator==(const SudokuSquareSet & other){

    }

    bool operator!=(const SudokuSquareSet & other){

    }

    begin(){

    }

    end(){

    }

    insert(){

    }

    find(){

    }

    erase(){

    }

    erase(iterator){

    }*/


};


// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
