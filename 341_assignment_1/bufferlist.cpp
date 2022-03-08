#include "bufferlist.h"
BufferList::BufferList(int minBufCapacity){
    // **************************************
    // Implement the alternative constructor
    // **************************************

  m_minBufCapacity = minBufCapacity;
  
  if (minBufCapacity <1){
    m_cursor = new Buffer (DEFAULT_MIN_CAPACITY); 
  }else{
    m_cursor = new Buffer (minBufCapacity);
  }
  m_listSize = 0;
  if (m_listSize ==0){
    m_cursor->m_next = m_cursor;}
  
  m_listSize++;
  
}
BufferList::~BufferList(){
    clear();
}

void BufferList::clear(){
    // *****************************
    // Implement clear() function
    // *****************************

  Buffer* temp = m_cursor;
  for (int i=1; i<m_listSize;++i){//delete until the last node 
    m_cursor = temp->m_next;
    delete temp;
    temp = m_cursor; 
  }
  delete temp; //delete last node 
    
   
}
void BufferList::enqueue(const int& data) {
    // ****************************************************************************
    // Implement enqueue(...) function
    // we always insert at the back, that would be the cursor
    // if the current cursor is full we create a new node as cursor then we insert
    // ****************************************************************************
  try {
    m_cursor->enqueue(data);
  }catch(overflow_error &e){
    Buffer* newBuffer;
    if ((m_minBufCapacity*MAX_FACTOR) != (m_cursor->capacity())){
      
      newBuffer = new Buffer ((m_cursor->capacity())*INCREASE_FACTOR); //make buffer with increased factor 
    }else{ 
      newBuffer = new Buffer (m_minBufCapacity);} // make buffer with min buffer capacity since previous buffer reached max size.

    
    newBuffer -> m_next = m_cursor -> m_next; //assign new m_cursor 
    m_cursor -> m_next = newBuffer;
    m_cursor = newBuffer;
    m_cursor ->enqueue(data);
    m_listSize ++;
  }

  
}

int BufferList::dequeue() {
    // *****************************
    // Implement dequeue() function
    // *****************************
  int dequeueNum = 0;
  try {
    dequeueNum = m_cursor->m_next->dequeue();
  }catch(underflow_error &e){ //if the last node is node is empty, remove the node. 
    if (m_cursor->empty()){
      throw underflow_error("bufferlist is empty! "); //if only one node in list and is empty, it will not remove the node. 
    }else{
    
      Buffer* deleteNode = m_cursor->m_next; //remove the last node and assign next oldest node to m_next of the m_cursor
      m_cursor->m_next = deleteNode->m_next;
      delete deleteNode;
      m_listSize --;
      dequeueNum = m_cursor -> m_next ->dequeue();
    }
  }
  return dequeueNum;
}

BufferList::BufferList(const BufferList & rhs){
    // *******************************
    // Implement the copy constructor
    // *******************************
  if (rhs.m_listSize>0){
    m_listSize = rhs.m_listSize;
    Buffer* temp = rhs.m_cursor->m_next;         
    m_cursor =  new Buffer(temp->m_capacity);  //make first linked list 
    
    if(!(temp->m_count == 0)){   //if array already has itens in it
      for (int i=temp->m_start;i<temp->m_count;i++){
	m_cursor->m_buffer[i] = temp->m_buffer[i];}
      for (int i=temp->m_end; i>0;i--){
	m_cursor->m_buffer[i] = temp->m_buffer[i];
      }}  
    m_cursor -> m_capacity = temp->m_capacity; //copy variables 
    m_cursor -> m_count = temp->m_count;
    m_cursor -> m_start = temp->m_start;
    m_cursor -> m_end = temp-> m_end;  
    m_cursor ->m_next = m_cursor;
    if (m_listSize >1){                       //if the link list has more than 2 lists, append new link list and change m_cursor. 
      for (int i=1 ; i<m_listSize ; i++ ){ 	
	temp = temp->m_next;
	
	Buffer* newBuffer = new Buffer(temp->m_capacity);
	if(!(temp->m_count == 0)){   //if array already has itens in it
	  for (int i=temp->m_start;i<temp->m_count;i++){
	    newBuffer->m_buffer[i] = temp->m_buffer[i];}
	  for (int i=temp->m_end; i>0;i--){
	    newBuffer->m_buffer[i] = temp->m_buffer[i];
	  }}  
	newBuffer -> m_capacity = temp->m_capacity; //copy variables 
	newBuffer -> m_count = temp->m_count;
	newBuffer -> m_start = temp->m_start;
	newBuffer -> m_end = temp-> m_end;  
	
	newBuffer ->m_next = m_cursor ->m_next;
	m_cursor -> m_next = newBuffer;
	m_cursor = newBuffer;}
    }
  }
}
	

const BufferList & BufferList::operator=(const BufferList & rhs){
  // ******************************
    // Implement assignment operator
    // ******************************
  if(this !=&rhs){ //avoid self assignmnt
    if (rhs.m_listSize>0){
      m_listSize = rhs.m_listSize;
      Buffer* temp = rhs.m_cursor->m_next;         
      m_cursor =  new Buffer(temp->m_capacity);  //make first linked list 
      
      if(!(temp->m_count == 0)){   //if array already has itens in it
	for (int i=temp->m_start;i<temp->m_count;i++){
	  m_cursor->m_buffer[i] = temp->m_buffer[i];}
	for (int i=temp->m_end; i>0;i--){
	  m_cursor->m_buffer[i] = temp->m_buffer[i];
	}}  
      m_cursor -> m_capacity = temp->m_capacity; //copy variables 
      m_cursor -> m_count = temp->m_count;
      m_cursor -> m_start = temp->m_start;
      m_cursor -> m_end = temp-> m_end;  
      m_cursor ->m_next = m_cursor;
      if (m_listSize >1){                       //if the link list has more than 2 lists, append new link list and change m_cursor. 
	for (int i=1 ; i<m_listSize ; i++ ){ 	
	  temp = temp->m_next;
	  
	  Buffer* newBuffer = new Buffer(temp->m_capacity);
	  if(!(temp->m_count == 0)){   //if array already has itens in it
	    for (int i=temp->m_start;i<temp->m_count;i++){
	      newBuffer->m_buffer[i] = temp->m_buffer[i];}
	    for (int i=temp->m_end; i>0;i--){
	      newBuffer->m_buffer[i] = temp->m_buffer[i];
	    }}  
	  newBuffer -> m_capacity = temp->m_capacity; //copy variables 
	  newBuffer -> m_count = temp->m_count;
	  newBuffer -> m_start = temp->m_start;
	  newBuffer -> m_end = temp-> m_end;  
	  
	  newBuffer ->m_next = m_cursor ->m_next;
	  m_cursor -> m_next = newBuffer;
	  m_cursor = newBuffer;}
      }
    }
  }
  return *this;
}

  


void BufferList::dump(){
  
    Buffer* temp = m_cursor->m_next;
    for(int i=0;i<m_listSize;i++){
        temp->dump();
        temp = temp->m_next;
        cout << endl;
    }
    cout << endl;
}
