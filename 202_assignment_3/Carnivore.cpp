//Filename: Carnivore.cpp
//name: Dan Ebisawa
//section:13
//date: 11/13/18
//description: cpp file for carnivore.h

#include"Carnivore.h"
#include"Animal.h"
#include"Lion.h"
#include<iomanip>
#include<cmath>
#include<string>
#include<cstdlib>

using namespace std;

Carnivore::Carnivore(){

}

Carnivore::Carnivore(Gender gender, int health, int age):Animal(gender,health,age){

}

bool Carnivore::eat(){
  int ageOfAnimal = getAge();

  if ((ageOfAnimal == 1)||(hunt() == true))
    {return true;}

  bool resultRandom = randomPercentBased(50);
  if (resultRandom == true)
    {return true;}
  
  return false;       
}
