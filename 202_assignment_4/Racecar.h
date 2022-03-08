#ifndef RACECAR_H
#define RACECAR_H

#include "Racer.h"
const int CAR_SPEED = 200;

class Racecar: public Racer{
 public:
  //Default constructor
  Racecar();
  //Overloaded constructor
  Racecar(string name, int number):Racer(name, number, CAR_SPEED){}
  //ToString
  string ToString() const{
    return "Racecar";
  }
  //Overloaded << operator (to be implemented);
  friend ostream& operator<<(ostream&, const Racecar&);
};

#endif
