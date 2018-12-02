// 234TreeAssingment6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <time.h>
#include "TwoThreeFourTree.h"

using namespace std;

void visit(int& item)
{
	cout << item<<" ";
}

void fillDriver(TwoThreeFourTree<int>* tree)
{
	vector<int> uniqueRandom;


	int itemCount = 0;
	srand(time(NULL));
	while (itemCount < 100)
	{
		int number = rand() % (501 - 200) + 200;
		int count = std::count(uniqueRandom.begin(), uniqueRandom.end(), number);

		if ((count == 0) || (uniqueRandom.size() == 0))
		{
			uniqueRandom.push_back(number);
			itemCount++;
		}
	}

	for (int i = 0; i < itemCount;i++)
	{
		tree->add(uniqueRandom.at(i));
	}
	cout << endl;

	for (int i = 0;i < itemCount;i++)
	{
		cout << uniqueRandom.at(i) << " ";
	}
	cout << endl << endl;
}

int main()
{
	TwoThreeFourTree<int>* twoThreeFourTree = new TwoThreeFourTree<int>();
	//insert 100 random between 200 and 500
	fillDriver(twoThreeFourTree);
	// changes to update repository
	twoThreeFourTree->inOrderTraversal(visit, twoThreeFourTree);
	//twoThreeFourTree->remove(item);
	
	
}

