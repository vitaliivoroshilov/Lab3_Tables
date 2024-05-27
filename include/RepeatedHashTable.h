#pragma once

#include <iostream>
#include "Table.h"



template <typename K, typename T>
class RepeatedHashTable: public Table<K, T> {

private:

	Line<K, T>* array;
	size_t sz, arrSz, step, number;

	size_t GreatCommonDiv(size_t a, size_t b) const;
	void UpdateStep();
	size_t HashFunction(const std::string& id) const;
	size_t RepeatedFunction(const size_t& code) const;
	void RebuildTable();

public:

	RepeatedHashTable(const size_t& arraySize = 10);
	RepeatedHashTable(const RepeatedHashTable& table);
	~RepeatedHashTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;

	size_t Size() const;
	size_t MaxSize() const;
};



template <typename K, typename T>
size_t RepeatedHashTable<K, T>::GreatCommonDiv(size_t a, size_t b) const {
	if ((a == 0) || (b == 0))
		return a + b;
	if (a > b)
		return GreatCommonDiv(a - b, b);
	else
		return GreatCommonDiv(a, b - a);
}

template <typename K, typename T>
void RepeatedHashTable<K, T>::UpdateStep() {
	for (size_t i = arrSz / 2; i > 0; i--)
		if (GreatCommonDiv(arrSz, i) == 1) {
			step = i;
			break;
		}
}

template <typename K, typename T>
size_t RepeatedHashTable<K, T>::HashFunction(const std::string& id) const {
	size_t code = 0;
	for (size_t i = 0; i < id.length(); i++)
		code += id[i];
	return code % arrSz;
}

template <typename K, typename T>
size_t RepeatedHashTable<K, T>::RepeatedFunction(const size_t& code) const {
	return (code + step) % arrSz;
}

template <typename K, typename T>
void RepeatedHashTable<K, T>::RebuildTable() {
	size_t oldArrSz = arrSz;
	arrSz *= 2;
	UpdateStep();
	Line<K, T>* tmp = new Line<K, T>[oldArrSz];
	for (size_t i = 0; i < oldArrSz; i++) {
		tmp[i].key = array[i].key;
		tmp[i].value = array[i].value;
	}
	delete[] array;
	array = new Line<K, T>[arrSz];
	for (size_t i = 0; i < arrSz; i++) {
		array[i].key = "Empty";
		//array[i].value = nullptr;
	}
	sz = 0;
	for (size_t i = 0; i < oldArrSz; i++)
		if ((tmp[i].key != "Empty") && (tmp[i].key != "Removed"))
			Insert(tmp[i].key, tmp[i].value);
}



template <typename K, typename T>
RepeatedHashTable<K, T>::RepeatedHashTable(const size_t& arraySize) {
	sz = 0;
	arrSz = arraySize;
	array = new Line<K, T>[arrSz];
	for (size_t i = 0; i < arrSz; i++) {
		array[i].key = "Empty";
		//array[i].value = nullptr;
	}
	step = 1;
	UpdateStep();
	number = arrSz;
}

template <typename K, typename T>
RepeatedHashTable<K, T>::RepeatedHashTable(const RepeatedHashTable& table) {
	sz = table.sz;
	arrSz = table.arrSz;
	step = table.step;
	number = table.number;
	for (size_t i = 0; i < arrSz; i++)
		array[i] = table.array[i];
}

template <typename K, typename T>
RepeatedHashTable<K, T>::~RepeatedHashTable() {
	delete[] array;
}



template <typename K, typename T>
T* RepeatedHashTable<K, T>::Search(const K& id) {
	size_t code = HashFunction(id);
	number = arrSz;
	while (true) {
		if (array[code].key == id) {
			number = code;
			return &array[code].value;
		}
		if (array[code].key == "Empty")
			return nullptr;
		code = RepeatedFunction(code);
	}
}

template <typename K, typename T>
void RepeatedHashTable<K, T>::Insert(const K& id, T& elem) {
	if (sz == arrSz)
		RebuildTable();
	size_t code = HashFunction(id);
	while (true) {
		if (array[code].key == id)
			return;
		number = arrSz;
		if ((array[code].key == "Removed") && (number == arrSz))
			number = code;
		if (array[code].key == "Empty")
			if (number == arrSz) {
				array[code].key = id;
				array[code].value = elem;
				sz++;
				return;
			}
			else {
				array[number].key = id;
				array[number].value = elem;
				sz++;
				return;
			}
		code = RepeatedFunction(code);
	}
}

template <typename K, typename T>
void RepeatedHashTable<K, T>::Remove(const K& id) {
	Search(id);
	if (number < arrSz) {
		array[number].key = "Removed";
		//array[number].value = nullptr;
		sz--;
	}
}

template <typename K, typename T>
void RepeatedHashTable<K, T>::Print() const {
	for (size_t i = 0; i < arrSz; i++)
		if ((array[i].key != "Empty") && (array[i].key != "Removed"))
			std::cout << array[i].key << " == " << array[i].value << std::endl;
}

template <typename K, typename T>
size_t RepeatedHashTable<K, T>::Size() const {
	return sz;
}

template <typename K, typename T>
size_t RepeatedHashTable<K, T>::MaxSize() const {
	return arrSz;
}
