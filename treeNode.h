//Huy Tran
#include <string>
using namespace std;
struct treeNode {
	string data;
	int time;
	treeNode* left;
	treeNode* right;
	treeNode* prev;
	bool isLeaf = false;
	treeNode() {
		data = "";
		time = -1;
		left = NULL;
		right = NULL;
		prev = NULL;
	}
	treeNode(string data, int time, treeNode* left, treeNode* right, treeNode* prev, bool isLeaf) {
		this->data = data; this->time = time; this->left = left; this->right = right; this->prev = prev; this->isLeaf = isLeaf;
	}
	string getData() { return data; }
	void setData(string data) { this->data = data; }
	void clearData() { data = ""; }

	int getTime() { return time; }
	void setTime(int time) { this->time = time; }
	void clearTime() { time = -1; }
	void clearNode() { clearData(); clearTime(); }

	void setLeft(treeNode* left) { this->left = left; }
	void setRight(treeNode* right) { this->right = right; }
	treeNode* Left() { return left; }
	treeNode* Right() { return right; }

	bool checkLeaf() {
		if (left == NULL && right == NULL) { //return true if both left and right are Null (node = leaf)
			isLeaf = true;
			return true;
		}
		isLeaf = false;
		return false; //return false otherwise
	}
	void setLeaf(bool leaf) {
		isLeaf = leaf;
	}
	void clearLeaf() {
		isLeaf = false;
	}
};

