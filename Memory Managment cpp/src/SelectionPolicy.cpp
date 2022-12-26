#include "SelectionPolicy.h"
#include <vector>

using namespace std;
class Party;
class Agent;
class simulation;

SelectionPolicy* MandatesSelectionPolicy:: getSelectType(){return new MandatesSelectionPolicy;}

SelectionPolicy* EdgeWeightSelectionPolicy:: getSelectType(){return new EdgeWeightSelectionPolicy;}

Party& MandatesSelectionPolicy:: Select(Simulation &s, int idAgent)
{
  int max=0;
  int idPartyToSelect = -1;
  int idPartyOfAgent=s.getAgents().at(idAgent).getPartyId();
  for(int i=0; i < s.getGraph().getNumVertices(); ++i)
  {
    if(s.getGraph().getEdgeWeight(idPartyOfAgent, i) > 0 && s.getParty(i).getState() != Joined && s.getParty(i).getMandates() > max)
    {
      bool flag = false;
      int myCoallNumber=s.getParty(idPartyOfAgent).getCol();
      for(int x:s.getParty(i).getColVector()){
        if(x==myCoallNumber) //if the coalition has already offered
          flag=true;
      }
      if(flag == false) 
      {
        max = s.getParty(i).getMandates();
        idPartyToSelect = i;
      }
    }
  }
  if(idPartyToSelect == -1)
    return s.getParty(idPartyOfAgent);
  else
    return s.getParty(idPartyToSelect);
}

Party& EdgeWeightSelectionPolicy:: Select(Simulation& s, int idAgent){
  int max=0;
  int idPartyToSelect = -1;
  int idPartyOfAgent=s.getAgents().at(idAgent).getPartyId();
  for(int i=0; i < s.getGraph().getNumVertices(); ++i)
  {
    if(s.getGraph().getEdgeWeight(idPartyOfAgent, i) > max && s.getParty(i).getState() != Joined)
    {
      bool flag = false;
       int myCoallNumber=s.getParty(idPartyOfAgent).getCol();
      for(int x:s.getParty(i).getColVector()){
        if(x==myCoallNumber) //if the coalition has already offered
          flag=true;
      }
      if(flag == false)
      {
        max = s.getGraph().getEdgeWeight(idPartyOfAgent, i);
        idPartyToSelect = i;
      }
    }
  }
    
  
  if(idPartyToSelect == -1)
    return s.getParty(idPartyOfAgent);
  else
    return s.getParty(idPartyToSelect);
    
}

