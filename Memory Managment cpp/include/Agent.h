#pragma once
#include <vector>

class SelectionPolicy;
class Simulation;
class Graph;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    // **** RULE OF 5 ****
    Agent(const Agent& other, int size,int partyIdChosen, int col);//Clone Function
    Agent(const Agent& other); // Copy Constructor
    Agent& operator=(const Agent &other); //Copy assignment
    Agent(Agent &&other);//Move constructor
    Agent& operator=(Agent &&other);//Move assignment
    ~Agent();// Destructor

    char selectionType();
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    int getCol() const;
    void setCol(int k);
    SelectionPolicy& getSelectedPolicy();

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCol;
};
