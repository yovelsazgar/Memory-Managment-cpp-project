#pragma once
#include "Agent.h"
#include "Party.h"
#include "Simulation.h"

class JoinPolicy {
  public:
  virtual JoinPolicy* getPolicyType() =0;
  virtual int Chosen(vector<int> offer, Simulation &s)=0;
  virtual~JoinPolicy() {};
};

class MandatesJoinPolicy : public JoinPolicy {
  public:
  JoinPolicy* getPolicyType();
  int Chosen(vector<int> offer, Simulation &s);
};

class LastOfferJoinPolicy : public JoinPolicy {
  public:
  JoinPolicy* getPolicyType();
  int Chosen(vector<int> offer, Simulation &s);
};