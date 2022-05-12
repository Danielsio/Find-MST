#include "Queue.h"

Queue::Queue() : front(nullptr), rear(nullptr)
{
}
/*----------------------------------------------------------------*/
void Queue::makeEmpty() // makes an empty queue
{
    // as long as the queue is not empty, deletes the front node
    while (front)
    {
        qNode* temp = front;
        front = front->next;
        delete temp;
    }
    front = nullptr;
    rear = nullptr;
}
/*----------------------------------------------------------------*/
void Queue::enqueue(int v) // inserts a new node to the rear of the queue
{
    qNode* newNode = new qNode(v);

    if (rear == nullptr)
    {
        rear = newNode;
        front = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    
}
/*----------------------------------------------------------------*/
int Queue::dequeue() // takes the node that is in the front, out of the queue and returns its value
{
    int res;

    if (!front)
    {
        res = IS_EMPTY;
    }
    else if (front == rear)
    {
        res = front->dataVertex;
        delete front;

        front = rear = nullptr;

    }
    else
    {
        res = front->dataVertex;
        qNode* temp = front;
        front = front->next;

        delete temp;
    }
    return res;
}
/*----------------------------------------------------------------*/
bool Queue::isEmpty() // checks if the queue is empty
{
    return ((!front) || (!rear)) ? true : false;
}
/*----------------------------------------------------------------*/
Queue::~Queue()
{
    makeEmpty();
}
/*----------------------------------------------------------------*/
Queue::qNode::qNode(int v) : dataVertex(v), next(nullptr)
{
}
