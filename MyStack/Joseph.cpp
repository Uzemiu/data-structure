#include "LinkedList.h"

#include <iostream>

using namespace std;

class JosephList:public LinkedList<int> {

public:
	void doJoseph(int n, int m) {
		for (int i = 1; i <= n; i++) {
			push_last(i);
		}
		Node<int>* node = head;
		while (_size > 1) {
			for (int i = 1;i<m; i++) {
				node = node->next;
			}
			cout << "Get rid of: " << node->ele << endl;
			Node<int>* tmp = node;
			node = node->next;
			remove(tmp);
		}
		cout << "The left element is: " << node->ele << endl;
	}
};