//Title: Animal.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the parent class Animal

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

//enumerated type for gender
enum Gender { FEMALE,MALE };

//Constants
const int MAX_HEALTH = 10;
const int MAX_AGE = 5;

class Animal {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: A simple object is created (like an animal was born)
  Animal();
  
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Animal (Gender,int health ,int age);
  
  // Destructor - virtual (implement in child classes)
  // Preconditions: Animal object in memory
  // Postconditions: Deallocates animal object in memory
  virtual ~Animal(){};
  
  // getGender() - returns the gender of animal
  // Preconditions: m_gender is set
  // Postconditions: returns an enum Gender referring to which gender
  Gender getGender();
  
  // getHealth() - returns the health of animal
  // Preconditions: m_health is set
  // Postconditions: returns an int referring to health 1 - MAX_health

  int getHealth();
  
  // getAge() - returns the age of animal
  // Preconditions: m_age is set
  // Postconditions: returns an int referring to age 1- MAX_AGE
  int getAge();
  
  // liveAYear() - changes parameters based on 1 year of life
  // - 50% chance that health diminishes
  // - if Eat() is false health diminishes
  // - 50% chance of aging
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal lives
  bool liveAYear();
  
  // diminishHealth() - take one from health
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal lives
  bool diminishHealth();
  
  // breed() - if an animal successfully produces offspring it returns a pointer to it
  // Preconditions: all variables are set valid
  // Postconditions: returns an pointer to a new animal or NULL
  virtual Animal* breed() = 0;
  
  // eat() - Tests if animal successfully ate
  // Preconditions: all variables are set valid
  // Postconditions: returns an bool of whether animal ate or did not
  //                 in the course of the year
  virtual bool eat() = 0;
  
  // Overloaded << - Prints the credentials of an animal
  // Preconditions: all variables are set valid
  // Postconditions: returns an ostream with output of animal
  friend ostream& operator<<(ostream&, Animal&);
  
  // randomPercentBased (Helper function)
  // Precondition: Given int to "pass"
  // Description: This function is used to see if a certain random event occurs
  //              A random number 1-100 is compared to the int passed
  //              If the random number is less than the passed value, return true
  //              Else return false (30 = 30%, 70 = 70%)
  // Postcondition: Returns boolean
  static bool randomPercentBased(int); 

protected:
  // toString() - a string representation of the animal
  // Preconditions: all variables are set valid
  // Postconditions: returns an string describing the animal
  virtual string toString() = 0;
private:
  int m_health; 		//1-10, 0 means they die
  int m_age;			//1-5, after 5 you die
  Gender m_gender;		//female or an male
};

#endif /* ANIMAL_H_ */


