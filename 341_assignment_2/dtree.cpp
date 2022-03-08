/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
DTree::~DTree() {
  clear();
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {
  if (this != &rhs){
    this->clear();
    DNode* node = rhs._root;
    if (rhs._root !=nullptr){
      preOrderInsertAccount(node);                    //make DNode
      preOrderInsertData(this->_root,rhs._root);      //add values
    }else{
      this->_root = nullptr;
    }}
  return *this;
}
//helper for overload assignment 
void DTree::preOrderInsertAccount(DNode* node){
  if (node != nullptr){
    Account account = (node->getAccount());
    this->insert(account);
    if (node->_left != nullptr){
      preOrderInsertAccount(node->_left);
    }
    if (node->_right !=nullptr){
      preOrderInsertAccount(node->_right);
    }
  }}

void DTree::preOrderInsertData(DNode* newNode,DNode* oldNode){
  if (newNode!=nullptr){
    newNode->_size = oldNode->getSize();
    newNode->_numVacant = oldNode->getNumVacant();
    newNode->_vacant = oldNode->isVacant();

    preOrderInsertData(newNode->_left,oldNode->_left);
    preOrderInsertData(newNode->_right,oldNode->_right);
  }
}
/*helper for insert function*/

bool DTree::recursiveInsert(DNode* currentNode, Account newAcct){
  if (newAcct.getDiscriminator() < currentNode -> getDiscriminator()){        //insert in left child 
    if (currentNode -> _left == nullptr){
      DNode* node = new DNode(newAcct);
      currentNode ->_left = node;
      return true;}
    if ((currentNode->_left->isVacant())&& (retrieve(newAcct.getDiscriminator()) == nullptr)){      //in case the left child is vacant;
      DNode* nodeLeftChild = currentNode->_left->_left;
      DNode* nodeRightChild = currentNode->_left->_right;
      if ((nodeRightChild != nullptr) && (nodeLeftChild != nullptr)) {
	if ((nodeRightChild->getDiscriminator() > newAcct.getDiscriminator()) && (nodeLeftChild->getDiscriminator() < newAcct.getDiscriminator())){
	  currentNode->_left->getAccount()._username = newAcct._username;
	  currentNode->_left->_account._disc = newAcct._disc;
	  currentNode->_left->getAccount()._badge = newAcct._badge;
	  currentNode->_left->getAccount()._status = newAcct._status;
	  currentNode->_left->_vacant = false;
	  return true; 
	}
      }else if ((nodeRightChild != nullptr) && (nodeLeftChild == nullptr)) {
	if ((nodeRightChild->getDiscriminator()) > newAcct.getDiscriminator()){
	  currentNode->_left->getAccount()._username = newAcct._username;
	  currentNode->_left->_account._disc = newAcct.getDiscriminator();
	  currentNode->_left->getAccount()._badge = newAcct._badge;
	  currentNode->_left->getAccount()._status = newAcct._status;
	  currentNode->_left->_vacant = false; 
	  return true; 
	}
      }else if ((nodeRightChild == nullptr) && (nodeLeftChild != nullptr)){
	if ((nodeLeftChild->getDiscriminator()) < (newAcct.getDiscriminator())){
	  currentNode->_left->getAccount()._username = newAcct._username;
	  currentNode->_left->_account._disc = newAcct.getDiscriminator();
	  currentNode->_left->getAccount()._badge = newAcct._badge;
	  currentNode->_left->getAccount()._status = newAcct._status;
	  currentNode->_left->_vacant = false; 
	  return true; 
	}}}}
  if (newAcct.getDiscriminator() > currentNode -> getDiscriminator()){                           //insert in right child
    if (currentNode -> _right ==nullptr){
      currentNode->_right = new DNode(newAcct);
      return true;}    
    if ((currentNode->_right->isVacant())&& (retrieve(newAcct.getDiscriminator()) == nullptr)){    //in case the right child  is vacant
      DNode* nodeLeftChild = currentNode->_right->_left;
      DNode* nodeRightChild = currentNode->_right->_right;
      if ((nodeRightChild != nullptr) && (nodeLeftChild != nullptr)) {
	if ((nodeRightChild->getDiscriminator() > newAcct.getDiscriminator()) && (nodeLeftChild->getDiscriminator() < newAcct.getDiscriminator())){
	  currentNode->_right->getAccount()._username = newAcct._username;
	  currentNode->_right->_account._disc = newAcct._disc;
	  currentNode->_right->getAccount()._badge = newAcct._badge;
	  currentNode->_right->getAccount()._status = newAcct._status;
	  currentNode->_right->_vacant = false;
	  return true; 
	}
      }else if ((nodeRightChild != nullptr) && (nodeLeftChild == nullptr)) {
	if ((nodeRightChild->getDiscriminator()) > newAcct.getDiscriminator()){
	  currentNode->_right->getAccount()._username = newAcct._username;
	  currentNode->_right->_account._disc = newAcct.getDiscriminator();
	  currentNode->_right->getAccount()._badge = newAcct._badge;
	  currentNode->_right->getAccount()._status = newAcct._status;
	  currentNode->_right->_vacant = false; 
	  return true; 
	}
	
      }else if ((nodeRightChild == nullptr) && (nodeLeftChild != nullptr)){
	if ((nodeLeftChild->getDiscriminator()) < (newAcct.getDiscriminator())){
	  currentNode->_right->getAccount()._username = newAcct._username;
	  currentNode->_right->_account._disc = newAcct.getDiscriminator();
	  currentNode->_right->getAccount()._badge = newAcct._badge;
	  currentNode->_right->getAccount()._status = newAcct._status;
	  currentNode->_right->_vacant = false; 
	  return true; 
	}}}}

  if (newAcct.getDiscriminator() < currentNode ->getDiscriminator()){
    return recursiveInsert(currentNode-> _left,newAcct);
  }else if (newAcct.getDiscriminator() > currentNode ->getDiscriminator()){
    return recursiveInsert(currentNode->_right,newAcct);
  }else{
    return false;
  }
  return false;
}

/**
 * Dynamically allocates a new DNode in the tree. 
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {
  
  if(_root == nullptr){
    _root = new DNode(newAcct);
    return true; 
  }else{
    DNode* checkNode = retrieve(newAcct.getDiscriminator());    // check if it does not exist already 
    if (checkNode == nullptr){
      bool result = recursiveInsert(_root,newAcct);
      if (result ==true){
	updateSize(_root);
	updateNumVacant(_root);
	while (checkImbalanceHelper()){}     //correct imbalance in tree 
	return result;
      }else{
	return result;}
    }else{
      return false;}
  }
  return false;
}


/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */

bool DTree::remove(int disc, DNode*& removed) {
  if (_root == nullptr){
    cout<<"tree not made yet"<<endl;
    return false;
  }
  if (removed == nullptr){
    return false;
  }
  bool result = checkRemove(disc,removed);
  
  if (result||(remove(disc,removed->_left))||(remove(disc,removed->_right))){
    updateNumVacant(_root);
    return true;
  }else{
    return false;
  }
  return false; 
}
//change to vacant is it is not already 
bool DTree::checkRemove(int disc, DNode*& removed){
  if (removed !=nullptr){
    if (disc == removed ->getDiscriminator() && removed->isVacant() == false){
      removed -> _vacant = true;
      return true;
    }}
  return false;
}

bool DTree::removeHelper(int disc){
  bool result = remove(disc, _root);
  return result;  
}

//helper for retrieve
DNode* DTree::recursiveRetrieve(int disc, DNode* node){
  if(node!=nullptr){
    if (node->getDiscriminator() == disc){
      return node;
    }
    if (node->getDiscriminator() > disc){
      return recursiveRetrieve(disc,node->_left);
    }else{
      return recursiveRetrieve(disc,node->_right);
    }}
  
  return nullptr;
  
}
/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */

DNode* DTree::retrieve(int disc) {
  DNode* node = recursiveRetrieve(disc, _root);
  return node;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::recursiveClear(DNode* node){
  if (node == nullptr){
    return;
  }else{
    recursiveClear(node -> _left);
    recursiveClear(node -> _right);
    delete node;
  }
}

void DTree::clear() {
  recursiveClear(_root);
  _root = nullptr;
}
 
//helper for printaccount()
void DTree::recursivePrintAccounts(DNode* node) const{
  if (node != nullptr){
    recursivePrintAccounts(node->_left);
    cout<<node->getAccount()<<endl;
    recursivePrintAccounts(node -> _right);
  }
}  
/**
 * Prints all accounts' details within the DTree.
 */

void DTree::printAccounts() const {
  recursivePrintAccounts(_root);
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
  /*  cout<<"inside getNumUsers"<<endl;
  cout<<_root->getSize()<<endl;
  cout<<_root->_numVacant<<endl;*/
  return ((_root->getSize()) - (_root->_numVacant));
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */

void DTree::updateSize(DNode* node) {
  if (node != nullptr){
    updateSize(node->_left);  //postorder the tree
    updateSize(node->_right);
    int leftLeaf=0;
    int rightLeaf=0;
    if (node ->_left !=nullptr)
      leftLeaf = node->_left->_size;
    if (node ->_right !=nullptr)
      rightLeaf = node ->_right->_size;
    node->_size = leftLeaf + rightLeaf + 1;
  }
}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {
  if (node !=nullptr){
    updateNumVacant(node ->_left);  //postorder the tree 
    updateNumVacant(node ->_right);
    int leftLeaf=0;
    int rightLeaf=0;
    int currentLeaf=0;
    if (node ->_left != nullptr)
      leftLeaf = node -> _left ->_numVacant;
    if (node ->_right !=nullptr)
      rightLeaf = node ->_right ->_numVacant;
    if (node->_vacant == true)
      currentLeaf= 1 ;   
    node ->_numVacant = leftLeaf + rightLeaf + currentLeaf;
  }
}

/*
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */

bool DTree::checkImbalance(DNode* node) {
  if (node == nullptr){
    return false;
  }

  if (findImbalance(node->_left)){
    node->_left = rebalance(node->_left);
    return true;
  }
  if (findImbalance(node->_right)){
    node->_right = rebalance(node->_right);
    return true;
  }
  if (findImbalance(node)){
    _root = rebalance(node);
    
    return true;
  }
  if ((checkImbalance(node->_left))||(checkImbalance(node->_right))){
    return true;
  }
  return false;
}
//looks for the imbalance in the tree as a whole
bool DTree::checkImbalanceHelper(){
  bool result = checkImbalance(_root);
  if (result){
    updateNumVacant(_root);
    updateSize(_root);
  }
  return result;
}

//return where the imbalance was found at. 
bool DTree::findImbalance(DNode* node){
  if (node == nullptr){
    return false;
  }
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



//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
//void DTree::rebalance(DNode*& node) {

//}

// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
DNode* DTree::rebalance(DNode* node) {
  DNode* newRoot;
  int newSize = node->getSize() - node ->getNumVacant() ;
  DNode** array;
  array = new DNode*[newSize];
  int i = 0 ;
  int a = helperMakeArray(node,array,i);
  removeVacant(node);
  newRoot = makeArrayToBST(array,0,newSize-1);
  updateSize(newRoot);

  delete [] array; 
  return newRoot;
}
//----------------
void DTree::removeVacant(DNode* node){
  if (node!=nullptr){
    removeVacant(node->_left);
    removeVacant(node->_right);
    if (node->isVacant()){
      delete node;
      }
  }
}

//convert tree into sorted array 
int DTree::helperMakeArray(DNode* node, DNode* array[],int i){
  if (node !=nullptr){
    i = helperMakeArray(node->_left,array,i);
    if (!node->isVacant()){
      array[i]=node;
      i++;
    }
    i = helperMakeArray(node->_right,array,i);
  }
  return i;
}

DNode* DTree::makeArrayToBST(DNode* array[], int min, int max){
  if (min >  max){
    return NULL;
  }
  
  int middle = max + (min - max)/2;
  array[middle]->_right = nullptr;
  array[middle]->_left = nullptr;
  updateSize(array[middle]);
  DNode* root = array[middle];
  root->_left = makeArrayToBST(array,min, middle-1 );
  root->_right = makeArrayToBST(array, middle+1 ,max);
  
  return root;
}
/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() << 
            "\n\tDiscriminator: " << acct.getDiscriminator() <<
            "\n\tNitro: " << acct.hasNitro() << 
            "\n\tBadge: " << acct.getBadge() << 
            "\n\tStatus: " << acct.getStatus();
    return sout;
}
