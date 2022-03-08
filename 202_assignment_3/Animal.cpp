
//TItle: Animal.cpp
//name : Dan Ebisawa
//date: 11/10/18
//section: 13
//Description: cpp file for Animal.h

#include<string>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include"Animal.h"
#include"Herbivore.h"
#include"Carnivore.h"
#include"Elephant.h"
#include"Lion.h"
#include"Gazelle.h"

using namespace std;

Animal::Animal(){
  //initialize variable
  m_gender = MALE;
  m_health = MAX_HEALTH;
  m_age = MAX_AGE;
}

Animal::Animal(Gender gender, int health, int age){
  //setter
  m_gender = gender;
  m_health = health;
  m_age = age;
}

//getter
Gender Animal::getGender(){
  return m_gender;
}

int Animal::getHealth(){
  return m_health;
}

int Animal::getAge(){
  return m_age;
}


bool Animal::liveAYear(){
  //return true if animal live, false if dead

  //check if aniaml ate food
  bool animalEat = eat();
  if (animalEat == false)
    {m_health --;}

    //50% to age(if the animal is old(5), it will not age)
  if (m_age<MAX_AGE){
  bool doesItAge = randomPercentBased(50);
  if (doesItAge == true)
    {m_age ++;}
  }
  
  //50% to decrease health 
  bool animalHealth = diminishHealth();
  if (animalHealth == false)//if animal health is less than 1
    {return false;}
  
  return true; //animal lives
}

bool Animal::diminishHealth(){
    bool doesHealthDecrease = randomPercentBased(50);
    if (m_health != 0){
      if(doesHealthDecrease == true)
	{m_health --;}}
    if (m_health <= 0)
      {return false;}
    return true;
}


ostream& operator<<(ostream& output, Animal& animal){
  string name = animal.toString();
  Gender gender = animal.getGender();
  int health = animal.getHealth();
  int age = animal.getAge();
  output<<left<<setw(15)<<name;
  switch (gender){
  case(FEMALE):
    {output<<setw(15)<<"Female";
      break;}
  case (MALE):
    {output<<setw(15)<<"Male";
	break;}
  }
  //display correct desciption based on number
  switch(age){
  case(1):
    {output<<setw(13)<<"Very Young(1)"<<"\t";
    break;}
  case(2):
    {output<<setw(13)<<"Young(2)"<<"\t";
      break;}
  case(3):
    {output<<setw(13)<<"Prime(3)"<<"\t";
      break;}
  case(4):
    {output<<setw(13)<<"Middle(4)"<<"\t";
      break;}
  case(5):
    {output<<setw(13)<<"Old(5)"<<"\t";
      break;}
  }//switch age

  switch(health){
  case(0):
    {output<<"Dead(0)"<<"\t";
      break;}
  case(1):
    {output<<"Bad(1)"<<"\t";
      break;}
  case(2):
    {output<<"Diminishing(2)"<<"\t";
      break;}
  case(3):
    {output<<"Poor(3)"<<"\t";
      break;}
  case(4):
    {output<<"Ok(4)"<<"\t";
      break;}
  case(5):
    {output<<"Average(5)"<<"\t";
      break;}
  case(6):
    {output<<"Good(6)"<<"\t";
      break;}
  case(7):
    {output<<"Very Good(7)"<<"\t";
	break;}
  case(8):
    {output<<"Great(8)"<<"\t";
      break;}
  case(9):
    {output<<"Excellent(9)"<<"\t";
      break;}
  case(10):
    {output<<"Perfect(10)"<<"\t";
      break;}
  }//switch health
  return output;
}



bool Animal::randomPercentBased(int percentNum){
  int randNum = rand() % 100 + 1 ;
  //test the probability of getting a number less than the parameter int number
  //return true(success) if the random nunber is less, else return false(fail).
  if (randNum <= percentNum)
    {
      return true;
    }
  return false; 
}



//virtual bool Animal::eat () = 0;
//virtual Animal* Animal::breed() = 0;
