#pragma once

#include <iostream>
#include <vector>

using namespace std;

const int NO_PARENT = -1;

class DisjointSet {
private:
	int* parent;
	int* setSize;
	int sizeOfForest;
	
public:
	DisjointSet(int sizeOfForest);
	~DisjointSet();

	void MakeSet(int vertex); // makes a new set with 'vertex'
	void Union(int u, int v); // combines two different sets
	int Find(int vertex); // finds the set representor of 'vertex'
};