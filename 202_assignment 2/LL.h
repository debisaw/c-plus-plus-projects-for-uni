#ifndef LL_H
#define LL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
  char m_data;
  Node *m_next;
};

class LL {
 public:
  // Name: LL() - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head and m_tail point to NULL
  LL();

  // Name: ~LL() - Destructor
  // Desc: Used to destruct a new linked list
  // Preconditions: There is an existing linked list with at least one node
  // Postconditions: A linked list is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!

  ~LL();
  // Name: InsertEnd
  // Preconditions: Takes in a char. Creates new node. 
  //                Requires a linked list
  // Postconditions: Adds a new node to the end of the linked list.
  void InsertEnd(char data);

  // Name: Display
  // Preconditions: Outputs the linked list.
  // Postconditions: Returns number of nodes displayed.
  int Display();

  // Name: IsEmpty
  // Preconditions: Requires a linked list
  // Postconditions: Returns if the linked list is empty.
  bool IsEmpty();

  // Name: SizeOf
  // Preconditions: Requires a linked list
  // Postconditions: Populates m_size with the total number of nodes and returns m_size;
  int SizeOf();

  // Name: Clear
  // Preconditions: Requires a linked list
  // Postconditions: Removes all nodes in a linked list
  void Clear();

  // Name: ReplaceData (works like find and replace)
  // Desc: Iterates over the linked list and replaces every *quantity* charFrom with charTo
  //       For ReplaceData ('A','C', 3) then every third 'A' would be replaced with a 'C'
  // Preconditions: Requires a linked list
  // Postconditions: Updates a linked list by mutating data based on a frequency
  int ReplaceData(char charFrom, char charTo, int frequency);

  // Name: GetData
  // Preconditions: Requires a linked list
  // Postconditions: Returns the data at a specific node
  char GetData(int nodeNum);

  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a linked list
  // Postconditions: Returns an ostream with the data from every node separated by ->
  friend ostream &operator<< (ostream &output, LL &myLL);
private:
  Node *m_head; //Node  pointer for the head
  Node *m_tail; //Node  pointer for the tail
  int m_size; //Int size
};

#endif
