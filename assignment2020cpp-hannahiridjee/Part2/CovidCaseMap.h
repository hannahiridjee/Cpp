#ifndef COVIDCASEMAP_H
#define COVIDCASEMAP_H

#include "CovidCase.h"

// TODO: your code goes here

#include <vector>
using std::vector;

#include <iostream>
using std::cout;

#include <iterator>
using std::iterator;

#include <algorithm>

#include <limits>


class TimeAndCaseData{

private:

int time; 
int cases;      

public:

    TimeAndCaseData(int timeIn, int casesIn)
        : time(timeIn), cases(casesIn) {}

    int getTime(){
        return time;
    }

    int getNumberOfCases(){
        return cases;
    }


};

class CovidCaseMap{

private:

    vector<CovidCase> covidVector;

public:

    void addCase(const CovidCase & caseToAdd){
        covidVector.push_back(caseToAdd);
    }

    vector<TimeAndCaseData> getCasesOverTime(int quarantineTime){

        vector<TimeAndCaseData> toReturn;

        //vector representine times that need to be checked
        vector<int> timesToInspect;

        //adding time 0 to the vector
        timesToInspect.push_back(0);

        //adding the time each patient tested positive as well as the time they should no longer be positive
        for(auto patient : covidVector){
            timesToInspect.push_back(patient.getTime());
            timesToInspect.push_back(patient.getTime() + quarantineTime);
        }

        //sorting the times into ascending order 
        for(auto time: timesToInspect){
            sort(timesToInspect.begin(), timesToInspect.end());
        }

        //check each time in the vector
        for(auto time : timesToInspect){

            int currentTime = time;
            int casesAtThisTime = 0;

            //check each patient for that time
            for(auto checkPatient: covidVector){

                //was patient positive AT that time
                if(checkPatient.getTime() == currentTime){
                    casesAtThisTime++;
                }

                //was patient positive BEFORE that time
                if(checkPatient.getTime() < currentTime){

                    //has patient recovered since then
                    if((currentTime - checkPatient.getTime()) >= quarantineTime){
                        //patient recoverred
                    }
                    else{
                        //patient not recoverred
                        casesAtThisTime++;
                    }
                }

            }
            //add that time and the number of cases at that time to the vector
            toReturn.push_back(TimeAndCaseData(currentTime, casesAtThisTime));
        }

        return toReturn;
    }

    double distanceTo(double latitude1, double longitude1, double latitude2, double longitude2){

        const int R = 3960;

        double lat1 = latitude1 * M_PI / 180.0;
        double lon1 = longitude1 * M_PI / 180.0;

        double lat2 = latitude2 * M_PI / 180.0;
        double lon2 = longitude2 * M_PI / 180.0;

        double dlon = lon2 - lon1;  
        double dlat = lat2 - lat1; 
        double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);  
        double c = 2 * atan2( sqrt(a), sqrt(1-a) );  
        double distance = R * c ;

        return distance; 
    }

    double supportVisitGreedyTSP(double lat, double longt, int visitTime ,int isolation){

        vector<CovidCase> patientsToVisit;

        //check all patients that need to be visited
        for(auto patient: covidVector){

            //check if they are positive before the visit
            if(patient.getTime() < visitTime){

                //Check if they are still positive at time of visit
                if(visitTime < (patient.getTime() + isolation)){
                    patientsToVisit.push_back(patient);
                }
            }
        }

        //starting and ending point
        double startLat = lat;
        double startLongt = longt;

        //current position
        double currentLat = startLat;
        double currentLongt = startLongt;

        double totalDistance= 0;
        double thisDistance = 0;

        while (!(patientsToVisit.empty())){
            
            //set initial minimum distance to a very very big number in order to compare
            double minDistance = std::numeric_limits<double>::infinity();
            int pos;

            for(int i = 0; i < patientsToVisit.size(); i++){

                //check shortest distance from current position to next unvisited patient
                thisDistance = distanceTo(currentLat, currentLongt, patientsToVisit.at(i).getLatitude(), patientsToVisit.at(i).getLongitude());

                if (thisDistance < minDistance) { 
                    minDistance = thisDistance;
                    pos = i; 
                }

            }

            totalDistance += minDistance;

            //save the current position
            currentLat = patientsToVisit.at(pos).getLatitude();
            currentLongt = patientsToVisit.at(pos).getLongitude();
            
            //delete patient that has been visited
            patientsToVisit.erase(patientsToVisit.begin()+pos);
        }

        //find distance back to starting point
        double distanceToStart = distanceTo(currentLat, currentLongt, startLat, startLongt);
        totalDistance += distanceToStart;

        return totalDistance;
    }




};


// don't write any code below this line

#endif

