#include "pch.h"
#include "TwoThreeFourTree.h"
#include <iostream>

using namespace std;

template<class ItemType>
QuadNode<ItemType>* TwoThreeFourTree<ItemType>::getRootNode()
{
	return rootPtr;
}

template<class ItemType>
TwoThreeFourTree<ItemType>::TwoThreeFourTree()
{
	rootPtr = nullptr;
}

template<class ItemType>
bool TwoThreeFourTree<ItemType>::add( ItemType& newEntry)
{
	QuadNode<ItemType>* tempNode = rootPtr;
	QuadNode<ItemType>* newNodePtr = new QuadNode<ItemType>(newEntry);

	//locate the leaf node the newEntry belongs in
	if (tempNode == nullptr)  //tree is empty
	{

		rootPtr = newNodePtr;
	}
	else if (rootPtr->isLeaf()) //tree not empty only rootPtr
	{

		if ((rootPtr->getSmallItem() != -1) && (rootPtr->getMiddleItem() != -1) &&
			(rootPtr->getLargeItem() != -1))//root already contains three item, split root then place entry 
		{
			ItemType middleItem = rootPtr->getMiddleItem();
			ItemType smallItem = rootPtr->getSmallItem();
			ItemType largeItem = rootPtr->getLargeItem();

			QuadNode<ItemType>* newRootPtr = new QuadNode<ItemType>(middleItem);
			QuadNode<ItemType>* newLeftChildPtr = new QuadNode<ItemType>(smallItem);
			QuadNode<ItemType>* newRightChildPtr = new QuadNode<ItemType>(largeItem);

			newRootPtr->setLeftChildPtr(newLeftChildPtr);
			newRootPtr->setRightChildPtr(newRightChildPtr);
			
			rootPtr = newRootPtr;
			tempNode = rootPtr;

			//find place to put newEntry after root has split
			//place entry where need to go
			if (newEntry > rootPtr->getSmallItem())  //move to right child, right is leaf, with small item filled.
			{
				tempNode = rootPtr->getRightChildPtr();
				{
					if (newEntry > tempNode->getSmallItem())
					{
						tempNode->setLargeItem(newEntry);
					}

					else
						tempNode->setSmallItem(newEntry);
				}
			}

			else // go to left node, left node is a leaf with only small item 
			{
				tempNode = rootPtr->getLeftChildPtr();
				if (newEntry < tempNode->getSmallItem())
				{
					ItemType smallItem = tempNode->getSmallItem();
					tempNode->setLargeItem(smallItem);
					tempNode->setSmallItem(newEntry);
				}

				else
				{
					tempNode->setLargeItem(newEntry);
				}

			}

		}
		else
			PlaceItemInNotFullNode(rootPtr, newEntry);

	}



	//if root node is a two node, has one data item in small, and two children
	else if (rootPtr->isTwoNode())
	{
		QuadNode<ItemType>* parentNode = nullptr;
		tempNode = rootPtr;

		//root is two node move down right side.
		if (newEntry > tempNode->getSmallItem())
		{
			//check if next node needs to be split before moving into it.
			if (tempNode->getRightChildPtr()->isFourNode())
			{

				splitRightNode(tempNode->getRightChildPtr());

				//tempNode right child is now split to two nodes, right child middle item comes up to tempNode
				if (newEntry < tempNode->getLargeItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getRightMidChildPtr();
				}
				else if (newEntry > tempNode->getLargeItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getRightChildPtr();
				}
			}
			else
				tempNode = tempNode->getRightChildPtr();
		}
		else if (newEntry < tempNode->getSmallItem())
		{
			//check if next node needs to be split before moving into it.
			if (tempNode->getLeftChildPtr()->isFourNode())
			{

				splitLeftNode(tempNode->getLeftChildPtr());

				//tempNode left child is now split to two nodes, left child middle item comes up to tempNode
				if (newEntry < tempNode->getSmallItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getLeftChildPtr();
				}
				else if (newEntry > tempNode->getSmallItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getLeftMidChildPtr();
				}
			}
			tempNode = tempNode->getRightChildPtr();
		}

		//if tempNode is not a leaf//

		if (!tempNode->isLeaf())
		{
			isNotLeafOperations(tempNode, parentNode, newEntry);
		}

		else if (tempNode->isLeaf())
		{
			isLeafOperations(tempNode, parentNode, newEntry);
		}
	}

	//root  is three node
	else if (rootPtr->isThreeNode())
	{    

	    QuadNode<ItemType>* parentNode = nullptr;

	    //if new entry is greater than small item move down right side
		if (newEntry > tempNode->getSmallItem())
		{
			//check if next node needs to be split before moving into it.
			if (tempNode->getRightChildPtr()->isFourNode())
			{

				splitRightNode(tempNode->getRightChildPtr());

				//tempNode right child is now split to two nodes, right child middle item comes up to tempNode
				if (newEntry < tempNode->getLargeItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getRightMidChildPtr();
				}
				else if (newEntry > tempNode->getLargeItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getRightChildPtr();
				}
			}
			else
				tempNode = tempNode->getRightChildPtr();
		}

		//move down left side
		else if (newEntry < tempNode->getSmallItem())
		{
			//check if next node needs to be split before moving into it.
			if (tempNode->getLeftChildPtr()->isFourNode())
			{

				splitLeftNode(tempNode->getLeftChildPtr());

				//tempNode left child is now split to two nodes, left child middle item comes up to tempNode
				if (newEntry < tempNode->getSmallItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getLeftChildPtr();
				}
				else if (newEntry > tempNode->getSmallItem())
				{
					parentNode = tempNode;
					tempNode = tempNode->getLeftMidChildPtr();
				}
			}
			tempNode = tempNode->getRightChildPtr();
		}
		//move down center node
		{
			if (tempNode ->getLeftMidChildPtr() != nullptr)
			{
				if (tempNode->getLeftMidChildPtr()->isFourNode())
				{
					splitLeftMid(tempNode->getLeftMidChildPtr());
					if (newEntry < tempNode->getMiddleItem())
					{
						parentNode = tempNode;
						tempNode = tempNode->getLeftMidChildPtr();
					}
					else if (newEntry > tempNode->getMiddleItem())
					{
						parentNode = tempNode;
						tempNode = tempNode->getRightMidChildPtr();
					}
				}
			}
			else if (tempNode->getRightMidChildPtr() != nullptr)
			{
				if (tempNode->getRightMidChildPtr()->isFourNode())
				{
					splitRightMid(tempNode->getRightMidChildPtr());
					if (newEntry < tempNode->getMiddleItem())
					{
						parentNode = tempNode;
						tempNode = tempNode->getLeftMidChildPtr();
					}
					else if(newEntry > tempNode->getMiddleItem())
					{
						parentNode = tempNode;
						tempNode = tempNode->getRightMidChildPtr();
					}
				}
			}
		}
		if (!tempNode->isLeaf())
		{
			isNotLeafOperations(tempNode,parentNode, newEntry);
		}
		else
		{
			isLeafOperations(tempNode, parentNode, newEntry);
		}
	}

	else if (rootPtr->isFourNode())
	{
		QuadNode<ItemType>* oldLeftChild = rootPtr->getLeftChildPtr();
		QuadNode<ItemType>* oldLeftMidChild = rootPtr->getLeftMidChildPtr();
		QuadNode<ItemType>* oldRightMidChild = rootPtr->getRightMidChildPtr();
		QuadNode<ItemType>* oldRightChild = rootPtr->getRightChildPtr();

		ItemType middleItem = rootPtr->getMiddleItem();
		ItemType smallItem = rootPtr->getSmallItem();
		ItemType largeItem = rootPtr->getLargeItem();

		QuadNode<ItemType>* newRootPtr= new QuadNode<ItemType>(middleItem);
		QuadNode<ItemType>* newLeftChild= new QuadNode<ItemType>(smallItem);
		QuadNode<ItemType>* newRightChild= new QuadNode<ItemType>(largeItem);


		rootPtr = newRootPtr;
		rootPtr->setLeftChildPtr(newLeftChild);
		rootPtr->setRightChildPtr(newRightChild);

		rootPtr->getLeftChildPtr()->setLeftChildPtr(oldLeftChild);
		rootPtr->getLeftChildPtr()->setRightChildPtr(oldLeftChild);
		rootPtr->getRightChildPtr()->setRightChildPtr(oldRightChild);
		rootPtr->getRightChildPtr()->setLeftChildPtr(oldRightMidChild);

		add(newEntry);
	}
	
	return true;
}

template<class ItemType>
void TwoThreeFourTree<ItemType>::inOrderTraversal(void visit(ItemType&), TwoThreeFourTree<ItemType>* treePtr)
{
	QuadNode<ItemType>* tempNode = treePtr->getRootNode();
	inOrderTraversalHelper(visit, tempNode);
}

	

	//operations to find leafNode
template<class ItemType>
void TwoThreeFourTree<ItemType>::isNotLeafOperations(QuadNode<ItemType>* tempNode, QuadNode<ItemType>* parentNode,
	ItemType& newEntry)
{
	while (!tempNode->isLeaf())
	{
		if (tempNode->isTwoNode())
		{
			if (newEntry < tempNode->getSmallItem())
			{
				parentNode = tempNode;
				leftSideOperations(tempNode, newEntry);

			}
			if (newEntry > tempNode->getSmallItem())
			{
				parentNode = tempNode;
				rightSideOperations(tempNode, newEntry);
			}
		}
		else if (tempNode->isThreeNode())
		{
			if (newEntry < tempNode->getSmallItem())
			{
				parentNode = tempNode;
				leftSideOperations(tempNode, newEntry);

			}
			else if (newEntry > tempNode->getLargeItem())
			{
				parentNode = tempNode;
				rightSideOperations(tempNode, newEntry);
			}
			else
			{
				if (tempNode->getLeftMidChildPtr() != nullptr)
				{
					parentNode = tempNode;
					leftMidOperations(tempNode, newEntry);
				}
				if (tempNode->getRightMidChildPtr() != nullptr)
				{
					parentNode = tempNode;
					rightMidOperations(tempNode, newEntry);
				}

			}
		}

	}
}

template<class ItemType>
void TwoThreeFourTree<ItemType>::splitLeftMid(QuadNode<ItemType>* tempNode)
{
	QuadNode<ItemType>* nodeBeforeSplit = tempNode->getLeftMidChildPtr();
	QuadNode<ItemType>* oldLeftChild =nullptr;
	QuadNode<ItemType>* oldLeftMidChild =nullptr;
	QuadNode<ItemType>* oldRightMidChild =nullptr;
	QuadNode<ItemType>* oldRightChild =nullptr;
	if (!nodeBeforeSplit->isLeaf())
	{
		 oldLeftChild = nodeBeforeSplit->getLeftChildPtr();
		 oldLeftMidChild = nodeBeforeSplit->getLeftMidChildPtr();
		 oldRightMidChild = nodeBeforeSplit->getRightMidChildPtr();
		 oldRightChild = nodeBeforeSplit->getRightChildPtr();
	}

	ItemType middleItem = nodeBeforeSplit->getMiddleItem();
	tempNode->setMiddleItem(middleItem);

	ItemType smallItem = nodeBeforeSplit->getSmallItem();

	QuadNode<ItemType>* newLeftMid = new QuadNode<ItemType>(smallItem);
	tempNode->setLeftMidChildPtr(newLeftMid);
	tempNode->getLeftMidChildPtr()->setLeftChildPtr(oldLeftChild);
	tempNode->getLeftMidChildPtr()->setRightChildPtr(oldLeftMidChild);

	if (tempNode->getRightMidChildPtr() == nullptr)
	{
		ItemType largeItem = nodeBeforeSplit->getLargeItem();
		QuadNode<ItemType>* newRightMidPtr = new QuadNode<ItemType>(largeItem);
		tempNode->setRightMidChildPtr(newRightMidPtr);
		tempNode->getRightMidChildPtr()->setLeftChildPtr(oldRightMidChild);
		tempNode->getRightMidChildPtr()->setRightChildPtr(oldRightChild);
	}


}

template<class ItemType>
void TwoThreeFourTree<ItemType>::splitRightMid(QuadNode<ItemType>* tempNode)
{
	QuadNode<ItemType>* nodeBeforeSplit = tempNode->getLeftMidChildPtr();
	QuadNode<ItemType>* oldLeftChild =nullptr;
	QuadNode<ItemType>* oldLeftMidChild =nullptr;
	QuadNode<ItemType>* oldRightMidChild =nullptr;
	QuadNode<ItemType>* oldRightChild = nullptr;

	if (!nodeBeforeSplit->isLeaf())
	{
		oldLeftChild = nodeBeforeSplit->getLeftChildPtr();
		oldLeftMidChild = nodeBeforeSplit->getLeftMidChildPtr();
		oldRightMidChild = nodeBeforeSplit->getRightMidChildPtr();
		oldRightChild = nodeBeforeSplit->getRightChildPtr();
	}
	ItemType middleItem = nodeBeforeSplit->getMiddleItem();
	tempNode->setMiddleItem(middleItem);

	ItemType largeItem = nodeBeforeSplit->getLargeItem();
	QuadNode<ItemType>* newRightMid = new QuadNode<ItemType>(largeItem);
	tempNode->setRightMidChildPtr(newRightMid);
	tempNode->getRightMidChildPtr()->setLeftChildPtr(oldRightMidChild);
	tempNode->getRightMidChildPtr()->setRightChildPtr(oldRightChild);

	if (tempNode->getRightMidChildPtr() == nullptr)
	{
		ItemType smallItem = nodeBeforeSplit->getSmallItem();
		QuadNode<ItemType>* leftMidPtr = new QuadNode<ItemType>(smallItem);
		tempNode->setLeftMidChildPtr(leftMidPtr);
		tempNode->getLeftMidChildPtr()->setLeftChildPtr(oldLeftChild);
		tempNode->getLeftMidChildPtr()->setRightChildPtr(oldLeftMidChild);
	}

	


}
template<class ItemType>
void TwoThreeFourTree<ItemType>::rightMidOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry)
{
	if (tempNode->getRightMidChildPtr()->isFourNode())
	{
		splitRightMid(tempNode);
		if (tempNode->isFourNode())
		{
			ItemType smallItem = tempNode->getSmallItem();
			ItemType middleItem = tempNode->getMiddleItem();
			ItemType largeItem = tempNode->getLargeItem();
			if (newEntry < middleItem)
			{
				tempNode = tempNode->getLeftMidChildPtr();
			}
			if (newEntry > middleItem)
			{
				tempNode = tempNode->getRightMidChildPtr();
			}
		}
	}
	else
	{
		tempNode = tempNode->getRightMidChildPtr();
	}
}
template<class ItemType>
void TwoThreeFourTree<ItemType>::leftMidOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry)
{
	if (tempNode->getLeftMidChildPtr()->isFourNode())
	{
		
		splitLeftMid(tempNode);
		if (tempNode->isFourNode())
		{
			ItemType smallItem = tempNode->getSmallItem();
			ItemType middleItem = tempNode->getMiddleItem();
			ItemType largeItem = tempNode->getLargeItem();
			if (newEntry < middleItem)
			{
				tempNode = tempNode->getLeftMidChildPtr();
			}
			if (newEntry > middleItem)
			{
				tempNode = tempNode->getRightMidChildPtr();
			}
		}
	}
	else
	{
		tempNode = tempNode->getLeftMidChildPtr();
	}
}
template<class ItemType>
void TwoThreeFourTree<ItemType>::rightSideOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry)
{
	if (tempNode->getRightChildPtr()->isFourNode())
	{
		splitRightNode(tempNode);
		if (newEntry < tempNode->getLargeItem())
		{
			tempNode = tempNode->getRightMidChildPtr();
		}
		else
		{
			tempNode = tempNode->getRightChildPtr();
		}
	}
	tempNode = tempNode->getRightChildPtr();
}
template<class ItemType>
void TwoThreeFourTree<ItemType>::leftSideOperations(QuadNode<ItemType>* tempNode, ItemType& newEntry)
{
	if (tempNode->getLeftChildPtr()->isFourNode())
	{
		
		splitLeftNode(tempNode->getLeftChildPtr());
		if (tempNode->isThreeNode())
		{
			if (newEntry < tempNode->getSmallItem())
			{
				tempNode = tempNode->getLeftChildPtr();
			}
			if (newEntry > tempNode->getLargeItem())
			{
				tempNode = tempNode->getLeftChildPtr();
			}
			else
			{
				tempNode = tempNode->getLeftMidChildPtr();
			}
		}

	}
	else if (tempNode->getLeftChildPtr()->isThreeNode())
	{
		if(newEntry < tempNode->getLeftChildPtr()->getSmallItem())
		{ 
			tempNode = tempNode->getLeftChildPtr();
		}
		else if (newEntry > tempNode->getLeftChildPtr()->getLargeItem())
		{
			tempNode = tempNode->getRightChildPtr();
		}
		else
		{
			tempNode = tempNode->getLeftMidChildPtr();
		}
	}
	else
	{
		if (newEntry < tempNode->getLeftChildPtr()->getSmallItem())
		{
			tempNode = tempNode->getLeftChildPtr();
		}
	}
	
}
template<class ItemType>
void TwoThreeFourTree<ItemType>::splitRightNode(QuadNode<ItemType>* tempNode)
{
	QuadNode<ItemType>* nodeBeforeSplit = tempNode->getRightChildPtr();

	QuadNode<ItemType>* oldLeftChild =nullptr;
	QuadNode<ItemType>* oldLeftMidChild =nullptr;
	QuadNode<ItemType>* oldRightMidChild =nullptr;
	QuadNode<ItemType>* oldRightchild =nullptr;


	if (!nodeBeforeSplit->isLeaf())
	{
		oldLeftChild = nodeBeforeSplit->getLeftChildPtr();
		oldLeftMidChild = nodeBeforeSplit->getLeftMidChildPtr();
		oldRightMidChild = nodeBeforeSplit->getRightMidChildPtr();
		oldRightchild = nodeBeforeSplit->getRightChildPtr();

	}

	ItemType middleItem = nodeBeforeSplit->getMiddleItem();
	tempNode->setLargeItem(middleItem);
	ItemType largeItem = nodeBeforeSplit->getLargeItem();
	QuadNode<ItemType>* newRightChild= new QuadNode<ItemType>(largeItem);
	tempNode->setRightChildPtr(newRightChild);
	tempNode->getRightChildPtr()->setRightChildPtr(oldRightchild);
	tempNode->getRightChildPtr()->setRightMidChildPtr(oldRightMidChild);

	if (tempNode->getRightMidChildPtr() != nullptr)
	{
		tempNode->setLeftMidChildPtr(tempNode->getRightMidChildPtr());
		ItemType smallItem = nodeBeforeSplit->getSmallItem();
		QuadNode<ItemType>* newRightMid= new QuadNode<ItemType>(smallItem);
		tempNode->setRightMidChildPtr(newRightMid);
		tempNode->getRightMidChildPtr()->setLeftChildPtr(oldLeftChild);
		tempNode->getRightMidChildPtr()->setRightChildPtr(oldLeftMidChild);
	}
	else if (tempNode->getRightChildPtr() == nullptr)
	{
		ItemType smallItem = nodeBeforeSplit->getSmallItem();
		QuadNode<ItemType>*newRightMid = new QuadNode<ItemType>(smallItem);
		tempNode->setRightMidChildPtr(newRightMid);
		tempNode->getRightMidChildPtr()->setLeftChildPtr(oldLeftChild);
		tempNode->getRightMidChildPtr()->setRightChildPtr(oldLeftMidChild);
	}
}

template<class ItemType>

void TwoThreeFourTree<ItemType>::splitLeftNode(QuadNode<ItemType>* tempNode)
{

	QuadNode<ItemType>* nodeBeforeSplit = tempNode->getLeftChildPtr();

	QuadNode<ItemType>* oldLeftChild = nullptr;
	QuadNode<ItemType>* oldLeftMidChild =nullptr;
	QuadNode<ItemType>* oldRightMidChild =nullptr;
	QuadNode<ItemType>* oldRightchild =nullptr;


	if (!nodeBeforeSplit->isLeaf())
	{
		oldLeftChild = nodeBeforeSplit->getLeftChildPtr();
		oldLeftMidChild = nodeBeforeSplit->getLeftMidChildPtr();
		oldRightMidChild = nodeBeforeSplit->getRightMidChildPtr();
		oldRightchild = nodeBeforeSplit->getRightChildPtr();

	}
	ItemType middleItem = nodeBeforeSplit->getMiddleItem();
	tempNode->setSmallItem(middleItem);

	ItemType smallItem = nodeBeforeSplit->getSmallItem();
	QuadNode<ItemType>* newLeftChild= new QuadNode<ItemType>(smallItem);

	tempNode->setLeftChildPtr(newLeftChild);
	tempNode->getLeftChildPtr()->setLeftChildPtr(oldLeftChild);
	tempNode->getLeftChildPtr()->setLeftMidChildPtr(oldLeftMidChild);

	if (tempNode->getLeftMidChildPtr() != nullptr)
	{
		tempNode->setRightMidChildPtr(tempNode->getLeftMidChildPtr());
		ItemType largeItem = nodeBeforeSplit->getLargeItem();
		QuadNode<ItemType>* newLeftMid= new QuadNode<ItemType> (largeItem);
		tempNode->setLeftMidChildPtr(newLeftMid);
		tempNode->getLeftMidChildPtr()->setLeftChildPtr(oldRightchild);
		tempNode->getLeftMidChildPtr()->setRightChildPtr(oldRightchild);
	}
	else if (tempNode->getRightChildPtr() == nullptr)
	{
		ItemType smallItem = nodeBeforeSplit->getSmallItem();
		QuadNode<ItemType>*newRightMid = new QuadNode<ItemType> (smallItem);
		tempNode->setRightMidChildPtr(newRightMid);
		tempNode->getRightMidChildPtr()->setLeftChildPtr(oldRightMidChild);
		tempNode->getRightMidChildPtr()->setRightChildPtr(oldRightchild);
	}
}
template <class ItemType>
void TwoThreeFourTree<ItemType>::isLeafOperations(QuadNode<ItemType>* tempNode, 
	QuadNode<ItemType>* parentNode,ItemType& newEntry)
{
	//if leaf node is full split it

	if ((tempNode->getMiddleItem() != -1) && (tempNode->getMiddleItem() != -1) &&
		(tempNode->getLargeItem() != -1))
	{
		if (parentNode->isTwoNode())
		{
			ItemType middleItem = tempNode->getMiddleItem();
			parentNode->setLargeItem(middleItem);
		}
		if (parentNode->isThreeNode())
		{
			if (tempNode->getMiddleItem() < parentNode->getSmallItem())
			{
				ItemType middleItem = parentNode->getMiddleItem();
				ItemType smallItem = parentNode->getSmallItem();

				parentNode->setMiddleItem(smallItem);
				parentNode->setSmallItem(middleItem);
			}
			else if (tempNode->getMiddleItem() > parentNode->getLargeItem())
			{
				ItemType middleItem = parentNode->getMiddleItem();
				ItemType largeItem = parentNode->getLargeItem();

				parentNode->setMiddleItem(largeItem);
				parentNode->setLargeItem(middleItem);
			}
			else
			{
				ItemType middleItem = tempNode->getMiddleItem();
				parentNode->setMiddleItem(middleItem);
			}
		}
		ItemType smallItem = tempNode->getSmallItem();
		ItemType largeItem = tempNode->getLargeItem();

		QuadNode<ItemType>* newLeftChild= new QuadNode<ItemType>(smallItem);
		QuadNode<ItemType>* newRightChild= new QuadNode<ItemType>(largeItem);

		parentNode->setLeftChildPtr(newLeftChild);
		parentNode->setRightChildPtr(newRightChild);
		if (newEntry < parentNode->getSmallItem())
		{
			parentNode->getLeftChildPtr()->setSmallItem(newEntry);

		}
		else
		{
			parentNode->getRightChildPtr()->setSmallItem(newEntry);
		}

	}
	else
	{
		PlaceItemInNotFullNode(tempNode, newEntry);
	}
}


template<class ItemType>
void TwoThreeFourTree<ItemType>::PlaceItemInNotFullNode(QuadNode<ItemType>* nodeToPlaceItemInPtr,
	ItemType& newEntry)
{
	//only one item in node in the small item spot.
	if((nodeToPlaceItemInPtr->getMiddleItem() == -1) && (nodeToPlaceItemInPtr->getLargeItem() == -1))
	{
		nodeToPlaceItemInPtr->setLargeItem(newEntry);
	}

	//two items in node one in small and one in large
	else if((nodeToPlaceItemInPtr->getSmallItem() != -1) && (nodeToPlaceItemInPtr->getMiddleItem() == -1) &&
		(nodeToPlaceItemInPtr->getLargeItem() != -1))
	{
		if (newEntry < nodeToPlaceItemInPtr->getSmallItem())
		{
			ItemType smallItem = nodeToPlaceItemInPtr->getSmallItem();

			nodeToPlaceItemInPtr->setMiddleItem(smallItem);
			nodeToPlaceItemInPtr->setSmallItem(newEntry);
		}
		else if (newEntry > nodeToPlaceItemInPtr->getLargeItem())
		{
			ItemType largeItem = nodeToPlaceItemInPtr->getLargeItem();

			nodeToPlaceItemInPtr->setMiddleItem(largeItem);
			nodeToPlaceItemInPtr->setLargeItem(newEntry);
		}
		else
		{
			nodeToPlaceItemInPtr->setMiddleItem(newEntry);
		}
	}
	
	
}



template<class ItemType>
void TwoThreeFourTree<ItemType>::inOrderTraversalHelper(void visit(ItemType&), QuadNode<ItemType>* tempNode)
{

	ItemType smallItem = tempNode->getSmallItem();
	ItemType middleItem = tempNode->getMiddleItem();
	ItemType largeItem = tempNode->getLargeItem();

	if (tempNode->isLeaf())
	{
		

		visit(smallItem);
		if (tempNode->getMiddleItem() != -1)
		{

			visit(middleItem);
		}
		if (tempNode->getLargeItem() != -1)
		{
			visit(largeItem);
		}
	}
	if (tempNode->isTwoNode())
		
	{
		inOrderTraversalHelper(visit, tempNode->getLeftChildPtr());
		visit(smallItem);
		inOrderTraversalHelper(visit, tempNode->getRightChildPtr());
	}
	if (tempNode->isThreeNode())
	{
		inOrderTraversalHelper(visit, tempNode->getLeftChildPtr());
		visit(smallItem);
		if (tempNode->getLeftMidChildPtr() != nullptr)
		{
			inOrderTraversalHelper(visit, tempNode->getLeftMidChildPtr());
		}
		if (tempNode->getRightMidChildPtr() != nullptr)
		{
			inOrderTraversalHelper(visit, tempNode->getRightMidChildPtr());
		}
		visit(largeItem);
		inOrderTraversalHelper(visit, tempNode->getRightChildPtr());
	}
	if (tempNode->isFourNode())
	{
		inOrderTraversalHelper(visit, tempNode->getLeftChildPtr());
		visit(smallItem);
		inOrderTraversalHelper(visit, tempNode->getLeftMidChildPtr());
		visit(middleItem);
		inOrderTraversalHelper(visit, tempNode->getRightMidChildPtr());
		visit(largeItem);
		inOrderTraversalHelper(visit, tempNode->getRightChildPtr());
	}
}


//Henry S
template<class ItemType>
QuadNode<ItemType>* TwoThreeFourTree<ItemType>::findNode(QuadNode<ItemType>* treePtr, ItemType & entry)
{
	if ((treePtr->getSmallItem() == entry) || (treePtr->getMidItem() == entry) || (treePtr->getLargeItem() == entry))
	{
		return treePtr;
	}

	else if (treePtr->isLeaf())
	{
		ItemType treeItem = nullptr;
		return treeItem;
	}

	else if (treePtr->isFourNode())
	{
		if (entry < treePtr->getSmallItem())
		{
			return findNode(treePtr->getLeftChildPtr(), entry);
		}

		else if ((entry > treePtr->getSmallItem()) && (entry < treePtr->getMidItem()))
		{
			return findNode(treePtr->getLeftMidChildPtr(), entry);
		}

		else if ((entry > treePtr->getMidItem()) && (entry < treePtr->getLargeItem()))
		{
			return findNode(treePtr->getRightMidChildPtr(), entry);
		}

		else if (entry > treePtr->getLargeItem())
		{
			return findNode(treePtr->getRightChildPtr(), entry);
		}
	}

	else if (treePtr->isThreeNode())
	{
		if (entry < treePtr->getSmallItem())
		{
			return findNode(treePtr->getLeftChildPtr(), entry);
		}

		else if (entry < treePtr->getLargeItem())
		{
			return findNode(treePtr->getLeftMidChildPtr(), entry);
		}

		else
		{
			return findNode(treePtr->getRightChildPtr(), entry);
		}
	}

	else if (treePtr->isTwoNode())
	{
		if (entry < treePtr->getSmallItem())
		{
			return findNode(treePtr->getLeftChildPtr(), entry);
		}

		else
		{
			return findNode(treePtr->getRightChildPtr(), entry);
		}
	}
}

//method code by Henry S//
/*template<class ItemType>
bool TwoThreeFourTree<ItemType>::remove(QuadNode<ItemType>* Ptr, const ItemType& entry)	//Henry S
{
	QuadNode<ItemType>* removeNode = findNode(Ptr, entry);
	QuadNode<ItemType>* tempNode = new QuadNode<ItemType>();

	if (removeNode == nullptr)
	{
		cout << "Entry not found. No entry deleted." << endl;
		return false;
	}

	else
	{
		if (!removeNode->isLeaf()) {
			tempNode = removeNode;
			while (!tempNode->isLeaf())
			{
				if (tempNode->isFourNode())
				{
					if (newItem < tempNode->getSmallItem())
					{
						tempNode = tempNode->getLeftChildPtr();
					}

					else if ((newItem > tempNode->getSmallItem()) && (newItem < tempNode->getMidItem()))
					{
						tempNode = tempNode->getLeftMidChildPtr();
					}

					else if ((newItem > tempNode->getMidItem()) && (newItem < tempNode->getLargeItem()))
					{
						tempNode = tempNode->getRightMidChildPtr();
					}

					else if (newItem > tempNode->getLargeItem())
					{
						tempNode = tempNode->getRightPtr();
					}
				}

				else if (tempNode->isThreeNode())
				{
					if (newItem < tempNode->getSmallItem())
					{
						tempNode = tempNode->getLeftChildPtr();
					}

					else if (newItem < tempNode->getLargeItem())
					{
						tempNode = tempNode->getLeftMidChildPtr();
					}

					else
					{
						tempNode = tempNode->getRightChildPtr();
					}
				}

				else if (tempNode->isTwoNode())
				{
					if (newItem < tempNode->getSmallItem())
					{
						tempNode = tempNode->getLeftChildPtr();
					}

					else
					{
						tempNode = tempNode->getRightChildPtr();
					}
				}
			}

			if (removeNode->getSmallItem() == newItem)
			{
				ItemType temp = removeNode->getSmallItem();
				removeNode->setSmallItem(tempNode->getSmallItem);
				tempNode->setSmallItem(temp);
			}
			else if (removeNode->getMidItem() == newItem)
			{
				ItemType temp = removeNode->getMidItem();
				removeNode->setMidItem(tempNode->getSmallItem);
				tempNode->setSmallItem(temp);
			}

			else if (removeNode->getLargeItem() == newItem)
			{
				ItemType temp = removeNode->getLargeItem();
				removeNode->setLargeItem(tempNode->getSmallItem);
				tempNode->setSmallItem(temp);
			}


			if ((tempNode->getSmallItem() == newItem) && (tempNode->getLargeItem() != NULL))
			{
				tempNode->setSmallItem(tempNode->getLargeItem());
				tempNode->setLargeItem(NULL);
			}

			else if ((tempNode->getLargeItem() == newItem) && (tempNode->getMidItem() != NULL))
			{
				tempNode->setLargeItem(tempNode->getMidItem());
				tempNode->setMidItem(NULL);

			}

			else if ((tempNode->getLargeItem() == newItem) && (tempNode->getMidItem() == NULL))
			{
				tempNode->setLargeItem(NULL);

			}

			else if ((tempNode->getMidItem() == newItem))
			{
				tempNode->setMidItem(NULL);
			}

			else if (tempNode->getLargeItem() == NULL)
			{


				QuadNode<ItemType>* parentNode = tempNode->getParentPtr();
				QuadNode<ItemType>* mergeNode = new QuadNode<ItemType>();
				QuadNode<ItemType>* newNode = new QuadNode<ItemType>();

				if (parentNode->isFourNode())
				{
					if (tempNode == parentNode->getRightChildPtr)
					{
						mergeNode == parentNode->getRightMidChildPtr();
						if (mergeNode->getLargeItem() != NULL)
						{

						}
					}
				}
			}
		}
	}

} */
