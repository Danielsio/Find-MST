#include "heap.h"

int heap::Left(int node)
{

	return (2 * node + 1);
}
/*----------------------------------------------------------------*/
int heap::Right(int node)
{
	return (2 * node + 2);
}
/*----------------------------------------------------------------*/
int heap::Parent(int node)
{
	return (node - 1) / 2;
}
/*----------------------------------------------------------------*/
void heap::FixMinHeap(int node) // fixes the heap
{
	int min;
	int left = Left(node);
	int right = Right(node);

	// finds the minimum value out of 'node' and its left and right children
	if ((left < heapSize) && (heapArr[left].keyWeight < heapArr[node].keyWeight))
	{
		min = left;
	}	
	else
	{
		min = node;
	}

	if ((right < heapSize) && (heapArr[right].keyWeight < heapArr[min].keyWeight))
	{
		min = right;
	}
		
	if (min != node)
	{
		std::swap(heapArr[node], heapArr[min]);
		std::swap(placeOfVertices[heapArr[node].dataVertex - 1], placeOfVertices[heapArr[min].dataVertex - 1]);
		FixMinHeap(min);
	}
}
/*----------------------------------------------------------------*/
heap::heap(int heapSize) : maxSize(heapSize), heapSize(0), allocated(1)
{
	heapArr = new hNode[maxSize];
	placeOfVertices.resize(maxSize);
}
/*----------------------------------------------------------------*/
heap::~heap()
{
	if (allocated)
	{
		delete[] heapArr;
	}

	heapArr = nullptr;
}
/*----------------------------------------------------------------*/
hNode* heap::getHeapArr() // returns 'heapArr'
{
	return this->heapArr;
}
/*----------------------------------------------------------------*/
int heap::getHeapSize() const // returns 'heapSize'
{
	return heapSize;
}
/*----------------------------------------------------------------*/
vector<int>& heap::getPlaceOfVertices() // returns 'placeOfVertices'
{
	return placeOfVertices;
}
/*----------------------------------------------------------------*/
void heap::setHeapSize(int heapSize) // sets 'heapSize' to a new value
{
	this->heapSize = heapSize;
}
/*----------------------------------------------------------------*/
void heap::Build(vector<hNode>& arr) // uses Floyd's algorythm to build a heap from a vector
{
	int i;

	// inserts the data from the vector to the heap's array
	for (i = 0; i < maxSize; i++)
	{
		heapArr[i].keyWeight = arr[i].keyWeight;
		heapArr[i].dataVertex = arr[i].dataVertex;
		placeOfVertices[arr[i].dataVertex-1] = i;
		heapSize++;
	}

	// fixes heap
	for ( i = heapSize / 2; i >= 0; i--)
	{
		FixMinHeap(i);
	}
}
/*----------------------------------------------------------------*/
hNode heap::DeleteMin() // deletes the min value and return it
{
	if (this->heapSize == 0)
	{
		throw (string)"Invalid Input";
	}

	const hNode min = heapArr[0];

	nodeSwap(heapArr[0], heapArr[heapSize - 1]);
	clear(heapSize - 1);
	heapSize--;
	FixMinHeap(0);

	return min;
}
/*----------------------------------------------------------------*/
bool heap::IsEmpty() // checks if the heap is empty
{
	return !heapSize ? true : false;
}
/*----------------------------------------------------------------*/
void heap::DecreaseKey(int place, int newKeyWeight) // gives the heap node in 'place', a new key value, then fixes the heap
{
	heapArr[place- 1].keyWeight = newKeyWeight;
	bubbleUp(place);
}
/*----------------------------------------------------------------*/
void heap::decreaseHeapSize() // decreases 'heapSize' by one
{
	this->heapSize--;
}
/*----------------------------------------------------------------*/
void heap::bubbleUp(int place) // bubbles up a node in the heap
{
	while (place > 1 && heapArr[Parent(place-1)].keyWeight > heapArr[place-1].keyWeight)
	{
		nodeSwap(heapArr[Parent(place-1)], heapArr[place-1]);
		place = Parent(place - 1) + 1;
	}
}
/*----------------------------------------------------------------*/
void heap::nodeSwap(hNode& n1, hNode& n2) // gets two hNodes and swaps them
{
	std::swap(n1.keyWeight, n2.keyWeight);
	std::swap(n1.dataVertex, n2.dataVertex);

	std::swap(placeOfVertices[n1.dataVertex - 1], placeOfVertices[n2.dataVertex - 1]);
}
/*----------------------------------------------------------------*/
void heap::clear(int index) // resets the node's values
{
	heapArr[index].keyWeight = INT32_MAX;
}
/*----------------------------------------------------------------*/
hNode::hNode() : keyWeight(INT32_MAX), dataVertex(NO_PARENT)
{
}
/*----------------------------------------------------------------*/
hNode::hNode(int key, int data) : keyWeight(key), dataVertex(data)
{
}
