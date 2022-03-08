//filename: Lion.cpp
//name: Dan Ebisawa
//section: 13
//desctiprion: cpp file for lion.h

#include"Animal.h"
#include"Lion.h"
#include"Carnivore.h"

#include<iomanip>
#include<string>
#include<cstdlib>

using namespace std;

Lion::Lion(Gender gender, int health, int age):Carnivore(gender,health,age){}

string Lion::toString(){
  return "Lion";
}

bool Lion::hunt(){
  int animalHealth = getHealth();
  int successHunt = animalHealth * 10 ; //success = health * 10%

  bool result = randomPercentBased (successHunt);

  if (result == true)
    {return true;}

  return false;
}

Animal* Lion::breed(){
  Gender gender = getGender();
  int animalAge = getAge();

  if (((animalAge == 3)||(animalAge ==4))&&(gender == FEMALE)){
    bool success = randomPercentBased(50);
    if (success == true){
      bool genderDetermine = randomPercentBased(50);
      Gender genderOffspring;
      switch (genderDetermine){
      case (true):
	{genderOffspring = MALE;
	  break;}
      case (false):
	{genderOffspring = FEMALE;
	  break;}
      }
      //return pointer to new object
      Animal *newLion = new Lion(genderOffspring,MAX_HEALTH,1);
      return newLion;
    }
  }
  return NULL;
}
