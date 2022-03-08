#ifndef FORMULA_H
#define FORMULA_H

#include "Racer.h"
const int FORMULA_SPEED = 220;

class Formula: public Racer{
 public:
  //Default Constructor
  Formula();
  //Overloaded Constructor
  Formula(string name, int number):Racer(name, number, FORMULA_SPEED){}
  //ToString
  string ToString() const{
    return "Formula";
  }
  //Overloaded << operator (to be implemented)
  friend ostream& operator<<(ostream&, const Formula&);
};

#endif
