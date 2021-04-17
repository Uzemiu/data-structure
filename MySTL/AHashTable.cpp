#include "AHashTable.h"
using namespace std;

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
bool AHashTable<K, V>::get(const K& key, V& value){
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
int AHashTable<K, V>::next_probe(const K& key, int status){
	int probe_count = 0, increment = 1, probe = HashTable<K,V>::hash(key);
	while ((table[probe].status & status)
		   && table[probe].key != key
		   && probe_count < (HASH_SIZE + 1) / 2) {
		probe_count++;
		probe = (probe + increment) % HASH_SIZE;
		increment += 2;
	}
	return probe;
}

