//filename: Game.cpp
//name: Dan Ebisawa
//date: 10/15/18
//section: 8
//description: game.cpp

#include "Game.h"
#include "Hero.h"
#include "Dance.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

Game::Game()
{
  char cStringName[30];
  
  srand(time(NULL));
  //load dances and hero(add 5 random dances) from text file to vector
  LoadDances();
  LoadHeroes();

  cout<<"Welcome to Fortnite Dance Royale"<<endl;
  cout<<"\n";
  cout<<"What is your main characters name?"<<endl;
  cin.getline(cStringName,30);
  
  string protagonistName(cStringName);
  
  m_name = protagonistName;
  m_myHero.SetName(protagonistName);
  m_myHero.SetIsPlayer(PLAYER);
  //add "Dance Move" into players dance 
  m_myHero.AddDance(m_dances[0]);
}

void Game::LoadDances()
{
  ifstream dancesInStream;
  dancesInStream.open(PROJ2_DANCES.c_str());
  string name;
  int difficulty;
  int style;
  
  //load dance from text file. 
  if (dancesInStream.is_open())
    {
      while(getline(dancesInStream,name,','))
	{
	  dancesInStream >> style;
	  if (dancesInStream.peek()==',')
	    dancesInStream.ignore(10,',');
	  dancesInStream >> difficulty;
	  if (dancesInStream.peek()=='\n')
	    dancesInStream.ignore(10,'\n');
	  m_dances.push_back(Dance(name,style,difficulty,MIN_LEVEL));
	}
    } else{
    cout <<"dance file did not open"<<endl;
  }
  
  dancesInStream.close();
}

void Game::LoadHeroes()
{
  string heroName;
  
  ifstream heroesInStream;
  heroesInStream.open(PROJ2_HEROES);
  //load heroname from text file
  if (heroesInStream.is_open())
    {
      while (!heroesInStream.eof())
	{
	  heroesInStream >> heroName;
	  m_heroes.push_back(Hero(heroName,CPU));
	}
    }else{
    cout <<"file did not open"<<endl;
  }

  heroesInStream.close();

  int mHeroesSize;
  int randomNum;
  mHeroesSize = m_heroes.size();
  //add 5 random dance moves to each CPU hero
  for (int i=0;i < mHeroesSize;i++ )
    {
      for (int j=0;j<NUM_DANCES;j++ )
	{
	  randomNum = (rand()% m_dances.size());
	  //when user have same dance move 
	  while (m_heroes[i].CheckDance(m_dances[randomNum].m_name) == true)
	    randomNum = (rand()% m_dances.size());
	  //else, add dance
	  m_heroes[i].AddDance(m_dances[randomNum]);
	}
    }
}

void Game::DisplayMyDances()
{
  m_myHero.DisplayDances();
}
void Game::StartGame()
{
  int userNum;
  cout<<"\n";
  cout<<setw(20)<<"Game Start!"<<endl;
  cout<<"\n";
  //if user enter 5(quit), switch will not run
  while (userNum !=MAX_INPUT_NUM)
    {
      userNum = MainMenu();
      switch(userNum)
	{
	  //display dance move
	case 1:
	  cout<<"\n";
	  cout<<m_name<< "'s dance moves"<<endl;
	  DisplayMyDances();
	  break;
	  
	  //train dance move
	case 2:
	  TrainDance();
	  break;

	  //learn new dance
	case 3:
	  LearnNewDance();
	  break;
	  //enter tournament
	case 4:
	  EnterTournament();
	  break;
	}
    }
  cout<<"thank you for playing the game"<<endl;
}

int Game::MainMenu()
{
  int userNum;
  cout<<"What would you like to do?"<<endl;
  //display main menu
  for (int i =1; i<= 5; i++)
    {
      switch(i)
	{
	case 1:
	  cout<< i <<". Display Dances"<<endl;
	  break;
	case 2:
	  cout<< i <<". Train Dance Move"<<endl;
	  break;
	case 3:
	  cout<< i <<". Learn New Dance"<<endl;
	  break;
	case 4:
	  cout<< i <<". Enter Dance Tournament"<<endl;
	  break;
	case 5:
	  cout<< i <<". Quit"<<endl;
	  break;
	}
    }
  cin>>userNum;
  return userNum;
}

void Game::TrainDance()
{
  int userNum;
  int successOrFail;
  int danceLevel;
  cout<<"Which dance move would you like to train?"<<endl;

  DisplayMyDances();
  //input validation if user enter num more than known dance move(s)
  cin>>userNum;
  while (!(userNum <= m_myHero.GetDanceCount()) || userNum==0)
    {
      cout<<"Invadid input"<<endl;
      cout<<"Which dance move would you like to train?"<<endl;
      DisplayMyDances();
      cin>>userNum;
    }
  //training   
  danceLevel = m_myHero.GetDanceLevel(userNum-1);
  if (danceLevel < MAX_LEVEL)
    {
      //50% chance 
      successOrFail = rand() % 2 + 1;
      cout<<successOrFail<<endl;
      switch(successOrFail)
	{
	case 1:
	  cout<<"Training failed :("<<endl;
	  break;
	case 2 :
	  cout<<"Training Success :}"<<endl;
	  m_myHero.IncreaseDance(danceLevel,userNum-1);
	  break;
	}
    }else{
    cout<<"the dance is already at max level"<<endl;
    cout<<"\n"<<endl;
  }
}

void Game::LearnNewDance()
{
  int userNum;
  int numDance;
  int randNumForSwitch;
  int randNumForDance;
  
  numDance = m_myHero.GetDanceCount();
  //check if user has less than 5 dance moves. else/ will not run code below 
  if ( numDance < NUM_DANCES)
    {
      //menu
      cout<<"What Difficulty of dance would you like to learn"<<endl;
      cout<<"1. Easy"<<endl;  
      cout<<"2. Difficult"<<endl;
      cout<<"3. Epic"<<endl;
      cin>> userNum;
      
      //input validation
      while (!(userNum <= MAX_LEARN_MOVES_INPUT)||(userNum <=0))
	{
	  cout<<"invalid input"<<endl;
	  cout<<"please enter a new value"<<endl;
	  cin>>userNum;
	}
      
      //learn new move 
      bool canAddDance;
      canAddDance = false;
      switch(userNum)
	{
	  //easy dance move 
	case 1:
	  randNumForSwitch = rand() % 10+1;
	  //90% chance to not get 1
	  if (!(randNumForSwitch == 1))
	    {
	      //find easy dance moves and check if user do not have it yet 
	      while (canAddDance == false )
		{
		  randNumForDance = (rand()% m_dances.size());	      
		  while (!(m_dances[randNumForDance].m_difficulty == EASY_DANCE))
		    {
		      //find new dance move if dance is not easy
		      randNumForDance = (rand()% m_dances.size());
		    }
		  //unless that move is not already learnt, bool flag  do not change
		  if (m_myHero.CheckDance(m_dances[randNumForDance].m_name) == false)
		    {
		      canAddDance = true;
		      cout<<"training success :)"<<endl;
		      m_myHero.AddDance(m_dances[randNumForDance]);
		    }
		}//while false
	    }else{
	    cout<<"training failed"<<endl;}
	  break;
	  
	  //difficult move
	case 2:
	  randNumForSwitch = rand() % 2+1;
	  //50% chance to not get 1 (code is identical to above, changed the constant)
	  if (!(randNumForSwitch == 1))
	      {while (canAddDance == false )
		{randNumForDance = (rand()% m_dances.size());
		  while (!(m_dances[randNumForDance].m_difficulty == DIFFICULT_DANCE))
		    randNumForDance = (rand()% m_dances.size());
		  if (m_myHero.CheckDance(m_dances[randNumForDance].m_name) == false)
		    { canAddDance = true;
		      cout<<"training success:)"<<endl;
		      m_myHero.AddDance(m_dances[randNumForDance]);
		    }}
	    }else{
	    cout<<"training failed"<<endl;}
	  break;
	  
	  //epic move
	case 3:
	  randNumForSwitch = rand() % 10+1;
	  //10% to get 1
	  if (randNumForSwitch == 1)
	    {while (canAddDance == false )
		{randNumForDance = (rand()% m_dances.size());
		  while (!(m_dances[randNumForDance].m_difficulty == EPIC_DANCE))
		    randNumForDance = (rand()% m_dances.size());
		  if (m_myHero.CheckDance(m_dances[randNumForDance].m_name) == false)
		    { canAddDance = true;
		      cout<<"training success:)"<<endl;
		      m_myHero.AddDance(m_dances[randNumForDance]);
		    }}
	    }else{
	    cout<<"training failed"<<endl;}
	  break;
	}//switch
      
    }else{
    //if user has more than 5 moves
    cout<<"cannot have more than 5 dances"<<endl;
  }
}

void Game::EnterTournament()
{
  int enemyNum;
  int danceBattleNum;
  int randNum;
  int userChoice;
  
  cout<<"\n"<<endl;
  cout<<"you entered the tournament"<<endl;
  cout<<"\n"<<endl;
  cout<<"How many people would you like in your dance battle royale?(1-10)"<<endl;
  cin >> enemyNum;
  
  //input validation
  while ((enemyNum >MAX_ENEMY) ||(enemyNum <MIN_ENEMY))
    {
      cout<<"please enter the appropriate enemy number"<<endl;
      cin >> enemyNum;
    }
  
  danceBattleNum = 0;
  bool tournamentResult = WIN;
  bool fightResult = WIN;
  cout<< tournamentResult<<endl;
  
  //dance fight 
  while ((danceBattleNum < enemyNum)&&(tournamentResult == WIN))
    {
      cout<<"\n"<<endl;
      cout<<"Battle number: "<< danceBattleNum+1<<endl;
      randNum = (rand()% m_heroes.size());
      cout<<m_heroes[randNum].GetName()<<" wants to fight you!"<<endl;
      m_myHero.DisplayDances();
      cout<<"Select your dance move to fight back!"<<endl;
      cin>>userChoice;
      
      //input validation
      while ((userChoice > m_myHero.GetDanceCount()) || (userChoice < MIN_INPUT_NUM))
	{ cout<<"invalid input"<<endl;
	  cout<<"Select your dance move to fight back!"<<endl;
	  cin>>userChoice;}
      
      //get if player win or not  
      fightResult = m_myHero.DanceBattle(m_heroes[randNum],danceBattleNum+1,userChoice);
      switch (fightResult)
	{
	case WIN:
	  cout<<"you Won :)"<<endl;
	  cout<<"proceeding to next round..."<<endl;
	  break;
	case LOSE:
	  cout<<m_heroes[randNum].GetName()<<" has DEFEATED you"<<endl;
	  tournamentResult = LOSE;
	  break;
	}
      danceBattleNum ++;
    }
  //check if user won more than half of the time 
  if (tournamentResult == WIN)
    {
      float winTournament;
      winTournament = double(WINNUM) / double(danceBattleNum);
      if (winTournament <.50)
	{
	  cout<<"Sorry, you did not win the tournament because you did not win more than half of the time "<<endl;
	}
      if (winTournament >=.50)
	{
	  cout<<"you won the tournament"<<endl;
	}}
}
