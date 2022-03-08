#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

template <class T>
class Node {
public:
  Node( const T& data ); //Overloaded constructor
  T& GetData(); //Getter
  void SetData( const T& data ); //Setter
  Node<T>* GetNext(); //Getter
  void SetNext( Node<T>* next ); //Setter
private:
  T m_data; //Data stored in node
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

template <class T>
T& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to NULL
  Lqueue();

  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~Lqueue();

  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue(const Lqueue&);

  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  Lqueue<T>& operator = (Lqueue&);

  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  void Push(const T&);

  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  T Pop();

  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  void Display();

  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front 
  T Front();

  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  bool IsEmpty();

  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  int GetSize();

  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  void Swap(int);

  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  void Clear();

  // Name: RemoveInsertEnd
  // Preconditions: Requires a lqueue
  // Postconditions: Moves a node from somewhere to the end of the lqueue
  void RemoveInsertEnd(int);

  // Name: TestHeadTail() (Optional test function)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns the value of the head and the tail (used for main below)
  void TestHeadTail();

  // Name: operator<< (Overloaded << operator)
  // Preconditions: Requires a lqueue
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const Lqueue<U>&);

  //Name: Overloaded [] operator
  //Precondition: Existing Lqueue
  //Postcondition: Returns object from Lqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from Lqueue

private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};
//*********************************************************************
//******************Implement Lqueue Functions Here********************

template<class T>
Lqueue<T>::Lqueue(){
  m_head=nullptr;
  m_tail=nullptr;
  m_size=0;
}

template<class T>
Lqueue<T>::~Lqueue(){
  Clear();
}

template<class T>
Lqueue<T>::Lqueue(const Lqueue& LQ){

  if (LQ.m_head == nullptr){
    m_head = nullptr;
    m_tail = nullptr;}
  else{
    m_head = new Node<T>(LQ.m_head ->GetData());  
    Node<T>* current = m_head;
    Node<T>* currentObj = LQ.m_head;
    while(currentObj -> GetNext() !=nullptr){
      current -> SetNext(new Node<T>(currentObj -> GetNext() -> GetData()));
      currentObj = currentObj -> GetNext();
      current = current -> GetNext();
      m_size ++;
    }
    m_tail = current;
  }

}

template<class T>
Lqueue<T> & Lqueue<T>::operator = (Lqueue& source){
  if (& source != this){
    Clear();
    Node<T>* temp = source.m_head;
    while (temp != nullptr){
      Push(temp -> GetData());
      temp = temp -> GetNext();
    }
  }
  return *this;
}

template<class T>
void Lqueue<T>::Push(const T& data){
  //add node to the end
  Node<T>* temp = new Node<T>(data);
  temp -> SetNext(nullptr);
  if(m_head == nullptr){
    m_head = temp;
    m_tail = temp;
    }
  else{
    m_tail -> SetNext(temp);
    m_tail = temp;
  }
  m_size ++;
}

template<class T>
T Lqueue<T>::Pop(){
  //remove first node
  Node<T>* temp = m_head ->GetNext();
  T data = m_head -> GetData();
  delete m_head;
  m_head = temp;

  return data;
}

template<class T>
void Lqueue<T>::Display(){
  
  Node<T>* temp = m_head;
  while (temp != nullptr){
    T data = temp ->GetData();
    cout<< data <<endl;
    temp = temp -> GetNext();
  }
}

template<class T>
T Lqueue<T>::Front(){
  T data = m_head ->GetData();
  return data;
}

template<class T>
bool Lqueue<T>::IsEmpty(){
  //  return true if empty, false if filled
  if (m_head = NULL){
    return true;
  }
  return false;
}

template<class T>
int Lqueue<T>::GetSize(){
  return m_size;
}

template<class T>
void Lqueue<T>::Swap(int index){
  Node<T>* previous1 = m_head;
  Node<T>* previous2 = m_head;
  Node<T>* current = m_head;
  int count = 0;

  if ((m_head ==nullptr)||(index ==0)||(index >m_size)||(m_head ->GetNext() ==nullptr))
    {return;}
  else if (index ==1){
    current = m_head -> GetNext();
    m_head=current;
    previous1 -> SetNext(current ->GetNext());
    current -> SetNext(previous1);
    if ((index+1)==m_size){
      m_tail = previous1;
    }}
  else{
    while ((current != nullptr)&&(count !=index)){
      previous2= previous1;
      previous1 = current;
      current = current -> GetNext();
      count++;
    }//while
    //swap node here 
    previous1 -> SetNext(current -> GetNext());
    previous2 -> SetNext(current);
    current -> SetNext(previous1);
    if ((index+1)==m_size)
      {m_tail = previous1;}
  }
}

template<class T>
void Lqueue<T>::Clear(){
  
  Node<T>* temp = m_head;
  Node<T>* nextNode = temp;
  
  while (temp != nullptr){
    nextNode = temp ->GetNext();
    delete temp;
    temp = nextNode;}

  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

template<class T>
void Lqueue<T>::RemoveInsertEnd(int index){
  //move node to the end 
  Node<T>* current = m_head;
  Node<T>* previousNode = m_head;
  int count = 0;
  if ((index > m_size)||(m_size ==0)||(m_head == nullptr)){
    return;
  }
  else if (index ==0){
    //if index of interest is the first node
    m_head = current -> GetNext();
    m_tail -> SetNext(current);
    current -> SetNext(nullptr);
    m_tail = current;
    return;
  }
  else{
    while ((current!=nullptr)&&(count != index)){
      //moving to the next node
      previousNode = current;
      current = current -> GetNext();
      count ++;
	}
    if (count == index){
      //finds the index of interest
      previousNode ->SetNext(current ->GetNext());
      m_tail -> SetNext(current);
      current -> SetNext(nullptr);
      m_tail = current;}
  }  
}

template<class T>
void Lqueue<T>::TestHeadTail(){
  //display head and tail of the node 
  T headData = m_head -> GetData();
  T tailData = m_tail -> GetData();

  cout<<"head: " <<headData<<"\t tail:"<<tailData<<endl;

}

template<class U>
ostream& operator<<(ostream& output, const Lqueue<U>& myLQ){
  if(myLQ.m_head !=nullptr){
    Node<U> *temp = myLQ.m_head;
    while (temp != nullptr){
      output<< temp -> GetData()<<"\n";
      temp = temp-> GetNext();
    }
  }else{
    output<<"List is empty";
      }
  return output;
}
template<class T>
T& Lqueue<T>::operator[] (int x){
  int count = 0;
  Node<T>* car = m_head;
  while ((car!=nullptr)&&(count != x)){
    car = car -> GetNext();
    count ++;}
  return car->GetData();
}

//************************Lqueue Tests Below***************************
// To test just Lqueue follow these instructions:
//   1.  mv Lqueue.h Lqueue.cpp
//   2.  Uncomment out int main below
//   3.  make Lqueue
//   4.  ./Lqueue
/*

int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  Lqueue <int> newLQ1;
  //Push 4 nodes into Lqueue
  newLQ1.Push(10);
  newLQ1.Push(11);
  newLQ1.Push(12);
  newLQ1.Push(13);
  cout << endl;

  
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  Lqueue <int> newLQ2(newLQ1);
  //Test Overloaded Assignment Operator
  Lqueue <int> newLQ3;
  newLQ3 = newLQ2;
  cout << endl;
  
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLQ1" << endl;
  newLQ1.Display();
  cout << "newLQ2" << endl;
  newLQ2.Display();
  cout << "newLQ3" << endl;
  newLQ3.Display();
  cout << "newLQ1" << endl;
  cout << newLQ1;
  cout << "newLQ2" << endl;
  cout << newLQ2;
  cout << "newLQ3" << endl;
  cout << newLQ3;
  cout << endl;
  
  //Test 4 - Test Front and Pop
  cout << "Test 4 - Front and Pop Running" << endl;
  //Test Front()
  cout << "Testing Front - Output 10" << endl;
  cout << newLQ1.Front() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  //Test Pop with Display of Pop
  cout << "Popping one node and displaying it" << endl;
  cout << newLQ1.Pop() << endl;
  cout << endl;
  
  //Test 5 - Test GetSize and Clear
  cout << "Test 5 - GetSize and Clear Running" << endl;
  //Test GetSize()
  cout << "Outputting the size" << endl;
  cout << newLQ1.GetSize() << endl;
  //Test Clear()
  cout << "Clearing all nodes" << endl;
  newLQ1.Clear();
  cout << endl;
  
  //Test 6 - Test Swap
  cout << "Test 6 - Swap Running" << endl;
  newLQ2.Swap(2);
  cout << "Swap 2 - Should display 10->12->11->13->END" << endl;
  newLQ2.Display();
  //Testing to make sure head and tail point at the correct node
  newLQ2.TestHeadTail();
  cout << "Should display head 10 and tail 13" << endl;
  cout << endl;
  
  //Test 7 - Test RemoveInsertEnd(2)
  cout << "Test 7 - RemoveInsertEnd Running" << endl;
  cout << "Before RemoveInsertEnd" << endl;
  newLQ3.Display();
  newLQ3.TestHeadTail();
  newLQ3.RemoveInsertEnd(2);
  cout << "After RemoveInsertEnd 10->11->13->12->END" << endl;
  newLQ3.Display();
  newLQ3.TestHeadTail();
  return 0;
}
*/


