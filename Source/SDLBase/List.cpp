#include "List.h"
/*
template <class SelectedType> 
LinkedList<SelectedType>::LinkedList()
{
	startNodeAddress = nullptr;
}

template <class SelectedType> 
LinkedList<SelectedType>::LinkedList(SelectedType startNodeContents)
{
	startNodeAddress = new Node<SelectedType>(startNodeContents, nullptr, nullptr);
}

template <class SelectedType> 
LinkedList<SelectedType>::~LinkedList()
{
	Node<SelectedType> *tempAddress = nullptr;
	while (startNodeAddress != nullptr)
	{
		tempAddress = startNodeAddress->nextNode;
		delete(startNodeAddress);
		startNodeAddress = tempAddress;
	}
}

template <class SelectedType> 
void LinkedList<SelectedType>::AddItem(SelectedType item)
{
	if (startNodeAddress != nullptr)
	{
		Node<SelectedType> *tempAddress = startNodeAddress;
		while (tempAddress->nextNode != nullptr)
		{
			tempAddress = tempAddress->nextNode;
		}
		tempAddress->nextNode = new Node<SelectedType>(item, tempAddress, nullptr);
	}
	else
	{
		startNodeAddress = new Node<SelectedType>(item, nullptr, nullptr);
	}	
}

template <class SelectedType> 
void LinkedList<SelectedType>::RemoveItem(int itemNum)
{
	Node<SelectedType> *tempPointer = startNodeAddress;

	if (itemNum != 0)
	{
		int counter = 0;

		while (counter != itemNum)
		{
			counter++;
			tempPointer = tempPointer->nextNode;
		}

		tempPointer->previousNode->nextNode = tempPointer->nextNode;
		delete(tempPointer);
	}
	else
	{
		startNodeAddress = startNodeAddress->nextNode;
		delete(tempPointer);
	}
}

template <class SelectedType> 
SelectedType* LinkedList<SelectedType>::GetItem(int itemNum)
{
	Node<SelectedType> *tempPointer = startNodeAddress;
	int counter = 0;

	while (counter!=itemNum)
	{
		counter++;
		tempPointer = tempPointer->nextNode;
	}

	return *(tempPointer->content);
}

template <class SelectedType> 
int LinkedList<SelectedType>::GetLength()
{
	Node<SelectedType> *tempPointer = startNodeAddress;
	int counter = 0;

	while (tempPointer != nullptr)
	{
		counter++;
		tempPointer = tempPointer->nextNode;
	}

	return counter;
}*/