#pragma once

#include "Utillities.h"

class Neighbor
{
private:
	int vertex;
	int weight;
	bool isAlreadyEdge;
	Neighbor * next;

public:
	Neighbor(int vertex, int weight);
	Neighbor(int vertex, int weight, bool isAlreadyEdge);

	int getVertex() const; // returns 'vertex'
	int getWeight() const; // returns 'weight'
	bool getIsAlreadyEdge() const; // returns 'isAlreadyEdge'
	Neighbor* getNext(); // returns 'next'

	void setNext(Neighbor* next); // sets 'next' to a new value
};

