#include "Neighbor.h"

Neighbor::Neighbor(int vertex, int weight) : vertex(vertex), weight(weight), isAlreadyEdge(false) , next(nullptr)
{
}
/*----------------------------------------------------------------*/
Neighbor::Neighbor(int vertex, int weight, bool isAlreadyEdge) : vertex(vertex), weight(weight), isAlreadyEdge(isAlreadyEdge), next(nullptr)
{
}
/*----------------------------------------------------------------*/
int Neighbor::getVertex() const // returns 'vertex'
{
    return this->vertex;
}
/*----------------------------------------------------------------*/
int Neighbor::getWeight() const // returns 'weight'
{
    return this->weight;
}
/*----------------------------------------------------------------*/
bool Neighbor::getIsAlreadyEdge() const // returns 'isAlreadyEdge'
{
    return isAlreadyEdge;
}
/*----------------------------------------------------------------*/
Neighbor* Neighbor::getNext() // returns 'next'
{
    return this->next;
}
/*----------------------------------------------------------------*/
void Neighbor::setNext(Neighbor* next) // sets 'next' to a new value
{
    this->next = next;
}
