#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;


// TODO: your code goes here:

//write a function `stringConstruction` that takes the target string, the clone cost, and the append cost (in that order), 
//and returns the cheapest way of making the target string.  It doesn't need to return *how* to do it, just the cost.
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <iostream>
using std::cout;

class Compare{

public:
    bool operator()(const string & s1, const string & s2){
        return s1.size()>s2.size();
    }
};

vector<string> getValidSub(const string & newString){
    vector<string> substrings;
    
    for (int i = 0; i < newString.length(); i++) {
        for (int j = newString.length(); j > i; j--) {

            string sub_str = newString.substr(i, j);
            substrings.push_back(sub_str);

            for (int k = 1; k < sub_str.length() - 1; k++) 
            {
                string sb = sub_str;
 
                // Drop character from the string
                sb.erase(sb.begin() + k);
                getValidSub(sb);
            }
        }
    }
    //erase duplicates
    Compare c;
    sort(substrings.begin(), substrings.end(),c);
    substrings.erase(unique(substrings.begin(), substrings.end()), substrings.end());

    //only keep those of length >= 2
    for(int i = 0; i<substrings.size(); i++){
        if(substrings.at(i).length() < 2){
            substrings.erase(substrings.begin()+i);
        }
    }

    return substrings;
}


int stringConstruction(string target, int clonecost, int appendcost){
    int cost = 0;
    string newString = "";
    vector<string> validSubstr;
    bool cloneable = true;
    

    for(int i = 0; i < target.size(); i++){
        //cout << "\n";
        //cout << "target string element " << target[i] << "\n";
        bool cloned = false;
        
        
        validSubstr = getValidSub(newString);
        for(string str: validSubstr){
            if((!cloned) && target.substr(i,str.size()) == str){
                //cout << "   can clone substring " << str << "\n";
                newString = newString + str;
                //cout << "       newString = " << newString << "\n";
                cost += clonecost;
                i = i + str.size();
                cloned = true;
            }
        }
        
        if((i==0) || (i==1) || !cloned){
            //cout << "   first or second character APPEND \n";
            newString = newString + target[i];
            //cout << "       newString = " << newString << "\n";
            cost += appendcost;
        }
 
    }
    return cost;

}

// do not write or edit anything below this line

#endif