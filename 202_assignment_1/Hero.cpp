
//File: Hero.cpp  //for project2
//Name: Dan Ebisawa
//section: 8
//date: 10/13/18
//Descripction: cpp file for hero.h

#include "Hero.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

int WINNUM = 0;
using namespace std;

Hero::Hero( )
{
  //unused
}
Hero::Hero(string name, bool isPlayer)
{
  m_name = name ;
  m_isPlayer = isPlayer;
  
}

string Hero::GetName()
{
  return m_name;
}

void Hero::SetName(string name)
{
  m_name = name;
}

void Hero::SetIsPlayer(bool isPlayer)
{
  m_isPlayer = isPlayer;
}
bool Hero::GetIsPlayer()
{
  if (m_isPlayer == PLAYER)
    {
      return true;
    }
  if (m_isPlayer == CPU)
    {
      return false;
    }
  //if nothing returns
  return NULL;
}

void Hero::DisplayDances()
{
  
  int vectorSize;
  int styleNum;
  vectorSize = GetDanceCount();
  cout << setw(22) <<"Dance"
       << setw(20)  <<"Style"
       << setw(10)  <<"Level"
       << setw(15)  <<"Difficulty\n";
  
  for (int i=0; i < vectorSize; i++)
    {
      cout <<i+1<<".";
      cout << setw(20)<<m_dances[i].m_name;

      styleNum = m_dances[i].m_style;
      //change number to designated string
      switch (styleNum)
	{
	case 0:
	  cout <<setw(20) << " freestyle";
	  break;
	  
	case 1:
	  cout <<setw(20) << " breakin";
	  break;

	case 2:
	  cout <<setw(20) << " silly";
	  break;
	}
      
      cout << setw(8) <<m_dances[i].m_level;
      cout << setw(11) <<m_dances[i].m_difficulty;
      
      cout <<"\n" <<endl;
    }
}

int Hero::GetDanceCount()
{
  int size;
  size = m_dances.size();
  return size; 
}

bool Hero::CheckDance(string danceMove)
{
  int HeroDanceVectorSize;
  HeroDanceVectorSize = GetDanceCount();

  for (int i = 0; i < HeroDanceVectorSize ; i++)
    {
      if (m_dances[i].m_name == danceMove)
	{
	  // return true to indicate found same dance move
	  return true;
	}
    }

  // did not find same dance move 
  return false;

}
void Hero::AddDance(Dance danceWithDetail)
{
  string name = danceWithDetail.m_name;
  int style = danceWithDetail.m_style;
  int difficulty = danceWithDetail.m_difficulty;
  int level = danceWithDetail.m_level;
  
  m_dances.push_back(Dance(name,style,difficulty,level));
}

void Hero::IncreaseDance(int danceLevel, int danceIndexInVector)
{
  danceLevel += 1;
  m_dances[danceIndexInVector].m_level = danceLevel;
}

int Hero::GetDanceLevel(int danceIndexInVector)
{
  return m_dances[danceIndexInVector].m_level;
}

string Hero::HeroicDance()
{
  //automatically win
  return "HeroicDance";
}

bool Hero::DanceBattle(Hero& cpu, int danceBattleNum, int playerDanceMove)
{
  //this function is only used by player

  int randCPUDance;
  int CPUDifficultyNum;
  int CPUTotalDanceNum;
  int CPUDanceLevelNum;
  int PlayerTotalDanceNum;
  int result;
  
  //choose random enemy move (sorry if i shoulve used a constant)
  randCPUDance = rand() % 5 +1 ;
  CPUDifficultyNum = cpu.m_dances[randCPUDance-1].m_difficulty;
  CPUDanceLevelNum = danceBattleNum;
  //calculated total dance scoer for CPU
  CPUTotalDanceNum = CPUDifficultyNum * CPUDanceLevelNum;
  //calculated total dance scoer for player
  PlayerTotalDanceNum = m_dances[playerDanceMove-1].m_level * m_dances[playerDanceMove-1].m_difficulty;

  //calculate the difference between CPU and player total dance num
  result = PlayerTotalDanceNum - CPUTotalDanceNum;

  //check HeroicDance
  int randNum = rand() % 20 + 1;
  if (randNum == 1) // 5% chance of being 1 
    {
      cout<<HeroicDance()<<endl;
      result = 1;
    }
  
  //return bool value based on result 
  if (result > 0)//if positive num
    {
      cout<<"you won the battle"<<endl;
      WINNUM += 1;
      return true;
    }
  if (result < 0) //if negative num
    {
      cout<<"you lost the battle"<<endl;
      return false;
    }
  
//if same
  cout<<"you tied the battle"<<endl;
  return true;
}
