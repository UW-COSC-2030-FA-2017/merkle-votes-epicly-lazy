//Huy Tran
//comment this file to run other test cpp files
#include "bTREE.h"
#include <iostream>
using namespace std;

int main() {
	bTREE* tree = new bTREE();
	tree->insert("this is a", 123);
	tree->insert("this is b", 123);
	tree->insert("this is c", 123);
	tree->insert("this is d", 123);
	tree->insert("this is e", 123);
	tree->insert("this is f", 123);
	tree->insert("this is g", 123);

	

	tree->display(cout);
	cout << tree->dataInserted() << endl;
	cout << tree->numberOfNodes() << endl;
	cout << tree->getHeight() << endl;
	cout << "Finding this is g: " << tree->find("this is g") << endl;
	cout << "Finding this is nothing: " << tree->find("this is nothing") << endl;
	cout << "this is tree" << endl;
	cout << *tree << endl;

	bTREE* tree2 = new bTREE();
	tree2->insert("this is a", 123);
	tree2->insert("this is b", 123);
	tree2->insert("this is c", 123);
	tree2->insert("this is d", 123);
	tree2->insert("this is e", 123);
	tree2->insert("this is f", 123);
	tree2->insert("this is g", 123);
	tree2->display(cout);
	
	if (*tree == *tree2) {
		cout << "The two trees are equal" << endl;
	}
	else {
		cout << "not equal" << endl;
	}
	
	cout <<"Locating this is g: " << tree->locate("this is g") << endl;
	cout << "Locating this is h: " << tree->locate("this is h") << endl;
	cout << "Locating this is e: " << tree->locate("this is e") << endl;

	return 0;
	
}