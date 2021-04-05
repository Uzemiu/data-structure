#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

template<class T>
struct Node {
	T ele;
	Node<T>* next;
	Node();
	Node(T ele);
};

template<class T>
inline Node<T>::Node() {
	ele = T();
	next = nullptr;
}

template<class T>
inline Node<T>::Node(T ele) {
	this->ele = ele;
	next = nullptr;
}

template<class T>
void flip(Node<T>* &head) {
	Node<T>* prev = NULL;
	Node<T>* cur = head;
	do{
		Node<T>* tmp = cur;
		cur = cur->next;
		tmp->next = prev;
		prev = tmp;
	} while (cur);
	head = prev;
}

template<class T>
void print(Node<T>* head) {
	for (; head != NULL; head = head->next) {
		cout << head->ele << " ";
	}
	cout << endl;
}

int main() {
	Node<int>* head = new Node<int>(0);
	Node<int>* node = head;
	for (int i = 1; i < 10; i++) {
		node->next = new Node<int>(i);
		node = node->next;
	}
	flip(head);
	print(head);
}

