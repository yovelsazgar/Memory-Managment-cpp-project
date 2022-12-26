#include "JoinPolicy.h"
#include <vector>
#include "Agent.h"
#include "Simulation.h"
#include <iostream>

using namespace std;
class Party;


JoinPolicy* MandatesJoinPolicy:: getPolicyType(){return new MandatesJoinPolicy;}

JoinPolicy* LastOfferJoinPolicy:: getPolicyType(){return new LastOfferJoinPolicy;}

int MandatesJoinPolicy:: Chosen(vector<int> ageOffer, Simulation &s){
  int max = 0;
  int agentIdToJoin;
  for(int x:ageOffer)
  {
    if(s.getColVector()[s.getAgents()[x].getCol()] > max) //check who is the col that has the highest mandates from the offers
    {
       max = s.getColVector()[s.getAgents()[x].getCol()];
       agentIdToJoin = x;
    }
  }
    return agentIdToJoin;
}
int LastOfferJoinPolicy:: Chosen(vector<int> ageOffer, Simulation &s)
{
  return ageOffer.back();
}
