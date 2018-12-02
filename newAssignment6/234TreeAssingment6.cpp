// 234TreeAssingment6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "TwoThreeFourTree.h"
#include "234TreeAssingment6.h"

using namespace std;

void visit(int& item)
{
	cout << item<<" ";
}

int main()
{
	TwoThreeFourTree<int>* twoThreeFourTree = new TwoThreeFourTree<int>();
	int item = 10;
	twoThreeFourTree->add(item);
	twoThreeFourTree->inOrderTraversal(visit, twoThreeFourTree);
	int item2 = 20;
	int item3 = 30;
	int item4 = 40;
	twoThreeFourTree->add(item2);
	twoThreeFourTree->inOrderTraversal(visit, twoThreeFourTree);
	
}

