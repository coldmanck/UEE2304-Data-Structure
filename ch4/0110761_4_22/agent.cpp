#include <iostream>
#include <iomanip>
#include "agent.h"
using namespace std;

agent::agent(double s, int i){
  skill = (s <= 3 ? s:2);
  agentID = i;
  avail = true;
  nextAvail = 0;
  activeTime = 0;
  idleTime = 0;
  calls = 0;
}

int agent::getAgentID(){
  return agentID;
}

double agent::getSkill(){
  return skill;
}

bool agent::getAvail(){
  return avail;
}

int agent::getNextAvail(){
  return nextAvail;
}

void agent::decNextAvail(){
  nextAvail--;
}

double agent::getActiveTime(){
  return activeTime;
}

void agent::incActiveTime(){
  activeTime++;
}

double agent::getIdleTime(){
  return idleTime;
}

void agent::incIdleTime(){
  idleTime++;
}

double agent::getEfficiency(){
  if(idleTime<=0&&activeTime>0)
    return 100.00;
  if(activeTime<-0&&idleTime>0)
    return 0.00;
  return (100*(1-(idleTime/activeTime)));
}

void agent::giveCall(){
  avail=false;
  nextAvail=skill;
  calls++;
}

void agent::endCall(){
  if (!avail){
    if (skill==3){
      idleTime = idleTime+0.5;
      activeTime = activeTime+0.5;
    } else {
      activeTime++;
    }
    avail=true;
  }
}

int agent::getCallsCount(){
  return calls;
}

void agent::printRepHead(){
  cout << "\n\n";
  cout << "Final Report:\n"
    << setw(7) << "Agent #"
    << setw(13) << "Active Time"
    << setw(11) << "Idle Time"
    << setw(13) << "Total Calls"
    << setw(12) << "Efficiency"
    << endl;
}

void agent::printReport(){
  cout << setw(7) << agentID
    <<setw(13) << activeTime
    << setw(11) << idleTime
    << setw(13) << calls
    << setw(11) << setprecision(4) << getEfficiency() << "%";
    if (skill>=3)
      cout << " (novice)";
    cout << endl;
}

agent::~agent(){
}
