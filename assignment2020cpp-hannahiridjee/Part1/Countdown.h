#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>

// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:

using std::string;

#include <vector>
using std::vector;

using std::stringstream;

#include <iostream>
#include <sstream>

#include <locale>
#include <stack>
using std::stack;

double evaluateCountdown(string str){

    vector<double> vectorDoubles;
    stringstream ss(str);
    double number;
    string token;

    while (getline(ss, token, ' ')) {

        bool isNumber = false;  
        for(int i = 0; i < token.length(); i++){
            if(isdigit(token[i])){
                isNumber = true;
            }
            else{
                isNumber = false;
            }
        }

        if(token.find(".") != -1 || isNumber){
            //std::cout<<token<<"\n";
             vectorDoubles.push_back(std::stod(token));
             
        }
        else
        {

            //get b and remove it
            double b = vectorDoubles.back();
            vectorDoubles.pop_back();

            //get a and remove it
            double a = vectorDoubles.back();
            vectorDoubles.pop_back();      

            if(token == "+"){
                vectorDoubles.push_back(a+b);
            }
            if(token == "-"){
                vectorDoubles.push_back(a-b);
            }
            if(token == "*"){
                vectorDoubles.push_back(a*b);
            }
            if(token == "/"){

                vectorDoubles.push_back(a/b);
            }
        }
    }

    double result = vectorDoubles.back();
    return result;

}


// Do not edit below this line


#endif
