#pragma once

#include "Table.h"



template <typename K, typename T>
class AVLTreeTable: public Table<K, T> {

private:

	struct Node {
		Line<K, T> data;
		Node* left;
		Node* right;
		size_t height;

		Node(const K& id, T& elem) {
			data.key = id;
			data.value = elem;
			left = nullptr;
			right = nullptr;
			height = 1;
		}
	};

	Node* root;
	size_t countNodes;

	size_t HeightOf(const Node* node) const;
	int BalanceOf(const Node* node) const;
	void UpdateHeightOf(Node* node);

	Node* RotateRight(Node* node);
	Node* RotateLeft(Node* node);
	Node* RotateDouble(Node* node);

	Node* InsertNode(Node* node, const K& id, T& elem);
	
	Node* FindMin(Node* node) const;
	Node* RemoveMin(Node* node);
	Node* RemoveNode(Node* node, const K& id);
	
	void PrintNode(const Node* node) const;
	
	Node* FindNode(Node* node, const K& id) const;
	
	void Destruct(const Node* node);

public:

	AVLTreeTable();
	~AVLTreeTable();

	T* Search(const K& id) override;
	void Insert(const K& id, T& elem) override;
	void Remove(const K& id) override;
	void Print() const override;
	
};



template <typename K, typename T>
size_t AVLTreeTable<K, T>::HeightOf(const Node* node) const {
	if (node == nullptr)
		return 0;
	else
		return node->height;
}

template <typename K, typename T>
int AVLTreeTable<K, T>::BalanceOf(const Node* node) const {
	return HeightOf(node->right) - HeightOf(node->left);
}

template <typename K, typename T>
void AVLTreeTable<K, T>::UpdateHeightOf(Node* node) {
	if (HeightOf(node->left) > HeightOf(node->right))
		node->height = HeightOf(node->left) + 1;
	else
		node->height = HeightOf(node->right) + 1;
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::RotateRight(Node* node) {
	Node* l = node->left;
	node->left = l->right;
	l->right = node;
	if (node == root)
		root = l;
	UpdateHeightOf(node);
	UpdateHeightOf(l);
	return l;
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::RotateLeft(Node* node) {
	Node* r = node->right;
	node->right = r->left;
	r->left = node;
	if (node == root)
		root = r;
	UpdateHeightOf(node);
	UpdateHeightOf(r);
	return r;
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::RotateDouble(Node* node) {
	UpdateHeightOf(node);
	if (BalanceOf(node) == 2) {
		if (BalanceOf(node->right) == -1)
			node->right = RotateRight(node->right);
		return RotateLeft(node);
	}
	if (BalanceOf(node) == -2) {
		if (BalanceOf(node->left) == 1)
			node->left = RotateLeft(node->left);
		return RotateRight(node);
	}
	return node;
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::InsertNode(Node* node, const K& id, T& elem) {
	if (node == nullptr) {
		Node* newNode = new Node(id, elem);
		if (countNodes == 0)
			root = newNode;
		return newNode;
	}
	if (id < node->data.key)
		node->left = InsertNode(node->left, id, elem);
	else
		node->right = InsertNode(node->right, id, elem);
	return RotateDouble(node);
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::FindMin(Node* node) const {
	if (node->left == nullptr)
		return node;
	return FindMin(node->left);
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::RemoveMin(Node* node) {
	if (node->left == nullptr)
		return node->right;
	node->left = RemoveMin(node->left);
	return RotateDouble(node);
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::RemoveNode(Node* node, const K& id) {
	if (node == nullptr)
		return nullptr;
	if (id < node->data.key)
		node->left = RemoveNode(node->left, id);
	else 
		if (id > node->data.key)
			node->right = RemoveNode(node->right, id);
		else {
			Node* l = node->left;
			Node* r = node->right;
			if (r == nullptr) {
				if (node == root) 
					root = l;
				return l;
			}
			Node* minR = FindMin(r);
			minR->right = RemoveMin(r);
			minR->left = l;
			if (node == root)
				root = minR;
			delete node;
			return RotateDouble(minR);
		}
	return RotateDouble(node);
}

template <typename K, typename T>
void AVLTreeTable<K, T>::PrintNode(const Node* node) const {
	if (node == nullptr)
		return;
	PrintNode(node->left);
	std::cout << node->data.key << " == " << node->data.value << std::endl;
	PrintNode(node->right);
}

template <typename K, typename T>
typename AVLTreeTable<K, T>::Node* AVLTreeTable<K, T>::FindNode(Node* node, const K& id) const {
	if (node == nullptr)
		return nullptr;
	if (id < node->data.key)
		return FindNode(node->left, id);
	if (id > node->data.key)
		return FindNode(node->right, id);
	return node;
}

template <typename K, typename T>
void AVLTreeTable<K, T>::Destruct(const Node* node) {
	if (node == nullptr)
		return;
	Destruct(node->left);
	Destruct(node->right);
	delete node;
}



template <typename K, typename T>
AVLTreeTable<K, T>::AVLTreeTable() {
	root = nullptr;
	countNodes = 0;
}

template <typename K, typename T>
AVLTreeTable<K, T>::~AVLTreeTable() {
	Destruct(root);
}



template <typename K, typename T>
T* AVLTreeTable<K, T>::Search(const K& id) {
	Node* node = FindNode(root, id);
	if (node == nullptr)
		return nullptr;
	return &node->data.value;
}

template <typename K, typename T>
void AVLTreeTable<K, T>::Insert(const K& id, T& elem) {
	if (Search(id) != nullptr)
		return;
	InsertNode(root, id, elem);
	countNodes++;
}

template <typename K, typename T>
void AVLTreeTable<K, T>::Remove(const K& id) {
	if (RemoveNode(root, id) != nullptr)
		countNodes--;
}

template <typename K, typename T>
void AVLTreeTable<K, T>::Print() const {
	PrintNode(root);
}
