#pragma once
#include "LinkedList.h"
#include "HashTable.h"
template<class K, class V>
class CHashTable : HashTable<K, V>{
public:
	void clear();
	bool insert(const K key, const V value);
	bool get(const K& key, V& value);
	bool exists(const K& key);
	bool remove(const K& key, V& value);

private:
	template<class K, class V>
	struct Record {
		K key;
		V value;
		Record() {}
		Record(K k): key(k) {}
		Record(K k, V v) : key(k), value(v){}
		bool operator==(const Record& record) {
			return key == record.key;
		}
		bool operator!=(const Record& record) {
			return key != record.key;
		}
	};

	const static int HASH_SIZE = HashTable<K, V>::HASH_SIZE;

	LinkedList<Record<K, V>> table[HASH_SIZE];
};
