#pragma once

class Edge
{
private:
	int startV;
	int endV;
	int weight;

public:
	Edge();
	Edge(int start, int end, int weight);

	int getStartV() const; // returns 'startV'
	int getEndV() const; // returns 'endV'
	int getWeight()const; // returns 'weight'
};

