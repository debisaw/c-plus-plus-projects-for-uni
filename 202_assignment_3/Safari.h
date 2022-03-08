//Title: Safari.h
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the header file for the simulation practicing polymorphism

#ifndef SAFARI_H_
#define SAFARI_H_

#include "Animal.h"
#include "Gazelle.h"
#include "Lion.h"
#include "Elephant.h"

#include <iostream>
#include <fstream>
#include <vector>


class Safari {
public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Safari();
  // Destructor
  // Preconditions: m_animals is populated
  // Postconditions: Deallocates animal object in memory
  ~Safari();
  // Name: loadAnimals
  // Desc - Loads each animals into m_animals from file
  // Preconditions - Requires file with valid dance data
  // Postconditions - m_animals is populated with animal pointers
  void loadAnimals(char*);
  // Name: simulateYear()
  // Desc - simulates a year in the safari for all the animals
  // Preconditions - Requires a populated m_animals
  // Postconditions - simulates a year in time each animal:
  // 1. has a chance to breed. If they are successful their offspring
  //    is added to m_animals
  // 2. lives a year
  void simulateYear();
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - m_animal has been populated
  // Postconditions - exits if user entered 3
  void mainMenu();
  // Name: simulate()
  // Desc - gets number of years to simulate and simulates for that number
  // Preconditions - m_animals is populated
  // Postconditions - Has simulated that number years and m_animals reflects changes
  void simulate();
  // Name: displayAnimals()
  // Desc - Displays all animals in m_animals ina formated fashion
  // Preconditions - m_animals is populated
  // Postconditions - N/A
  void displayAnimals();  
private:
  vector<Animal*> m_animals; // all animals in our simulation
};

#endif /* SAFARI_H_ */
