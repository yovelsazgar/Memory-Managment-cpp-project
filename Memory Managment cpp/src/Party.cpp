#include "Party.h"
#include <vector>
using namespace std;

#include "Agent.h"

#include "JoinPolicy.h"
#include <iostream>
using namespace ::std;


Party::Party(int id, string name, int mandates, JoinPolicy *jp) : 
mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mCounter(1),mAgeOffer(), mColOffer(), mCol(-1)
{

}
// **** RULE OF 5 ****
Party::Party(const Party& other):
mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), 
mCounter(other.mCounter) ,mAgeOffer(other.mAgeOffer), mColOffer(other.mColOffer), mCol(other.mCol)
{
    mJoinPolicy=other.mJoinPolicy->getPolicyType(); 
}
Party& Party::operator=(const Party &other) //Copy assignment
{
    if(&other != this)
    {
        this->mId = other.mId;
        this->mName = other.mName;
        this->mMandates = other.mMandates;
        this->mCol= other.mCol;
        this->mCounter = other.mCounter;
        this->mAgeOffer = other.mAgeOffer;
        this->mColOffer = other.mColOffer;
        delete mJoinPolicy;
        mJoinPolicy=other.mJoinPolicy->getPolicyType();
        this->mState = other.mState;
    }
    return *this;
}
Party:: Party(Party &&other)://Move constructor
mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), 
mCounter(other.mCounter) ,mAgeOffer(other.mAgeOffer), mColOffer(other.mColOffer), mCol(other.mCol)
{
    other.mJoinPolicy= nullptr;
}
Party& Party::operator=(Party &&other)//Move assignment
{
    this->mId = other.mId;
    this->mName = other.mName;
    this->mMandates = other.mMandates;
    this->mCol= other.mCol;
    this->mCounter = other.mCounter;
    this->mAgeOffer = other.mAgeOffer;
    this->mColOffer = other.mColOffer;
    delete mJoinPolicy;
    mJoinPolicy=other.mJoinPolicy->getPolicyType();
    this->mState = other.mState;
    other.mJoinPolicy= nullptr;
    return *this;
}
Party::~Party() //Destructor
{
    if(mJoinPolicy)
    {
        delete mJoinPolicy;
        mJoinPolicy = nullptr;
    }
}
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getId()
{
    return mId;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}
int Party:: getCol()
{
    return mCol;
}
void Party:: setCol(int k)
{
    mCol = k;
}
int Party:: getCounter(){
    return mCounter;
}
void Party:: setCounter(int i){
    mCounter=i;
}
JoinPolicy &Party:: getPolicy()
{
    return *mJoinPolicy;
}
vector<int>& Party::getAgentVector()
{
    return mAgeOffer;
}

vector<int>& Party::getColVector()
{
    return mColOffer;
}

void Party::step(Simulation &s)
{
    int numOfAgents=s.getAgents().size();
    if(getState() == CollectingOffers)
    {
        if(getCounter() > 2)
        {
            setState(Joined);
            int toCopy = mJoinPolicy->Chosen(mAgeOffer, s);// id of agent that offered most mandates
            int indexAgentInVector=0;
            for(unsigned int i=0;i<s.getAgents().size();++i){
                if(s.getAgents()[i].getId()==toCopy)
                {
                    indexAgentInVector = i;
                }
            }
            int coal = s.getAgents()[indexAgentInVector].getCol();
            Agent copiedAgent(s.getAgents()[indexAgentInVector] ,numOfAgents, mId, coal); //clone the agent
            mCol = coal; //update the party's coalition
            s.getAgents().push_back(copiedAgent); //insert the clone agent into the agents vector
            s.getColVector()[coal]+=mMandates; //update the number of mandates of the coalition
        }
        else{
            setCounter(getCounter()+1); //update the iteration counter
        }
    }
}
