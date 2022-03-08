#include "bufferlist.h"
class Tester{
public:
  bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
  bool BufferEnqueueFull(int size);
  bool BufferDequeueEmpty(int size);
  bool BufferCopyConstructor(const Buffer &buffer);
  bool BufferListCopyConstructor( BufferList &bufferList);
  bool BufferAssignOperator(const Buffer &buffer);
  bool BufferListAssignOperator( BufferList &bufferList);
  void BufListEnqueuePerformance(int numTrials, int N);
  bool BufferListEnqueueDequeue(BufferList &bufferList, int dataCount);
  bool BufferListDequeueEmpty(int size);

};

int main(){
  Tester tester;
  int bufferSize = 1000;
  Buffer buffer(bufferSize);
  BufferList bufferList(bufferSize);

  //test for buffer class 
  {
    //testing insertion/removal for 1 data item
    cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
    if (tester.BufferEnqueueDequeue(buffer, 1))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion/removal for half data size
    cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize/2))
            cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion/removal for full data size
    cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion in a full buffer
    cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
    if (tester.BufferEnqueueFull(1000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing deletion in an empty buffer
    cout << "\nTest case: Buffer class: Throwing exception while deleting in empty buffer:\n";
    if (tester.BufferDequeueEmpty(1000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }

  {
    //testing Buffer class copy constructor with buffer size less than zero
    cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
    Buffer buffer(-1);
    if (tester.BufferCopyConstructor(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class copy constructor with buffer size with zero
    cout << "\nTest case: Buffer class: Copy constructor, buffer size: 0 \n";
    Buffer buffer(0);
    if (tester.BufferCopyConstructor(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }

  {
    //testing Buffer class copy constructor with buffer size with 1 
    cout << "\nTest case: Buffer class: Copy constructor, buffer size:1\n";
    Buffer buffer(1);
    if (tester.BufferCopyConstructor(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class copy constructor with buffer size more than 1
    cout << "\nTest case: Buffer class: Copy constructor, buffer size:10000\n";
    Buffer buffer(10000);
    if (tester.BufferCopyConstructor(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class AssignOperator with buffer size less than zero
    cout << "\nTest case: Buffer class: Assign Operator, negative buffer size:\n";
    Buffer buffer(-1);
    if (tester.BufferAssignOperator(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class AssignOperator with buffer size zero
    cout << "\nTest case: Buffer class: Assign Operator, buffer size:0\n";
    Buffer buffer(0);
    if (tester.BufferAssignOperator(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class AssignOperator with buffer size 1
    cout << "\nTest case: Buffer class: Assign Operator, buffer size:1\n";
    Buffer buffer(1);
    if (tester.BufferAssignOperator(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }
  {
    //testing Buffer class AssignOperator with buffer size more than 1 
    cout << "\nTest case: Buffer class: Assign Operator, buffer size:10000\n";
    Buffer buffer(10000);
    if (tester.BufferAssignOperator(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n"; 
  }

  //Test for buffer list class
  {
    //testing insertion/removal for 1 data size
    cout << "\nTest case: BufferList class: Inserting/removing 1 data size:\n";
    if (tester.BufferListEnqueueDequeue(bufferList, 1))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion/removal for 10x data size
    cout << "\nTest case: BufferList class: Inserting/removing 10x data size:\n";
    if (tester.BufferListEnqueueDequeue(bufferList, 10 * bufferSize))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing deletion in an empty bufferList
    cout << "\nTest case: BufferList class: Throwing exception while deleting in empty bufferList:\n";
    if (tester.BufferListDequeueEmpty(10000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing copy constructor of bufferlist
    cout << "\nTest case: BufferList class: copy constructor with several empty linked list"<<endl;
    BufferList aBufferList(10000);
    if (tester.BufferListCopyConstructor(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
  }
  {
    //testing copy constructor of bufferlist with one linked list
    cout << "\nTest case: BufferList class: copy constructor with empty linked list"<<endl;
    BufferList aBufferList(1000);
    if (tester.BufferListCopyConstructor(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
  }
  //testint copy constructor of bufferlist with negative number 
  {
    cout<<"\nTest case: BufferList class: copy constructor with negative number"<<endl;
    BufferList aBufferList(-1);
    if (tester.BufferListCopyConstructor(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else{
      cout<<"\tTest failed!\n";
    }
  }
  {
    //Testing copy constructor with object in the linked list
    cout<<"\nTest case: BufferList class: copy constructor with object in linked list"<<endl;
    BufferList aBufferList(1000);
    for (int i =0; i<10000;i++){
      aBufferList.enqueue(i);}
    if (tester.BufferListCopyConstructor(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
  }

  //testing assignment operator with one empty linked list
  {
    cout<<"\nTest case: BufferList class: assign operator with one empty linked list"<<endl;
    BufferList aBufferList(1000);
    if (tester.BufferListAssignOperator(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
    
  } 
  {
    //Testing assignment operator with several empty linked list
    cout<<"\nTest case: BufferList class: assign operator with several empty linked list"<<endl;
    BufferList aBufferList(10000);
    if (tester.BufferListAssignOperator(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
  }
  {
    //Testing assignment operator with negative number 
    cout<<"\nTest case: BufferList class: assign operator with negative number"<<endl;
    BufferList aBufferList(-1);
    if (tester.BufferListAssignOperator(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
  }
  {
    //Testing assignment operator with object in the linked list
    cout<<"\nTest case: BufferList class: assign operator with object in linked list"<<endl;
    BufferList aBufferList(1000);
    for (int i =0; i<10000;i++){
      aBufferList.enqueue(i);}
    if (tester.BufferListAssignOperator(aBufferList)){
      cout <<"\tTest passed!\n"<<endl;}
    else
      cout <<"\tTest failed!\n";
    
  } 
  
  {  
    //Measuring the efficiency of insertion functionality
    cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
    int M = 5;//number of trials
    int N = 10000;//original input size
    tester.BufListEnqueuePerformance(M, N);
  }
 
  
  {
    //an example of BufferList::dump()
    cout << "\nHere is an example of a linked list:" << endl;
    BufferList bufferList(5);
    for (int i=40;i>0;i--)
      bufferList.enqueue(i);
    bufferList.dump();
  }
  
  return 0;
}

bool Tester::BufferListAssignOperator( BufferList &bufferList){
  BufferList copyList = bufferList;
  if (bufferList.m_cursor -> m_next->empty()){
    Buffer* tempCopy = copyList.m_cursor;
    Buffer* tempBuffer = bufferList.m_cursor;
    for (int i=0;i<bufferList.m_listSize;i++){
      if (&tempCopy == &tempBuffer){
	return false;}
      tempCopy = tempCopy ->m_next;
      tempBuffer = tempBuffer ->m_next; 
    }
  }else{
    Buffer* temp = copyList.m_cursor;
    temp->clear();
    try{
      bufferList.dequeue(); //should give an error if original linked list m_cursor does not have any item in it 
    }catch(...){
      return false;
    }
  }
  return true;	
}
bool Tester::BufferListCopyConstructor( BufferList &bufferList){
  BufferList copyList(bufferList);
  if (bufferList.m_cursor -> m_next->empty()){
    Buffer* tempCopy = copyList.m_cursor;
    Buffer* tempBuffer = bufferList.m_cursor;
    for (int i=0;i<bufferList.m_listSize;i++){
      if (&tempCopy == &tempBuffer){
	return false;}
      tempCopy = tempCopy ->m_next;
      tempBuffer = tempBuffer ->m_next; 
    }
  }else{
    Buffer* temp = copyList.m_cursor;
    temp->clear();
    try{
      bufferList.dequeue(); // should give an error if the original linked list m_cursor does not have an item in it 
    }catch(...){
      return false;
    }
  }
  return true;
  
}
bool Tester::BufferAssignOperator(const Buffer &buffer){
  Buffer copy = (buffer);
  //the case of empty object
  if (buffer.m_capacity == 0 && copy.m_capacity == 0){
    return true;
  }
  //the case that sizes are the same and the array pointer are not the same
  else if(buffer.m_capacity == copy.m_capacity && buffer.m_buffer != copy.m_buffer){
    if (buffer.m_count == 0 && copy.m_count == 0){ //if array is empty
      return true;
    }
    
    for (int i=0; i<buffer.m_capacity;i++){//check if pointer are different
      if (&buffer.m_buffer[i]== &copy.m_buffer[i]){
	return false;}}
    
    for (int i=buffer.m_start;i<buffer.m_count;i++){ //check data 
      if (buffer.m_buffer[i] != copy.m_buffer[i]){
	return false; }}
    for (int i = buffer.m_end; i>=0; i--){
      if (buffer.m_buffer[i] != copy.m_buffer[i]){
	return false;}}
    
    return true;
  }else{
    //everything else
    return false;}


}
bool Tester::BufferCopyConstructor(const Buffer &buffer){
  Buffer copy(buffer);
  //the case of empty object
  if (buffer.m_capacity == 0 && copy.m_capacity == 0){
    return true;
  }
  //the case that sizes are the same and the array pointer are not the same
  else if(buffer.m_capacity == copy.m_capacity && buffer.m_buffer != copy.m_buffer){
    if (buffer.m_count == 0 && copy.m_count == 0){ //if array is empty
      return true;
    }
    
    for (int i=0; i<buffer.m_capacity;i++){//check if pointer are different
      if (&buffer.m_buffer[i]== &copy.m_buffer[i]){
	return false;}}
    
    for (int i=buffer.m_start;i<buffer.m_count;i++){ //check data 
      if (buffer.m_buffer[i] != copy.m_buffer[i]){
	return false; }}
    for (int i = buffer.m_end; i>=0; i--){
      if (buffer.m_buffer[i] != copy.m_buffer[i]){
	return false;}}
    
    return true;
  }else{
    //everything else
    return false;}
  
}


void Tester::BufListEnqueuePerformance (int numTrials, int N){
  //Measuring the efficiency of insertion algorithm with system clock ticks
  //clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
  //dividing a count of clock ticks by CLOCK_PER_SEC yields the number of seconds.
  
  const int a = 2;//scaling factor for input size 
  double T = 0.0; //to store running times.
  clock_t start, stop; //stores the clock ticks while runnign the program
  BufferList bufferList(1000);
  for (int k=0;k<numTrials-1;k++){
    start = clock();
    for (int i=0;i<N;i++){
      bufferList.enqueue(i);
    }
    stop = clock();
    T = stop - start;
    
    cout<<"Inserting "<< N<<" members took "<<T<<" clock ticks ("<<T/CLOCKS_PER_SEC<<" seconds)!"<<endl;
    //   bufferList.dump();
    for (int k=0;k<N;k++){
      bufferList.dequeue();
    }
    N = N*a; //increse the input size by the scaling factor
  }
}

bool Tester::BufferEnqueueDequeue(Buffer &buffer, int dataCount){
  
  try{
    for (int i=0;i<dataCount;i++){
      buffer.enqueue(i);
    }
  }catch(...){
    return false;
  }
  try{
    for (int i=0;i<dataCount;i++){
      buffer.dequeue();
    }
  }catch(...){
    return false;
  }
  return true; 
}
bool Tester::BufferListEnqueueDequeue(BufferList &bufferList, int dataCount){
  try{
    for (int i=0;i<dataCount;i++){
      bufferList.enqueue(i);
    }
  }
  catch(overflow_error &e){
  }
  catch(...){
    return false;
  }
  try{
    for (int i=0; i<dataCount; i++){
      bufferList.dequeue();
    }
  }catch(underflow_error &e){}
  catch(...){
    return false;
  }
  return true;
}

bool Tester::BufferEnqueueFull(int size){
  Buffer aBuffer(size);
  for (int i=0;i<size;i++)
    aBuffer.enqueue(i);
  try{
    //trying to insert in a full buffer
    aBuffer.enqueue(size+1);
    }
  catch(overflow_error &e){
    //the exception that we expect
    return true;
  }
  catch(...){
        //any other exception, this case is not acceptable
    return false;
  }
  //no exception thrown, this case is not acceptable
  return false;
}
bool Tester::BufferListDequeueEmpty(int size){
  BufferList aBufferList(size);
  try{
    //trying to delete in a empty buffer
    aBufferList.dequeue();
  }catch (underflow_error &e){
    //the exception that we expect
    return true;
  }
  catch(...){
    //any other exceptionm this case is not acceptable
    return false;
  }
  //no exception thrown, this case is not acceptable
  return false;
  
}


bool Tester::BufferDequeueEmpty(int size){
  Buffer aBuffer(size);
  try{
    //trying to delete in a empty buffer
    aBuffer.dequeue();
  }catch (underflow_error &e){
    //the exception that we expect
    return true;
  }
  catch(...){
    //any other exceptionm this case is not acceptable
    return false;
  }
  //no exception thrown, this case is not acceptable
  return false;
}
