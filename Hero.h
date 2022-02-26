//Title: Hero.h
//Author: Dan Ebisawa
//Date: 10/4/2018
//Description: This is part of the Fortnite Dance Royale Project in CMSC 202 @ UMBC

#ifndef HERO_H //Include/Header Guard
#define HERO_H //Include/Header Guard

#include "Dance.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

//Constants (allowed to add more as needed)
const int MIN_LEVEL = 1;
const int MAX_LEVEL = 10;
const int NUM_DANCES = 5;

const int MIN_INPUT_NUM = 1;
const int MAX_INPUT_NUM = 5;
const int MAX_LEARN_MOVES_INPUT = 3;

const int MIN_ENEMY = 1;
const int MAX_ENEMY = 10;

const int EASY_DANCE=0;
const int DIFFICULT_DANCE=1;
const int EPIC_DANCE=2;

const bool PLAYER = true;
const bool CPU = false;

const bool WIN = true;
const bool LOSE = false;
const bool TIE = NULL;
extern int WINNUM;

//Hero class - allowed to add HELPER functions only

class Hero{
 public:
  // Name: Hero() - Default Constructor (unused)
  // Desc: Used to build a new hero
  // Preconditions - Requires default values
  // Postconditions - Creates a new hero
  Hero();

  // Name: Hero(name, isPlayer, isSeen, level) - Overloaded constructor
  // Desc - Used to build a new hero (player or enemy)
  // Preconditions - Requires name and isPlayer
  // Postconditions - Creates a new hero
  Hero(string name, bool isPlayer);

  // Name: GetName()
  // Desc - Getter for Hero name
  // Preconditions - Hero exists
  // Postconditions - Returns the name of the hero
  string GetName();

  // Name: SetName(string)
  // Desc - Allows the user to change the name of the hero
  // Preconditions - Hero exists
  // Postconditions - Sets name of hero
  void SetName(string name);

  // Name: SetIsPLayer(bool)
  // Desc: setter to indicate if hero is player or non-player character
  // preCond: Hero exists
  // postCond: sets true (player) or false (CPU) 
  void SetIsPlayer(bool isPlayer);

  // Name: GetIsPlayer()
  // Desc - Getter for if hero is a player or a non-player character (computer)

  //      - I didnt use this function in this program  // 
  
  // Preconditions - Hero Exists
  // Postconditions - Returns true (is user) or false (is computer)
  bool GetIsPlayer();


  // Name: DisplayDances()
  // Desc - Displays a numbered list of all dance moves known by the player
  // Preconditions - Heros exist
  // Postconditions - None
  void DisplayDances();

  // Name: GetDanceCount()
  // Desc - Returns number of dances known by hero
  // Preconditions - Heros exist
  // Postconditions - None
  int GetDanceCount();

  // Name: DanceBattle(Hero&)
  // Desc - Allows the user to dance attack an enemy hero
  //      - only m_myHero uses 
  // Preconditions - Heros exist
  // Postconditions - Returns if hero hero wins fight (true wins, false loses)
  bool DanceBattle(Hero& cpu, int danceBattleNum, int playerDanceMove);

  // Name: HeroicDance(Hero&)
  // Desc - Allows the user to attack an enemy hero using a special dance
  //        Returns the string of the specific dance
  // Preconditions - During normal attack, 5% chance a special dance attack called
  // Postconditions -  Automatically wins fight
  string HeroicDance();

  // Name: IncreaseDance(int)
  // Desc - Increases level of a dance up to 10 (value passed is index of dance to increase)
  // Preconditions - Hero has dances
  // Postconditions - None
  void IncreaseDance(int danceLevel, int danceIndexInVector);

  // Name: CheckDance(string)
  // Desc - Checks the player to see if they know a specifice dance by name
  // Preconditions - Hero has dances
  // Postconditions - Returns true if player already has dance, else false
  bool CheckDance(string);  

  // Name: AddDance(Dance)
  // Desc - Adds a new dance to the player's dance list
  // Preconditions - Hero does not already know this dance
  // Postconditions - Dance is added (level 1)
  void AddDance(Dance danceWithDetail);

  //Name: getdancelevel(int)
  //desc: getter for the level of the dance
  //precondition: hero exists with dance
  //postcondition: dance level is returned
  int GetDanceLevel(int danceIndexInVector);

  
private:
  string m_name; //Name of Hero
  bool m_isPlayer; //Identifies user controled (true) or computer controlled (false)
  vector<Dance> m_dances; //List of known dance styles
};

#endif //Exit Header Guard
