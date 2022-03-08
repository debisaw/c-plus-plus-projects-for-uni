//filename: Elephant.cpp
//name: Dan Ebisawa
//date:11/14/18
//Description: cpp file for Elephant.h

#include"Herbivore.h"
#include"Elephant.h"
#include"Animal.h"

#include<iomanip>
#include<cstdlib>

using namespace std;

Elephant::Elephant(Gender gender, int health, int age):Herbivore(gender,health,age){}

string Elephant::toString(){
  return "Elephant";
}

bool Elephant::graze(){
  bool result = randomPercentBased(95);
  if (result==true)
    {return true;}
  return false;
}

Animal* Elephant::breed(){
  Gender gender = getGender();
  int animalAge = getAge();

  if ((animalAge > 2)&&(gender == FEMALE)){
    bool success = randomPercentBased(40);
    if (success == true){
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
      Animal *newElephant = new Elephant(genderOffspring,MAX_HEALTH,1);
      return newElephant;
    }
  }
  return NULL;
}
