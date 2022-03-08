//Title: Gazelle.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the child class Gazelle

#ifndef GAZELLE_H_
#define GAZELLE_H_

#include "Herbivore.h"

class Gazelle: public Herbivore {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Gazelle();
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Gazelle(Gender,int,int);
  
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // - If female and age > 1 there is a 30% chance
  // - otherwise false
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  Animal* breed();
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the animal
  string toString();  
  // graze() - Tests if animal successfully graze
  // - if the age is not 5 than chance is health*15%
  // - otherwise it is false
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal successfully graze
  bool graze();
};

#endif /* GAZELLE_H_ */
