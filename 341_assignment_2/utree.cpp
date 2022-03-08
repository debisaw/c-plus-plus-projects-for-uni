/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
  clear();
}

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */ 
void UTree::loadData(string infile, bool append) {
    std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];

    /* Check to make sure the file was opened */
    if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
    if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
    while(std::getline(instream, line)) {
        std::stringstream buffer(line);

        /* Quick check to make sure each line is formatted correctly */
        int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes - 
         * Each line always has 5 sections of data */
        for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
}

//helper for insert(). add DNode into UNode.
bool UTree::recursiveInsert(UNode* node, Account newAcct){
  if (node == nullptr){   //if account not found
    return false;
  }else{
    if (node->getUsername() == newAcct.getUsername()){
      bool result = node->getDTree()->insert(newAcct);     //if accound found
      return result;}
    recursiveInsert(node->_left, newAcct);
    recursiveInsert(node->_right, newAcct);
  }
  return false;
}
//helper for Insert(). add a new UNode if account not found.
void UTree::addNewNode(UNode* node,Account newAcct){
  if (node == nullptr) 
    {return;}
  if (node->getUsername() > newAcct.getUsername()){    //add new UNode into the tree
    if (node->_left == nullptr){
      UNode* newNode = new UNode;
      newNode->getDTree()->insert(newAcct);
      node->_left = newNode;
      return;
    }}
  if (node->getUsername() < newAcct.getUsername()){
    if (node->_right == nullptr){
      UNode* newNode = new UNode;
      newNode->getDTree()->insert(newAcct);
      node->_right = newNode;
      return;
    }}
  if (node->getUsername() > newAcct.getUsername()){   // recurse the function 
    addNewNode(node->_left, newAcct);}
  if (node->getUsername() < newAcct.getUsername()){
    addNewNode(node->_right, newAcct);}
}
/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree. 
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct) {
  if (_root == nullptr){
    _root = new UNode;
    _root->getDTree()->insert(newAcct);
    updateHeight(_root);
    return true;
  }else{
    if (recursiveInsert(_root,newAcct)){ //insert account exising UNode
      return true;
    }else{ //insert a new UNode 
      addNewNode(_root, newAcct);
      updateHeight(_root);
      recursiveCheckImbalance(_root);
      _root = rebalance(_root);
      return true;
    }
  }
  
  return false;
}

//helper for remove function. 
//return the parent of nodeX.
UNode* UTree::findParentLargestNode(UNode* node){
  if (node->_right->_right == nullptr) {return node;}
  else{
       return findParentLargestNode(node->_right);}
}
//helper for remove function.
//@param:  UNode that is empty.
//return the Unode that was used to be empty, now filled with value according to AVL tree rule.  
UNode* UTree::removeUNode(UNode* node){
  UNode* nodeX = nullptr;
  UNode* parentOfNodeX = nullptr;
  
  if (node->_left !=nullptr){   //find the largest node in leftsubtree if exist
    if (node->_left->_right == nullptr){
      parentOfNodeX = node;
      nodeX = node->_left;
    }else{
      parentOfNodeX = findParentLargestNode(node->_left);
      nodeX = parentOfNodeX ->_right;
    }
  }

  if (nodeX == nullptr){ //in case empty UNode does not have a left subtree
    UNode* rightChildofEmptyUNode =  node->_right;
    if (node->_right !=nullptr){
      *node->getDTree() = *rightChildofEmptyUNode->getDTree();
      delete node;
      updateHeight(_root);
  
      return rightChildofEmptyUNode;}
    if(node->_right == nullptr){ // in case UNode is the _root;
      delete node;
      return nullptr;
    }
  }else{
    if (nodeX->_left != nullptr){ // in case nodeX has left subtree
      UNode* leftChildNodeX = nodeX->_left;
      parentOfNodeX ->_left = leftChildNodeX;
      *node->getDTree() = *nodeX->getDTree();
      delete nodeX;
      updateHeight(_root);
      return node;
    }else{   //in case nodeX does not have a left subtree
      *parentOfNodeX->getDTree()= *nodeX->getDTree();
     
      delete nodeX;
      parentOfNodeX->_left = nullptr;
      updateHeight(_root);
      
      return parentOfNodeX;}
  }
  cout<<"non matched: exit removeUNode"<<endl;
  return nullptr;
}
/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {
 
  UNode* uNodeWithUser = retrieve(username);
  DNode* dNodeToBeRemoved = retrieveUser(username,disc);
  if (dNodeToBeRemoved !=nullptr){
    bool result = uNodeWithUser->getDTree()->remove(disc,dNodeToBeRemoved);
    
    if (uNodeWithUser->getDTree()->getNumUsers() == 0){//if the removed account caused the UNode to be empty.
      
      if (_root ->getDTree()->getNumUsers() == 0){ //in case root has no valid user.
	_root = removeUNode(_root);
      }else{findParentEmptyUNode(_root);}  //traverse the UTree and find the parent of the UNode with no valid user and delete the empty UNode. 
      updateHeight(_root);
      recursiveCheckImbalance(_root);
      _root = rebalance(_root);
    }
    return result;  //return if the accound has been removed
  }
  return false;
}

//helper for remove()
//@param: the parent of the empty UNode;
//assign new child
void UTree::findParentEmptyUNode(UNode* node){
  if (node!=nullptr){
    if (node->_left!=nullptr){      
      if (node ->_left->getDTree()->getNumUsers() == 0){
	node->_left = removeUNode(node->_left);}}
    if (node->_right != nullptr){
      if (node->_right->getDTree()->getNumUsers() ==0){
	node->_right =removeUNode(node->_right);}}
    findParentEmptyUNode(node->_left);
    findParentEmptyUNode(node->_right);
  }
}
/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
  
  UNode* result = recursiveRetrieve(_root,username);
  return result;
}
//helper for retrieve
UNode* UTree::recursiveRetrieve(UNode* node, string username){
  if (node== nullptr){
    return nullptr;}
  if (node->getUsername() == username){
    return node;
  }
  if (node->getUsername() > username){
    return recursiveRetrieve(node->_left,username);
  }else{
   return  recursiveRetrieve(node->_right,username);}
  
  
  
}
/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
  UNode* uNode = retrieve(username);
  if (uNode !=nullptr){
    DNode* dNode= uNode->getDTree()-> retrieve(disc);
    if (dNode != nullptr){
      return dNode;
    }
  }
  return nullptr;
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {
  UNode* node = retrieve(username);
  if(node==nullptr){
    return 0;
  }else{
    int numValidUsers = node->getDTree()-> getNumUsers();
    return numValidUsers;}
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
  recursiveClear(_root);
}

void UTree::recursiveClear(UNode* node){
  if (node==nullptr){
      return;
    }else{
      recursiveClear(node->_left);
      recursiveClear(node->_right);
      delete node;
  }
}
/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {
  recursivePrintUsers(_root);
}
void UTree::recursivePrintUsers(UNode* node)const{
  
  if ( node!=nullptr){
    recursivePrintUsers(node->_left);
    node->getDTree()->printAccounts();
    recursivePrintUsers(node->_right);
  }
}

/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
  if (node != nullptr){
    updateHeight(node->_left);                //post-order all nodes and update the height 
    updateHeight(node->_right);
    int leftLeaf =-1;
    int rightLeaf = -1;
    if (node->_left != nullptr)
      leftLeaf = node->_left->getHeight();
    if (node->_right !=nullptr)
      rightLeaf = node->_right->getHeight();
    node->_height = 1+ (leftLeaf > rightLeaf ? leftLeaf : rightLeaf );  
      }
}
void UTree::recursiveCheckImbalance(UNode* node){
  if (node != nullptr){
    recursiveCheckImbalance(node->_left);     //postorder the nodes and rebalance it. 
    recursiveCheckImbalance(node->_right);
    node->_left = rebalance(node->_left);    
    updateHeight(node);
    node->_right = rebalance(node->_right);
    updateHeight(node);
  }
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int  UTree::checkImbalance(UNode* node) {
  if (node == nullptr){
    return -1;
  }else{
    int leftHeight = -1;
    int rightHeight =-1;

    if (node->_left !=nullptr){
      leftHeight = node->_left->getHeight();
    }
    if (node->_right !=nullptr){
      rightHeight = node->_right->getHeight();
    }
    return (leftHeight - rightHeight);
  }
}
UNode* UTree::leftRotation(UNode* node){
  UNode* parent = node;
  UNode* child = parent->_right;
  parent->_right = child->_left;
  child->_left = parent;

  updateHeight(parent);
  updateHeight(child);
  return child;
}

UNode* UTree::rightRotation(UNode* node){
  UNode* parent = node;
  UNode* child = node->_left;

  parent->_left = child -> _right;
  child->_right = parent;

  updateHeight(parent);
  updateHeight(child);

  return child;
}
//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
//void UTree::rebalance(UNode*& node) {}
  /*
// -- OR --
}

/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
  
UNode* UTree::rebalance(UNode* node) {

  //LL rotation
  if ((checkImbalance(node) < -1) && (checkImbalance(node->_right) <= 0)){
    return leftRotation(node);
  }
  //RR rotation 
  else if ((checkImbalance(node) > 1) && (checkImbalance(node->_left) >= 0)){
    return rightRotation(node);
  }
  //RL rotation
  else if ((checkImbalance(node) < -1) && (checkImbalance(node->_right) >=0)){
    node->_right = rightRotation(node->_right); // R rotate at right child
    return leftRotation(node); // L rotate at root
  }
  //LR rotation
  else if ((checkImbalance(node) > 1) && (checkImbalance(node->_left) <= 0)){
    node->_left = leftRotation(node->_left);//L rotation at left child
    return rightRotation(node);// R rotation at root
  }
  else
    return node;
  
}
//----------------
