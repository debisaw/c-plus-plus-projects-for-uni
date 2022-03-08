//file name: LL.cpp
//name: Dan Ebisawa
//date 10/31/18
//section 8
//description: cpp file for linked list


#include<string>
#include<iostream>
#include<cmath>
#include<iomanip>
#include "LL.h"

using namespace std;

LL::LL(){
  
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
  
}

LL::~LL(){
  
  Clear();

}

void LL::Clear(){
  //delete from the head
  Node *currentNode = m_head;  
  while (currentNode != NULL)
    {
      Node *nextNode = currentNode ->m_next;
      delete currentNode;
      currentNode = nextNode;
    }
  m_head = NULL;
  m_tail = NULL;
  
}
void LL::InsertEnd(char data){
  
  Node *temp = new Node;

  if(m_head == NULL){//input data in head
    m_head = temp;
    m_tail = temp;
    temp -> m_data = data;
    temp -> m_next = NULL;
  }else{//the tail 
    m_tail -> m_next = temp;
    m_tail = temp;
    temp -> m_data = data;
    temp -> m_next = NULL;    
  }
  // adding delete temp; here gives error but decrease memory leak by 6 
}

int LL::Display(){

  Node *temp = m_head;
  int nodeNum = 0;
  for (int i = 0; i < m_size; i++){
    cout << temp -> m_data << " -> ";
    temp = temp -> m_next;
    nodeNum++;
  }
  cout <<"END"<<endl;
  delete temp;
  temp = NULL;
  return nodeNum;
}

int LL::SizeOf(){
  
  if (m_size != 0)
    return m_size;
  
  Node *temp = m_head;
  while (temp != NULL)
    {
      m_size ++;
      temp = temp -> m_next;
    }
  delete temp;
  temp = NULL;
  return m_size;
}

bool LL::IsEmpty(){
  if (m_head == NULL){
    cout<< "linked list is empty"<<endl;
    return true; // return empty
  }else{
    cout<<"linked list is not empty"<<endl;
  }
  return false;//return has something 
}
char LL::GetData(int nodeNum)
//memory leak is found here 
{
  int nodeNumCheck = 0;
  char nucleotide = 'x';
  
  for(Node *currentNode = m_head; currentNode != NULL; currentNode = currentNode ->m_next)
    {
      if (nodeNumCheck == nodeNum)
	{
	  nucleotide = currentNode ->m_data;
	  return nucleotide;
	}
      nodeNumCheck ++;
    }
  return nucleotide;
      
}

int LL::ReplaceData(char charFrom, char charTo, int frequency)
{
  int checkFrequency =0 ;
  char nucleotide ;
  for (Node *currentNode = m_head; currentNode != NULL;currentNode =currentNode ->m_next)
    {
      nucleotide = currentNode ->m_data;
      if (nucleotide == charFrom){
	checkFrequency ++;
	if (checkFrequency == frequency)
	  { currentNode -> m_data = charTo;
	    checkFrequency =0;}
      }
    }
  return 1 ; 
}
ostream &operator<<(ostream &output, LL &myLL){
  Node *temp = myLL.m_head;
  while (temp !=NULL)
    {
      output<< temp->m_data<<" -> ";
      temp = temp -> m_next;
    }
  output<<"END"<<endl;
  delete temp;
  return output;
}
