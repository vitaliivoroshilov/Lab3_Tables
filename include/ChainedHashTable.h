#pragma once

#include <iostream>

#include "Table.h"
#include "TList.h"



template <typename K, typename T>
class ChainedHashTable : public Table<K, T> {

private:

	TList<Line<K, T>>* array;
	size_t sz, arrSz;

	size_t HashFunction(const std::string& id) const;
	void RebuildTable();

public:

	ChainedHashTable(const size_t& arraySize = 10);
	~ChainedHashTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;

	size_t Size() const;
	size_t MaxSize() const;
};



template <typename K, typename T>
size_t ChainedHashTable<K, T>::HashFunction(const std::string& id) const {
	size_t code = 0;
	for (size_t i = 0; i < id.length(); i++)
		code += id[i];
	return code % arrSz;
}

template <typename K, typename T>
void ChainedHashTable<K, T>::RebuildTable() {
	TList<Line<K, T>>* tmp = new TList<Line<K, T>>[arrSz];
	for (size_t i = 0; i < arrSz; i++)
		tmp[i] = array[i];
	delete[] array;
	arrSz *= 2;
	array = new TList<Line<K, T>>[arrSz];
	for (size_t i = 0; i < arrSz / 2; i++)
		for (size_t j = 0; j < tmp[i].Size(); j++)
			Insert(tmp[i][j].key, tmp[i][j].value);
}



template <typename K, typename T>
ChainedHashTable<K, T>::ChainedHashTable(const size_t& arraySize) {
	sz = 0;
	arrSz = arraySize;
	array = new TList<Line<K, T>>[arrSz];
}

template <typename K, typename T>
ChainedHashTable<K, T>::~ChainedHashTable() {
	delete[] array;
}



template <typename K, typename T>
T* ChainedHashTable<K, T>::Search(const K& id) {
	size_t code = HashFunction(id);
	for (size_t i = 0; i < array[code].Size(); i++)
		if (array[code][i].key == id)
			return &array[code][i].value;
	return nullptr;
}

template <typename K, typename T>
void ChainedHashTable<K, T>::Insert(const K& id, T& elem) {
	if (Search(id) != nullptr)
		return;
	if (sz == arrSz)
		RebuildTable();
	size_t code = HashFunction(id);
	Line<K, T> line;
	line.key = id;
	line.value = elem;
	array[code].PushBack(line);
	sz++;
}

template <typename K, typename T>
void ChainedHashTable<K, T>::Remove(const K& id) {
	if (Search(id) == nullptr)
		return;
	size_t code = HashFunction(id);
	for (size_t i = 0; i < array[code].Size(); i++)
		if (array[code][i].key == id)
			array[code].PopPos(i);
}

template <typename K, typename T>
void ChainedHashTable<K, T>::Print() const {
	for (size_t i = 0; i < arrSz; i++)
		for (size_t j = 0; j < array[i].Size(); j++)
			std::cout << array[i][j].key << " == " << array[i][j].value << std::endl;
}

template <typename K, typename T>
size_t ChainedHashTable<K, T>::Size() const {
	return sz;
}

template <typename K, typename T>
size_t ChainedHashTable<K, T>::MaxSize() const {
	return arrSz;
}
