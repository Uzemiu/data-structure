#pragma once
#include "HashTable.h"
#include <algorithm>
using namespace std;
template<class K, class V>
class AHashTable: HashTable<K, V>{
public:
	void clear();
	bool insert(const K key, const V value);
	bool get(const K& key, V& value);
	bool exists(const K& key);
	bool remove(const K& key, V& value);

protected:
	template<class K, class V>
	struct Record {
		K key;
		V value; 
		// 0 empty 1 exists 2 deleted
		int status;
		Record() : status(0) {}
		Record(K k, V v) : key(k), value(v), status(0) {}
		Record(K k, V v, int status) : key(k), value(v), status(status) {}
	};
	const static int HASH_SIZE = HashTable<K, V>::HASH_SIZE;

	const static int
		STATUS_EMPTY = 0,
		STATUS_EXISTS = 1,
		STATUS_DELETED = 2,
		STATUS_NOT_EMPTY = 3;
	Record<K, V> table[HASH_SIZE];
	int next_probe(const K& key, int status);

};
