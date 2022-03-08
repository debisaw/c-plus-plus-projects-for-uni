//Title: Carnivore.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the carnivores

#ifndef CARNIVORE_H_
#define CARNIVORE_H_

#include "Animal.h"

class Carnivore: public Animal {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Carnivore();
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Carnivore(Gender,int,int);
  // eat() - Tests if animal successfully ate.
  // - if the hunt was a success or they are age 1 then true
  // otherwise they have a 50% chance
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal ate or did not
  //                 in the course of the year
  bool eat();
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  virtual Animal* breed() = 0;
  
protected:
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the animal
  virtual string toString() = 0;
  // hunt() - Tests if animal successfully hunted
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal successfully hunted
  virtual bool hunt() = 0;
};

#endif /* CARNIVORE_H_ */
