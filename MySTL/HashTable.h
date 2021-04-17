#pragma once
#include <algorithm>
using namespace std;
template<class K, class V>
class HashTable {
public:
	virtual void clear() = 0;
	virtual bool insert(const K key, const V value) = 0;
	virtual bool get(const K& key, V& value) = 0;
	virtual bool exists(const K& key) = 0;
	virtual bool remove(const K& key, V& value) = 0;

	const static int HASH_SIZE = 97;

	template<class T>
	int hash(const T& t);
};

template<class K, class V>
template<class T>
inline int HashTable<K, V>::hash(const T& t) {
	std::hash<T> h;
	return h(t) % HASH_SIZE;
}