#pragma once
#include <string>

using namespace std;

class Trie {
public:
	Trie() : root(new Node()) {}
	~Trie();
	bool insert(const string& str);
	bool search(const string& str);
	bool start_with(const string& str);
	void clear();

protected:
	const static int NUM_CHARS = 28;

	struct Node {
		bool is_end;
		Node* branch[NUM_CHARS];
		Node() : is_end(false) {
			memset(branch, NULL, sizeof(branch));
		}
	};

	Node* root;

	int alphabetic_order(char c);
	Node* search_prefix(const string &prefix);
	void clear(Node* node);

};

