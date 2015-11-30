#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue(int htime) : holdTimes(0){
  if(htime != 3)  // default: 3 minutes
    maxHold=htime;
  else
    maxHold = 3;
  inQueue=false;
}

bool Queue::getInQueue(){
  return inQueue;
}

void Queue::setInQueue(bool tf){
  inQueue=tf;
}

int Queue::getHoldSize(){
  return holdTimes.size();
}

void Queue::addCall(int n = 1){
  for (int x=1; x<=n; x++){
    inQueue = true;
    holdTimes.push_back(0);
  }
}

void Queue::takeCall(){
  if (getHoldSize()>0){
    holdTimes.erase(holdTimes.begin());
    if (getHoldSize()==0)
      setInQueue(false);
  } else {
    setInQueue(false);
  }
}

int Queue::getHoldTime(int x){
  return holdTimes.at(x);
}

bool Queue::incHoldTimes(){
  for (int x=0; x<holdTimes.size(); x++){
    holdTimes.at(x)++;
    std::cout << "hold call " << x+1 <<
      " has been on hold for " << holdTimes.at(x) << endl;
    if  (holdTimes.at(x)==maxHold)
      return true;
  }
  return false;
}

Queue::~Queue(){
  holdTimes.clear();
}
