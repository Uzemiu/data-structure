#pragma once
template<class K, class V>
class HashTable {
public:
	void clear();
	void insert(const K key, const V value);
	V& get(const K& key) const;
	bool remove(const K& key, const V& value);

private:
	const static int HASH_SIZE = 97;
	V table[HASH_SIZE];
};

