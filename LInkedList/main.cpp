#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

template<class T>
struct TreeNode {
	T ele;
	TreeNode<T>* next;
	TreeNode();
	TreeNode(T ele);
};

template<class T>
inline TreeNode<T>::TreeNode() {
	ele = T();
	next = nullptr;
}

template<class T>
inline TreeNode<T>::TreeNode(T ele) {
	this->ele = ele;
	next = nullptr;
}

template<class T>
void flip(TreeNode<T>* &head) {
	TreeNode<T>* prev = NULL;
	TreeNode<T>* cur = head;
	do{
		TreeNode<T>* tmp = cur;
		cur = cur->next;
		tmp->next = prev;
		prev = tmp;
	} while (cur);
	head = prev;
}

template<class T>
void print(TreeNode<T>* head) {
	for (; head != NULL; head = head->next) {
		cout << head->ele << " ";
	}
	cout << endl;
}

int main() {
	TreeNode<int>* head = new TreeNode<int>(0);
	TreeNode<int>* node = head;
	for (int i = 1; i < 10; i++) {
		node->next = new TreeNode<int>(i);
		node = node->next;
	}
	flip(head);
	print(head);
}

