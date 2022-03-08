#include "utree.h"
#include <random>

#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
  bool testBasicDTreeInsert(DTree& dtree);
  bool testDTreeDelete1(DTree& dtree);
  bool testDTreeDelete2(DTree& dtree);
  bool testBasicUTreeInsert(UTree& utree);
  bool testDTreeOverload(DNode* newNode,DNode* oldNode);
  bool testDTreeBSTProperty(DNode* node);
  bool testDTreeBalance(DNode* node);
  bool testDTreeRemove(DTree& dtree);
  bool testUTreeRemove(UTree& utree);
  bool testDTreeRetrieve(DTree& dtree);
  bool testUTreeInsertSame(UTree& utree);
  bool testUTreeRebalance(UTree& utree);
  bool testUTreeRemoveUser();
  bool testUTreeRemoveUserNotFound();
  bool testUTreeBSTProperty();
  bool testUTreeBSTPropertyHelper(UNode* node);
  bool testUTreeAVLProperty();
  bool testUTreeAVLPropertyHelper(UNode* node);
  bool testDTreeRemoveEmpty(DTree& dtree);
  bool testUTreeRemoveEmpty();
};

bool Tester::testUTreeRemoveEmpty(){
  UTree utree;

  DNode* node = nullptr;

  bool result = utree.removeUser("a",1,node);

  if (!result){return true;}
  else{return false;}
}
bool Tester::testDTreeRemoveEmpty(DTree& dtree){
  bool result = dtree.removeHelper(1);
  if (result){
    return false;
  }else{
    return true;}
}


bool Tester::testDTreeRemove(DTree& dtree){
    
  dtree.insert(Account("",10,0,"",""));
  dtree.insert(Account("",16,0,"",""));
  dtree.insert(Account("",5,0,"",""));
  dtree.insert(Account("",4,0,"",""));
  dtree.insert(Account("",6,0,"",""));     
  dtree.removeHelper(5);
  dtree.removeHelper(4);
  dtree.removeHelper(6);
  for (int i=0;i<3; i++){
    Account newAcct = Account("", i,0,"","");
    dtree.insert(newAcct);
  }
  if ((dtree.retrieve(5) == nullptr)&&(dtree.retrieve(4)==nullptr)&&(dtree.retrieve(6)==nullptr))
    {return true;}
  return false;
} 
bool Tester::testDTreeBalance(DNode* node){
  if (node == nullptr){
	return false;}

  int leftSize;
  int rightSize;
  if (node->_left != nullptr){
    leftSize = node->_left->getSize();
  }else{
    leftSize = 0;
  }
  if (node->_right != nullptr){
    rightSize = node ->_right->getSize();
  }else{
    rightSize = 0;
  }
  if ((leftSize >= 4)||(rightSize >= 4)){
    int bigNum;
    int smallNum;
    if (leftSize > rightSize){
      bigNum = leftSize;
      smallNum = rightSize;
    }else{
      bigNum = rightSize;
      smallNum = leftSize;
    }
    if ((smallNum == 0) && (bigNum >= 4)){ //cases where 50% bigger.
      return true;
    }else if (bigNum / smallNum >= 1.5){
      return true;
    } else{
      return false;
    } 
  }else
    return false;
  return false;
}



bool Tester::testDTreeBSTProperty(DNode* node){
  if (node == nullptr){
    return true;}
  if ((node->_left != nullptr)&&(node->_left->getDiscriminator() > node->getDiscriminator())){
    return false;}
  if ((node->_right != nullptr)&&(node->_right->getDiscriminator() < node->getDiscriminator())){
    return false;}

  if ((!(testDTreeBSTProperty(node->_left))) || (!(testDTreeBSTProperty(node->_right)))){
    return false;}
  
  return true;
}

bool Tester::testDTreeOverload(DNode* newNode,DNode* oldNode){
  if (newNode != nullptr){
    if ((&newNode == &oldNode)||(!(newNode->getDiscriminator() == oldNode->getDiscriminator()))||(!(newNode->getSize() ==oldNode->getSize()))||
	(!(newNode->getSize() == oldNode->getSize()))||(!(newNode->isVacant() ==oldNode->isVacant()))||(!(newNode->getNumVacant() ==oldNode->getNumVacant()))
	||(!(newNode->getUsername() == oldNode->getUsername()))){
      return false;
    }
    testDTreeOverload(newNode->_left,oldNode->_left);
    testDTreeOverload(newNode->_right,oldNode->_right);
  }
  return true;
}
bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < 5; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    
    return allInserted;
}
//check if delete was found.  return true if found, return false when not found 
bool Tester::testDTreeDelete1(DTree& dtree){
  int disc = 200;
  Account newAcct = Account("",disc,0,"","");
  dtree.insert(newAcct);
  bool deleteFound = dtree.removeHelper(disc);
  return deleteFound;
}

//check if delete was not found.  return true if found, return false, when not found 
bool Tester::testDTreeDelete2(DTree& dtree){
  int disc = 200;
  Account newAcct = Account("",disc,0,"","");
  dtree.insert(newAcct);
  bool deleteFound = dtree.removeHelper(disc +1);

  return deleteFound;
}

bool Tester::testDTreeRetrieve(DTree& dtree){
  
  dtree.insert(Account("a",1,0,"",""));
  dtree.insert(Account("a",2,0,"",""));
  dtree.insert(Account("a",3,0,"",""));
  dtree.insert(Account("a",4,0,"",""));
  dtree.insert(Account("a",5,0,"",""));
  dtree.insert(Account("a",6,0,"",""));

  DNode* node = dtree.retrieve(5);
  if (node->getDiscriminator() == 5)
    return true;
  else{return false;}
}

bool Tester::testBasicUTreeInsert(UTree& utree) {
    string dataFile = "accounts.csv";
    try {
      utree.loadData(dataFile);
    } catch(std::invalid_argument e) {
      std::cerr << e.what() << endl;
      return false;
    }

    return true;
}

bool Tester::testUTreeRemove(UTree& utree){
  utree.insert((Account("a",1,0,"","")));
  utree.insert((Account("a",2,0,"","")));  
  utree.insert((Account("a",2,0,"","")));  
  utree.insert((Account("a",4,0,"","")));  
  utree.insert((Account("a",5,0,"","")));
  
  DNode* node = nullptr;
  bool result = utree.removeUser("a",1,node);

  if ((utree.retrieveUser("a",1)->isVacant()) && (result)){
    return true;}
  return false;
}

bool Tester::testUTreeInsertSame(UTree& utree){
  utree.insert((Account("a",3,0,"","")));
  utree.insert((Account("a",3,0,"","")));

  if (utree.retrieve("a")->getDTree()->getNumUsers() == 1){return true;}
  return false;
}

bool Tester::testUTreeRebalance(UTree& utree){
  utree.insert((Account("a",1,0,"","")));
  utree.insert((Account("b",1,0,"","")));
  utree.insert((Account("c",1,0,"","")));
  if ((utree.retrieve("b")->_left == utree.retrieve("a")) && (utree.retrieve("b")->_right == utree.retrieve("c")) && (utree.retrieve("b")->getHeight() == 1)
      &&(utree.retrieve("a")->getHeight() == 0)&&(utree.retrieve("c")->getHeight() == 0)){
    return true;}
  else{return false;}
  
}

bool Tester:: testUTreeRemoveUser(){
  UTree utree;
  utree.insert((Account("b",1,0,"","")));
  utree.insert((Account("a",1,0,"","")));
  utree.insert((Account("d",1,0,"","")));
  utree.insert((Account("c",1,0,"","")));
  utree.insert((Account("e",1,0,"","")));
  DNode* node = nullptr;
  bool result = utree.removeUser("d",1,node);
  if (utree.retrieve("d") == nullptr){
    return true;}else{return false;}
  
}
bool Tester::testUTreeAVLPropertyHelper(UNode* node){
  if(node!=nullptr){
    int leftHeight = -1;
    int rightHeight =-1;
    
    if (node->_left !=nullptr){
      leftHeight = node->_left->getHeight();
    }
    if (node->_right !=nullptr){
      rightHeight = node->_right->getHeight();
    }
    if ((leftHeight - rightHeight >1) || (leftHeight - rightHeight <-1)){
      return false;
    }
  
  testUTreeAVLPropertyHelper(node->_left);
  testUTreeAVLPropertyHelper(node->_right);
}
  return true;
}
bool Tester::testUTreeAVLProperty(){
   UTree utree;	
   string dataFile = "accounts.csv"; 
   utree.loadData(dataFile);
   
   if (testUTreeAVLPropertyHelper(utree._root)){return true;}
else{return false;}

}


bool Tester::testUTreeBSTPropertyHelper(UNode* node){
  if (node == nullptr){
    return true;}
  if ((node->_left != nullptr)&&(node->_left->getUsername() > node->getUsername())){
    return false;}
  if ((node->_right != nullptr)&&(node->_right->getUsername() < node->getUsername())){
    return false;}

  if ((!(testUTreeBSTPropertyHelper(node->_left))) || (!(testUTreeBSTPropertyHelper(node->_right)))){
    return false;}
  
  return true;

}
bool Tester::testUTreeBSTProperty(){
   UTree utree;	
   
   string dataFile = "accounts.csv"; 
   utree.loadData(dataFile);
   
   if (testUTreeBSTPropertyHelper(utree._root)){return true;}
   else{return false;}

}
bool Tester::testUTreeRemoveUserNotFound(){
  
  UTree utree;

  utree.insert((Account("a",1,0,"","")));
  utree.insert((Account("b",2,0,"","")));
  utree.insert((Account("c",3,0,"","")));
  utree.insert((Account("d",4,0,"","")));
  
  DNode* node = nullptr;
  bool result = utree.removeUser("e",5,node);
  if (result == true)
    {return false;}
  else{
    return true;}
}

int main() {
    Tester tester;
    //DTree tests

    {
      DTree dtree;
      cout<<"test DTree remove empty tree"<<endl;
      if(tester.testDTreeRemoveEmpty(dtree))
	{cout<<"success"<<endl;}
      else{cout<<"fail"<<endl;}
    }
    {//testing dtree retrieve function
      DTree dtree;
      cout<<"Testing DTree retrieve..."<<endl;
      if (tester.testDTreeRetrieve(dtree))
	{cout<<"success"<<endl;}
      else{cout<<"fail"<<endl;}
    }
    {//testing dtree inserttion fucntion
      DTree dtree;
      cout << "Testing DTree insertion...";
      if(tester.testBasicDTreeInsert(dtree)) {
	cout << "test passed" << endl;
      } else {
        cout << "test failed" << endl;}
    }
    //testing delete function
    {
      DTree dtree;
      cout<< "Tester DTree delete with 1 node and find the correct one..."<<endl;
      if (tester.testDTreeDelete1(dtree)){
	cout<<"test passed: node was deleted"<<endl;
      }else{
	cout << "test failed"<<endl;}
    }
    {//testing delete function
      DTree dtree;
      cout<<"Tester DTree delete with 1 node and not find it..."<<endl;
      if (!tester.testDTreeDelete2(dtree)){
	  cout<<"test passed; node was not found"<<endl;
	}else{
	  cout<<"test failed"<<endl;}
    }
    {//testing if overload assignment operator made a deep copy
      DTree dtree;
      cout<<"Tester DTree: testing overload assignment operator..."<<endl;
      DTree newCopy;
      for(int i = 0; i < 5; i++) {
	int disc = RANDDISC;
	Account newAcct = Account("", disc, 0, "", "");
	dtree.insert(newAcct);}
      newCopy = dtree;
      if (tester.testDTreeOverload(newCopy.getRoot(),dtree.getRoot())){
        cout<<"test passed, made a deepcopy"<<endl;
      }else{
	cout<<"test failed"<<endl;}
    }
  
    {//test if BST property is true in dtree
      DTree dtree;
      cout<<"Tester DTree; test if BST property is true..."<<endl;
      for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);}
      if (tester.testDTreeBSTProperty(dtree.getRoot())){
	cout<<"test passed, BST property maintained"<<endl;
      }else{cout<<"test failed"<<endl;}
    }
    {//test if the tree is DISCORD balanced
      DTree dtree;
      cout<<"Tester DTree; test if tree is balanced..."<<endl;
      for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        dtree.insert(newAcct);}
      if (!tester.testDTreeBalance(dtree.getRoot())){
	cout<<"test passed, tree balance maintained"<<endl;
      }else{cout<<"test failed"<<endl;}
    }
    {//test if dtree rearrange after remove
      DTree dtree;
      cout<<"Tester DTree; test if tree remove function work properly after rearrangement..."<<endl;
      if (tester.testDTreeRemove(dtree)){
	cout<<"test passed, tree remove function work property"<<endl;
      }else{cout<<"test failed"<<endl;}
    }
    
   
{
    UTree utree;
    cout << "\n\nTesting UTree insertion...";
    if(tester.testBasicUTreeInsert(utree)) {
      cout << "test passed" << endl;
    } else {
      cout << "test failed" << endl;
    } 
    cout << "Resulting UTree:" << endl;
    utree.dump();
    cout << endl;
 }
//testing remove funciton
 {
   UTree utree;
   cout <<"\n\nTesting UTree remove...";
   if(tester.testUTreeRemove(utree)){
     cout<<"test passes"<<endl;
   }else{cout<<"test failed"<<endl;}
 }
 //test if insert same account cause problem
 {
   UTree utree;
   cout<<"\n\nTesting Utree insert the same account"<<endl;
   if(tester.testUTreeInsertSame(utree)){
     cout<<"test passed"<<endl;
   }else{cout<<"test failed"<<endl;}
 }
 //test if the tree rebalances
 {
   UTree utree;
   cout<<"\n\nTesting Utree rebalance"<<endl;
   if (tester.testUTreeRebalance(utree)){
     cout<<"test passed"<<endl;}
   else{cout<<"test failed"<<endl;}
 }
 //test remove user function
 {
   UTree utree;
   cout<<"\n\nTestomg Utree remove user"<<endl;
   if (tester.testUTreeRemoveUser()){
     cout<<"test passed"<<endl;}
   else{cout<<"test failed"<<endl;}
 }
 //test removing account that does not exist
 {
   UTree utree;
   cout<<"\n\nTesting UTree edge case... removing account that is not found"<<endl;
   if(tester.testUTreeRemoveUserNotFound()){
     cout<<"test passed"<<endl;}
   else{cout<<"test failed"<<endl;}
 }
 //check BST property of UTree
{
   cout<<"\n\nTesting UTree BST property"<<endl;
   if(tester.testUTreeBSTProperty()){cout<<"test passed"<<endl;}
   else{cout<<"test failed"<<endl;}
}
//chech AVL property of UTree
{
   cout<<"\n\nTesting UTree AVL property"<<endl;
   if(tester.testUTreeAVLProperty()){cout<<"test passed"<<endl;}
   else{cout<<"test failed"<<endl;}

}
{
  cout<<"\nTest UTree remove empty tree"<<endl;
  if(tester.testUTreeRemoveEmpty()){cout<<"test passed"<<endl;}
  else{cout<<"test failed"<<endl;}
}
 return 0;
}
