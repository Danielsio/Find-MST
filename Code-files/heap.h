#pragma once

#include "Utillities.h"

struct hNode
{
	int keyWeight;
	int dataVertex;

	hNode();
	hNode(int key, int data);
};

class heap
{
private:
	hNode* heapArr;
	int maxSize;
	int heapSize;
	int allocated;
	vector<int> placeOfVertices;

	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void FixMinHeap(int node); // fixes the heap
public:
	heap(int heapSize);
	~heap();

	hNode* getHeapArr(); // returns 'heapArr'
	int getHeapSize() const; // returns 'heapSize'
	vector<int>& getPlaceOfVertices(); // returns 'placeOfVertices'

	void setHeapSize(int heapSize); // sets 'heapSize' to a new value

	void Build(vector<hNode>& arr); // uses Floyd's algorythm to build a heap from a vector
	hNode DeleteMin(); // deletes the min value and return it
	bool IsEmpty(); // checks if the heap is empty
	void DecreaseKey(int place, int newKeyWeight); // gives the heap node in 'place', a new key value, then fixes the heap

	void decreaseHeapSize(); // decreases 'heapSize' by one
	void bubbleUp(int index); // bubbles up a node in the heap
	void nodeSwap(hNode& n1, hNode& n2); // gets two hNodes and swaps them
	void clear(int index); // resets the node's values
};

