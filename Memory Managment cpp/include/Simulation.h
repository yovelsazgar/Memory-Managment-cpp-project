#pragma once
#include <vector>
#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;


class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    Graph &getGraph();
    const vector<Agent> &getAgents() const;
    vector<Agent> &getAgents();
    const Party &getParty(int partyId) const;
    Party &getParty(int partyId);
    const vector<vector<int>> getPartiesByCoalitions() const;
    vector<int> &getColVector();

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<int> mCoalition;
};
