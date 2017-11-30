//Huy Tran
//I put the treeNode structure in a separate header file

#pragma once

#include "treeNode.h"
#include <vector>
using namespace std;

class bTREE{
private:
	treeNode* root;
	void freeNode(treeNode* node); //used in destructor
	int nodeCount(treeNode* node) const; //used in numberOfNodes
	int resetNode(treeNode* node);
	int resetHeight(treeNode* node);
	void resetParent(treeNode* node);//reset the parent pointer of the whole tree
	void resetLeaves(treeNode* node);//reset the variable isLeaf through the tree
	void resetTree();//fast way to reset the numbNode, Height and Prev variable of tree
	int findH(string, treeNode*) const; // helper of find 
	int dataInsertedH(treeNode*) const; //helper of dataInserted
	int insertNotFull(treeNode* root, treeNode* toInsert, int level);//used when we insert data in an not-full-tree
	vector<string> preOrderData() const;//used in ==
	void preOrderDataH(vector<string>& treeData, treeNode* root) const; //helper of preOrderData
	vector<int> preOrderTime() const;	//used in << operator
	void preOrderTimeH(vector<int>& treeTime, treeNode* root) const; //helper of preOrderTime
	int getHeightH(treeNode*) const; //helper of getHeight, also reset the height variable
	int maxInt(int a, int b) const; //used in geiHeighH function
	string locateH(string toFind, treeNode* root, string& step); //helper of locate function
	

	int numbNode;
	int height;
public:
	bTREE();
	~bTREE();

	int dataInserted() const;	//the same as Leaf Counting
	int numberOfNodes() const;//check nodeCount function
	int getHeight() const; //get the height of the tree, also reset the value of height
	int insert(string, int); //check insertH function
	int find(string) const; //check findH private function
	string locate(string);
	friend bool operator==(const bTREE& lhs, const bTREE& rhs);
	friend bool operator!=(const bTREE& lhs, const bTREE& rhs);
	friend std::ostream& operator<<(std::ostream& out, const bTREE& p);
	treeNode* getRoot() const { return root; }

	//these are the functions from Lab 8. I put them here to help with the testing and visualizing the tree
	void
		display(std::ostream& outfile) 
	{
		std::string prefix;
		if (root == NULL)
		{
			outfile << "-" << std::endl;
		}
		else
		{
			displayLeft(outfile, root->left, "    ");
			outfile << "---" << root->data << std::endl;
			displayRight(outfile, root->right, "    ");
		}
	};
	void
		displayLeft(std::ostream & outfile,
			treeNode * subtree, std::string prefix)
	{
		if (subtree == NULL)
		{
			outfile << prefix + "/" << std::endl;
		}
		else
		{
			displayLeft(outfile, subtree->left, prefix + "     ");
			outfile << prefix + "/---" << subtree->data << std::endl;
			displayRight(outfile, subtree->right, prefix + "|    ");
		}
	};
	void
		displayRight(std::ostream & outfile,
			treeNode * subtree, std::string prefix)
	{
		if (subtree == NULL)
		{
			outfile << prefix + "\\" << std::endl;
		}
		else
		{
			displayLeft(outfile, subtree->left, prefix + "|    ");
			outfile << prefix + "\\---" << subtree->data << std::endl;
			displayRight(outfile, subtree->right, prefix + "     ");
		}
	}
};