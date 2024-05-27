#pragma once


#include "Table.h"


template <typename K, typename T>
class OrderedArrayTable: public Table<K, T> {

private:

	Line<K, T>* array, * end;
	size_t sz;

public:

	OrderedArrayTable(const size_t n = 10);
	~OrderedArrayTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;

	size_t Size() const;
	size_t MaxSize() const;
};



template <typename K, typename T>
OrderedArrayTable<K, T>::OrderedArrayTable(const size_t n) {
	sz = n;
	array = end = new Line<K, T>[sz];
}

template <typename K, typename T>
OrderedArrayTable<K, T>::~OrderedArrayTable() {
	delete[] array;
}



template <typename K, typename T>
T* OrderedArrayTable<K, T>::Search(const K& id) {
	for (size_t i = 0; i < end - array; i++)
		if (array[i].key == id)
			return &array[i].value;
	return nullptr;
}

template <typename K, typename T>
void OrderedArrayTable<K, T>::Insert(const K& id, T& elem) {
	if (Search(id) != nullptr)
		return;
	if (end - array == sz) {
		size_t newSz = sz * 2;
		Line<K, T>* tmp = new Line<K, T>[newSz];
		for (size_t i = 0; i < sz; i++)
			tmp[i] = array[i];
		delete[] array;
		array = tmp;
		end = array + sz;
		sz = newSz;
	}
	size_t i = 0;
	for (; i < end - array; i++)
		if (id < array[i].key)
			break;
	for (size_t j = end - array; j > i; j--)
		array[j] = array[j - 1];
	Line<K, T> line = { id, elem };
	array[i] = line;
	end++;
}

template <typename K, typename T>
void OrderedArrayTable<K, T>::Remove(const K& id) {
	for (size_t i = 0; i < end - array; i++)
		if (array[i].key == id) {
			for (size_t j = i + 1; j < end - array; j++)
				array[j - 1] = array[j];
			end--;
			return;
		}
}

template <typename K, typename T>
void OrderedArrayTable<K, T>::Print() const {
	for (size_t i = 0; i < end - array; i++)
		std::cout << array[i].key << " == " << array[i].value << std::endl;
}

template <typename K, typename T>
size_t OrderedArrayTable<K, T>::Size() const {
	return end - array;
}

template <typename K, typename T>
size_t OrderedArrayTable<K, T>::MaxSize() const {
	return sz;
}
