#pragma once

namespace AVLTreeProject
{

	// Node of AVL-tree
	template<typename T>
	class AVLNode
	{
	private:
		size_t height;			// Height of sub-tree from this node

		AVLNode<T>* left;		// Left branch
		AVLNode<T>* right;		// Right branch

		T data;		// Stored data in node

	public:
		AVLNode(T& data);
		~AVLNode();

		AVLNode<T>* getLeft();
		AVLNode<T>* getRight();
		void setLeft(AVLNode<T>* node);
		void setRight(AVLNode<T>* node);

		T& getData();

		size_t getHeight();
		
		void updateHeight();		// Update current height of sub-tree from this node
		short getHeightDifference();
	};




	template<typename T>
	AVLNode<T>::AVLNode(T& data)
	{
		this->data = data;
		this->left = nullptr;
		this->right = nullptr;
		this->height = 1;
	}

	template<typename T>
	AVLNode<T>::~AVLNode()
	{
	}

	template<typename T>
	AVLNode<T>* AVLNode<T>::getLeft()
	{
		return left;
	}

	template<typename T>
	AVLNode<T>* AVLNode<T>::getRight()
	{
		return right;
	}

	template<typename T>
	void AVLNode<T>::setLeft(AVLNode<T>* node)
	{
		left = node;
	}

	template<typename T>
	void AVLNode<T>::setRight(AVLNode<T>* node)
	{
		right = node;
	}

	template<typename T>
	T& AVLNode<T>::getData()
	{
		return data;
	}

	template <typename T>
	void AVLNode<T>::updateHeight()
	{
		size_t heightRight = (right == nullptr) ? 0 : right->getHeight();
		size_t heightLeft = (left == nullptr) ? 0 : left->getHeight();

		if (heightRight >= heightLeft)
			height = heightRight + 1;
		else
			height = heightLeft + 1;
	}

	template <typename T>
	size_t AVLNode<T>::getHeight()
	{
		return height;
	}

	template <typename T>
	short AVLNode<T>::getHeightDifference()
	{
		size_t heightRight = (right == nullptr) ? 0 : right->getHeight();
		size_t heightLeft = (left == nullptr) ? 0 : left->getHeight();

		return (heightLeft - heightRight);
	}

}
