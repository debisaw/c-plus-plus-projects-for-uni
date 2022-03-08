//Title: driver.cpp
//Author: Nadja Bzhilyanskya
//Date: 9/16/2018
//Description: This is the driver for project 4 practicing polymorphism

#include "Safari.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argv, char* argc[]){
  //load file from command line argument
  if(argv != 2){
    cout << "Invalid number of parameters..." << endl;
    return -1;
  }
  
  cout << "Loading file: " << argc[1] << endl << endl;
  
  //Make new safari load file and run program
  Safari s;
  s.loadAnimals(argc[1]);
  s.mainMenu();
  
  return 0;
}
