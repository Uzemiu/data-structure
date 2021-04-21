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

template<class K, class V>
void AHashTable<K, V>::clear() {
	for (int i = 0; i < HASH_SIZE; i++) {
		table[i].status = STATUS_EMPTY;
	}
}

template<class K, class V>
bool AHashTable<K, V>::insert(const K key, const V value) {
	int probe = next_probe(key, STATUS_EXISTS);
	if (table[probe].status == STATUS_EXISTS && table[probe].key == key) {
		return false;
	}
	table[probe] = Record<K, V>(key, value, true);
	return true;
}

template<class K, class V>
bool AHashTable<K, V>::get(const K& key, V& value) {
	int probe = next_probe(key, STATUS_NOT_EMPTY);
	if (table[probe].status == STATUS_EXISTS && table[probe].key == key) {
		value = table[probe].value;
		return true;
	}
	return false;
}

template<class K, class V>
bool AHashTable<K, V>::exists(const K& key) {
	int probe = next_probe(key, STATUS_NOT_EMPTY);
	return table[probe].status == STATUS_EXISTS && table[probe].key == key;
}

template<class K, class V>
bool AHashTable<K, V>::remove(const K& key, V& value) {
	int probe = next_probe(key, STATUS_NOT_EMPTY);
	if (table[probe].status == STATUS_EXISTS && table[probe].key == key) {
		value = table[probe].value;
		table[probe].status = STATUS_DELETED;
		return true;
	}
	return false;
}

template<class K, class V>
int AHashTable<K, V>::next_probe(const K& key, int status) {
	int probe_count = 0, increment = 1, probe = HashTable<K, V>::hash(key);
	while ((table[probe].status & status)
		   && table[probe].key != key
		   && probe_count < (HASH_SIZE + 1) / 2) {
		probe_count++;
		probe = (probe + increment) % HASH_SIZE;
		increment += 2;
	}
	return probe;
}

