#pragma once

#include "Utillities.h"

const int IS_EMPTY = -1;

class Queue
{
public:
    struct qNode;
private:

    qNode* rear;
    qNode* front;

public:
    Queue();
     ~Queue();

    void makeEmpty(); // makes an empty queue

    void enqueue(int v); // inserts a new node to the rear of the queue
    int dequeue(); // takes the node that is in the front, out of the queue and returns its value 
    bool isEmpty(); // checks if the queue is empty

    struct qNode
    {
        int dataVertex;
        qNode* next;

        qNode(int v);
    };
   
};