#pragma once

#include <iostream>


template <typename T>
class TList {

private:

	struct TNode {
		T value;
		TNode* pNext;
	};

	TNode* pFirst;
	TNode* pLast;
	TNode* pCurrent;
	size_t sz;
	size_t posCurrent;

public:

	TList();
	TList(const TList<T>& list);
	~TList();

	size_t Size() const;
	bool IsEmpty() const;
	void CurrentNext();
	void CurrentToPos(size_t pos);
	T& GetPos(size_t pos) const;
	void PushFront(const T& val);
	void PopFront();
	void PushBack(const T& val);
	void PopBack();
	void PushPos(size_t pos, const T& val);
	void PopPos(size_t pos);
	void PushSort(const T& val);
	void Clear();
	void Print();

	TList& operator=(const TList<T>& list);
	T& operator[](size_t pos);
	bool operator==(const TList<T>& list) const;

};


template <typename T>
TList<T>::TList() {
	pFirst = pLast = pCurrent = nullptr;
	sz = posCurrent = 0;
}

template <typename T>
TList<T>::TList(const TList<T>& list) {
	pFirst = pLast = pCurrent = nullptr;
	sz = list.sz;
	posCurrent = list.posCurrent;
	if (list.pFirst == nullptr)
		return;
	size_t i = 0;
	TNode* nodeNew = pFirst = new TNode{ *list.pFirst };
	while (nodeNew->pNext != nullptr) {
		if (i == posCurrent)
			pCurrent = nodeNew;
		nodeNew->pNext = new TNode{ *nodeNew->pNext };
		nodeNew = nodeNew->pNext;
		i++;
	}
	pLast = nodeNew;
}

template <typename T>
TList<T>::~TList() {
	TNode* nodeDel;
	while (pFirst != nullptr) {
		nodeDel = pFirst;
		pFirst = pFirst->pNext;
		delete nodeDel;
	}
}

template <typename T>
size_t TList<T>::Size() const {
	return sz;
}

template <typename T>
bool TList<T>::IsEmpty() const {
	return sz == 0;
}

template <typename T>
void TList<T>::CurrentNext() {
	pCurrent = pCurrent->pNext;
	posCurrent++;
}

template <typename T>
void TList<T>::CurrentToPos(size_t pos) {
	/*if (pos >= sz) {
		throw std::out_of_range("pos >= sz !!!");
		return nullptr;
	}*/
	if (posCurrent > pos) {
		pCurrent = pFirst;
		posCurrent = 0;
	}
	while ((pCurrent != pLast) && (posCurrent < pos)) {
		CurrentNext();
	}
}

template <typename T>
T& TList<T>::GetPos(size_t pos) const {
	TNode* node = pFirst;
	size_t i = 0;
	while ((node != pLast) && (i < pos)) {
		node = node->pNext;
		i++;
	}
	return node->value;
}

template <typename T>
void TList<T>::PushFront(const T& val) {
	TNode* nodeNew = new TNode{ val, pFirst };
	pFirst = nodeNew;
	sz++;
	posCurrent++;
	if (sz == 1)
		pCurrent = pLast = pFirst;
}

template <typename T>
void TList<T>::PopFront() {
	if (IsEmpty())
		return;
	TNode* nodeDel = pFirst;
	pFirst = pFirst->pNext;
	delete nodeDel;
	sz--;
	posCurrent = 0;
	pCurrent = pFirst;
}

template <typename T>
void TList<T>::PushBack(const T& val) {
	if (IsEmpty())
		PushFront(val);
	else {
		TNode* nodeNew = new TNode{ val, nullptr };
		pLast->pNext = nodeNew;
		pLast = nodeNew;
		sz++;
	}
}

template <typename T>
void TList<T>::PopBack() {
	if (IsEmpty())
		return;
	if (sz == 1) {
		PopFront();
		return;
	}
	CurrentToPos(sz - 2);
	delete pLast;
	pLast = pCurrent;
	pLast->pNext = nullptr;
	sz--;
}

template <typename T>
void TList<T>::PushPos(size_t pos, const T& val) {
	if (IsEmpty())
		PushFront(val);
	CurrentToPos(pos - 1);
	TNode* nodeNew = new TNode{ val, pCurrent->pNext };
	pCurrent->pNext = nodeNew;
	sz++;
}

template <typename T>
void TList<T>::PopPos(size_t pos) {
	if (IsEmpty())
		return;
	if (sz == 1) {
		PopFront();
		return;
	}
	if (pos == sz - 1) {
		PopBack();
		return;
	}
	if (pos == 0) {
		PopFront();
		return;
	}
	CurrentToPos(pos - 1);
	TNode* nodeDel = pCurrent->pNext;
	if (nodeDel == pLast)
		pLast = pCurrent;
	pCurrent->pNext = nodeDel->pNext;
	delete nodeDel;
	sz--;
}

template <typename T>
void TList<T>::PushSort(const T& val) {
	if (IsEmpty()) {
		PushFront(val);
		return;
	}
	if (val < pFirst->value) {
		PushFront(val);
		return;
	}
	if (val > pLast->value) {
		PushBack(val);
		return;
	}
	CurrentToPos(0);
	while ((pCurrent->pNext != pLast) && (val > pCurrent->pNext->value))
		CurrentNext();
	TNode* nodeNew = new TNode{ val, pCurrent->pNext };
	pCurrent->pNext = nodeNew;
	sz++;
}

template <typename T>
void TList<T>::Clear() {
	TNode* nodeDel;
	while (pFirst != nullptr) {
		nodeDel = pFirst;
		pFirst = pFirst->pNext;
		delete nodeDel;
	}
	pFirst = pLast = pCurrent = nullptr;
	sz = posCurrent = 0;
}

template <typename T>
void TList<T>::Print() {
	if (IsEmpty())
		return;
	std::cout << "{ ";
	TNode* node = pFirst;
	while (node != pLast) {
		std::cout << node->value << " ";
		node = node->pNext;
	}
	std::cout << node->value << "}" << std::endl;
}

template <typename T>
TList<T>& TList<T>::operator=(const TList<T>& list) {
	if (this == &list)
		return *this;
	TList<T> tmp(list);
	std::swap(pFirst, tmp.pFirst);
	std::swap(pLast, tmp.pLast);
	std::swap(pCurrent, tmp.pCurrent);
	std::swap(sz, tmp.sz);
	std::swap(posCurrent, tmp.posCurrent);
	return *this;
}

template <typename T>
T& TList<T>::operator[](size_t pos) {
	CurrentToPos(pos);
	return pCurrent->value;
}

template <typename T>
bool TList<T>::operator==(const TList<T>& list) const {
	if (Size() != list.Size())
		return false;
	for (size_t i = 0; i < Size(); i++)
		if (GetPos(i) != list.GetPos(i))
			return false;
	return true;
}