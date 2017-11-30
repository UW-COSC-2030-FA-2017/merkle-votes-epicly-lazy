//Huy Tran
//For the hash functions, I hash strings into ints and then convert those ints into strings to return.
#include "pMT.h"

//done
pMT::pMT(int hashSelect)
/**
 * @brief 
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return 
 */
{
	if (hashSelect > 3 || hashSelect < 1) {
		selectedHash = 1;
	}
	else {
		selectedHash = hashSelect;
	}
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}
//done
int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time 
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
	int a = myMerkle.insert(vote, time);
	resetTree();
	return a;
}

//done
int pMT::find(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
	int numbOp = 0;
	string step = myMerkle.locate(vote);	numbOp++;
	treeNode* tmp = myMerkle.getRoot();		numbOp++;
	for (int i = 0; i < step.size(); i++) {
		numbOp++;
		if (step[i] == 'L') {
			numbOp++;
			tmp = tmp->left;	numbOp++;
		}
		else if (step[i] == 'R') {
			numbOp++;
			tmp = tmp->right;	numbOp++;
		}
		else {
			break;
		}
	} //when we are out of the loop tmp should point to the location of the TreeNode that has data = vote
	numbOp++;
	if (tmp->checkLeaf() == false) { //if its not a leaf then return false
		return 0; 
	}
	numbOp++;
	if ((tmp->data != vote) || (tmp->time != time)) {
		return 0;
	}
	else {
		numbOp++;
		return numbOp;
	}
}

//done
int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
	resetTree();
	return myMerkle.find(mhash);
}

//done
string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param vote, the data to search for 
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	return myMerkle.locate(vote);
}
//done
string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param mhash, the hash to search for 
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
{
	return myMerkle.locate(mhash);
}

void pMT::resetTree()
{
	resetTreeH(myMerkle.getRoot(), selectedHash);
}
void pMT::resetTreeH(treeNode* tree, int hash) {
	if (hash == 1) {
		resetTreeH1(tree);
	}
	else if (hash == 2) {
		resetTreeH2(tree);
	}
	else {
		resetTreeH3(tree);
	}
}
string pMT::resetTreeH1(treeNode* node) {
	if (node == NULL) { return ""; } //return empty string if NULL
	if (node->checkLeaf() == true) { //return data if a leaf
		return node->data;
	}//out here node is not a leaf or NULL
	string toHash = "";
	toHash += resetTreeH1(node->left) + resetTreeH1(node->right); //post-order traversal
	toHash = hash_1(toHash); 
	node->data = toHash;// data of node = Hash(left + right)
	return toHash;
}
string pMT::resetTreeH2(treeNode* node) {
	if (node == NULL) { return ""; } //return empty string if NULL
	if (node->checkLeaf() == true) { //return data if a leaf
		return node->data;
	}//out here node is not a leaf or NULL
	string toHash = "";
	toHash += resetTreeH2(node->left) + resetTreeH2(node->right); //post-order traversal
	toHash = hash_2(toHash);
	node->data = toHash;// data of node = Hash(left + right)
	return toHash;
}
string pMT::resetTreeH3(treeNode* node) {
	if (node == NULL) { return ""; } //return empty string if NULL
	if (node->checkLeaf() == true) { //return data if a leaf
		return node->data;
	}//out here node is not a leaf or NULL
	string toHash = "";
	toHash += resetTreeH3(node->left) + resetTreeH3(node->right); //post-order traversal
	toHash = hash_3(toHash);
	node->data = toHash;// data of node = Hash(left + right)
	return toHash;
}

//RSHash
string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	for (std::size_t i = 0; i < key.length(); i++)
	{
		hash = hash * a + key[i];
		a = a * b;
	}
	string s = to_string(hash);
	return s;
}

//JSHash
string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int hash = 1315423911;

	for (std::size_t i = 0; i < key.length(); i++)
	{
		hash ^= ((hash << 5) + key[i] + (hash >> 2));
	}
	string s = to_string(hash);
	return s;
}

//DEKHash
string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int hash = static_cast<unsigned int>(key.length());

	for (std::size_t i = 0; i < key.length(); i++)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ key[i];
	}
	string s = to_string(hash);
	return s;
}

//done
bool operator ==(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	return (lhs.myMerkle == rhs.myMerkle);
}

//done
bool operator !=(const pMT& lhs, const pMT& rhs)
/*
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	return !(lhs == rhs);
}

pMT operator ^=(const pMT& lhs, const pMT& rhs)	//the similarity of 2 tree?
/**
 * @brief XOR between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	return lhs;
}

//done
std::ostream& operator <<(std::ostream& out, const pMT& p)
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	out << p.myMerkle;
	return out;
}


pMT operator ^(const pMT& lhs, const pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
{
	pMT* result = new pMT(1);
	return *result;
}

string pMT::getRootData() {
	return myMerkle.getRoot()->data;
}
