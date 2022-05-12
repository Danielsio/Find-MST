#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Edge.h"
#include "DisjointSet.h"
#include "Graph.h"
#include "heap.h"
#include "Queue.h"

using namespace std;

class Graph;

int partition(vector<Edge>& edges, int start, int end); // uses partition algorythm to put pivot in its place
void quickSort(vector<Edge>& edges, int start, int end); // uses quickSort algorythm to sort a vector
void findAndErase(vector<Edge>& edges, int start, int end); // finds an edge in a vector and erases it from the vector
void getVNumInputFromFile(ifstream& inputFile, int& n); // reads the number of vertices from file
void getENumInputFromFile(ifstream& inputFile, int& m); // reads the number of edges from file
void getEdgesInputFromFile(ifstream& inputFile, const int& m, Graph& G, int& startVToRemove, int& endVToRemove); // reads the details of the edges from file
void runTasks(const char* inFileName); // runs the program