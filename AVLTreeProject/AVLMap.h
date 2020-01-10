#pragma once

#include "AVLMapNode.h"
#include <ostream>
#include <iomanip>

namespace AVLTreeProject
{
	// AVL-tree class
	template<typename K, typename T>
	class AVLMap
	{
	private:
		AVLMapNode<K, T>* root;		// Root-node of tree
		size_t size;			// Size of tree
		
		void deleteSubTree(AVLMapNode<K, T>* node);		// Delete all sub-tree from argument node (recursive)
		
		AVLMapNode<K, T>* recursiveInsert(AVLMapNode<K, T>* node, K& key, T& data);
		AVLMapNode<K, T>* recursiveRemove(AVLMapNode<K, T>* node, K& key);
		AVLMapNode<K, T>* recursiveFind(AVLMapNode<K, T>* node, K& key);

		AVLMapNode<K, T>* findMin(AVLMapNode<K, T>* node);
		AVLMapNode<K, T>* findMax(AVLMapNode<K, T>* node);
		AVLMapNode<K, T>* removeMin(AVLMapNode<K, T>* node);

		AVLMapNode<K, T>* reBalance(AVLMapNode<K, T>* node);

		AVLMapNode<K, T>* rotateRight(AVLMapNode<K, T>* node);
		AVLMapNode<K, T>* rotateLeft(AVLMapNode<K, T>* node);
		AVLMapNode<K, T>* rotateBigRight(AVLMapNode<K, T>* node);
		AVLMapNode<K, T>* rotateBigLeft(AVLMapNode<K, T>* node);

		void print(AVLMapNode<K, T>* n, std::ostream& out, size_t displacement);

	public:
		AVLMap();
		~AVLMap();

		T get(K key);					// Returns data from node with argument key
		void put(K key, T data);		// Add to tree (value will be copyied into Node)
		void remove(K key);			// Remove from tree (will be remove Node with same value)
		bool containsKey(K key);		// Check: has tree Node with same value or not

		size_t getSize();


		void printAll(std::ostream& out);
	};





	template<typename K, typename T>
	T AVLMap<K, T>::get(K key)
	{
		return recursiveFind(root, key)->getData();
	}

	template<typename K, typename T>
	AVLMap<K, T>::AVLMap()
	{
		root = nullptr;
		size = 0;
	}

	template<typename K, typename T>
	AVLMap<K, T>::~AVLMap()
	{
		if (root != nullptr)
			deleteSubTree(root);
	}

	template<typename K, typename T>
	void AVLMap<K, T>::deleteSubTree(AVLMapNode<K, T>* n)
	{
		if (n == nullptr)
			return;

		deleteSubTree(n->getLeft());
		deleteSubTree(n->getRight());

		delete n;
	}

	template<typename K, typename T>
	size_t AVLMap<K, T>::getSize()
	{
		return size;
	}

	template<typename K, typename T>
	void AVLMap<K, T>::put(K key, T data)
	{
		if (size == 0)
		{
			root = new AVLMapNode<K, T>(key, data);		// newNode;
			size++;
		}
		else
		{
			root = recursiveInsert(root, key, data);
		}
	}


	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::recursiveInsert(AVLMapNode<K, T>* node, K& key, T& data)
	{
		if (node == nullptr)
		{
			size++;
			return new AVLMapNode<K, T>(key, data);
		}

		if (key == node->getKey())
		{
			node->setData(data);
			return node;
		}
		else if (key < node->getKey())
			node->setLeft(recursiveInsert(node->getLeft(), key, data));
		else
			node->setRight(recursiveInsert(node->getRight(), key, data));

		return reBalance(node);
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::rotateRight(AVLMapNode<K, T>* node)		// Left Left
	{
		AVLMapNode<K, T>* temp = node->getLeft();
		node->setLeft(temp->getRight());
		temp->setRight(node);

		node->updateHeight();
		temp->updateHeight();

		return temp;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::rotateLeft(AVLMapNode<K, T>* node)		// Right Right
	{
		AVLMapNode<K, T>* temp = node->getRight();
		node->setRight(temp->getLeft());
		temp->setLeft(node);

		node->updateHeight();
		temp->updateHeight();

		return temp;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::rotateBigRight(AVLMapNode<K, T>* node)	// Left Right
	{
		node->setLeft(rotateLeft(node->getLeft()));
		return rotateRight(node);
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::rotateBigLeft(AVLMapNode<K, T>* node)		// Right Left
	{
		node->setRight(rotateRight(node->getRight()));
		return rotateLeft(node);
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::reBalance(AVLMapNode<K, T>* node)
	{
		node->updateHeight();

		if (node->getHeightDifference() == 2)
			if (node->getLeft()->getHeightDifference() >= 0)
				return rotateRight(node);
			else
				return rotateBigRight(node);
		else if (node->getHeightDifference() == -2)
			if (node->getRight()->getHeightDifference() <= 0)
				return rotateLeft(node);
			else
				return rotateBigLeft(node);

		return node;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::recursiveFind(AVLMapNode<K, T>* node, K& key)
	{
		if (node == nullptr)
			return nullptr;

		if (node->getKey() == key)
			return node;

		if (node->getKey() < key)
			return recursiveFind(node->getRight(), key);
		else
			return recursiveFind(node->getLeft(), key);
	}

	template<typename K, typename T>
	bool AVLMap<K, T>::containsKey(K key)
	{
		if (recursiveFind(root, key) == nullptr)
			return false;
		else
			return true;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::findMin(AVLMapNode<K, T>* node)
	{
		if (node->getLeft() == nullptr)
			return node;
		else
			return findMin(node->getLeft());
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::findMax(AVLMapNode<K, T>* node)
	{
		if (node->getRight() == nullptr)
			return node;
		else
			return findMin(node->getRight());
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::removeMin(AVLMapNode<K, T>* node)
	{
		if (node->getLeft() == nullptr)
			return node->getRight();

		node->setLeft(removeMin(node->getLeft()));
		return reBalance(node);
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMap<K, T>::recursiveRemove(AVLMapNode<K, T>* node, K& key)
	{
		if (node == nullptr)
			return nullptr;

		if (node->getKey() == key)
		{
			AVLMapNode<K, T>* nodeLeft = node->getLeft();
			AVLMapNode<K, T>* nodeRight = node->getRight();
			delete node;

			size--;

			if (nodeRight == nullptr)
				return nodeLeft;

			AVLMapNode<K, T>* minNode = findMin(nodeRight);
			minNode->setRight(removeMin(nodeRight));
			minNode->setLeft(nodeLeft);

			return reBalance(minNode);
		}

		if (node->getKey() < key)
			node->setRight(recursiveRemove(node->getRight(), key));
		else
			node->setLeft(recursiveRemove(node->getLeft(), key));

		return reBalance(node);
	}

	template<typename K, typename T>
	void AVLMap<K, T>::remove(K key)
	{
		root = recursiveRemove(root, key);
	}



	template<typename K, typename T>
	void AVLMap<K, T>::print(AVLMapNode<K, T>* n, std::ostream& out, size_t displacement)
	{
		for (size_t i = 0; i < displacement; i++)
			out << std::setw(10) << "";

		if (n != nullptr)
		{
			out << n->getData() << " --> " << std::endl;
			print(n->getLeft(), out, displacement + 1);
			print(n->getRight(), out, displacement + 1);
		}
		else
			out << "End of branch" << std::endl;
	}

	template<typename K, typename T>
	void AVLMap<K, T>::printAll(std::ostream& out)
	{
		if (root == nullptr)
			out << "Tree is empty" << std::endl;
		else
			print(root, out, 0);
	}

}
