#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "LL.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Sequencer {
 public:
  // Name: Sequencer (default constructor)
  // Preconditions: A linked list (DNA) is available
  // Postconditions: A linked list (DNA) where m_head and m_tail points to NULL
  //                m_size is also populated with SizeOf
  Sequencer(string fileName);

  // Name:  Sequencer (destructor)
  // Preconditions: There is an existing linked list (DNA)
  // Postconditions: A linked list (DNA) is deallocated (including nucleotides) to have no memory leaks!
  ~Sequencer();

  // Name:  DisplayStrands
  // Preconditions: At least one linked list is in m_dna
  // Postconditions: Displays each linked list (DNA strand) in m_dna
  void DisplayStrands();

  // Name:  readFile
  // Preconditions: Valid file name of characters (Either A, T, G, or C)
  // Postconditions: Populates the LinkedList (DNA)
  void readFile();

  // Name:  mainMenu
  // Preconditions: Populated LinkedList (DNA)
  // Postconditions: None
  void mainMenu();

  // Name:  CalculateConsensus
  // Preconditions: Populated m_dna vector populated with 3 or  more strands
  // Postconditions: Creates a  new strand that represents the  most common nuceloti
  // at each position
  void CalculateConsensus();

  // Name:  MutateStrand
  // Preconditions: Populated LinkedList (DNA)
  // Postconditions: DNA strand is mutated from a specific nucleotide (G,C,A,T) to another
  //                 valid nucleotide (G,C,A,T) at a given interval.
  void MutateStrand();

private:
  vector<LL*> m_dna; //Holds all DNA strands loaded from files. Each strand is its own linked list
  LL* m_consensus; //Linked list that stores the current consensus
  string m_fileName; //File that holds the strands to be read in
};

#endif
