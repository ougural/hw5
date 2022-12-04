#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool helper(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, 
    int shiftCurr,
    int dayCurr);

bool check(const AvailabilityMatrix& avail,
    const size_t maxShifts,
    const DailySchedule sched,
    int shiftCurr,
    int dayCurr);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched)
{
    if(avail.size() == 0U){
      return false;
    }
    sched.clear();
  
    // calculate n (number of days)
    int numDays = 0;
    for(int i = 0; i < avail.size(); i++){
        numDays++;
    }

    // initialize an n x d schedule with dummy vars
    Worker_T dummy = -1;
    // loop through number of days
    for(unsigned int i = 0; i < numDays; i++){
        vector<Worker_T> temp;
        // for each day, add a d-lenghted vector
        for(unsigned int j = 0; j < dailyNeed; j++){
            temp.push_back(dummy);
        }
        sched.push_back(temp);
    }

    return helper(avail, maxShifts, sched, 0, 0);
}

bool helper(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    DailySchedule& sched, 
    int shiftCurr,
    int dayCurr)
{
    // increase current day, reset current shift
    if(shiftCurr == sched[0].size()){
        shiftCurr = 0;
        dayCurr++;
    }
    // return true if recursed everyday
    if(dayCurr == sched.size()){
        return 1;
    }
    for(Worker_T id = 0; id < avail[0].size(); id++){
        sched[dayCurr][shiftCurr] = id;
	    //  check
        if(check(avail, maxShifts, sched, shiftCurr, dayCurr)){
            shiftCurr++;
            return helper(avail, maxShifts, sched, shiftCurr, dayCurr);
        }
    }
    return 0;
}

bool check(
    const AvailabilityMatrix& avail,
    const size_t maxShifts,
    const DailySchedule sched,
    int shiftCurr,
    int dayCurr)
{
    Worker_T id = sched[dayCurr][shiftCurr];
    // count number of shifts worker has
    int numShifts = 0;
    for(int i = 0; i < sched.size(); i++){
        for(int j = 0; j < sched[0].size(); j++){
            if(sched[i][j] == id){
                numShifts++;
            }
        }
    }
    // check if number of shifts exceeds max 
    bool exceedMaxShift = false;
    if(numShifts > maxShifts){
        exceedMaxShift = true;
    }
    // check if worker is available for the day
    bool available = false;
    if(avail[dayCurr][id]){
        available = true;
    }
    return (available && !exceedMaxShift);
}

