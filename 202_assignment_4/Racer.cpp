//file: racer.cpp
//name: Dan Ebisawa
//date 12/5
//description: cpp file for parent class Racer

#include "Racer.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

//default constuctor
Racer::Racer(){
  m_name ="";
  m_number = 0;
  m_speed = 0;
  m_isCrashed = false;
}

//overloaded constructor
Racer::Racer(string name, int numberRacer, int numberSpeed){
  m_name = name;
  m_number = numberRacer;
  m_speed = numberSpeed;
}

//Getter and Setter
void Racer::SetValues(string name, int numberRacer, int numberSpeed){
  m_name = name;
  m_number = numberRacer;
  m_speed = numberSpeed;
}

string Racer::GetName() const{
  return m_name;
}

void Racer::SetName(string name){
  m_name = name;
}

int Racer::GetNumber() const{
  return m_number;
}

void Racer::SetNumber(int num){
  m_number = num;
}

int Racer::GetSpeed() const{
  return m_speed;
}

void Racer::SetSpeed(int num){
  m_speed = num;
}

void Racer::SetIsCrashed(bool crash){
  m_isCrashed = crash;
}

bool Racer::GetIsCrashed() const{
  return m_isCrashed;
}
//overloaded operator
ostream& operator<<(ostream& out, Racer& racer){
  string name = racer.m_name;
  int number = racer.m_number;
  int speed = racer.m_speed;
  bool crash = racer.m_isCrashed;

  out<<name<<" ";
  if(crash ==false ){
    out<<name<<"(# "<<number<<") going "
       <<speed<<" MPH";
  }else{
    out<<name<<" crashed and it is out of the race.";
  }
  return out;
}
