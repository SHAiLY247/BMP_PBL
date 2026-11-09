#include "RequestQueue.h"

RequestQueue::RequestQueue()
{
    front = nullptr;
    rear = nullptr;
}

// Add a request at the rear
void RequestQueue::enqueue(const ProcessingJob& request)
{
    Node* newNode = new Node;

    newNode->request = request;
    newNode->next = nullptr;

    if (front == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

// Remove a request from the front
bool RequestQueue::dequeue(ProcessingJob& request)
{
    if (front == nullptr)
    {
        return false;
    }

    Node* temp = front;

    request = temp->request;

    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;

    return true;
}

// Check whether queue is empty
bool RequestQueue::isEmpty()
{
    return front == nullptr;
}

// Remove all requests
void RequestQueue::clear()
{
    while (front != nullptr)
    {
        Node* temp = front;

        front = front->next;

        delete temp;
    }

    rear = nullptr;
}

// Destructor
RequestQueue::~RequestQueue()
{
    clear();
}