#include "Trie.h"

Trie::~Trie() {
	clear();
}

bool Trie::insert(const string& str) {
	Node* node = root;
	bool res = false; // °üº¬¼´false
	for (int i = 0; i < str.length(); i++) {
		int c = alphabetic_order(str[i]);
		if (node->branch[c] == NULL) {
			res = true; 
			node->branch[c] = new Node();
		} 
		node = node->branch[c];
	}
	node->is_end = true;
	return res;
}

bool Trie::search(const string& str) {
	Node* node = search_prefix(str);
	return node && node->is_end;
}

bool Trie::start_with(const string& str) {
	return search_prefix(str);
}

void Trie::clear() {
	clear(root);
}

int Trie::alphabetic_order(char c) 	{
	if (c == ' ') return 0;
	if (islower(c)) return c - 'a' + 1;
	if (isupper(c)) return c - 'A' + 1;
	return 27;
}

Trie::Node* Trie::search_prefix(const string& prefix) {
	Node* node = root;
	for (int i = 0; i < prefix.length(); i++) {
		int c = alphabetic_order(prefix[i]);
		if (node->branch[c] == NULL) {
			return NULL;
		}
		node = node->branch[c];
	}
	return node;
}

void Trie::clear(Node* node) {
	if (!node) { 
		return;
	}
	for (int i = 0; i < NUM_CHARS; i++) {
		clear(node->branch[i]);
	}
	delete node;
}
