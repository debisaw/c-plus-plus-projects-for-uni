//filename: Truck.cpp
//name: Dan Ebisawa
//data: 12/5
//description cpp file for truck. a child class of racer

#include"Racer.h"
#include"Truck.h"

#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;
//default constuctor
Truck::Truck(){
  SetValues("",1,150);
}
//overloaded operator
ostream& operator<<(ostream& out, const Truck& car){
  out<<car.ToString()<<" ";
  if(!car.GetIsCrashed()){
    out<<car.GetName()<<"(# "<<car.GetNumber()<<") going "
       <<car.GetSpeed()<<" MPH";
  }else{
    out<<car.GetName()<<" crashed and it is out of the race.";
  }
  return out;
}
