#include "DisjointSet.h"

DisjointSet::DisjointSet(int sizeOfForest) : sizeOfForest(sizeOfForest)
{
	this->parent = new int[sizeOfForest];
	this->setSize = new int[sizeOfForest];

	for (int i = 0; i < sizeOfForest; i++) // initializes the arrays
	{
		parent[i] = NO_PARENT;
		setSize[i] = 0;
	}
}
/*----------------------------------------------------------------*/
DisjointSet::~DisjointSet()
{
	delete parent;
	delete setSize;
}
/*----------------------------------------------------------------*/
void DisjointSet::MakeSet(int vertex) // makes a new set with 'vertex'
{
	parent[vertex - 1] = vertex;
	setSize[vertex - 1] = 1;
}
/*----------------------------------------------------------------*/
void DisjointSet::Union(int u, int v) // combines two different sets
{
	int repU = Find(u);
	int repV = Find(v);

	// selects the bigger set and merges the smaller one into the bigger one (union by size)
	if (setSize[repU - 1] > setSize[repV - 1]) // the set of 'u' is bigger
	{
		parent[repV - 1] = repU;
		setSize[repU - 1] += setSize[repV - 1];
	}	
	else // the set of 'v' is bigger
	{
		parent[repU - 1] = repV;
		setSize[repV - 1] += setSize[repU - 1];
	}
		

}
/*----------------------------------------------------------------*/
int DisjointSet::Find(int vertex) // finds the set representor of 'vertex'
{
	// reaches the parent of 'vertex' until finds its representor, then updates each vertex's representor in the path to be that representor (path compression)
	if (vertex != parent[vertex - 1])
	{
		parent[vertex - 1] = Find(parent[vertex - 1]);
	}
		
	return parent[vertex - 1];
}
