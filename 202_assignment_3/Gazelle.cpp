//filename:Gazelle.cpp
//name: Dan Ebisawa
//date: 11/14/18
//description: cpp file for Gazelle.h

#include"Animal.h"
#include"Gazelle.h"
#include"Herbivore.h"

#include<iomanip>
#include<cstdlib>

using namespace std;

Gazelle::Gazelle(Gender gender, int health, int age):Herbivore(gender,health,age){}

string Gazelle::toString()
{ return "Gazelle";}

bool Gazelle::graze(){
  int ageAnimal = getAge();
  int healthAnimal = getHealth();

  if (ageAnimal <MAX_AGE){
    int successRate = healthAnimal *15;
    bool result = randomPercentBased(successRate);
    if (result == true)
      {return true;}
  }
  return false; 
}

Animal* Gazelle::breed(){
  Gender gender = getGender();
  int animalAge = getAge();
  if ((animalAge >1)&&(gender ==FEMALE)){
    bool success = randomPercentBased(30);
    if (success == true ){
      Gender genderOffspring;
      bool genderDetermine = randomPercentBased(50);
      switch (genderDetermine){
      case (true):
	{genderOffspring = MALE;
	  break;}
      case (false):
	{genderOffspring = FEMALE;
	  break;}  
      }
      //return pointer to new object
      Animal *newGazelle = new Gazelle(genderOffspring,MAX_HEALTH,1);
      return newGazelle;
    }
  }
  return NULL;
}
