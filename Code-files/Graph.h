#pragma once

#include <iostream>
#include <vector>
#include "Neighbor.h"
#include "Edge.h"
class Neighbor;

class Graph
{
private:
	vector<Neighbor*> vertices;
	int vSize;

	void removeXfromYlist(int y, int x); // removes the vertex 'x' from the neighbors list of vertex 'y'
	
public:
	Graph(int vSize);
	~Graph();

	int getVSize() const; // returns 'vSize'

	void MakeEmptyGraph(int vSize); // creates an empty graph
	bool isAdjacent(const int& u, const int& v); // checks if the edge (u,v) exists (from u to v)
	Neighbor* GetAdjList(int u); // returns the head of a list of all the neighbors of 'u'
	void AddEdge(int u, int v, int weight); // adds a new edge to the graph
	void RemoveEdge(int u, int v); // removes the edge (u,v) from the graph

	int MSTKruskal(vector<Edge>& edges); // uses kruskal algorythm to calculate the weight of an MST
	int MSTPrimm(); // uses primm algorythm to calculate the weight of an MST

	void makeEdgeListFromGraph(vector<Edge>* edges); // creates a vector of all the edges of the graph
	void BFS(int s, vector<int>& distances); // receives a source 's', and uses BFS algorythm to find distances from 's' to other vertices
	bool isConnected(string& outRes); // checks if the graph is connected
};

