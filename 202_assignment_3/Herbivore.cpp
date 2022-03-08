//fileName: Herbivore.cpp
//name: Dna Ebisawa
//section: 13
//Description: cpp file for Herbivore.h

#include"Animal.h"
#include"Herbivore.h"
#include"Gazelle.h"
#include"Elephant.h"
#include<iomanip>
#include<cmath>
#include<string>
#include<cstdlib>

using namespace std;

Herbivore::Herbivore(){}

Herbivore::Herbivore(Gender gender,int health,int age):Animal(gender,health,age){}

bool Herbivore::eat(){
  int ageOfAnimal = getAge();
  //success
  if ((ageOfAnimal == 1) || (graze() == true))
    {return true;}
  //fail
  return false;
}
