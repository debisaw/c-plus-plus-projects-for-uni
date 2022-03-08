#include "rqueue.h"
using namespace std;

int priorityFn1(const Student &student);
int priorityFn2(const Student &student);
class Tester{
public:
  bool testCopyConstructor(const RQueue& rhs);
  bool testCopyHelper(const Node* rhs,const Node* copy);
  void testEfficiency(int numTrials,int N);
  bool testProperty(RQueue& rhs);
  bool helperTestProperty(Node*  rhs);
  bool testAssignOperator(const RQueue& rhs);
  bool mergeTwoDifferent(RQueue& rqueue1, RQueue& rqueue2);
  bool dequeueEmpty(RQueue& rqueue);
  bool edgeCopyConstructor(RQueue& rqueue);
  bool edgeAssignmentOperator(RQueue& rqueue);
  bool protectSelfAssignment(RQueue& rqueue);
  bool basicCorrectness(RQueue& rhs);
};

bool Tester::basicCorrectness(RQueue& rhs){
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student3("Nick",2,0,0,0);
  Student student4("Eva",4,3,2,1);
  Student student5("John",6,3,2,1);
  Student student6("Mia",3,0,0,0);
  
  rhs.insertStudent(student5);
  rhs.insertStudent(student6);
  rhs.insertStudent(student3);
  rhs.insertStudent(student1);
  rhs.insertStudent(student2);
  rhs.insertStudent(student4);
  while (rhs.numStudents() > 0) {
    
    Student student = rhs.getNextStudent();
    int priorityNumRemoved = priorityFn1(student);
    if (rhs._heap !=nullptr){
      int currentPriorityNum = priorityFn1(rhs._heap->getStudent());
      if (priorityNumRemoved > currentPriorityNum){
	return false;}
    }
  }
  
  return true;
}
bool Tester::protectSelfAssignment(RQueue& rqueue){
  try {
    rqueue = rqueue;}
  catch(exception& err){return false;}

  return true;
  
}
bool Tester::edgeAssignmentOperator(RQueue& rqueue){
  RQueue copy = rqueue;
  if (&copy ==&rqueue){
    return false;}
  else{return true;}
}

bool Tester::edgeCopyConstructor(RQueue& rqueue){
  RQueue copy(rqueue);
  if(&copy == &rqueue){
    return false;}
  else{return true;}
}
bool Tester::dequeueEmpty(RQueue& rqueue){
  try{
    Student student = rqueue.getNextStudent();
  }catch(exception& err){return true;}
  return false;
  
}
bool Tester::mergeTwoDifferent(RQueue& rqueue1, RQueue& rqueue2){
  try{
    rqueue1.mergeWithQueue(rqueue2);
      }catch(exception& err){
    return true;
  }
  return false;
}
bool Tester::testProperty(RQueue& rhs){
  Student student1("Sam",1,1,1,1);
  Student student2("Liz",5,1,2,0);
  Student student3("Nick",2,0,0,0);
  Student student4("Eva",4,3,2,1);
  Student student5("John",6,3,2,1);
  Student student6("Mia",3,0,0,0);

  rhs.insertStudent(student5);
  rhs.insertStudent(student6);
  rhs.insertStudent(student3);
  rhs.insertStudent(student1);
  rhs.insertStudent(student2);
  rhs.insertStudent(student4);
  
  rhs.setPriorityFn(priorityFn2);
  if (helperTestProperty(rhs._heap)){
    return true;
  }else{return false;}

  return false;
}
bool Tester::helperTestProperty( Node* node){
  if (node != nullptr){
    prifn_t priorityFn = priorityFn2;
    int currentPriNum = priorityFn(node->getStudent());
    if (node->_left !=nullptr){
      if (currentPriNum > priorityFn(node->_left->getStudent())){
	  return false;}
    }
    if (node->_right != nullptr){
      if (currentPriNum > priorityFn(node->_right->getStudent())){
	return false;}
    }
    helperTestProperty(node->_left);
    helperTestProperty(node->_right);

  } 
  return true;
}
void Tester::testEfficiency(int numTrials, int N){
  const int a=2;
  double T = 0.0;
  clock_t start, stop;
  RQueue rqueue(priorityFn1);
  for (int k=0; k<numTrials;k++){
    start = clock();
    for (int i=0; i<N;i++){
      Student student ("",1,0,0,0);
      rqueue.insertStudent(student);
    }
    stop = clock();
    T = stop - start;
    cout<<"Insertting "<<N<<" students took "<< T<<" clock ticks ("<<T/CLOCKS_PER_SEC<<" seconds)!"<<endl;

    start = clock();
    for (int i=0; i<N;i++){
      Student student = rqueue.getNextStudent();
    }
    stop = clock();
    T = stop - start;
    cout<<"Extracting "<<N<<" students took "<<T<<" clock ticks ("<<T/CLOCKS_PER_SEC<<" seconds)!"<<endl;
  N=N*a;
  }
}
bool Tester::testAssignOperator(const RQueue& rhs){
 RQueue copy(priorityFn1);
  copy = rhs;
  if (rhs._size == 0){
    if (&rhs == &copy){
      return false;
    }else{return true;}
  }
  else{
    if (testCopyHelper(rhs._heap ,copy._heap)){
      return true;
    }else{return false;}
  }
  return false;
}
bool Tester::testCopyConstructor(const RQueue& rhs){
  RQueue copy(rhs);
  if (rhs._size == 0){
    if (&rhs == &copy){
      return false;
    }else{return true;}
  }
  else{
    if (testCopyHelper(rhs._heap ,copy._heap)){
      return true;
    }else{return false;}
  }
}
bool Tester::testCopyHelper(const Node* rhs,const Node* copy){
  if (rhs != nullptr){
    testCopyHelper(rhs->_left,copy->_left);
    if ((rhs->getStudent().getName()!=copy->getStudent().getName())||&rhs==&copy){
      return false;}
    testCopyHelper(rhs->_right,copy->_right);
  }
  return true;
  
}

  int main(){					
  Tester tester;
    {
    cout<<"test Copy constructor: "<<endl;
    RQueue queue(priorityFn1);
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);
    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.insertStudent(student3);
    queue.insertStudent(student4);
    if (tester.testCopyConstructor(queue)){
      cout<<"test passed"<<endl;}
    else{cout<<"test failed"<<endl;};
  }
      {
    cout<<"test assign operator : "<<endl;
    RQueue queue(priorityFn1);
    Student student1("Sam",1,1,1,1);
    Student student2("Liz",5,1,2,0);
    Student student3("Nick",2,0,0,0);
    Student student4("Eva",4,3,2,1);
    queue.insertStudent(student1);
    queue.insertStudent(student2);
    queue.insertStudent(student3);
    queue.insertStudent(student4);
    if (tester.testAssignOperator(queue)){
      cout<<"test passed"<<endl;}
    else{cout<<"test failed"<<endl;};
  }
  
  {
    cout<<"test inserttion/ deleting performance"<<endl;
    tester.testEfficiency(5,1000);
  }
    
  {
    cout<<"test min-heap property after changing the priority function"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.testProperty(rqueue)){
      cout<<"test passed"<<endl;}
    else{cout<<"test failed"<<endl;}

  }
  {
    cout<<"test merge two different priority"<<endl;
    RQueue rqueue1(priorityFn1);
    RQueue rqueue2(priorityFn2);
    if (tester.mergeTwoDifferent(rqueue1,rqueue2)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  {
    cout<<"test dequeue a empty queue"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.dequeueEmpty(rqueue)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }

  {
    cout<<"test edge case for copy constructor: copy empty rqueue"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.edgeCopyConstructor(rqueue)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  {
    cout<<"test edge case for assignment operator: copy empty rqueue"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.edgeAssignmentOperator(rqueue)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  {
    cout<<"test edge case for assignment operator: protect self assignment"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.protectSelfAssignment(rqueue)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  {
    cout<<"testing basic correctness"<<endl;
    RQueue rqueue(priorityFn1);
    if (tester.basicCorrectness(rqueue)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  

  return 0;
  }

int priorityFn1(const Student&student) {
  //priority value is determined based on some criteria
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  int priority = student.getYear() + student.getMajor() + student.getGroup();
  return priority;
}

int priorityFn2(const Student&student) {
  //priority is determined by an officer in registrar office
  //priority value falls in the range [0-6]
  //the smaller value means the higher priority
  return student.getPriority();
}
