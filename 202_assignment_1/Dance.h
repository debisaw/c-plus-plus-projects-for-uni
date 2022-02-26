//Title: Dance.h
//Author: Jeremy Dixon
//Date: 10/4/2018
//Description: This is part of the Fortnite Dance Royale Project in CMSC 202 @ UMBC

#ifndef DANCE_H //Include/Header Guard
#define DANCE_H //Include/Header Guard

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

  // Name: Dance
  // Desc - Used to store data about dances
struct Dance{
    string m_name; //Name of the dance
    int m_style; //Style of the dance (0 = freestyle, 1 = breakin, 2 = silly)
    int m_difficulty; //Difficulty of dance (0 = easy, 1 = difficult, 2 = epic)
    int m_level; //Level of the dance (1-10)
    Dance(){}
    Dance(string name, int style, int difficulty, int level){
        m_name = name;
        m_style = style;
        m_difficulty = difficulty;
        m_level = level;
    }
};

#endif
