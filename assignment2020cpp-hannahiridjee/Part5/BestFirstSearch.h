#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <queue>
using std::priority_queue;
//using std::greater;

class Compare{

public:
    bool operator()(const unique_ptr<Searchable> & p1,const unique_ptr<Searchable> & p2)const{
        return p1.get()->heuristicValue()>p2.get()->heuristicValue();
    }

};

class BestFirstSearch {

protected:

    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;

    priority_queue<unique_ptr<Searchable>, vector<unique_ptr<Searchable>>, Compare > Q;
    
    
public:



    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        Q.push(std::move(startFrom));
        
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        // TODO Implement search, returning a pointer to the solution (if one is found)

        // If there are still incomplete solutions on the queue//
        while (!Q.empty()) {
            
            // If the solution on the front of the queue is a solution 
            if (Q.top()->isSolution()) {
                return Q.top().get(); // return the pointer 
            }
                  
            ++nodes; // we've now looked at one more node, increment our counter
            
            // Steal the pointer to the board at the front of the queue, by moving it into a unique_ptr here
            // After this, the pointer on the front of the queue is `nullptr`...

            unique_ptr<Searchable> current(std::move(const_cast<unique_ptr<Searchable>&>(Q.top())));
            
            // ...which can then be popped off the front of the queue
            Q.pop();
            
            // Get the successors...
            vector<unique_ptr<Searchable>> successors = current->successors();
            
            for (auto & successor : successors) {
                // and push each one onto the back of queue.
                Q.push(std::move(successor));
            }
        }
    
        return nullptr;
    }
};


// Do not edit below this line

#endif
