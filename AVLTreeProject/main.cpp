#include <iostream>
#include <string>

#include "AVLTree.h"
#include "AVLMap.h"

using namespace std;
using namespace AVLTreeProject;

void demoAVLTree();
void demoAVLMap();

int main()
{
	// Demonstration methods of AVLTree
	demoAVLTree();

	system("cls");

	// Demonstration methods of AVLMap
	demoAVLMap();
}

template<typename T>
void printAVLTree(AVLTree<T>* tree)
{
	tree->printAll(cout);
	cout << endl;
	system("pause");
	system("cls");
}

void demoAVLTree()
{
	AVLTree<int>* tree = new AVLTree<int>();

	cout << "Adding 1 and 3 to empty AVLTree" << endl;
	tree->add(1);
	tree->add(3);
	printAVLTree(tree);

	cout << "Adding array of five numbers (6, 9, 0, -10, 3) to AVLTree" << endl;
	tree->addAll(new int[5]{ 6, 9, 0, -10, 3 }, 5);
	printAVLTree(tree);

	tree->printAll(cout);
	cout << "\nCheck if nums are in tree:" << endl;
	cout << "3 is contained? " << tree->contains(3) << endl;
	cout << "7 is contained? " << tree->contains(7) << endl;
	cout << "9 is contained? " << tree->contains(9) << endl;

	cout << endl;

	cout << "Remove two nums: one exist in tree (9) and another is not (7)" << endl;
	tree->remove(9);
	tree->remove(7);
	printAVLTree(tree);

	tree->printAll(cout);
	cout << "Size of tree = " << tree->getSize() << endl;
	cout << "Getted first num (min) = " << tree->getFirst() << endl;
	cout << "Getted last num (max) = " << tree->getLast() << endl;
	cout << "Getted num by index 3 = " << tree->at(3) << endl;
	cout << "Getted index of num 6 = " << tree->getIndex(6) << endl;
	cout << "Getted index of num 9 = " << tree->getIndex(9) << endl;
	cout << endl;

	system("pause");
}

template<typename K, typename T>
void printAVLMap(AVLMap<K, T>* map)
{
	map->printAll(cout);
	cout << endl;
	system("pause");
	system("cls");
}

void demoAVLMap()
{
	AVLMap<string, string>* map = new AVLMap<string, string>();

	cout << "Adding four new elements to empty AVLMap" << endl;
	map->put("keyFirst", "dataFirst");
	string keyStr = "keySecond", dataStr = "dataSecond";
	map->put(keyStr, dataStr);
	map->put("keyFourth", "dataFourth");
	map->put("keyFifth", "dataFifth");
	printAVLMap(map);

	map->printAll(cout);
	cout << endl;
	cout << "Check if map contains 'keyFirst' key: " << map->containsKey("keyFirst") << endl;
	string str = "keyThird";
	cout << "Check if map contains '" + str + "' key: " << map->containsKey(str) << endl;

	cout << endl;

	cout << "Removing by key '" + keyStr + "':" << endl;
	map->remove(keyStr);
	printAVLMap(map);

	map->printAll(cout);
	cout << "Size of tree = " << map->getSize() << endl;
	cout << "Getted data from key 'keyFourth' = " << map->get("keyFourth") << endl;
	cout << "Getted data from key 'keyFirst' = " << map->get("keyFirst") << endl;
	cout << endl;

	system("pause");
}
