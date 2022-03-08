#include "buffer.h"

Buffer::Buffer(int capacity){
    // **************************************
    // Implement the alternative constructor
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // **************************************
  if (1<=capacity){ //allocate memory only if size more than 1 
    m_buffer = new int [capacity];
    m_capacity = capacity;
  }else{
    m_buffer = NULL;
    m_capacity = 0;
  }
  
  m_count = 0; //initialize member variables
  m_start =0;
  m_end = 0;
}

void Buffer::clear(){
    // ***********************************
    // Implement clear() function
    // No need to set m_next to nullptr, 
    // it will be handled by linked list,
    // because it is used by linked list
    // ***********************************
  
  m_count = 0; // reinitialize all member variable and deallocate memory of Buffer array. 
  m_start =0;
  m_end = 0;
  if (m_capacity != 0){
    delete [] m_buffer;
  }
  m_capacity =0; 
  
  
}

Buffer::~Buffer(){
    clear();
}


int Buffer::count(){return m_count;}

int Buffer::capacity(){return m_capacity;}

bool Buffer::full(){
    // **************************
    // Implement full() function
    // **************************
  if(m_count == m_capacity){
    return true;
  }else{
    return false;}
}

bool Buffer::empty(){
    // **************************
    // Implement empty() function
    // **************************
  if(m_count == 0){
    return true;
  }else{
  
    return false;}
}

void Buffer::enqueue(int data){
    // ********************************
    // Implement enqueue(...) function
    // ********************************
  //  cout<<"B: inside enqueue"<<endl;
  if (full()){
    throw overflow_error("over_flow error at enqueue at buffer.cpp");
  }
  
  if( empty() ){ //first time adding data to array
    m_buffer[0] = data;
    m_end = 0;
    m_start = 0;
  }
  else if((m_count != m_capacity) && (m_end+1 == m_capacity)){ // in case index of m_end is at the end of the array, but array not full yet.  reset m_end;
    m_buffer[0] = data;
    m_end = 0 ; 
  }else{ // add data to the next index of m_end
    m_buffer[ m_end + 1 ] = data;
    m_end ++;  
  }
  
  m_count ++;
  
}

int Buffer::dequeue(){
    // *****************************
    // Implement dequeue() function
    // *****************************
  //  cout<<"B: inside dequeue"<<endl;
  
  if (empty()){
    throw underflow_error("under_flow error at dequeue at buffer.cpp");
  }else{
    if (m_start != m_capacity){ // dequeue data 
      m_buffer[m_start] = 0;
      m_start ++;
    }else{// when m_start is at the end of the array
      m_buffer[m_start] =0;
      m_start = 0;
    }
  }
  m_count --;
  
  return 0;
}

Buffer::Buffer(const Buffer & rhs){
    // *******************************
    // Implement the copy constructor
    // *******************************
  if (rhs.m_capacity>0){
    //if memory already allocated
    m_buffer = new int [rhs.m_capacity];
    if(!(rhs.m_count == 0)){   //if array already has itens in it
      for (int i=rhs.m_start;i<rhs.m_count;i++){
	m_buffer[i] = rhs.m_buffer[i];
      }
      for (int i=rhs.m_end; i>0;i--){
	m_buffer[i] = rhs.m_buffer[i];
      }
    }
  }else{
    m_buffer = NULL;
 
  }
  m_capacity = rhs.m_capacity; //copy variables 
  m_count = rhs.m_count;
  m_start = rhs.m_start;
  m_end = rhs.m_end;  
}

const Buffer & Buffer::operator=(const Buffer & rhs){
    // ******************************
    // Implement assignment operator
    // ******************************
  if (this != &rhs){
    clear();
    if (rhs.m_capacity>0){
      //if memory already allocated
      m_buffer = new int [rhs.m_capacity];
      if(!(rhs.m_count == 0)){   //if array already has itens in it
	for (int i=rhs.m_start;i<rhs.m_count;i++){
	  m_buffer[i] = rhs.m_buffer[i];
	}
	for (int i=rhs.m_end; i>0;i--){
	  m_buffer[i] = rhs.m_buffer[i];
	}
      }
    }else{
      m_buffer = new int;
      
  }
    m_capacity = rhs.m_capacity; //copy variables 
    m_count = rhs.m_count;
    m_start = rhs.m_start;
    m_end = rhs.m_end;    
  }
  
  return *this;
}

void Buffer::dump(){
    int start = m_start;
    int end = m_end;
    int counter = 0;
    cout << "Buffer size: " << m_capacity << " : ";
    if (!empty()){
        while(counter < m_count){
            cout << m_buffer[start] << "[" << start << "]" << " ";
            start = (start + 1) % m_capacity;
            counter++;
        }
        cout << endl;
    }
    else cout << "Buffer is empty!" << endl;
}
