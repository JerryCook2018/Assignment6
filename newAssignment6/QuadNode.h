/**@file QuadNode.h*/

#pragma once
#include"pch.h"

template<class ItemType>
class QuadNode
{
private:
	ItemType smallItem;
	ItemType middleItem;
	ItemType largeItem;
	QuadNode<ItemType>* leftChildPtr;
	QuadNode<ItemType>* leftMidChildPtr;
	QuadNode<ItemType>* rightMidChildPtr;
	QuadNode<ItemType>* rightChildPtr;


public:

	//constructors
	QuadNode<ItemType>();
	QuadNode<ItemType>(ItemType& newItem);
	QuadNode<ItemType>(ItemType& newSmallItem, ItemType& newMiddleItem,
		 ItemType& largeItemType,QuadNode<ItemType>* leftChildPtr, QuadNode<ItemType>* leftMidChildPtr,
		QuadNode<ItemType>* rightMidChildPtr, QuadNode<ItemType>* rightChildPtr);
	

	//set Items methods
	void setSmallItem( ItemType& newSmallItem);
	void setMiddleItem( ItemType& newMiddleItem);
	void setLargeItem( ItemType& newLargeItem);

	//return Item methods
	ItemType getSmallItem();
	ItemType getMiddleItem();
	ItemType getLargeItem();

	//set Child pointer methods
	void setLeftChildPtr( QuadNode<ItemType>* newLeftChildPtr);
	void setLeftMidChildPtr( QuadNode<ItemType>* newLeftMidChildPtr);
	void setRightMidChildPtr( QuadNode<ItemType>* newRightMidChildPtr);
	void setRightChildPtr( QuadNode<ItemType>* newRightChildPtr);
	

	//return child pointer methods
	QuadNode<ItemType>* getLeftChildPtr();
	QuadNode<ItemType>* getLeftMidChildPtr();
	QuadNode<ItemType>* getRightMidChildPtr();
	QuadNode<ItemType>* getRightChildPtr();

	//check methods
	bool isLeaf(); //no children, can have one,two or three data items.
	bool isTwoNode(); //two node has two children and one data item
	bool isThreeNode(); //three node has three children and two data items
	bool isFourNode(); //four node has four children and three data item.
	



};
#include "QuadNode.cpp"