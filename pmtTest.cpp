//Huy Tran
#include <iostream>
#include "pMT.h"
using namespace std;

int main() {
	pMT* test = new pMT(1);
	cout << "Numbers of operations needed to insert: " << endl;
	int a = test->insert("safdds", 124);
	cout << a << endl;
	int b = test->insert("sdf", 32532);
	cout << b << endl;
	int c = test->insert("sdgfdsg", 1224314);
	cout << c << endl;
	int d = test->insert("berbg32", 421325);
	cout << d << endl;
	test->resetTree();
	cout << endl << endl;
	cout << *test;

	cout << "\n\nCreating new tree and insert exactly same data, testing if equal..." << endl;
	pMT* test2 = new pMT(1);
	test2->insert("safdds", 124);
	test2->insert("sdf", 32532);
	test2->insert("sdgfdsg", 1224314);
	test2->insert("berbg32", 421325);
	if (*test == *test2) {
		cout << "Two trees are equal " << endl << endl << endl;
	}
	else { cout << "Two trees are NOT EQUAL" << endl << endl << endl; }
	cout << "Displaying the tree: " << endl;
	test->display(cout);
	cout << "Locating data sdgfdsg :" << test->locateData("sdgfdsg") << endl;
	cout << "Locating hash 3031739076: " << test->locateHash("3031739076") << endl;
	cout << "Finding hash 3031739076: " << test->findHash("3031739076") << endl;
	cout << "Finding vote/time/hash = safdds/124/1: " << test->find("safdds", 124, 1) << endl;
	cout << "Finding vote/time/hash = 34634hgf/574/2 (the result should be 0): " << test->find("34634hgf", 574, 2) << endl;
	return 0;
}