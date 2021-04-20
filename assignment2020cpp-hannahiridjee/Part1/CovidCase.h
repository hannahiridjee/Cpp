#ifndef COVIDCASE_H
#define COVIDCASE_H

#include <iostream>
using std::ostream;

// TODO: your code  goes here

using std::cout;

#include <string>
using std::string;

#include <cmath>


class CovidCase{

private:

    double  latitude;
    double longtitude;
    string name;
    int  age;
    int caseTime;


public:

    //Task 1
    CovidCase(const double latitudeIn,const double longtitudeIn,const string nameIn,const int ageIn,const int timeIn)
        : latitude(latitudeIn), longtitude(longtitudeIn), name(nameIn), age(ageIn), caseTime(timeIn)
        {

        }

    //Task 2
    friend ostream & operator<<(ostream & o, const CovidCase & toPrint){

        //o << "{ " << toPrint.getLatitude() << ", " << toPrint.getLongtitude() << ", " << toPrint.getName() << ", " << toPrint.getAge() << ", " << toPrint.getTime() << " }";
        o << "{" << toPrint.latitude << ", " << toPrint.longtitude << ", " << "\"" << toPrint.name << "\"" << ", " << toPrint.age << ", " << toPrint.caseTime << "}";

        return o;
    }
    
    //Task 3
    double getLat() const{
        return latitude;
    }

    double getLon() const{
        return longtitude;
    }

    double distanceTo(const CovidCase & case2){

        const int R = 3960;

        double lat1 = latitude * M_PI / 180.0;
        double lon1 = longtitude * M_PI / 180.0;

        double lat2 = case2.getLat() * M_PI / 180.0;
        double lon2 = case2.getLon() * M_PI / 180.0;

        double dlon = lon2 - lon1;  
        double dlat = lat2 - lat1; 
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);  
        double c = 2 * atan2( sqrt(a), sqrt(1-a) );  
        double distance = R * c ;

        return distance; 
    }

};


// don't write any code below this line

#endif
 