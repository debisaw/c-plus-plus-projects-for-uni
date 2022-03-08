// CMSC 341 - Spring 2021 - Project 4
// driver.cpp
// Simple driver program for use with HashTable class
#include "hash.h"
#include <random>

// Using a fixed seed value generates always the same sequence
// of pseudorandom numbers, e.g. reproducing scientific experiments
// here it helps us with testing since the same sequence repeats
std::mt19937 generator(10);// 10 is the fixed seed value

// We distribute the pseudorandom numbers uniformaly within
// the range [1000,99999]
std::uniform_int_distribution<> distribution(1000, 99999);

// The hash function used by HashTable class
unsigned int hashCode(const string str);

// the function to generate random serial numbers
unsigned int vaccineSerial() {return distribution(generator);}

class Tester{ // Tester class to implement test functions
public:
  bool testInsertLinear(HashTable& aTable) ;
  bool testFindCorrectDelete(HashTable& aTable);
  bool testDifferentSerialDel(HashTable& aTable);
  bool testInsertLinearProbing(HashTable& aTable);
  bool testInsertQuadraticProbing(HashTable& aTable);
  bool testTriggerRehash(HashTable& aTable);
  bool testChangeProb(HashTable& aTable);
  bool testTriggerRehashDelete(HashTable& aTable);
  bool testMinPrime(HashTable& aTable);
  bool testNonPrime(HashTable& aTable);
  bool testInsertSame(HashTable& aTable);
};
bool Tester::testInsertSame(HashTable& aTable){
  aTable.insert(Person("Dan",1));
  if (aTable.insert(Person("Dan",1))){
    return false;
  }
  return true;
}
bool Tester::testNonPrime(HashTable& aTable){
  cout<<aTable.m_capacity<<endl;
  if (aTable.m_capacity == 103){   //table initialized with 102, thus m_capacity becomes next smallest prime bigger than initialized value, which is 103 .
    return true;
  }
  return false;
}

bool Tester::testMinPrime(HashTable& aTable){
  cout<<aTable.m_capacity<<endl;
  if (aTable.m_capacity == 101){   //table initialized with 8, thus m_capacity becomes MINPRIME.
    return true;
  }
  return false;
}
bool Tester::testTriggerRehashDelete(HashTable& aTable){
  for(int i=0;i<51;i++){
    aTable.insert(Person("John",i));
  }
  for (int i = 0;i<14;i++){
    aTable.remove(Person("John", i));}
  if (aTable.m_capacity == 157){   //m_capacity after removing 13 objects from rehashed table
    return true;
  }
  return false;
}

bool Tester::testChangeProb(HashTable& aTable){
  aTable.insert(Person("Dan",0));
  aTable.insert(Person("Dan",1));
  aTable.insert(Person("Dan",2));
  
  aTable.setProbingPolicy(QUADRATIC);
  hash_fn hash = aTable.m_hash;
  int index = (((hash("Dan")% aTable.m_capacity)+(2*2))% aTable.m_capacity);
  if ((aTable.m_table[index].key() == "Dan") && (aTable.m_table[index].serial() == 2)) {
    return true;}
  return false;
}
bool Tester::testTriggerRehash(HashTable& aTable){
  for(int i=0;i<50;i++){
    aTable.insert(Person("John",i));
  }
  aTable.insert(Person("John",51));
  if (aTable.m_capacity == 211){ //m_capacity after rehash 
    return true;
  }
  return false;
}
bool Tester::testInsertQuadraticProbing(HashTable& aTable){
  aTable.setProbingPolicy(QUADRATIC);
  for (int i=0;i<9;i++){
    aTable.insert(Person("Dan",i));
  }
  aTable.remove(Person("Dan",4));
  aTable.insert(Person("Dan",20));
  hash_fn hash = aTable.m_hash;
  int index = (((hash("Dan")% aTable.m_capacity)+(9*9))%aTable.m_capacity);
  if (aTable.m_table[index].serial() == 20){
    return true;}

  return false;
}
bool Tester::testInsertLinearProbing(HashTable& aTable){
  aTable.remove(Person("e",4));
  aTable.insert(Person("a",4));
  if (aTable.m_table[1].key()=="a"){
    return true;
  }
  return false;
}
bool Tester::testDifferentSerialDel(HashTable& aTable){
  for (int i=0;i<10;i++){
    aTable.insert(Person("Dan",i));
  }
  if (aTable.remove(Person("Dan",20))){
    return false;
  }
  return true;
}

bool Tester::testFindCorrectDelete(HashTable& aTable){
  aTable.remove(Person("aa",5));
  if (aTable.m_table[71]==DELETED)
    return true;

  return false;
}
bool Tester::testInsertLinear(HashTable& aTable){
  string table [3]= {"d","e","f"} ;
  hash_fn hash = aTable.m_hash;
  
  for (int i=0;i<3;i++){
    aTable.insert(Person(table[i],i));
    int stringNum = hash(table[i]);
    int index = (stringNum % aTable.m_capacity);
    if ((aTable.m_size != 4+i) || (aTable.m_table[index].key() != table[i])){
      return false;
    }
  }
  
  return true;
}

int main(){
  Tester tester;
  {
    cout<<"test edge case: insert same key and serial: "<<endl;
    HashTable aTable(101,hashCode);
    if (tester.testInsertSame(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test edge case: non-prime: "<<endl;
    HashTable aTable(102,hashCode);
    if(tester.testNonPrime(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test edge case: min-prime: "<<endl;
    HashTable aTable(8,hashCode);
    if(tester.testMinPrime(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
  }
  cout<<endl;
  {
    cout<<"test rehash: delete"<<endl;
    HashTable aTable(101,hashCode);
    if(tester.testTriggerRehashDelete(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test rehash: change probing"<<endl;
    HashTable aTable(101,hashCode);
    if(tester.testChangeProb(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test rehash: insert"<<endl;
    HashTable aTable(101,hashCode);
    if(tester.testTriggerRehash(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test insert: quadratic probing"<<endl;
    HashTable aTable(101,hashCode);
    if(tester.testInsertQuadraticProbing(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test insert: linear probing"<<endl;
    HashTable aTable(101,hashCode);
    string table [5]= {"a","b","c","d","e"} ;
    for (int i=0;i<5;i++){
      aTable.insert(Person(table[i],i));
    }
    if(tester.testInsertLinearProbing(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test remove operation: try to remove non-existent serial"<<endl;
    HashTable aTable(101,hashCode);
    if (tester.testDifferentSerialDel(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test remove operation"<<endl;
    HashTable aTable(101,hashCode);
    for(int i =0;i<10;i++){
      aTable.insert(Person("aa",i));
    }
    if(tester.testFindCorrectDelete(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }
  {
    cout<<"test insert"<<endl;
    HashTable aTable(101,hashCode);
    aTable.insert(Person("a",1));
    aTable.insert(Person("b",2));
    aTable.insert(Person("c",3));
    if(tester.testInsertLinear(aTable)){
      cout<<"test passed"<<endl;
    }else{cout<<"test failed"<<endl;}
    cout<<endl;
  }

  
  

  
     // We use this temp array to store some data points for later use
   int tempSerials[50] = {0};
   int secondIndex = 0;
   // create a hash table with the size 101, and the hash function hashCode
   HashTable aTable(101,hashCode);
   int temp = 0;
   // we insert 50 Person objects with the same key, person's name is the key
   for (int i=0;i<50;i++){
      temp = vaccineSerial();// generates a random number
      if (i%3 == 0){//this saves 17 numbers from the generated numbers for later use
         tempSerials[secondIndex] = temp;
         cout << temp << " was saved for later use." << endl;
         secondIndex++;
      }
      // print the random numbers which are inserted
      cout << "Insertion # " << i << " => " << temp << endl;
      aTable.insert(Person("John", temp));
   }
   cout << "Message: dump after 50 insertions in a table with 101 buckets:" << endl;
   aTable.dump();
   
   // We insert a data point to change the load factor, this should initiate a rehash
   temp = vaccineSerial();
   cout << "Insertion # 51" << " => " << temp << endl;
   aTable.insert(Person("John", temp));
   cout << "Message: dump after 51st insertion, the rehash should have happended to a table with 211 buckets:" << endl;
   aTable.dump();
   
   // Now we remove some data points which were saved in tempSerials array
   // Deleting 13 data points changes the deleteRatio, it should initiate a rehash 
   for (int i = 0;i<14;i++)
      aTable.remove(Person("John", tempSerials[i]));
   cout << "Message: dump after 14 removes, a rehash should have happened to a table with 157 buckets," << endl;
   cout << "Message: after 13 removals the rehash happens, then the 14th removal will be tagged as DELETED in the new table." << endl;
   aTable.dump();
   cout << endl;  
   return 0;
}

// The implementation of the hash function
// you can copy this function to your mytest.cpp file
unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for ( int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}


