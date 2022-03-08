//Title: Herbivore.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the Herbivores

#ifndef HERBIVORE_H_
#define HERBIVORE_H_

#include "Animal.h"

class Herbivore: public Animal {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Herbivore();
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Herbivore(Gender,int,int);
  // eat() - Tests if animal successfully ate.
  // - if the graze was a success or they are age 1 then true
  // otherwise they don't eat
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal ate or did not
  //                 in the course of the year
  bool eat();
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  virtual Animal* breed() = 0;
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the animal
  virtual string toString() = 0;
  // graze() - Tests if animal successfully grazed
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal successfully grazed
  virtual bool graze() = 0;
};

#endif /* HERBIVORE_H_ */
