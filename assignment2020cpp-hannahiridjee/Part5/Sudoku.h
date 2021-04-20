#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"

// TODO: Your Sudoku class goes here:
#include <set>
using std::set;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;

#include <algorithm>
#include <cmath>
using std::sqrt;
using std::floor;
using std::iterator;

using std::unique_ptr;

class Sudoku : public Searchable{

private:

    int size;
    vector<vector<set <int>>> grid;
    int boxSize;

public:

    Sudoku(const int sizeIn)
        :size(sizeIn)
    {
        boxSize = sqrt(size);

        for(int i = 0; i < size; i++){
            vector<set <int>> row;
            for(int j = 0; j < size; j++){
                set<int> square;
                for(int k = 1; k <= size; k++){
                    square.insert(k);
                    //cout << "adding " << k << "\n";
                }
                row.push_back(square);
            }
            grid.push_back(row);
        }
    }

    int getSquare(int row, int col){
        
        if(grid[row][col].size() == 1){
            return *grid[row][col].begin();
        }
        //cout << "Size is " << grid[row][col].size() << "\n";
        return -1;
    }



    bool checkRow(int Crow, int Ccol, int toRemove){

        for(int row = 0; row<size; row++){
            if(grid[row][Ccol].find(toRemove) != grid[row][Ccol].end()){
                if(row!= Crow){
                    grid[row][Ccol].erase(toRemove);
                    if(grid[row][Ccol].empty()){
                        return false;
                    }
                }
            }
        }
        return true;

    }  

    bool checkRowSetTwo(int Crow, int Ccol, int val1, int val2){

        for(int row = 0; row<size; row++){
            //remove val1
            if(grid[row][Ccol].find(val1) != grid[row][Ccol].end()){
                if(row!= Crow){
                    grid[row][Ccol].erase(val1);
                    if(grid[row][Ccol].empty()){
                        return false;
                    }
                }
            }
            //remove val2
            if(grid[row][Ccol].find(val2) != grid[row][Ccol].end()){
                if(row!= Crow){
                    grid[row][Ccol].erase(val2);
                    if(grid[row][Ccol].empty()){
                        return false;
                    }
                }
            }  
        }
        return true;

    }  

    bool checkCol(int Crow, int Ccol, int toRemove){

        for(int col = 0; col<size; col++){
            if(grid[Crow][col].find(toRemove) != grid[Crow][col].end()){
                if(col != Ccol){
                    grid[Crow][col].erase(toRemove);
                    if(grid[Crow][col].empty()){
                        return false;
                    }
                }
            }
        }
        return true;

    }  

    bool checkColSetTwo(int Crow, int Ccol, int val1, int val2){

        for(int col = 0; col<size; col++){
            //remove val1
            if(grid[Crow][col].find(val1) != grid[Crow][col].end()){
                if(col != Ccol){
                    grid[Crow][col].erase(val1);
                    if(grid[Crow][col].empty()){
                        return false;
                    }
                }
            }

            //remove val2
            if(grid[Crow][col].find(val2) != grid[Crow][col].end()){
                if(col != Ccol){
                    grid[Crow][col].erase(val2);
                    if(grid[Crow][col].empty()){
                        return false;
                    }
                }
            }

        }
        return true;

    }   

   /*bool checkBox(int row, int col, int toRemove){
        int boxSize = sqrt(size);
        //cout << "SET BOX \n";
        int r = row/boxSize;
        int c = col/boxSize;

        for(int i = 0; i<boxSize; ++i){
            int effectiveR = r*boxSize +i;
            for(int j=0; j<boxSize;j++){
                int effectiveC=c*boxSize +j;

                if(*grid[effectiveR][effectiveC].find(toRemove) == toRemove && effectiveR != row && effectiveC !=col){
                    grid[effectiveR][effectiveC].erase(toRemove);
                    if(grid[effectiveR][effectiveC].size() == 0){
                        return false;
                    }
                }
            }
        }
        return true;

   }*/
   
/*        int boxStartRow = floor(Crow/boxSize) * boxSize;
        int boxStartCol = floor(Ccol / boxSize) * boxSize;
        int endRow = boxStartRow + boxSize;
        int endCol = boxStartCol + boxSize;

        for (int row = boxStartRow; row < endRow; row++){
            for (int col = boxStartCol; col < endCol; col++){
                if (row != Crow && col != Ccol){
                    if (grid[row][col].find(toRemove) != grid[row][col].end()){
                        //check = true;
                        //canSet = true;
                        grid[row][col].erase(toRemove);
                        if (grid[row][col].empty() == true)
                        {
                            return false;
                        }
                        else if(grid[row][col].size()==1){
                            int v = *grid[row][col].begin();
                            setSquare(row,col,v);
                        }
                    }
                }
            }
        }
        return true;*/
    /*bool checkBoxSetTwo(int Crow, int Ccol, int val1, int val2){
        int boxStartRow = floor(Crow/boxSize) * boxSize;
        int boxStartCol = floor(Ccol/boxSize) * boxSize;

        for (int row = boxStartRow; row < boxStartRow+boxSize; row++) {
            for (int col = boxStartCol; col < boxStartCol+boxSize; col++) {
                if(row != Crow && col != Ccol) {
                    if (grid[row][col].find(toRemove) != grid[row][col].end()) {
                        grid[row][col].erase(toRemove);
                        if (grid[row][col].empty() == true) {
                            return false;
                        }
                    }
                }

            }

        }
        return true;
    }*/

//________________________________________________________________________________

bool setSquarePartTwo(){

        bool flag = false;

        for (int cRow = 0; cRow < size; cRow++) {
            for (int cCol = 0; cCol < size; cCol++) {

                if (grid[cRow][cCol].size() == 1) {
                    int toRemove = *grid[cRow][cCol].begin();

                    if(!checkRow(cRow,cCol,toRemove)){
                        flag = true;
                        return false;
                    }

                    if(!checkCol(cRow,cCol,toRemove)){
                        flag = true;
                        return false;
                    }

                    /*if(!checkBox(cRow,cCol,toRemove)){
                        flag = true;
                        return false;
                    }*/
                    //box
                    int boxStartRow = floor(cRow/boxSize) * boxSize;
                    int boxStartCol = floor(cCol/boxSize) * boxSize;
                    int endRow = boxStartRow+boxSize;
                    int endCol = boxStartCol+boxSize;


                    for (int row = boxStartRow; row < endRow; row++) {
                        for (int col = boxStartCol; col < endCol; col++) {
                            if(row != cRow && col != cCol) {
                                if (grid[row][col].find(toRemove) != grid[row][col].end()) {
                                    flag = true;
                                    grid[row][col].erase(toRemove);
                                    if (grid[row][col].empty() == true) {
                                        return false;
                                    }
                                }
                            }


                        }

                    }
                    //end box

                }

            }

        }
        if(flag){
            return this->setSquarePartTwo();
        }
        return true;
        
}


    bool setSquare(int row, int col, int value){
        //cout << "SET SQUARE \n";

        grid[row][col].clear();
        grid[row][col].insert(value);

        return this->setSquarePartTwo();
    }
//________________________________________________________________________________


    bool isSolution() const override{
        for(int row = 0; row < size; row++){
            for(int col = 0; col < size; col++){
                if(grid[row][col].size() != 1){
                    return false;
                }
            }
        }
        return true;

    }

    void write(ostream & o)const override{
        for(int row = 0; row< size; row++){
            for(int col = 0; col < size; col++){
                if(grid[row][col].size() > 1){
                    o << " ";
                }
                else{
                    o << *grid[row][col].begin();
                }
            }
            cout << "\n";
        }

    }

	vector<unique_ptr<Searchable>> successors() const override {

		vector< unique_ptr<Searchable>> successor;

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (grid[i][j].size() > 1) {

					for (auto  val : grid[i][j]) {
                        unique_ptr<Sudoku> currObj(new Sudoku(*this));

						if (currObj->setSquare(i, j, val)) {
							successor.push_back(std::move(currObj));
						} 
                        
					}
                    if((successor.size()==1) && !(successor[0]->isSolution())){
                        return successor[0]->successors();
                    }
					return successor;
				}
			}	
		}

		return successor;
        
	}

    int heuristicValue() const override {

        int number = 0;

        for(int row=0; row<size; row++){
            for(int col=0; col<size; col++){
                if(grid[row][col].size() >1){
                    number++;
                }
            }
        }
        return number;

    }


};


#endif
