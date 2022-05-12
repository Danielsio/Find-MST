# Find-MST

In this project you will find both Prim and Kruskal algorithms to find the MST in an Unadjusted graph of n vertices and m edges.

First Kruskal Algorithm will run, then Prim's and after both finished there is an option to remove an edge from the Graph and calculate the MST again with Kruskal.

the project recive input file name in argv[1], and output filename with argv[2]

input filename contains:
n
m
edges + Weight
edge to remove

for example:
5
6
1 2 5
2 3 2
4 1 3
1 3 6
1 5 2
2 4 1
2 3 // to remove
