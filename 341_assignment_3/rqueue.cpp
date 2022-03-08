// CMSC 341 - Spring 2021 - Project 3
// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  priority = priFn;    //initialize all variables and set priority function.
  _heap = nullptr;
  _size = 0;
  
}

RQueue::~RQueue()
{  
  recursiveDelete(_heap);  // recursively delete the heap by post-order  
}

//helper for descructor above.  
void RQueue::recursiveDelete(Node* node){
  if (node!= nullptr){
    recursiveDelete(node->_left);
    recursiveDelete(node->_right);
    delete node;
  }
  _heap = nullptr;
}
//copy constructor
RQueue::RQueue(const RQueue& rhs)
{
  if (rhs._size == 0){
    priority = rhs.getPriorityFn();
    _heap = nullptr;
  }
  else{
    _heap = nullptr;
    _size = rhs._size;
    priority = rhs.priority;
    _heap = makeDeepCopy(rhs._heap);
  }
}
//helper to make a deep copy
Node* RQueue::makeDeepCopy(const Node* rhsNode){
  if (rhsNode == nullptr){
    return nullptr;}
  Node* node = new Node(rhsNode->getStudent());
  
  node->_left = makeDeepCopy(rhsNode->_left);
  node->_right = makeDeepCopy(rhsNode->_right);

  return node;
}
//assignmnet operator
RQueue& RQueue::operator=(const RQueue& rhs)
{
  if (this != &rhs){
    if (rhs._size ==0){
      _heap = nullptr;
      _size = 0;
      priority = rhs.getPriorityFn();
    }else{
      priority = rhs.getPriorityFn();
      _heap = makeDeepCopy(rhs._heap);
      _size = rhs.numStudents();
    }
  }
  return *this;
}

void RQueue::insertStudent(const Student& input) {
  if (_heap == nullptr){
    Node *node = new Node(input);
    _heap = node;
    _size++;
  }else{ 
    Node *node = new Node(input);            //make a new heap and merge it 
    RQueue newQueue(getPriorityFn());
    newQueue._heap = node;
    newQueue._size = 1;
    mergeWithQueue(newQueue);
  }
}

Student RQueue::getNextStudent() {
  try{
    Node* NodeWithHighestPri = _heap;
    if (NodeWithHighestPri == nullptr){
      throw domain_error("empty queue");
    }
    _heap = recursiveMerge(_heap->_left,_heap->_right);
    Student studentWithHighestPri = NodeWithHighestPri->getStudent();
    delete NodeWithHighestPri;
    _size--;
    
    return studentWithHighestPri;
  }catch(exception& err)
    {throw domain_error("");}
}


void RQueue::mergeWithQueue(RQueue& rhs) {
  try{
    if (getPriorityFn()!=rhs.getPriorityFn()){
      throw domain_error("priority function does not match");
	}
    else{
      if (this != &rhs) { //protest self mergin
	_heap = recursiveMerge(_heap, rhs._heap);    //since current heap will share the same pointers as nodes in rhs, point rhs._heap to nullptr so that it does not double free 
	_size = _size + rhs._size; 
	rhs._heap = nullptr;
      }
    } 
  }catch(exception& err){
    cout<<err.what()<<endl;
    throw domain_error("");
  }
}
Node* RQueue::recursiveMerge(Node* heap1, Node* heap2){
  prifn_t priorityFn = getPriorityFn();
  if (heap1 == nullptr){
    return heap2;
  }
  else if (heap2 == nullptr){
    return heap1;
  }
  if (priorityFn(heap1->getStudent())> priorityFn(heap2->getStudent())){ // swap heap1 and heap2
    Node* temp = heap1;
    heap1 = heap2;
    heap2 = temp;
  }
 
  Node* temp = heap1->_left;    //swap child of heap
  heap1->_left = heap1->_right;
  heap1->_right = temp;
  //  cout<<heap1->getStudent()<<endl;
  heap1->_left = recursiveMerge(heap1->_left, heap2);
  
  return heap1;
}
  
void RQueue::clear() {

  _heap = nullptr; 
}
 
int RQueue::numStudents() const{
  return _size; 
   
}

void RQueue::printStudentQueue() const {
  recursivePreOrderPrint(_heap);
}

void RQueue::recursivePreOrderPrint(Node* node) const{
  if (node!=nullptr){
    prifn_t priFn = getPriorityFn();
    cout<<"["<<priFn(node->getStudent())<<"] "<<node->getStudent()<<endl;
    recursivePreOrderPrint(node->_left);
    recursivePreOrderPrint(node->_right);
  }
  
}

prifn_t RQueue::getPriorityFn() const {
  return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  priority = priFn;
  RQueue newQueue(priFn);
  recursiveInsertForSetPri(newQueue,_heap);  //merge a new heap made with new priorityFn.  
  recursiveDelete(_heap);
  _size = 0;
  mergeWithQueue(newQueue);
}

void RQueue::recursiveInsertForSetPri(RQueue& newQueue, Node* node){
  if (node!= nullptr){
    
    recursiveInsertForSetPri(newQueue,node->_left);
    recursiveInsertForSetPri(newQueue,node->_right);
    newQueue.insertStudent(node->getStudent());
  }
}
// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}
