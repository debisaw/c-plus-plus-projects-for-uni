//filename: Safari.cpp
//name: dan Ebisawa
//section: 13
//date: 11/14/18
//description: cpp file for Safari

#include"Safari.h"
#include"Animal.h"
#include"Gazelle.h"
#include"Lion.h"
#include"Elephant.h"

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;

Safari::Safari(){
  cout<<"Safari program start!"<<endl;
}

Safari::~Safari(){
  //deallocate memory
  for (unsigned int i =0; i< m_animals.size();i++){
    delete m_animals[i];
    m_animals[i] = NULL;
    }
}

void Safari::loadAnimals(char* fileName){
  cout<<"loadAnimals"<<endl;
  cout<<fileName<<endl;
  ifstream animalData;
  animalData.open(fileName);
  int type,health,genderNum,age;
  Gender animalGender;
  //load animal data from text file
  if (animalData.is_open()){
    while (! animalData.eof()){
      animalData>>type>>genderNum>>health>>age;
      if(animalData.peek()=='\n')
	{animalData.ignore(5,'\n');}
      switch(genderNum){
      case (0):
	{animalGender = FEMALE;
	  break;}
      case (1):
	{animalGender = MALE;
	  break;}
      }
      //pushback to vector based on class type
      switch (type){
      case (0)://Lion
	{Animal *LionPtr = new Lion(animalGender,health,age);
	  m_animals.push_back(LionPtr);
	  break;
	}
      case (1)://Gazelle
	{Animal *GazellePtr = new Gazelle(animalGender,health,age);
	  m_animals.push_back(GazellePtr);
	  break;}
      case (2)://Elephant
	{Animal *ElephantPtr = new Elephant(animalGender,health,age);
	  m_animals.push_back(ElephantPtr);
	  break;}
      }//switch
    }//while oef()
  }else{//is open
    cout<<"file not open"<<endl;}
}

void Safari::simulateYear(){
  cout<<"inside simulateYear"<<endl;

  vector <Animal*> tempVec;
  for (unsigned i = 0; i<m_animals.size();i++){
    //new animal is born
    Animal *temp = m_animals[i] ->breed();
    if (temp !=NULL)
      {tempVec.push_back(temp);
	cout<<left<<setw(10)<<"Born: "
	    <<*(temp)<<endl;}
    //animal lives
    if(m_animals[i]->liveAYear()== true){
      tempVec.push_back(m_animals[i]);
      cout<<left<<setw(10)<<"Survived: "
	  <<*m_animals[i]<<endl;
    }else{//animal is dead
      cout<<left<<setw(10)<<"Died: "
	  <<*m_animals[i]<<endl;;
      delete m_animals[i];
	m_animals[i] = NULL;
	} 
  }//for
  //replace old vector with new one 
  m_animals = tempVec;
  
}

void Safari::mainMenu(){

  int userInput;
  //display main menu
  do{
    cout<<"1. Display Animals"<<endl;
    cout<<"2. Simulate"<<endl;
    cout<<"3. Quit"<<endl;
    cin>>userInput;
    //input validation
    while ((userInput>3)||(userInput<1))
      {cout<<"Invalid Input"<<endl;
	cout<<"please enter a valid number"<<endl;
	cin>>userInput;}
    
    switch(userInput){
    case (1):
      {displayAnimals();
	break;}
    case (2):
      {simulate();
	break;}
    }
  }while (userInput!=3);//exit program if user chose 3 
  
}


void Safari::simulate(){
  int userInput;
  cout<<"How many years would you like to simulate for? (at least 1)"<<endl;
  cin>>userInput;
  //input validation
  while (userInput <1)
    {cout<<"invalid input"<<endl;
      cout<<"please enter a valid number"<<endl;
      cin>>userInput;}
  
  for(int i =0; i<userInput;i++)
    {
      cout<<"Year: "<<i+1<<endl;
      simulateYear();
    }
}

void Safari::displayAnimals(){
  for(unsigned i=0; i<m_animals.size();i++){
    cout<<left<<setw(5)<<i+1;
    cout<<*(m_animals[i])<<endl;
  }
}
