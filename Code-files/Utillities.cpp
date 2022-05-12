#include "Utillities.h"

int partition(vector<Edge>& edges, int start, int end) // uses partition algorythm to put pivot in its place
{
    int pivot = edges[end].getWeight(); // sets pivot 
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        // if current element is smaller than pivot
        if (edges[j].getWeight() <= pivot)
        {
            i++;  // increases the index of smaller element 
            swap(edges[i], edges[j]); // swaps elements at i and j
        }
    }

    swap(edges[i + 1], edges[end]);

    return (i + 1);
}
/*----------------------------------------------------------------*/
void quickSort(vector<Edge>& edges, int start, int end) // uses quickSort algorythm to sort a vector
{
    if (start >= end) // size <= 1
        return;

    // partition
    int pivot = partition(edges, start, end);

    // sorting left side of pivot
    quickSort(edges, start, pivot - 1);

    // sorting right side of pivot
    quickSort(edges, pivot + 1, end);

}
/*----------------------------------------------------------------*/
void findAndErase(vector<Edge>& edges, int start, int end) // finds an edge in a vector and erases it from the vector
{
    auto iter= edges.begin();

    while (iter != edges.end())
    {
        if (iter->getStartV() == start && iter->getEndV() == end)
        {
            edges.erase(iter);
            return;
        }
        iter++;
    }
}
/*----------------------------------------------------------------*/
void getVNumInputFromFile(ifstream& inputFile, int& n) // reads the number of vertices from file
{
    string buffer;
    stringstream sstream;

    getline(inputFile, buffer); // reads first line to 'buffer'
    sstream << buffer;
    sstream >> n; // tries to read an int from first line
    if (!sstream.eof() || n < 0) // if the vertice number is invalid
    {
        inputFile.close();
        throw (string)"Invalid Input";
    }
}
/*----------------------------------------------------------------*/
void getENumInputFromFile(ifstream& inputFile, int& m) // reads the number of edges from file
{
    string buffer;
    stringstream sstream;

    getline(inputFile, buffer); // reads second line to 'buffer'
    sstream << buffer;
    sstream >> m; // tries to read an int from second line
    if (!sstream.eof() || m <= 0) // if the edges number is invalid
    {
        inputFile.close();
        throw (string)"Invalid Input";
    }
}
/*----------------------------------------------------------------*/
void getEdgesInputFromFile(ifstream& inputFile, const int& m, Graph& G, int& startVToRemove, int& endVToRemove) // reads the details of the edges from file
{
    int i;
    int count = 0;
    int startV, endV, weight;
    string buffer;
    stringstream sstream;

    // goes through the file and reads its lines.
    // checks that each line is in the correct format.
    // expects to read 'm' edges.
    for (i = 0; i < m && !inputFile.eof(); i++)
    {
        sstream.str(""); sstream.clear(); // clears the stringstream buffer
        getline(inputFile, buffer); // gets next line
        sstream << buffer;
        if (sstream >> startV && sstream >> endV && sstream >> weight && sstream.eof()
            && startV >= 1 && startV <= G.getVSize() && endV >= 1 && endV <= G.getVSize())
        {
            // succeeds to read three ints,
            // and no more data in the line,
            // and the edge is in format
            G.AddEdge(startV, endV, weight);
        }
        else
        {
            inputFile.close();
            throw (string)"Invalid Input";
        }
        count++;
    }

    if (count < m) // not enough edges
    {
        inputFile.close();
        throw (string)"Invalid Input";
    }

    // tries to read the edge to remove
    sstream.str(""); sstream.clear(); // clears the stringsteam buffer
    getline(inputFile, buffer); // gets next line
    sstream << buffer;
    if (!(sstream >> startVToRemove && sstream >> endVToRemove && sstream.eof()
        && startVToRemove >= 1 && startVToRemove <= G.getVSize() && endVToRemove >= 1 && endVToRemove <= G.getVSize()
        && inputFile.eof()))
    {
        // doesn't succeed to read two ints,
        // or there is more data in the line or in the file,
        // or the edge is not in the format
        inputFile.close();
        throw (string)"Invalid Input";
    }
}
/*----------------------------------------------------------------*/
void runTasks(const char* inFileName) // runs the program
{
    int n, m;
    int startVToRemove, endVToRemove;
    bool isMST;
    vector<Edge> edges;
    string outRes;

    ifstream inputFile(inFileName);
    if (!inputFile)
    {
        throw (string)"Error. Couldn't open this file";
    }

    getVNumInputFromFile(inputFile, n); // get the number of vertice

    Graph G(n);

    getENumInputFromFile(inputFile, m); // get the number of edges

    getEdgesInputFromFile(inputFile, m, G, startVToRemove, endVToRemove); // get the edges data

    inputFile.close();

    isMST = G.isConnected(outRes); // checks if the graph is connected.
    // a matching output is inserted into 'outRes'.
    if (!isMST)
    {
        // the graph is not connected
        throw "Kruskal " + outRes + "\nPrim " + outRes + "\nKruskal2 " + outRes;
    }

    int resKruskal1 = G.MSTKruskal(edges);
    int resPrimm = G.MSTPrimm();

    outRes = "Kruskal " + to_string(resKruskal1) + "\nPrim " + to_string(resPrimm) + "\nKruskal2 ";


    G.RemoveEdge(startVToRemove, endVToRemove); // removes the wanted edge from the graph

    isMST = G.isConnected(outRes); // checks if the graph is connected.
    // a matching output is inserted into 'outRes'.
    // if the graph is no longer connected, it means that the removed edge was a bridge.
    // therefore, there is no MST.
    if (isMST)
    {
        // the graph is connected, which means the removed edge was not a bridge
        findAndErase(edges, startVToRemove, endVToRemove);
        outRes += to_string(G.MSTKruskal(edges));
    }

    throw outRes;
}
