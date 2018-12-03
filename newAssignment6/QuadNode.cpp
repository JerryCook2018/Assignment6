
/**Assingment 6.    Jerry Cook and Henry Sagehorn
 remove and removeItem developed and coded by Heny Sagehorn*/


#include "pch.h"
#include"QuadNode.h"


template<class ItemType>
QuadNode<ItemType>::QuadNode()
{
	leftChildPtr = leftMidChildPtr = rightMidChildPtr = rightChildPtr = nullptr;
}
template<class ItemType>
QuadNode<ItemType>::QuadNode(ItemType& newItem)
{
	smallItem = newItem;
	middleItem = largeItem = -1;
	leftChildPtr = leftMidChildPtr = rightMidChildPtr = rightChildPtr = nullptr;
	
}

template<class ItemType>
QuadNode<ItemType>::QuadNode( ItemType & newSmallItem, ItemType& newMiddleItem,
	 ItemType& newLargeItem,QuadNode<ItemType>* newLeftChildPtr, QuadNode<ItemType>* newLeftMidChildPtr, QuadNode<ItemType>* newRightMidChildPtr, QuadNode<ItemType>* newRightChildPtr)
{
	smallItem = newSmallItem;
	middleItem = newMiddleItem;
	largeItem = newLargeItem;

	leftChildPtr = newLeftChildPtr;
	leftMidChildPtr = newLeftMidChildPtr;
	rightMidChildPtr = newRightMidChildPtr;
	rightChildPtr = newRightChildPtr;
}

template<class ItemType>
 void QuadNode<ItemType>::setSmallItem( ItemType & newSmallItem)
{
	 smallItem = newSmallItem;
}

 template<class ItemType>
 void QuadNode<ItemType>::setMiddleItem( ItemType & newMiddleItem)
 {
	 middleItem = newMiddleItem;
 }

 template<class ItemType>
 void QuadNode<ItemType>::setLargeItem( ItemType & newLargeItem)
 {
	 largeItem = newLargeItem;
 }

 template<class ItemType>
 ItemType QuadNode<ItemType>::getSmallItem()
 {
	 return smallItem;
 }

 template<class ItemType>
 ItemType QuadNode<ItemType>::getMiddleItem()
 {
	 return middleItem;
 }

 template<class ItemType>
 ItemType QuadNode<ItemType>::getLargeItem()
 {
	 return largeItem;
 }

 template<class ItemType>
 void QuadNode<ItemType>::setLeftChildPtr( QuadNode<ItemType>* newLeftChildPtr)
 {
	 leftChildPtr = newLeftChildPtr;
 }

 template<class ItemType>
 void QuadNode<ItemType>::setLeftMidChildPtr(QuadNode<ItemType>* newLeftMidChildPtr)
 {
	 leftMidChildPtr = newLeftMidChildPtr;
 }

 template<class ItemType>
 void QuadNode<ItemType>::setRightMidChildPtr(QuadNode<ItemType>* newRightMidChildPtr)
 {
	 rightMidChildPtr = newRightMidChildPtr;
 }

 template<class ItemType>
 void QuadNode<ItemType>::setRightChildPtr(QuadNode<ItemType>* newRightChildPtr)
 {
	 rightChildPtr = newRightChildPtr;
 }

 template<class ItemType>
 QuadNode<ItemType>* QuadNode<ItemType>::getLeftChildPtr()
 {
	 return leftChildPtr;
 }

 template<class ItemType>
 QuadNode<ItemType>* QuadNode<ItemType>::getLeftMidChildPtr()
 {
	 return leftMidChildPtr;
 }

 template<class ItemType>
 QuadNode<ItemType>* QuadNode<ItemType>::getRightMidChildPtr()
 {
	 return rightMidChildPtr;
 }

 template<class ItemType>
 QuadNode<ItemType>* QuadNode<ItemType>::getRightChildPtr()
 {
	 return rightChildPtr;
 }

 template<class ItemType>
 bool QuadNode<ItemType>::isLeaf()
 {
	 if ((leftChildPtr == nullptr) && (leftMidChildPtr == nullptr) && (rightMidChildPtr == nullptr) &&
		 (rightChildPtr == nullptr))
	 {
		 return true;
	 }
	 return false;
 }

 template<class ItemType>
 bool QuadNode<ItemType>::isTwoNode()
 {
	 if ((smallItem != -1), (middleItem == -1) && (largeItem == -1) &&
		 (leftChildPtr != nullptr) || (rightChildPtr != nullptr) && (leftMidChildPtr == nullptr) &&
		 (rightMidChildPtr == nullptr))
	 {
		 return true;
	 }
	 return false;
 }

 template<class ItemType>
 bool QuadNode<ItemType>::isThreeNode()
 {
	 if((smallItem != -1)&&(middleItem == -1)&&(largeItem != -1)&&(leftChildPtr == nullptr)&&
		 (leftMidChildPtr != nullptr) && (rightMidChildPtr == nullptr) && (rightChildPtr != nullptr))
	 {
		 return true;
	 }
	 return false;

 }

 template<class ItemType>
 bool QuadNode<ItemType>::isFourNode()
 {
	 if ((smallItem != -1) && (middleItem != -1) && (largeItem != -1) &&
		 (leftChildPtr != nullptr) && (leftMidChildPtr != nullptr) && (rightMidChildPtr != nullptr) &&
		 (rightChildPtr != nullptr))
	 {
		 return true;
	 }
	 return false;
 }


