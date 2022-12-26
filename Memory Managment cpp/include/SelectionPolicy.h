#pragma once
#include "Simulation.h"

class Party;
class Simulation;
class Agent;

class SelectionPolicy {
  public:
  virtual Party& Select(Simulation &s, int id) =0;
  virtual SelectionPolicy* getSelectType() =0;
  virtual ~SelectionPolicy() {};

 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
  public:
  SelectionPolicy* getSelectType();
  Party& Select(Simulation &s, int id);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
  public:
  Party& Select(Simulation &s, int id);
  SelectionPolicy* getSelectType();
 };