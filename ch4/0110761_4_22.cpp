#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "0110761_4_22.h"

using std::vector; using std::sort;
using std::cout; using std::cin;
using std::endl; using std::setw;

int main(){
  int a=0, c=0; // number of agents,  calls per minute
  double n=0.0; // percentage of novice operators
  int hours=1, slot=0; // hours to simulate, tracks which operator is on deck
  int htime=0, runs=0; //max hold time

  cout << "Enter total number of agents: "; (cin >> a).get();
  cout << "Enter calls per minute: "; (cin >> c).get();
  cout << "Enter maximum hold time: "; (cin >> htime).get();
  htime = (htime>=1 && htime<=10 ? htime:3); 
  cout << "Enter number of hours to simulate: "; (cin >> hours).get();
  hours = (hours>=1 && hours<=24 ? hours:1); 

  cin.clear(); 

  vector<agent> agents; // vector of agents
  Queue hold(htime); // initialize our hold queue
  agent *f1; // temporary class for filling the vector

  for (int x=0; x<a; x++){
    f1 = new agent(2, x+1); // normal agent takes 2 mins per call
    agents.push_back(*f1); // Add this new agent onto the end of the vector
  }

  cout << "\nSimulation configured with\n- " << a << " operators\n- " 
    << "handling " << c << " calls per minute\n- over "
    << hours << " hours...\n\n";

  //Starting the simulation
  for (int x=1; x<=(hours*60); x++){
    runs++; 
    slot=0;

    cout << "\n\nMinute: " << x << endl;
    sort (agents.begin(), agents.end(), agent::callSort);
    cout << "Agent " << agents.at(0).getAgentID() << " is on deck\n";
    int calls = 0;
    if (hold.getInQueue()){
      cout << "There are " << hold.getHoldSize() << " calls on hold\n";
    }
    hold.addCall(c);
    calls = hold.getHoldSize();
    cout << calls << " calls need to be distributed\n";

    for (int z=0; z<calls;){
      for (;slot<a;){
        if (agents.at(slot).getAvail()){
          agents.at(slot).giveCall();
          cout << "\tCall assigned to agent " << agents.at(slot).getAgentID() << endl;
          hold.takeCall();
          z++; // a call has been handled
          slot++;
          break;
        } else {
          cout << "\tAgent " << agents.at(slot).getAgentID() << " is busy\n";
          slot++;
        }
      }
      if (slot>=a){
        if (z<calls){
          hold.setInQueue(true);
        }
        z=calls+1;
      }
    }
    if (hold.getInQueue())
      cout << hold.getHoldSize() << " calls went to hold\n";

    cout << "All calls have been assigned\n";

    // cleanup
    for (int z=0; z<a; z++){
      if (agents.at(z).getAvail()){
        agents.at(z).incIdleTime();
      } else {
        agents.at(z).decNextAvail();
        if (agents.at(z).getNextAvail()==0){
          agents.at(z).endCall();
        } else {
          agents.at(z).incActiveTime();
        }
      }
    }

    if (hold.getInQueue()){
      if (hold.incHoldTimes()){ // returns true if threshold reached
        cout << "\n******************\nHOLD THRESHOLD REACHED ON MINUTE ";
        cout << x << "\n******************\n";
        break;
      }
    }
  }

  // Put the agents back in order by ID
  sort (agents.begin(), agents.end(), agent::IDsort);

  int count=0;
  for (int x=0; x<a; x++){
    count+=agents.at(x).getCallsCount();
  }

  // Spit out the criteria for the simulation again
  cout << "\nCompleted Simulation with\n- " << a << " operators" 
    << "\n- handling " << c << " calls per minute\n- over "
    << hours << " hours...\n\n";

  // Spit out what
  cout << "- " << runs/60 << " hours " << runs%60 << " minutes processed\n";
  cout << "- " << count << " calls were handled by agents\n";
  if (hold.getInQueue())
    cout << "- "<< hold.getHoldSize() << " calls are still on hold\n";


  agent::printRepHead();
  // Print the stats from each agent
  for (int x=0; x<a; x++){
    agents.at(x).printReport();
  }
  for (int x=0; x<a-1; x++){
    agents.at(x).~agent();
  }
  agents.clear();
  cout << "\n\nSimulation complete.\n";

  return 0;
}

// class Queue

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

// class agent

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
