#include "Agent.h"
#include <vector>
#include "SelectionPolicy.h"
#include <iostream>

using namespace std;
class Party;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) :
 mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCol(-1)
 {

 }

Agent::Agent(const Agent& other, int size, int partyIdChosen, int col): // Clone the agent
mAgentId(size), mPartyId(partyIdChosen), mSelectionPolicy(nullptr), mCol(col)
{
    mSelectionPolicy=other.mSelectionPolicy->getSelectType();
}
// **** RULE OF 5 ****
Agent::Agent(const Agent& other) :// Copy Constructor
 mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCol(other.mCol)
{
    mSelectionPolicy=other.mSelectionPolicy->getSelectType();
}
Agent& Agent::operator=(const Agent &other) // //Copy assignment operator
{
    if(&other!=this){
        this->mAgentId=other.mAgentId;
        this->mPartyId=other.mPartyId;
        delete mSelectionPolicy;
        mSelectionPolicy=other.mSelectionPolicy->getSelectType();
        this->mCol=other.mCol;
    }
    return *this;
}

Agent::Agent(Agent &&other)://Move constructor
mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCol(other.mCol)
{
    other.mSelectionPolicy = nullptr;
}
Agent& Agent::operator=(Agent &&other)//Move assignment operator
{
    this->mAgentId=other.mAgentId;
    this->mPartyId=other.mPartyId;
    delete mSelectionPolicy;
    this->mSelectionPolicy= other.mSelectionPolicy;
    this->mCol=other.mCol;
    other.mSelectionPolicy = nullptr;
    return *this;
}
Agent::~Agent() //Destructor
{
    if(mSelectionPolicy)
    {
        delete mSelectionPolicy;
        mSelectionPolicy=nullptr;
    }
}
int Agent::getId() const
{
    return mAgentId;
}

SelectionPolicy &Agent:: getSelectedPolicy()
{
    return *mSelectionPolicy;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCol() const
{
    return mCol;
}

void Agent:: setCol(int k)
{
    mCol = k;
}

void Agent::step(Simulation &sim)
{
    Party& toSelect = mSelectionPolicy-> Select(sim, mAgentId); //the party to be selected
    if(toSelect.getId() != this->getPartyId()) //if there is party to select
    {
        if(toSelect.getState() == Waiting)
        {
            toSelect.setState(CollectingOffers);
        }
        toSelect.getAgentVector().push_back(mAgentId); //insert the agent to the party's offers vector
        toSelect.getColVector().push_back(mCol);
    }
}
