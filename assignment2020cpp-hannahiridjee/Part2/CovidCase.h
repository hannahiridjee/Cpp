// TODO: Replace this file with your CovidCase.h from Part1
// then extend as per the instructions in README.md

#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

// TODO: your code  goes here

using std::cout;

#include <string>
using std::string;

#include <cmath>

#include <sstream>


class CovidCase{

private:

    double  latitude;
    double longitude;
    string name;
    int  age;
    int caseTime;


public:

    //Part 1 Task 1
    CovidCase(const double latitudeIn,const double longitudeIn,const string nameIn,const int ageIn,const int timeIn)
        : latitude(latitudeIn), longitude(longitudeIn), name(nameIn), age(ageIn), caseTime(timeIn)
        {

        }

    //Part 1 Task 2
    friend ostream & operator<<(ostream & o, const CovidCase & toPrint){

        //o << "{ " << toPrint.getLatitude() << ", " << toPrint.getLongtitude() << ", " << toPrint.getName() << ", " << toPrint.getAge() << ", " << toPrint.getTime() << " }";
        o << "{" << toPrint.latitude << ", " << toPrint.longitude << ", " << "\"" << toPrint.name << "\"" << ", " << toPrint.age << ", " << toPrint.caseTime << "}";

        return o;
    }
    
    //Part 1 Task 3
    double getLatitude() const{
        return latitude;
    }

    double getLongitude() const{
        return longitude;
    }

    double distanceTo(const CovidCase & case2){

        const int R = 3960;

        double lat1 = latitude * M_PI / 180.0;
        double lon1 = longitude * M_PI / 180.0;

        double lat2 = case2.getLatitude() * M_PI / 180.0;
        double lon2 = case2.getLongitude() * M_PI / 180.0;

        double dlon = lon2 - lon1;  
        double dlat = lat2 - lat1; 
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);  
        double c = 2 * atan2( sqrt(a), sqrt(1-a) );  
        double distance = R * c ;

        return distance; 
    }

    //Part 2 Task 1 
        //implement an equality operator -- `operator==` -- that allows you to determine whether two `CovidCase` objects are the same -- i.e. have the same values for all member variables.
        //NOTE CHECK IS ABS IS NEEDED
        bool operator==(const CovidCase & other){
            if((abs(latitude) == abs(other.latitude)) && (abs(longitude) == abs(other.longitude)) && ( name == other.name) && (age == other.age) && (caseTime == other.caseTime)  ){
                return true;
            }
            return false;
        }
    


    //Part 2 Task 2 
        //implement 'getter' functions for accessing the values stored in the object.  These getters should be named `getLatitude`, `getLongitude`, `getName`, `getAge`, `getTime` for the respective member variables.

        string getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        int getTime() const{
            return caseTime;
        } 

    //Part 2 Task3 
        //add another constructor to `CovidCase` that takes a string, and uses this to initialise the member variables of the object.

    CovidCase(const string str)
        {
            string line; 
            string tempString;
            std::stringstream ss(str); 

            while(getline(ss, line)){

                getline(ss, line, ',');
                latitude = stod(line);

                getline(ss, line, ',');
                line = line.substr(line.find(" ")+1);
                longitude = stod(line);
             
                getline(ss, line, ',');
                line = line.substr(line.find(" ")+1);
                name = line;
                int firstpos = name.find("\"") + 1 ;
                int lastpos = name.rfind("\"");
                name = name.substr(firstpos, lastpos-1);

                getline(ss, line, ',');
                line = line.substr(line.find(" ")+1);
                age = stoi(line);

                getline(ss, line, ',');
                line = line.substr(line.find(" ")+1);
                caseTime = stoi(line);

            }
        }

};


// don't write any code below this line

#endif