// CMSC 341 - Spring 2021 - Project 4
// hash.cpp
// The impleme ntation of the class HashTable
#include "hash.h"
#include "math.h"
HashTable::HashTable(unsigned size, hash_fn hash){
  if (size < MINPRIME){
    m_capacity = MINPRIME;
  }else if (size > MAXPRIME){
    m_capacity = MAXPRIME;
  }else if (isPrime(size)){
    m_capacity = size;
  }else{
    m_capacity = findNextPrime(size);
  }
  m_hash = hash;
  m_currentProb = LINEAR;
  m_table = new Person [m_capacity];
  m_size = 0;
  m_numDeleted = 0;
  for (int i = 0; i<m_capacity;i++){
    m_table[i] = EMPTY;
  }
}

HashTable::~HashTable(){
  
  delete [] m_table;
  /*  for (int i=0; i<m_capacity;i++){
      delete m_table[i];
    }
  delete m_table; */
}

//return the index based on the returned hashed number and m_capacity
int HashTable::hashIndex(int stringNum){
  return (stringNum % m_capacity);
}

//return true if same key and serial found already in the hash table.
//return false if not found
bool HashTable::sameFinder(Person person){
  for (int i =0; i<m_capacity;i++){
    if (m_table[i].key() == person.key()&& m_table[i].serial()==person.serial()){
      return true;
    }
  }
  return false;
}
//return true if it successfully intert person.
//return false if it failed to insert person.
bool HashTable::insert(Person person){
  hash_fn hash = m_hash;                            //get the index to insert
  int convertedNum= hash(person.key());
  int index = hashIndex(convertedNum);                    
  if (sameFinder(person)){                         //look for copy 
    return false;
  }
   if (m_table[index] == EMPTY){                   //if index is already empty before.  if DELETED, it will treat it as already inserted 
    m_table[index] = person;
    m_size++;
  }else{
    int i = 0; 
    if (m_currentProb == LINEAR){                  //different probing function used based on m_currentProb                 
      while (!(m_table[index] == EMPTY)){
	index = ((hash(person.key()) + i) % m_capacity);
	i++;}
    }else if (m_currentProb == QUADRATIC){
      while (!(m_table[index] == EMPTY)){
	index = ((((hash(person.key()))%m_capacity)+(i*i))% m_capacity);
	i++;}
    }
    m_table[index] = person;
    m_size++;
    if (lambda()>(float(1)/float(2))){                //if trigger the condition for rehash for insert 
      (m_currentProb == LINEAR ? setProbingPolicy(QUADRATIC): setProbingPolicy(LINEAR));
    }
    return true;
  }
  return false;
}
//return true if removed
//return false if it did not find it/ failed to remove. 
bool HashTable::remove(Person person){
  hash_fn hash = m_hash;
  int index = hashIndex(hash(person.key()));
  int i = 0;
  if (m_currentProb == LINEAR){     //delete only if key and serial is the same.  
    while (!(m_table[index]==EMPTY)){
      if (m_table[index].key() == person.key()&&(m_table[index].serial()==person.serial())){
	m_table[index] = DELETED;
	m_numDeleted++;
	if (deletedRatio()>(float(1)/float(4))){           //rehash if fit criteria 
	  setProbingPolicy(QUADRATIC);
	}
	return true;
      }
      index = ((hash(person.key()) + i) % m_capacity);  //find using linear probing
      i++;}
  }else if (m_currentProb == QUADRATIC){
    while (!(m_table[index] == EMPTY)){
      if (m_table[index].key() == person.key()&&(m_table[index].serial()== person.serial())){
	m_table[index] = DELETED;
	m_numDeleted++;
	if (deletedRatio()>(float(1)/float(4))){   //rehash if fit criteria 
	  setProbingPolicy(LINEAR);
	}
	return true;
      }
      index = ((((hash(person.key()))%m_capacity)+(i*i))% m_capacity);  //find using quadratic probing 
      i++;}
  }
  return false;
}

//rehash the entire table 
void HashTable::setProbingPolicy(probing prob){
  if (m_currentProb == prob){ //does not change probing if assigned same probing as current probing 
    return;
  }
  Person* old_table = new Person [m_capacity];             //create a new table with all the entries.  Remove the DELETED object at this moment 
  int index = 0;
  int oldCapacity = 0;
  for (int i = 0; i<m_capacity;i++){                       
    if (!(m_table[i]==EMPTY)&&!(m_table[i]==DELETED)){
      old_table[index].setKey(m_table[i].key());
      old_table[index].setSerial(m_table[i].serial());
      index++;
      oldCapacity++;
    }}
  int newSize;
  int oldSize = m_capacity;
  delete [] m_table;      //delete current m_table and make allocate a new memory based on the speficic criteria. 
  if ((deletedRatio()>(1/4))||(lambda()>(1/2))){
    newSize = findNextPrime(4*(m_size-m_numDeleted));
    m_table = new Person [newSize];                 //smallest prime greated than 4 times the current data point 
  }else{
    m_table = new Person [m_capacity];             //same size if setprobingPolicy was not called from insert/delete 
    newSize = m_capacity;
  }
  for (int i=0;i<newSize;i++){  //reinitialize m_table 
    m_table[i]=EMPTY;
  }
  if (m_currentProb == QUADRATIC){  //change probing of hash 
    m_currentProb = LINEAR;} 
  else{m_currentProb = QUADRATIC;}
  m_capacity = newSize;
  m_numDeleted = 0;
  m_size = 0;
  
  for (int i=0;i<oldCapacity;i++){                              //insert datapoint from old table to new table 
    Person person(old_table[i].key(),old_table[i].serial());
    insert(person);
  }
  delete [] old_table;
}

float HashTable::lambda() const {
  return (float(m_size)/float(m_capacity));
}

float HashTable::deletedRatio() const {
  return (float(m_numDeleted)/float(m_size));
}

void HashTable::dump() const {
  for (int i = 0; i < m_capacity; i++) {
    cout << "[" << i << "] : " << m_table[i] << endl;
  }
}

bool HashTable::isPrime(int number){
    // If number is prime this function returns true
    // otherwise it returns false
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we won't go beyond MAXPRIME
    //the smallest prime would be next after MINPRIME
    if (current < MINPRIME) current = MINPRIME;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}
