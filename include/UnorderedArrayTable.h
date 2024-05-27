#pragma once

#include "Table.h"



template <typename K, typename T>
class UnorderedArrayTable: public Table<K, T> {

private:

	Line<K, T>* array, *end;
	size_t sz;

public:

	UnorderedArrayTable(const size_t n = 10);
	~UnorderedArrayTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;

	size_t Size() const;
	size_t MaxSize() const;
};



template <typename K, typename T>
UnorderedArrayTable<K, T>::UnorderedArrayTable(const size_t n) {
	sz = n;
	array = end = new Line<K, T>[sz];
}

template <typename K, typename T>
UnorderedArrayTable<K, T>::~UnorderedArrayTable() {
	delete[] array;
}



template <typename K, typename T>
T* UnorderedArrayTable<K, T>::Search(const K& id) {
	for (size_t i = 0; i < end - array; i++)
		if (array[i].key == id)
			return &array[i].value;
	return nullptr;
}

template <typename K, typename T>
void UnorderedArrayTable<K, T>::Insert(const K& id,  T& elem) {
	if (Search(id) != nullptr)
		return;
	if (end - array == sz) {
		size_t newSz = sz * 2;
		Line<K, T>* tmp = new Line<K, T>[newSz];
		for (size_t i = 0; i < sz; i++) 
			tmp[i] = array[i];
		delete[] array;
		array = tmp;
		end = tmp + sz;
		sz = newSz;
	}
	if (end - array < sz) {
		end->value = elem;
		end->key = id;
		end++;
	}
}

template <typename K, typename T>
void UnorderedArrayTable<K, T>::Remove(const K& id) {
	for (size_t i = 0; i < end - array; i++) {
		if (array[i].key == id) {
			array[i] = *(end - 1);
			end--;
			return;
		}
	}
}

template <typename K, typename T>
void UnorderedArrayTable<K, T>::Print() const {
	for (size_t i = 0; i < end - array; i++)
		std::cout << array[i].key << " == " << array[i].value << std::endl;
}



template <typename K, typename T>
size_t UnorderedArrayTable<K, T>::Size() const {
	return end - array;
}

template <typename K, typename T>
size_t UnorderedArrayTable<K, T>::MaxSize() const {
	return sz;
}
