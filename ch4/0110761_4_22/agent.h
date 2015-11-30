#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

class agent{
  public:
    agent(double, int);

    static bool callSort(agent lhs, agent rhs){
      return (lhs.calls < rhs.calls);
    }

    static bool IDsort(agent lhs, agent rhs){
      return (lhs.agentID < rhs.agentID);
    }

    int getAgentID();

    double getSkill();

    bool getAvail();
    int getNextAvail();
    void decNextAvail();

    double getActiveTime();
    void incActiveTime();

    double getIdleTime();
    void incIdleTime();

    double getEfficiency();

    void giveCall();
    void endCall();

    int getCallsCount();

    static void printRepHead();
    void printReport();

    ~agent();

  protected:
    int calls;
    int agentID;

  private:
    bool avail;
    int skill;
    int nextAvail;
    double activeTime;
    double idleTime;

};

#endif
