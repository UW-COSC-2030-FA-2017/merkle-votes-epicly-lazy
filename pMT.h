//Huy Tran
#pragma once

#include "bTREE.h"
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;
    
    string hash_1(string);
    string hash_2(string);
    string hash_3(string);
	
	void resetTreeH(treeNode* tree,int hash);
	string resetTreeH1(treeNode* tree);
	string resetTreeH2(treeNode* tree);
	string resetTreeH3(treeNode* tree);
public:
    pMT(int);
    ~pMT();
    
    int insert(string, int);
    
    int find(string, int, int);
    int findHash(string);
	
    string locateData(string);
	string locateHash(string);

	void resetTree();	//this function will go through the tree and set the hash of a node = hash of its children
    friend bool operator==(const pMT& lhs, const pMT& rhs);
    
    friend bool operator!=(const pMT& lhs, const pMT& rhs);
    
    friend pMT operator^(const pMT& lhs, const pMT& rhs);
    friend std::ostream& operator<<(std::ostream& out, const pMT& p); //this function print the data and time in 2 collumns
    
	string getRootData();
	void display(ostream& out) { //this function actually print how the tree looks
		myMerkle.display(out);
	}

};