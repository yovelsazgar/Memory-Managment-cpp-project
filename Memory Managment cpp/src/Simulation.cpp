#include "Simulation.h"
#include "Agent.h"
#include <vector>
#include <iostream>

using namespace :: std;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalition()
{
    for(unsigned int i = 0; i < mAgents.size(); ++i)
    {
        this->getParty(mAgents[i].getPartyId()).setCol(i);
        mCoalition.push_back(this->getParty(mAgents[i].getPartyId()).getMandates());
        mAgents[i].setCol(i);
    }
}
void Simulation::step()
{
    for(int i =0; i < mGraph.getNumVertices(); ++i)
    {
        mGraph.getParty(i).step(*this);
    }
    for(unsigned int i=0; i < getAgents().size(); ++i)
    {
        getAgents()[i].step(*this);
    }
}


bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    bool allJoined = true;
    for(int i =0; i < mGraph.getNumVertices(); ++i){
        if(mGraph.getParty(i).getState()!=Joined){
            allJoined = false;
            break;
        }
    }
    bool bigCol=false;
    for(unsigned int i=0; i<mCoalition.size();++i){
        if(mCoalition[i]>60)
        {
            bigCol=true;
        }
    }
    if(allJoined==true || bigCol==true)
        return true;
    else
        return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}
vector<Agent> &Simulation::getAgents()
{
    return mAgents;
}

vector<int> &Simulation::getColVector()
{
    return mCoalition;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int partyId)
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    vector<vector<int>> partiesByCoalitions;
    for(unsigned int i=0; i<mCoalition.size(); i++){
        vector<int> makeVec;
        partiesByCoalitions.push_back(makeVec);
    }
    for(unsigned int i=0;i< mAgents.size(); i++){
        partiesByCoalitions.at(mAgents[i].getCol()).push_back(mAgents[i].getPartyId());
    }
    return partiesByCoalitions;
}
