#pragma once
#include "pch.h"
#include "QuadNode.h"


template<class ItemType>
class TwoThreeFourTree
{
private:
	QuadNode<ItemType>* rootPtr;

	QuadNode<ItemType>* getRootNode();
	void PlaceItemInNotFullNode(QuadNode<ItemType>* nodeToPlaceItemInPtr, ItemType& newEntry);
	void isLeafOperations(QuadNode<ItemType>* tempNode,QuadNode<ItemType>* parentNode, ItemType& newEntry);
	void splitRightNode(QuadNode<ItemType>* tempNode);
	void leftSideOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry);
	void rightSideOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry);
	void leftMidOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry);
	void rightMidOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry);
	void isNotLeafOperations(QuadNode<ItemType>* tempNode, QuadNode<ItemType>* parentNode,ItemType& newEntry);
	void splitLeftMid(QuadNode<ItemType>* tempNode);
	void splitRightMid(QuadNode<ItemType>* tempNode);
	void splitLeftNode(QuadNode<ItemType>* tempNode);
	void inOrderTraversalHelper(void visit(ItemType&), QuadNode<ItemType>* tempNode);
public:
	TwoThreeFourTree();
	bool add( ItemType& newEntry);
	void inOrderTraversal(void visit(ItemType&), TwoThreeFourTree<ItemType>* tempNode);
	bool removeItem(QuadNode<ItemType>* Ptr, const ItemType& entry);	//Henry S
	QuadNode<ItemType>* findNode(QuadNode<ItemType>* treePtr, ItemType& entry); //Henry S
	void remove(const ItemType& entry);

};
#include "TwoThreeFourTree.cpp"