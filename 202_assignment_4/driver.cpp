#include "Race.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main () {
  int type = 0;
  while (type != 4){
    do{
      cout << "What type of vehicle would you like to race?" << endl;
      cout << "1. Cars" << endl;
      cout << "2. Trucks" << endl;
      cout << "3. Formula 1" << endl;
      cout << "4. Exit" << endl;
      cin >> type;
    }while(type<1 && type>4);
    
    switch(type){
    case 1:{
      Race<Racecar> myRace;
      break;
    }
    case 2:{
      Race<Truck> myRace;
      break;
    }
    case 3:{
      Race<Formula> myRace;
      break;
    }
    }
  }
  cout << "Thank you for racing today!" << endl;
  return 0;
}
