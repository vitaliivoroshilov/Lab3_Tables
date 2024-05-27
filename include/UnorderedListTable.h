#pragma once

#include "Table.h"



template <typename K, typename T>
class UnorderedListTable: public Table<K, T> {

private:

	TList<Line<K, T>> list;

public:

	UnorderedListTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;
	
	size_t Size() const;
};



template <typename K, typename T>
UnorderedListTable<K, T>::UnorderedListTable() {}



template <typename K, typename T>
T* UnorderedListTable<K, T>::Search(const K& id) {
	for (size_t i = 0; i < list.Size(); i++)
		if (list.GetPos(i).key == id)
			return &list.GetPos(i).value;
	return nullptr;
}

template <typename K, typename T>
void UnorderedListTable<K, T>::Insert(const K& id, T& elem) {
	if (Search(id) != nullptr)
		return;
	Line<K, T> line;
	line.key = id;
	line.value = elem;
	list.PushBack(line);
}

template <typename K, typename T>
void UnorderedListTable<K, T>::Remove(const K& id) {
	for (size_t i = 0; i < list.Size(); i++)
		if (list.GetPos(i).key == id) {
			list.PopPos(i);
			return;
		}
}

template<typename K, typename T>
void UnorderedListTable<K, T>::Print() const {
	for (size_t i = 0; i < list.Size(); i++)
		std::cout << list.GetPos(i).key << " == " << list.GetPos(i).value << std::endl;
}

template <typename K, typename T>
size_t UnorderedListTable<K, T>::Size() const {
	return list.Size();
}
