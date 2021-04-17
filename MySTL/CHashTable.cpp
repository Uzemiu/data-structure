#include "CHashTable.h"

template<class K, class V>
void CHashTable<K, V>::clear() {
	for (int i = 0; i < HASH_SIZE; i++) {
		table[i].clear();
	}
}

template<class K, class V>
bool CHashTable<K, V>::insert(const K key, const V value) {
	Record<K, V> r(key, value);
	int probe = HashTable<K, V>::hash(key);
	int i = table[probe].find(r);
	if (i >= 0) {
		return false;
	} else {
		table[probe].push_first(r);
	}
	return true;
}

template<class K, class V>
bool CHashTable<K, V>::get(const K& key, V& value) {
	int probe = HashTable<K, V>::hash(key);
	int i = table[probe].find(Record<K, V>(key));
	if (i >= 0) {
		value = table[probe].get(i).value;
		return true;
	} 
	return false;
}

template<class K, class V>
bool CHashTable<K, V>::exists(const K& key) {
	int probe = HashTable<K, V>::hash(key);
	return table[probe].find(Record<K, V>(key)) >= 0;
}

template<class K, class V>
bool CHashTable<K, V>::remove(const K& key, V& value) {
	int probe = HashTable<K, V>::hash(key);
	int i = table[probe].find(Record<K, V>(key));
	if (i >= 0) {
		value = table[probe].get(i).value;
		table[probe].remove(i);
		return true;
	}
	return false;
}
