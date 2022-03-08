//file: Formula.cpp
//name: Dan Ebisawa
//data: 12/5
//description: cpp file for formula, a child class of racer

#include "Formula.h"
#include "Racer.h"

#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
//default constructor
Formula::Formula(){
  SetValues("",1,220);
}
//overloaded operator
ostream& operator<<(ostream& out, const Formula& car){
  out<<car.ToString()<<" ";
  if(!car.GetIsCrashed()){
    out<<car.GetName()<<"(# "<<car.GetNumber()<<") going "
       <<car.GetSpeed()<<" MPH";
  }else{
    out<<car.GetName()<<" crashed and it is out of the race.";
  }
  return out;
}
