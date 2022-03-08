#ifndef RACER_H
#define RACER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Racer{
 public:
  Racer(); //Default constructor
  Racer(string, int, int); //Overloaded constructor
  string ToString() const{
    return "";
  };
  //Getters and setters for each Racer
  void SetValues(string, int, int);
  string GetName() const;
  void SetName(string);
  int GetNumber() const;
  void SetNumber(int);
  int GetSpeed() const;
  void SetSpeed(int);
  void SetIsCrashed(bool);
  bool GetIsCrashed() const;
  //Racer overloaded << operator
  friend ostream& operator<<(ostream&, Racer&);
 private:
  string m_name; //Name of racer
  int m_number; //Number of racer
  int m_speed; //Current speed of racer
  bool m_isCrashed; //If racer has crashed (true = crashed)
};

#endif
