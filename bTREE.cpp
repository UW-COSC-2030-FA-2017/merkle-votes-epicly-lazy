//Huy Tran
#include "bTREE.h"


//look at descriptions in pMT.h for guidance on what you might need for these function to actually do

bTREE::bTREE()	
{
	root = NULL;
	numbNode = 0;
	height = 0;
}

bTREE::~bTREE()	
{
	freeNode(root);
}


int bTREE::dataInserted()const
{
	int result = dataInsertedH(root);
	return result;
}


int bTREE::numberOfNodes() const	
{
	return nodeCount(root);
}

//DONE & tested
int bTREE::insert(string data, int time)
{
	int numbOp = 0;
	treeNode* toInsert = new treeNode(data, time, NULL, NULL, NULL, true);
	numbOp++;
	resetNode(root); numbOp++;	
	resetHeight(root);	numbOp++;

	if (root == NULL) {//if the tree is empty
		numbOp++;
		root = toInsert;	numbOp++;
		resetTree();
		return numbOp;
	}

	// if the tree is full, we insert the toInsert node to the leftmost location
	if (numbNode == pow(2, height + 1) - 1) {
		treeNode* tmp = root; numbOp++;
		while (tmp->left != NULL) {
			numbOp++;
			tmp = tmp->left;
		}//after the loop, left of tmp = NULL;
		treeNode* backUp = new treeNode(tmp->data, tmp->time, NULL, NULL, tmp, true); numbOp++; //THIS STEP CHANGE A LEAF INTO A NODE 
		tmp->left = backUp;	numbOp++;
		tmp->right = toInsert; numbOp++;	//THIS IS THE INTSERT STEP
		tmp->clearNode();
		resetNode(root);	//these are just functions to refresh the variables of the tree, not important to count 
		resetHeight(root);
		resetParent(root);
		return numbOp;
	}
	//out here the tree is not full, so we will check every level until find a NULL pointer
	numbOp += insertNotFull(root, toInsert, 1);
	return numbOp;
}


int bTREE::find(string toFind) const	
{
	int result = 2;
	int found = findH(toFind, root);
	if (found == 0) {
		return found;//return 0 if not found
	}
	return result + found;
	
}

//DONE, tested, it return right path sometimes with a dot at the end
string bTREE::locate(string toFind)
{
	string result = "";
	result = locateH(toFind, root, result);
	return result;
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
	bool result = true;
	if ((lhs.dataInserted() != rhs.dataInserted()) || (lhs.numberOfNodes() != rhs.numberOfNodes())) {
		result = false;
		return result;
	}
	else {
		vector<string> left = lhs.preOrderData();
		vector<string> right = rhs.preOrderData();
		for (int i = 0; i < left.size(); i++) {
			if (left[i] != right[i]) {
				result = false;
				return result;
			}
		}
	}
	return result;
}

bool operator !=(const bTREE& lhs, const bTREE& rhs)
{
	return !(lhs == rhs);
}


std::ostream& operator <<(std::ostream& out, const bTREE& p)
{
	int numbNode = p.numberOfNodes();
	p.getHeight();
	vector<int> treeTime = p.preOrderTime();
	vector<string> treeData = p.preOrderData();

	out << "Time\t\tData" << endl;
	for (int i = 0; i < numbNode; i++) {
		out << treeTime[i] << "\t\t" << treeData[i] << endl;
	}
	return out;

}


void bTREE::freeNode(treeNode* node) {	
	if (node != NULL) {
		freeNode(node->Left());
		freeNode(node->Right());
		delete node;
	}
}


int bTREE::nodeCount(treeNode* node) const {
	int result = 0;
	if (node == NULL) { return 0; }
	else {
		result= 1 + nodeCount(node->Left()) + nodeCount(node->Right());
		return result;
	}
}


int bTREE::findH(string toFind, treeNode* root) const
{
	int result = 0;
	bool found = false;	result++;
	if (toFind == "") {
		return 0;
	} //return if empty string
	if (root == NULL) { 
		return 0;
	} //also return false if root is null

	if (root->checkLeaf() == true) {
		result++;
		;//if root is a leaf
		if (root->getData() == toFind) {
			result++;
			found = true;	
			return result;
		}
		result++;
		found = false;
		return 0;
	}
	//if get here, root is not a leaf, we check the left first then the right
	if (root->data == toFind) {
		result++;
		found = true;
		return result;
	}
	int intFound = findH(toFind, root->Left()); result++;	//check left	
	if (intFound != 0) { //if found in left, we return true
	
		return result + intFound;
	}
	else {
		intFound = findH(toFind, root->Right());	result++;	// if not we found in right and return found
		if (intFound != 0) { return result + intFound; }
		else { return 0; }
	}
}


int bTREE::dataInsertedH(treeNode* root) const {
	if (root == NULL) { //return 0 if root is null
		return 0;
	}
	int count = 0;
	if (root->checkLeaf() == true) { //if root is a leaf
		if (root->getData() != "") { //if data in the leaf is not empty
			count++;
		}
		return count;
	}
	//out here, root is not a leaf
	count += dataInsertedH(root->Left()); //go to left, check how many leaves
	count += dataInsertedH(root->Right()); //then go right
	return count;
}

vector<string> bTREE::preOrderData() const {
	vector<string> treeData;
	preOrderDataH(treeData, root);
	return treeData;
}

void bTREE::preOrderDataH(vector<string>& treeData, treeNode* root) const {
	if (root == NULL) {
		return;
	}
	treeData.push_back(root->getData());
	preOrderDataH(treeData, root->Left());
	preOrderDataH(treeData, root->Right());
	return;
}


int bTREE::getHeight() const {
	return getHeightH(root);
}

int bTREE::getHeightH(treeNode* root) const {
	int result;
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		return 0;
	}
	else {
		result = 1 + maxInt(getHeightH(root->left), getHeightH(root->right));
	}
	return result;
}

int bTREE::maxInt(int a, int b) const {
	if (a > b) {
		return a;
	}
	return b;
}

int bTREE::resetNode(treeNode* root) {
	int result = 0;
	if (root == NULL) {
		numbNode = 0;
		return numbNode;
	}
	else {
		result = 1 + resetNode(root->Left()) + resetNode(root->Right());
		numbNode = result;
		return numbNode;
	}
}

int bTREE::resetHeight(treeNode* root) {
	int result;
	if (root == NULL) {
		height = 0;
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		height = 0;
		return 0;
	}
	else {
		result = 1 + maxInt(resetHeight(root->left), resetHeight(root->right));
		height = result;
	}
	return result;
}

void bTREE::resetParent(treeNode* root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) {	//the parent of left of root is root
		root->left->prev = root;
	}
	if (root->right != NULL) {	//the parent of right of root is root
		root->right->prev = root;
	}
	resetParent(root->left);
	resetParent(root->right);
	return;
}

//DONE
int bTREE::insertNotFull(treeNode* root, treeNode* toInsert, int level) {
	//we will check the current level of the tree, if this level is full, we pass the parameter to the next level
	bool inserted = false;
	int numbOp = 1;
	double numbLeaves = pow(2, level); numbOp++; //the number of available leaves at a current level = 2^level
	resetTree();	numbOp++;
	treeNode* tmp = root;	numbOp++;
	treeNode* tmpParent = tmp->prev;	numbOp++;
	double cur = numbLeaves;	numbOp++;
	for (int k = 1; k <= numbLeaves; k++) {
		int i = k;
		numbOp++;
		tmp = root;	numbOp++;
		cur = numbLeaves;	numbOp++;
		tmpParent = tmp->prev;	numbOp++;
		for (int j = 0; j < level ; j++) {
			numbOp++;
			if (i % 2 == 0) {
				numbOp++;// if i is even, we traverse to the right
				i = i / 2;	numbOp++;
				tmpParent = tmp;	numbOp++;
				tmp = tmp->right;	numbOp++;
			}
			else {//if i is odd, we traverse to the left
				numbOp++;
				i = i / 2;	numbOp++;
				tmpParent = tmp;	numbOp++;
				tmp = tmp->left;	numbOp++;
			}
		}
		
		if (tmpParent->checkLeaf() == true) {
			numbOp++;
			treeNode* backup = new treeNode(tmpParent->data, tmpParent->time, NULL, NULL, tmpParent, true);	numbOp++;
			tmpParent->left = backup;	numbOp++;
			tmpParent->right = toInsert;	numbOp++;
			tmpParent->clearNode();	numbOp++;
			inserted = true;	numbOp++;
			return numbOp;
		}
		else if (tmpParent->left == NULL) {//left = NULL but not right
			numbOp++;
			tmpParent->left = toInsert;	numbOp++;
			inserted = true;	numbOp++;
			return numbOp;
		}
		else if (tmpParent->right == NULL) {
			numbOp++;
			tmpParent->right = toInsert;	numbOp++;
			inserted = true;	numbOp++;
			return numbOp;
		}
	}
	//if we are out of the for loop, this current level is full
	if (inserted == false) { //double check
		level++;
		numbOp += insertNotFull(root, toInsert, level);
		return numbOp;
	}
	else {
		return numbOp;
	}
}

void bTREE::resetTree() {
	resetHeight(root);
	resetNode(root);
	resetParent(root);
	resetLeaves(root);
}

void bTREE::resetLeaves(treeNode* root) {
	if (root == NULL) { return; }
	root->checkLeaf();
	resetLeaves(root->left);
	resetLeaves(root->right);
}
vector<int> bTREE::preOrderTime() const {
	vector<int> treeTime;
	preOrderTimeH(treeTime, root);
	return treeTime;
}

void bTREE::preOrderTimeH(vector<int>& treeTime, treeNode* root) const{
	if (root == NULL) {
		return;
	}
	treeTime.push_back(root->getTime());
	preOrderTimeH(treeTime, root->Left());
	preOrderTimeH(treeTime, root->Right());
	return;
}

//DONE & tested
string bTREE::locateH(string toFind, treeNode* root, string& step) {
	if (root == NULL) {
		return ".";
	}
	if (root->data == toFind) {
		return "";
	}

		//somehow if we divide the and condition into 2 if statments it fails
	if (root->left != NULL && locateH(toFind, root->left, step) != ".") {
		step = "L" + step;
		return step;
	} else if (root->right != NULL && locateH(toFind, root->right, step) != ".") {
			step = "R" + step;
			return step;
	}
	else {
		step = ".";
		return step;
	}
}