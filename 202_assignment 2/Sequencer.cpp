//filename: sequencer.cpp
//name: dan ebisawa
//date: 10/29/18
//section: 8
//description: cpp file for sequencer.

#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Sequencer.h"
#include "LL.h"

using namespace std;

Sequencer::Sequencer(string fileName){
  //for proj3_test2.txt, there are only 33 nucleotides in total, instead of 35. 
  m_fileName = fileName;
  cout<<m_fileName<<endl;
  readFile();
  cout<<""<<endl;
  mainMenu();
}
Sequencer::~Sequencer(){
   for (unsigned i = 0; i < m_dna.size();i++)
    {
      m_dna[i] -> Clear();
      delete m_dna[i];
      m_dna[i] = NULL;
      }
}
void Sequencer::readFile(){
  //open file
  ifstream dnaStream;
  dnaStream.open(m_fileName);

  char nucleotide;
  int strandNum = 0;

  if (dnaStream.is_open()){
    cout<<m_fileName<<" loaded"<<endl;
    //create a LL pointer for first strand 
    LL *dnaStrandptr;
    dnaStrandptr = new LL;
    int num = 0;

    while(! dnaStream.eof()){
      dnaStream.get(nucleotide);
      while(dnaStream.peek() == ' ')
	{dnaStream.ignore(1);
	  num++;;
	}
      //insert node according to the letter
	switch (nucleotide){
	case 'A':
	  dnaStrandptr -> InsertEnd(nucleotide);
	  break;
	case 'G':
	  dnaStrandptr -> InsertEnd(nucleotide);
	  break;
	case 'T':
	  dnaStrandptr -> InsertEnd(nucleotide);
	  break;
	case 'C':
	  dnaStrandptr -> InsertEnd(nucleotide);
	  break;
	}
      if (dnaStream.peek() == '\n'){//if it reaches the end of the strand
	dnaStream.ignore(1);
	m_dna.push_back(dnaStrandptr);	
	m_dna[strandNum] -> SizeOf();
	dnaStrandptr = new LL;
	strandNum ++;}
    }//while .eof
    delete dnaStrandptr;
    dnaStrandptr = NULL;
    dnaStream.close();
  }//if .is_open
  else{
    cout<< "file not open"<< endl;
  }
  //display
  for (unsigned int i=0; i < m_dna.size(); i++){
    cout<<"Strand "<< i+1<<" loaded with "
	<<m_dna[i] -> SizeOf()
	<<" nucleotides."<<endl;
    m_dna[i] -> Display();
  }
  cout<<""<<endl;
  cout<<m_dna.size()<<" strands loaded."<<endl;  
}

void Sequencer::DisplayStrands(){
  //display strand using overload operant 
  for (unsigned i= 0; i< m_dna.size();i++)
    {
      cout<<"Number of nucleotide: "<<m_dna[i]->SizeOf()<<endl;
      cout<< *(m_dna[i])<<endl;
    }
}
void Sequencer::CalculateConsensus(){
  int sizeStrand = m_dna[0] -> SizeOf();
  int countA ,countT ,countC,countG;
  m_consensus = new LL;
  //loop to check each node 
  for(int numInStrand =0; numInStrand < sizeStrand; numInStrand ++)
    {
      countA = 0;
      countT = 0;
      countC = 0;
      countG = 0;
         //loop to check each strand
      for(unsigned int strandNum =0; strandNum < m_dna.size(); strandNum ++)
      {
	char nucleotide;
	nucleotide = m_dna[strandNum]->GetData(numInStrand);
	switch (nucleotide)
	  {
	  case 'A':
	    countA ++;
	    break;
	  case 'T':
	    countT ++;
	    break;
	  case 'C':
	    countC ++;
	    break;
	  case 'G':
	    countG ++;
	    break;}
      }
       //check which nucleotide appeared the most and add to consensus
      if ((countT<countA)&&(countC<countA)&&(countG<countA))
	{m_consensus ->InsertEnd('A');}      
      if ((countA<countT)&&(countC<countT)&&(countG<countT))
	{m_consensus ->InsertEnd('T');} 
      if ((countA<countC)&&(countT<countC)&&(countG<countC))
	{m_consensus ->InsertEnd('C');}
      if ((countA<countG)&&(countT<countG)&&(countC<countG))
	{m_consensus ->InsertEnd('G');}
      
    }//end loop to chech each node
  cout<<*(m_consensus)<<endl;
}
void Sequencer::MutateStrand(){
  int MINNUM = 1;
  int MAXNUM = 5;

  char nucReplace;
  char nucChange;
  char userInput;
  int userNum;
  
  cout<<"Which nucleotide would you like to replace? (A,T,G,C)"<<endl;
  cin>>userInput;
  //input validation
  //ask user for node to replace, to change and in what frequency
  while ((userInput!='A')&&(userInput!='T')&&(userInput!='G')&&(userInput!='C'))
    {
      cout<<"invalid input"<<endl;
      cout<<"Which nucleotide would you like to replace? (A,T,G,C)"<<endl;
      cin>>userInput;
    }
  nucReplace = userInput;
  cout<<"Which nucleotide would you like to change to? (A,T,G,C)"<<endl;
  cin>>userInput;
  while ((userInput!='A')&&(userInput!='T')&&(userInput!='G')&&(userInput!='C'))  
    {
      cout<<"invalid input"<<endl;
      cout<<"Which nucleotide would you like to change to? (A,T,G,C)"<<endl;
      cin>>userInput;
    }
  nucChange = userInput;
  cout<<"In what frequency? (every other? every third?\nplease enter a number between (1-5)"<<endl;
  cin>>userNum;
  while ((userNum < MINNUM)||(userNum >MAXNUM))
    {
      cout<< "invalid input"<<endl;
      cout<<"In what frequency? (every other? every third?\nplease enter a number between (1-5)"<<endl;
      cin>>userNum;
    }
  
  //replace data 
  for(unsigned int i =0; i < m_dna.size();i++){
    m_dna[i] -> ReplaceData(nucReplace,nucChange,userNum);
  }
}
void Sequencer::mainMenu(){
  //constant to avoid magic number (cannot edit header file)
  int MAINMENUNUM = 4; 
  int MINNUM = 1;
  int MAXNUM = 4;
  int EXIT = 4;
  cout<<"welcome to the DNA sequencer"<<endl;
  cout<<"What would yuou like to do?:"<<endl;
  int userChoice = 0;
  while (userChoice != EXIT){
    //main menu
    for (int i = 1; i <= MAINMENUNUM; i++){
      switch (i)
	{
	case 1:
	  cout<<i<<". Display Strands"<<endl;
	  break;
	case 2:
	  cout<<i<<". Use Consensus Tool"<<endl;
	  break;
	case 3:
	  cout<<i<<". Mutate Strands"<<endl;
	  break;
	case 4:
	  cout<<i<<". Exit"<<endl;
	  break;
	}}
    cin>>userChoice;
    while ((userChoice < MINNUM) || (userChoice >MAXNUM))
      {
	cout<<"invalid input"<<endl;
	cout<<"please enter a valid number"<<endl;
	cin>>userChoice;
      }
    switch (userChoice)
      {
      case 1:
	DisplayStrands();
	break;
      case 2:
	CalculateConsensus();
	break;
      case 3:
	MutateStrand();
	break;
      }
  }//while userChoice
  cout<<"thank you for using the DNA sequencer"<<endl;

}

