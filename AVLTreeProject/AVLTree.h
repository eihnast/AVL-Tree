#pragma once

#include "AVLNode.h"
#include <ostream>
#include <iomanip>

namespace AVLTreeProject
{
	// AVL-tree class
	template<typename T>
	class AVLTree
	{
	private:
		AVLNode<T>* root;		// Root-node of tree
		size_t size;			// Size of tree

		void deleteSubTree(AVLNode<T>* node);		// Delete all sub-tree from argument node (recursive)

		AVLNode<T>* recursiveInsert(AVLNode<T>* node, T& data);
		AVLNode<T>* recursiveRemove(AVLNode<T>* node, T& data);
		AVLNode<T>* recursiveFind(AVLNode<T>* node, T& data);

		AVLNode<T>* findMin(AVLNode<T>* node);
		AVLNode<T>* findMax(AVLNode<T>* node);
		AVLNode<T>* removeMin(AVLNode<T>* node);

		AVLNode<T>* reBalance(AVLNode<T>* node);

		AVLNode<T>* rotateRight(AVLNode<T>* node);
		AVLNode<T>* rotateLeft(AVLNode<T>* node);
		AVLNode<T>* rotateBigRight(AVLNode<T>* node);
		AVLNode<T>* rotateBigLeft(AVLNode<T>* node);

		void findByIndex(AVLNode<T>* node, size_t& i, size_t index, AVLNode<T>*& result);
		void findByData(AVLNode<T>* node, int& i, T& data, bool& isFound);

		void print(AVLNode<T>* n, std::ostream& out, size_t displacement);

	public:
		AVLTree();
		~AVLTree();

		void add(T data);							// Add to tree
		void addAll(T* dataArray, size_t length);	// Add array to tree
		void remove(T data);						// Remove from tree (will be remove Node with same value)
		bool contains(T data);						// Check: has tree Node with same value or not

		T getFirst();		// Get first (most min) value
		T getLast();		// Get las (most max) value

		T at(size_t index);			// Get by index (not optimized operation, that iterates through all values before same)
		int getIndex(T data);	// Get index of contained data (if not contained - return -1)

		size_t getSize();


		void printAll(std::ostream& out);
	};




	
	template<typename T>
	void AVLTree<T>::addAll(T* dataArray, size_t length)
	{
		for (size_t i = 0; i < length; i++)
			add(dataArray[i]);
	}
	
	template<typename T>
	void AVLTree<T>::findByData(AVLNode<T>* node, int& i, T& data, bool& isFound)
	{
		if (node->getLeft() == nullptr && node->getRight() == nullptr)
		{
			i++;
			if (node->getData() == data)
				isFound = true;
			return;
		}

		if (node->getLeft() != nullptr)
			findByData(node->getLeft(), i, data, isFound);

		if (isFound)
			return;

		i++;
		if (isFound)
			return;

		if (node->getRight() != nullptr)
			findByData(node->getRight(), i, data, isFound);
	}

	template<typename T>
	int AVLTree<T>::getIndex(T data)
	{
		int i = -1;
		bool isFound = false;

		findByData(root, i, data, isFound);
		if (!isFound)
			i = -1;

		return i;
	}

	template<typename T>
	void AVLTree<T>::findByIndex(AVLNode<T>* node, size_t& i, size_t index, AVLNode<T>*& result)
	{
		if (node->getLeft() == nullptr && node->getRight() == nullptr)
		{
			if (++i == index)
				result = node;
			return;
		}

		if (node->getLeft() != nullptr)
			findByIndex(node->getLeft(), i, index, result);

		if (i == index)
			return;

		if (++i == index)
		{
			result = node;
			return;
		}

		if (node->getRight() != nullptr)
			findByIndex(node->getRight(), i, index, result);
	}
	
	template<typename T>
	T AVLTree<T>::at(size_t index)
	{
		if (index >= size || index < 0 || size == 0)
			throw std::out_of_range{"AVLTree::at"};

		size_t i = -1;
		AVLNode<T>* result = nullptr;
		findByIndex(root, i, index, result);
		
		return result->getData();
	}

	template<typename T>
	T AVLTree<T>::getFirst()
	{
		return findMin(root)->getData();
	}

	template<typename T>
	T AVLTree<T>::getLast()
	{
		return findMax(root)->getData();
	}

	template<typename T>
	AVLTree<T>::AVLTree()
	{
		root = nullptr;
		size = 0;
	}

	template<typename T>
	AVLTree<T>::~AVLTree()
	{
		if (root != nullptr)
			deleteSubTree(root);
	}

	template<typename T>
	void AVLTree<T>::deleteSubTree(AVLNode<T>* n)
	{
		if (n == nullptr)
			return;

		deleteSubTree(n->getLeft());
		deleteSubTree(n->getRight());

		delete n;
	}

	template<typename T>
	size_t AVLTree<T>::getSize()
	{
		return size;
	}

	template<typename T>
	void AVLTree<T>::add(T data)
	{
		if (size == 0)
		{
			root = new AVLNode<T>(data);		// newNode;
			size++;
		}
		else
		{
			root = recursiveInsert(root, data);
		}
	}


	template<typename T>
	AVLNode<T>* AVLTree<T>::recursiveInsert(AVLNode<T>* node, T& data)
	{
		if (node == nullptr)
		{
			size++;
			return new AVLNode<T>(data);
		}

		if (data == node->getData())
			return node;
		else if (data < node->getData())
			node->setLeft(recursiveInsert(node->getLeft(), data));
		else
			node->setRight(recursiveInsert(node->getRight(), data));

		return reBalance(node);
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* node)		// Left Left
	{
		AVLNode<T>* temp = node->getLeft();
		node->setLeft(temp->getRight());
		temp->setRight(node);

		node->updateHeight();
		temp->updateHeight();

		return temp;
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* node)		// Right Right
	{
		AVLNode<T>* temp = node->getRight();
		node->setRight(temp->getLeft());
		temp->setLeft(node);

		node->updateHeight();
		temp->updateHeight();

		return temp;
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::rotateBigRight(AVLNode<T>* node)	// Left Right
	{
		node->setLeft(rotateLeft(node->getLeft()));
		return rotateRight(node);
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::rotateBigLeft(AVLNode<T>* node)		// Right Left
	{
		node->setRight(rotateRight(node->getRight()));
		return rotateLeft(node);
	}

	template<typename T>
	AVLNode<T>* AVLTree<T>::reBalance(AVLNode<T>* node)
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

	template<typename T>
	AVLNode<T>* AVLTree<T>::recursiveFind(AVLNode<T>* node, T& data)
	{
		if (node == nullptr)
			return nullptr;

		if (node->getData() == data)
			return node;

		if (node->getData() < data)
			return recursiveFind(node->getRight(), data);
		else
			return recursiveFind(node->getLeft(), data);
	}

	template<typename T>
	bool AVLTree<T>::contains(T data)
	{
		if (recursiveFind(root, data) == nullptr)
			return false;
		else
			return true;
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* node)
	{
		if (node->getLeft() == nullptr)
			return node;
		else
			return findMin(node->getLeft());
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* node)
	{
		if (node->getRight() == nullptr)
			return node;
		else
			return findMin(node->getRight());
	}

	template <typename T>
	AVLNode<T>* AVLTree<T>::removeMin(AVLNode<T>* node)
	{
		if (node->getLeft() == nullptr)
			return node->getRight();

		node->setLeft(removeMin(node->getLeft()));
		return reBalance(node);
	}

	template<typename T>
	AVLNode<T>* AVLTree<T>::recursiveRemove(AVLNode<T>* node, T& data)
	{
		if (node == nullptr)
			return nullptr;

		if (node->getData() == data)
		{
			AVLNode<T>* nodeLeft = node->getLeft();
			AVLNode<T>* nodeRight = node->getRight();
			delete node;

			size--;

			if (nodeRight == nullptr)
				return nodeLeft;

			AVLNode<T>* minNode = findMin(nodeRight);
			minNode->setRight(removeMin(nodeRight));
			minNode->setLeft(nodeLeft);

			return reBalance(minNode);
		}

		if (node->getData() < data)
			node->setRight(recursiveRemove(node->getRight(), data));
		else
			node->setLeft(recursiveRemove(node->getLeft(), data));

		return reBalance(node);
	}

	template<typename T>
	void AVLTree<T>::remove(T data)
	{
		root = recursiveRemove(root, data);
	}



	template<typename T>
	void AVLTree<T>::print(AVLNode<T>* n, std::ostream& out, size_t displacement)
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

	template<typename T>
	void AVLTree<T>::printAll(std::ostream& out)
	{
		if (root == nullptr)
			out << "Tree is empty" << std::endl;
		else
			print(root, out, 0);
	}

}

