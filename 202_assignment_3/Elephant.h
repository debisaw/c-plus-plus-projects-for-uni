//Title: Elephant.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the child class Elephant

#ifndef ELEPHANT_H_
#define ELEPHANT_H_

#include "Herbivore.h"

class Elephant: public Herbivore {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Elephant();
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Elephant(Gender,int,int);  
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // - If female and age > 2 there is a 40% chance
  // - otherwise false
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  Animal* breed();
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the animal
  string toString();
  // graze() - Tests if animal successfully graze
  // - 95% chance of success
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal successfully graze
  bool graze();
};

#endif /* ELEPHANT_H_ */
