#include "Graph.h"
#include "Utillities.h"

void Graph::removeXfromYlist(int y, int x) // removes the vertex 'x' from the neighbors list of vertex 'y'
{
	Neighbor* curr = vertices[y - 1];
	Neighbor* prev = nullptr;

	// goes through neighbors list
	while (curr)
	{
		if (curr->getVertex() == x)	// if finds 'x'
		{
			if (!prev) // 'x' is the head of the neighbors list
			{
				vertices[y - 1] = curr->getNext();
				delete curr;
				return;
			}
			else // 'x' is not the head of the neighbors list
			{
				prev->setNext(curr->getNext());
				delete curr;
				return;
			}
		}
		prev = curr;
		curr = curr->getNext();
	}
}
/*----------------------------------------------------------------*/
Graph::Graph(int vSize)
{
	MakeEmptyGraph(vSize); // creates an empty graph, of 'vSize' vertices and zero edges
}
/*----------------------------------------------------------------*/
Graph::~Graph()
{
	for (int i = 0; i < vSize; i++)
	{
		Neighbor* currNeighbor = vertices[i];
		Neighbor* nextNeighbor = nullptr;

		while (currNeighbor)
		{
			nextNeighbor = currNeighbor->getNext();
			delete currNeighbor;
			currNeighbor = nextNeighbor;
		}
	}
}
/*----------------------------------------------------------------*/
int Graph::getVSize() const // returns 'vSize'
{
	return vSize;
}
/*----------------------------------------------------------------*/
void Graph::MakeEmptyGraph(int vSize) // creates an empty graph
{
	this->vSize = vSize;

	for (int i = 0; i < vSize; i++)
	{
		this->vertices.push_back(nullptr);
	}
}
/*----------------------------------------------------------------*/
bool Graph::isAdjacent(const int& u, const int& v) // checks if the edge (u,v) exists (from u to v)
{
	Neighbor* curr = vertices[u - 1];

	// goes through neighbor list
	while (curr)
	{
		if (curr->getVertex() == v)
			return true;

		curr = curr->getNext();
	}
	return false;
}
/*----------------------------------------------------------------*/
Neighbor* Graph::GetAdjList(int u) // returns the head of a list of all the neighbors of 'u'
{
	return this->vertices[u - 1];
}
/*----------------------------------------------------------------*/
void Graph::AddEdge(int u, int v, int weight) // adds a new edge to the graph
{
	Neighbor* newEdgeUV = new Neighbor(v, weight);
	Neighbor* newEdgeVU = new Neighbor(u, weight, true);

	if (vertices[u - 1]) // if 'u' has already neighbors
	{
		// concatenates the existing neighbors to the new one
		newEdgeUV->setNext(vertices[u - 1]);
	}
	vertices[u - 1] = newEdgeUV;

	if (vertices[v - 1])  // if 'v' has already neighbors
	{
		// concatenates the existing neighbors to the new one
		newEdgeVU->setNext(vertices[v - 1]);
	}
	vertices[v - 1] = newEdgeVU;
	
}
/*----------------------------------------------------------------*/
void Graph::RemoveEdge(int u, int v) // removes the edge (u,v) from the graph
{

	// delete (u,v)
	removeXfromYlist(u, v);

	// delete (v,u)
	removeXfromYlist(v, u);
}
/*----------------------------------------------------------------*/
int Graph::MSTKruskal(vector<Edge>& edges) // uses kruskal algorythm to calculate the weight of an MST
{
	int mst_wt = 0; // initializes result
	
	if (edges.size() == 0) // if the function is used for the first time, therefore needs to sort the edges
	{
		makeEdgeListFromGraph(&edges);

		// sort edges in increasing order
		quickSort(edges, 0, edges.size() - 1);
	}

	DisjointSet ds(vSize); // creates disjoint sets

	for (int i = 1; i <= vSize; i++) // initializes a 'forest of vertices'
	{
		ds.MakeSet(i);
	}

	for (int i = 0; i < edges.size(); i++) // iterates through all sorted edges
	{
		int u = edges[i].getStartV();
		int v = edges[i].getEndV();

		int set_u = ds.Find(u);
		int set_v = ds.Find(v);

		// check if the selected edge is creating
		// a cycle or not (cycle is created if u
		// and v belong to same set)
		if (set_u != set_v)
		{
			// updats MST weight
			mst_wt += edges[i].getWeight();

			// merges two sets
			ds.Union(set_u, set_v);
		}
	}
	
	return mst_wt;
}
/*----------------------------------------------------------------*/
int Graph::MSTPrimm() // uses primm algorythm to calculate the weight of an MST
{
	int mst_wt = 0; // initializes result
	heap pQ(vSize); // creates empty priority queue

	int src = 1; // taking vertex 1 as source

	// create a vector for minimum values for
	// joining the MST, and initializes all of the
	// keys as infinite (INT32_MAX), 
	// except the source which initialized to 0
	vector<int> min(vSize, INT32_MAX);
	min[src - 1] = 0;

	// to store parent array which in turn store MST
	vector<int> parent(vSize, NO_PARENT);

	// to keep track of vertices included in MST
	vector<bool> InT(vSize, false);

	// builds a vector of key-data pairs (hNode), then builds priority queue from it
	vector<hNode> vertexArr;
	for (int i = 1; i <= vSize; i++)
	{
		vertexArr.push_back(hNode(min[i - 1], i));
	}
	pQ.Build(vertexArr);

	// looping till priority queue becomes empty
	while (!pQ.IsEmpty())
	{
		// the priority queue is prioritized by the minimum values
		// of joining the MST for each vertex.
		// extracts the current minimized vertex from priority queue
		hNode u = pQ.DeleteMin();

		mst_wt += u.keyWeight;

		InT[u.dataVertex - 1] = true;

		Neighbor* curr = GetAdjList(u.dataVertex);

		// goes through neighbors list
		while (curr)
		{
			if (!InT[curr->getVertex() - 1] && curr->getWeight() < min[curr->getVertex() - 1])
			{
				// the current neighbor is still no in the MST,
				// and the weight of the edge is less than the minimum joining value known so far,
				// therefore updates the new potential minimum values and parent, and the priority queue
				min[curr->getVertex() - 1] = curr->getWeight();
				parent[curr->getVertex() - 1] = u.dataVertex;
				pQ.DecreaseKey(pQ.getPlaceOfVertices()[curr->getVertex() - 1] +1, curr->getWeight());
			}
			curr = curr->getNext();
		}

		
	}


	return mst_wt;
}
/*----------------------------------------------------------------*/
void Graph::makeEdgeListFromGraph(vector<Edge>* edges) // creates a vector of all the edges of the graph
{
	int i;
	Neighbor* curr;

	// goes through the vertices
	for (i = 0; i < vSize; i++)
	{
		curr = vertices[i];

		// goes through neighbors list
		while (curr)
		{
			// avoids duplications of edges
			if (!curr->getIsAlreadyEdge())
			{
				edges->push_back(Edge(i + 1, curr->getVertex(), curr->getWeight()));
			}

			curr = curr->getNext();
		}
	}
}
/*----------------------------------------------------------------*/
void Graph::BFS(int s, vector<int>& distances) // receives a source 's', and uses BFS algorythm to find distances from 's' to other vertices
{
	int i;
	int u;
	Neighbor* curr;
	Queue Q;

	// initializes distances to infinite (INT32_MAX)
	for (i = 0; i < vSize; i++)
	{
		distances[i] = INT32_MAX;
	}
	Q.enqueue(s);
	distances[s - 1] = 0;

	// goes till the queue is empty
	while (!Q.isEmpty())
	{
		u = Q.dequeue();
		curr = vertices[u - 1];

		// goes though neighbors list
		while (curr)
		{
			if (distances[curr->getVertex() - 1] == INT32_MAX)
			{
				// the current neighbor is still set to infinite distance,
				// meaning still hasn't been discovered,
				// therefore, discovers it and setting its distance for 's'
				distances[curr->getVertex() - 1] = distances[u - 1] + 1;
				Q.enqueue(curr->getVertex());
			}
			curr = curr->getNext();
		}
	}
}
/*----------------------------------------------------------------*/
bool Graph::isConnected(string& outRes) // checks if the graph is connected
{
	vector<int> distances(vSize);
	BFS(1, distances);

	bool isMST = true;

	// goes through the distances vector
	for (int i = 0; i < distances.size(); i++)
	{
		if (distances[i] == INT32_MAX)
		{
			// the graph is no longer connected.
			// therefore there is no MST.
			// inserts a matching output to 'outRes'
			outRes += "No MST";
			isMST = false;
			break;
		}
	}

	return isMST;
}
