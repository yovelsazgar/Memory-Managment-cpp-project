#pragma once
#include <string>
#include <vector>

using std::string;
using namespace std;

class JoinPolicy;
class Simulation;
class Agent;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    // **** RULE OF 5 ****
    Party(const Party& other);//Copy constructor
    Party& operator=(const Party &other); //Copy assignment
    Party(Party &&other);//Move constructor
    Party& operator=(Party &&other);//Move assign
    ~Party(); // Destructor

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getCounter();
    int getCol();
    void setCol(int k);
    void setCounter(int i);
    JoinPolicy& getPolicy();
    vector<int>& getAgentVector();
    vector<int>& getColVector();
    int getId();


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mCounter;
    vector<int> mAgeOffer;
    vector<int> mColOffer;
    int mCol;
    
};
