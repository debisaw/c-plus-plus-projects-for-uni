#ifndef RACE_H
#define RACE_H

#include "Racer.h"
#include "Racecar.h"
#include "Truck.h"
#include "Formula.h"
#include "Lqueue.h"

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

//Constant array for Racer names (regardless of type of racer)
const string RACERS [] = {"Mcdowell","Abdel","Wheeler","Romero","Barton","Wood","Azam","Munoz","Baird","Moon","Cantrell","Kent","Hunter","Reilly","Rivas","Copeland","Sharp","York","Henson","Sweet","Horne","Cook","Vincent","Pearson","Sabir","Palmer","Sanders","Lynn","Merrill","King","Holt","Preston","Zhang","Dominguez","Workman","Roach","Franklin","Walker","Maynard","Burris","Scott","Li","Barrett","Carson","Hutchinson","Sargent","Woodward","Leblanc","Lopez","Chen","Soto","Contreras","Sellers","Espinoza","Pierce","Masood","Giles","Garrison","Garner","Garza","Spencer","Hill","Spence","Maldonado","Hassan","Garrett","Harris","Petersen","Rogers","Hester","Molla","Murphy","Conner","Yassin","Sloan","Long","Terrell","Matthews","Whitley","Kim","Branch","Crane","Browning","Gentry","English","Mayo","Barnes","Molina","Dodson","Mccray","Hines","Malone","Whitehead","Mccarty","Marsh","Fletcher","Fuller","Aguirre","Pacheco","Ozer"};
			  
//Constant array for Racer numbers (regardless of type)
const int RACE_NUMS [] = {73,62,86,78,75,8,65,17,58,17,71,21,64,33,62,95,11,98,34,8,83,37,61,33,86,79,12,17,36,41,84,34,22,5,62,80,46,33,45,45,65,64,50,11,96,27,68,71,25,11,41,2,37,43,75,4,34,86,62,59,92,49,87,27,42,64,5,20,97,11,68,97,32,45,96,43,94,81,17,71,84,99,6,91,68,46,50,44,18,8,67,28,12,10,44,6,92,35,17,58};

const int MAX_RACERS = 100; //Max number of racers in race
const int MIN_RACERS = 2; //Min number of racers in race
const int RAND_SEED = 10; //Constant seed for program (srand(RAND_SEED) in Race const.
const int SPEED_MOD = 15; //Percentage change for each lap (15%)

template <class T>
class Race{
public:
  // Name: Race (Default Constructor)
  // Preconditions: Creates a new race using a specific type of
  //                racer (racecar, truck, or formula 1
  // Postconditions: Asks how many cars in the race, inserts specific racer in race
  //                 and starts race. Also, srand(RAND_SEED) in constructor.
  Race();
  // Name: EnterRace
  // Preconditions: Has a race
  // Postconditions: Pushes the specific racer into the race
  void EnterRace(T newEntrant);
  // Name: StartRace
  // Preconditions: Has a race
  // Postconditions: Manages a race
  // Requests number of laps.
  // For each lap, checks to see if they crash (calls CheckCrash)
  // Then compares speed of each racer, if one racer is faster, swaps racers
  // At the end of chosen number of laps, the winner is who is in front
  void StartRace();
  // Name: GetRandomRacer
  // Preconditions: Has an array of names and numbers
  // Postconditions: Returns a random number from array of names/numbers
  int GetRandomRacer();
  // Name: CheckCrash
  // Preconditions: Has a race
  // Postconditions: Checks if a racer crashes (1/200 chance), if they crash speed = 0
  //          SetIsCrashed changes, Indicates crash, moves crashed racer to end of race
  void CheckCrash(int);
  // Name: RacerSpeed
  // Preconditions: Has a race and racers left in race
  // Postconditions: Calculates updated speed for a specific racer each lap
  void RacerSpeed(int);
  // Name: DisplayRacers
  // Preconditions: Has a race and racers left in race
  // Postconditions: Displays each racer in race (including if they crashed)
  void DisplayRacers();
private:
  Lqueue<T> race;
};

#endif

//***************************************************************************
//***********************Implement Race Here*********************************


//Don't forget to seed srand with 10 srand(RAND_SEED)

template<class T>
//default constructor
Race<T>::Race(){

  srand(RAND_SEED);
  int userNum =0;
  cout<<"welcome to UMBC Racing simulator :)"<<endl;
  cout<<"How many racers would you like in the race? (2-100)"<<endl;
  cin >> userNum;
  while ((userNum < MIN_RACERS)||(userNum > MAX_RACERS)){ // input validation
    cout<<"invalid input"<<endl;
    cout<<"How many racers would you like in the race? (2-100)"<<endl;
    cin>>userNum;
  }
  //add cars
  for (int i = 0; i< userNum; i++){
    int racerNum = GetRandomRacer();
    T racer(RACERS[racerNum],RACE_NUMS[racerNum]);
    EnterRace(racer);
  }
  cout<<"Pole Positions"<<endl;
  DisplayRacers();
  StartRace();
}

template <class T>
void Race<T>::EnterRace(T newEntrant){
  race.Push(newEntrant);
}

template< class T>
void Race<T>::StartRace(){
  int userNum;
  cout<<"How many laps would you like to do? (1 - 1000)"<<endl;
  cin>>userNum;
  while ((userNum<1)||(userNum >1000)){//input validation
    cout<<"invalid input"<<endl;
    cout<<"How many laps would you like to do? (1 - 1000)"<<endl;
    cin>>userNum;
  }
  
  //race simulation 
  for (int i = 0; i < userNum;i++){//for loop for laps
    cout<<"Laps: "<<i+1<<endl;
    for (int j = 0; j< race.GetSize(); j++){//for loop for racer
      RacerSpeed(j);
      CheckCrash(j);
    }
    
    for (int i =0; i< race.GetSize(); i++){//loop in case it need to swap multiple locations
      for (int i = 1; i< race.GetSize();i++){//swap locations
	if (race[i].GetSpeed() > race[i-1].GetSpeed()){
	  race.Swap(i);
	}}}
    
    DisplayRacers();
  }//end loop for laps
  
  cout<<"The winner of the racer is" << race.Front()<<endl;
}

template<class T>
int Race<T>::GetRandomRacer(){
  int randNum;
  randNum = rand() % 100+ 1;
  return randNum;
}

template<class T>
void Race<T>::CheckCrash(int racerNum){
  //crashes at chance of 1/200
  int carCrashPercent = rand() % 200 + 1 ;
  
  if (race[racerNum].GetIsCrashed()==false){
    if (carCrashPercent == 1){
      race[racerNum].SetIsCrashed(true);
      race[racerNum].SetSpeed(0);
      cout<<race[racerNum].GetName()<<" Crashed!";
      race.RemoveInsertEnd(racerNum);
	}}
}

template<class T>
void Race<T>::RacerSpeed(int racerNum){
  int currentSpeed = race[racerNum].GetSpeed();
  double calcModifier = rand() % SPEED_MOD;
  if(rand() % 2){
    race[racerNum].SetSpeed(currentSpeed + (currentSpeed * (calcModifier/100)));
  }else{
    race[racerNum].SetSpeed(currentSpeed - (currentSpeed * (calcModifier/100)));
  }
}

template<class T>
void Race<T>::DisplayRacers(){
  int LqueueSize = race.GetSize();
  for (int i = 0; i< LqueueSize; i++){
    cout<<race[i]<<endl; }
}
