#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <iomanip>

#include "Test.h";

using namespace std;


void test_trie() {
	Trie trie;
	trie.insert("a");
	trie.insert("aa");
	trie.insert("ab");
	trie.insert("ac");
	trie.insert("aba");
	trie.insert("abc");
	trie.insert("abba");
	trie.insert("abaca");

	trie.insert("baba");

	trie.insert("caaba");
	trie.insert("ca");
	trie.insert("c");
	trie.insert("ca");
	trie.insert("cab");
	trie.insert("caba");

	cout << trie.search("abaca") << endl
		<< trie.search("abac") << endl
		<< trie.search("bag") << endl;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Test test;
	//test.	
		test_trie();


	_CrtDumpMemoryLeaks();
	return 0;
}

