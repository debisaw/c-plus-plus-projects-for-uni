//file: racecar.cpp
//name: Dan Ebisawa
//Date: 12/5
//description; cpp file for racecar, a child class of Racer

#include "Racer.h"
#include "Racecar.h"

#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
//default constructor
Racecar::Racecar(){
  SetValues("",1,200);
}
//overloaded operator
ostream& operator<<(ostream& out, const Racecar& car){
  out<<car.ToString()<<" ";
  if(!car.GetIsCrashed()){
    out<<car.GetName()<<"(# "<<car.GetNumber()<<") going "
       << car.GetSpeed()<<" MPH";
  }else{
    out<<car.GetName()<<" crashed and it is out of the race.";
  }
  return out;
}
