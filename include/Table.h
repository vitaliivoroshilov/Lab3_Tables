#pragma once


template <typename K, typename T>
struct Line {
	K key;
	T value;
};

template <typename K, typename T>
class Table {

public:

	virtual T* Search(const K& id) = 0;
	virtual void Insert(const K& id, T& elem) = 0;
	virtual void Remove(const K& id) = 0;
	virtual void Print() const = 0;
};
