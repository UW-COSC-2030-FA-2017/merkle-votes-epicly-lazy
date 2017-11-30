//Huy Tran
#include <stdio.h>
#include "pMT.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void read(ifstream& infile, string filename, pMT* vote);
int main(int argc, char **argv)
{
	pMT* vote1 = new pMT(1);
	pMT* vote2 = new pMT(1);
	pMT* vote3 = new pMT(2);
	ifstream infile;
	cout << "Tree 1: ";
	read(infile, "test1.txt", vote1);
	cout << "Tree 2: ";
	read(infile, "test1.txt", vote2);
	cout << "Data of root of Tree 1: " << vote1->getRootData() << endl;
	cout << "Data of root of Tree 2: " << vote2->getRootData() << endl;
	cout << "Tree 1 and Tree 2: ";
	if (*vote1 == *vote2) {
		cout << "Validated" << endl << endl << endl;
	}
	else {
		cout << "Not Validated" << endl << endl << endl;
	}
	

	cout << "Tree 3: ";
	read(infile, "test2.txt", vote3);
	cout << "Data of root of Tree 3: " << vote3->getRootData() << endl;
	cout << "Tree 1 and Tree 3: ";
	if (*vote1 == *vote3) {
		cout << "Validated" << endl;
	}
	else {
		cout << "Not Validated" << endl;
	}
	//uncomment under lines to see the trees (not recommended)
	/*cout << "Printing tree 1" << endl;
	vote1->display(cout);
	cout << endl;

	cout << "Printing tree 2" << endl;
	vote2->display(cout);
	cout << endl;

	cout << "Printing tree 3" << endl;
	vote3->display(cout);
	cout << endl;*/


	return 0;
}

void read(ifstream& infile, string filename, pMT* vote) {
	string tmp;
	
	if (infile.is_open()) {
		infile.close();
	}
	infile.open(filename);
	infile >> tmp;
	infile >> tmp;//reading 'data' and 'timestamp'
	int i = 1; //i odd = data, even = timestamp
	while (!infile.eof()) {
		infile >> tmp;
		string data = tmp;
		infile >> tmp;
		stringstream convert(tmp);
		int time = 0;
		convert >> time;
		vote->insert(data, time);
	}
	infile.close();
	cout << "Reading " << filename << " and inserting to Merkle Tree finished." << endl;
}