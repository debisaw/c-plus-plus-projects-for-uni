#ifndef TRUCK_H
#define TRUCK_H

#include "Racer.h"
const int TRUCK_SPEED = 150;

class Truck: public Racer{
 public:
  //Default constructor
  Truck();
  //Overloaded constructor
  Truck(string name, int number):Racer(name, number, TRUCK_SPEED){}
  //To String
  string ToString() const{
    return "Truck";
  }
  //Overloaded << operator (to be implemented)
  friend ostream& operator<<(ostream&, const Truck&);
};

#endif
