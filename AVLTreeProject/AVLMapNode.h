#pragma once

namespace AVLTreeProject
{

	// Node of AVL-tree
	template<typename K, typename T>
	class AVLMapNode
	{
	private:
		size_t height;			// Height of sub-tree from this node

		AVLMapNode<K, T>* left;		// Left branch
		AVLMapNode<K, T>* right;		// Right branch

		T data;		// Stored data in node

		K key;				// Key of node

	public:
		AVLMapNode(K& key, T& data);
		~AVLMapNode();

		AVLMapNode<K, T>* getLeft();
		AVLMapNode<K, T>* getRight();
		void setLeft(AVLMapNode<K, T>* node);
		void setRight(AVLMapNode<K, T>* node);

		T& getData();

		size_t getHeight();

		void updateHeight();		// Update current height of sub-tree from this node
		short getHeightDifference();

		K& getKey();
		void setData(T& data);
	};




	template<typename K, typename T>
	AVLMapNode<K, T>::AVLMapNode(K& key, T& data)
	{
		this->key = key;
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
		this->height = 1;
	}

	template<typename K, typename T>
	K& AVLMapNode<K, T>::getKey()
	{
		return key;
	}

	template<typename K, typename T>
	void AVLMapNode<K, T>::setData(T& data)
	{
		this->data = data;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>::~AVLMapNode()
	{
	}


	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMapNode<K, T>::getLeft()
	{
		return left;
	}

	template<typename K, typename T>
	AVLMapNode<K, T>* AVLMapNode<K, T>::getRight()
	{
		return right;
	}

	template<typename K, typename T>
	void AVLMapNode<K, T>::setLeft(AVLMapNode<K, T>* node)
	{
		left = node;
	}

	template<typename K, typename T>
	void AVLMapNode<K, T>::setRight(AVLMapNode<K, T>* node)
	{
		right = node;
	}

	template<typename K, typename T>
	T& AVLMapNode<K, T>::getData()
	{
		return data;
	}

	template<typename K, typename T>
	void AVLMapNode<K, T>::updateHeight()
	{
		size_t heightRight = (right == nullptr) ? 0 : right->getHeight();
		size_t heightLeft = (left == nullptr) ? 0 : left->getHeight();

		if (heightRight >= heightLeft)
			height = heightRight + 1;
		else
			height = heightLeft + 1;
	}

	template<typename K, typename T>
	size_t AVLMapNode<K, T>::getHeight()
	{
		return height;
	}

	template<typename K, typename T>
	short AVLMapNode<K, T>::getHeightDifference()
	{
		size_t heightRight = (right == nullptr) ? 0 : right->getHeight();
		size_t heightLeft = (left == nullptr) ? 0 : left->getHeight();

		return (heightLeft - heightRight);
	}

}
