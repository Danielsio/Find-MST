#include "Edge.h"

Edge::Edge()
{
}
/*----------------------------------------------------------------*/
Edge::Edge(int start, int end, int weight) : startV(start), endV(end), weight(weight)
{
}
/*----------------------------------------------------------------*/
int Edge::getStartV() const // returns 'startV'
{
	return startV;
}
/*----------------------------------------------------------------*/
int Edge::getEndV() const // returns 'endV'
{
	return endV;
}
/*----------------------------------------------------------------*/
int Edge::getWeight() const // returns 'weight'
{
	return weight;
}
