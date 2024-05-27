#pragma once

#include "Polynomial.h"
#include "Table.h"
#include "UnorderedArrayTable.h"
#include "UnorderedListTable.h"
#include "OrderedArrayTable.h"
#include "AVLTreeTable.h"
#include "RepeatedHashTable.h"
#include "ChainedHashTable.h"



template <typename K, typename T>
class TablesManager {

private:

	Table<K, T>* tables[6];
	size_t active, sz;

public:

	TablesManager();

	void ChangeActive(const size_t& act);

	T* SearchInActive(const K& id);
	void InsertInAll(const K& id, T& elem);
	void RemoveInAll(const K& id);
	void PrintActive() const;

};



template <typename K, typename T>
TablesManager<K, T>::TablesManager() {
	UnorderedArrayTable<K, T>* unordArrTable = new UnorderedArrayTable<K, T>;
	UnorderedListTable<K, T>* unordListTable = new UnorderedListTable<K, T>;
	OrderedArrayTable<K, T>* ordArrTable = new OrderedArrayTable<K, T>;
	AVLTreeTable<K, T>* avlTreeTable = new AVLTreeTable<K, T>;
	RepeatedHashTable<K, T>* repeatHashTable = new RepeatedHashTable<K, T>;
	ChainedHashTable<K, T>* chainHashTable = new ChainedHashTable<K, T>;
	
	tables[0] = unordArrTable;
	tables[1] = unordListTable;
	tables[2] = ordArrTable;
	tables[3] = avlTreeTable;
	tables[4] = repeatHashTable;
	tables[5] = chainHashTable;

	sz = 6;
	active = 0;
}



template <typename K, typename T>
void TablesManager<K, T>::ChangeActive(const size_t& act) {
	active = act;
}

template <typename K, typename T>
T* TablesManager<K, T>::SearchInActive(const K& id) {
	return (*tables[active]).Search(id);
}

template <typename K, typename T>
void TablesManager<K, T>::InsertInAll(const K& id, T& elem) {
	for (size_t i = 0; i < sz; i++)
		(*tables[i]).Insert(id, elem);
}

template <typename K, typename T>
void TablesManager<K, T>::RemoveInAll(const K& id) {
	for (size_t i = 0; i < sz; i++)
		(*tables[i]).Remove(id);
}

template <typename K, typename T>
void TablesManager<K, T>::PrintActive() const {
	(*tables[active]).Print();
}
