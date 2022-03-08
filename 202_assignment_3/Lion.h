//Title: Lion.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the parent class Animal
#ifndef LION_H_
#define LION_H_

#include "Carnivore.h"

class Lion: public Carnivore {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Lion();
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Lion(Gender gender,int health,int age);
  
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // - If female and age 3 or 4 there is a 50% chance
  // - otherwise false
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  Animal* breed();
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns a string of the name of the animal
  string toString();
  // hunt() - Tests if animal successfully hunted
  // - if the age > 1 than chance is health*10%
  // - otherwise false
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal successfully hunted
  bool hunt();
};

#endif /* LION_H_ */
