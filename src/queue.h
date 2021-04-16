#ifndef QUEUE_H_
#define QUEUE_H

#include <iostream>
#include <vector>
#include <cassert>


template<typename T>
class Queue
{
private:
    T* queue;

    int front;
    int rear;
    int capacity;

    const int size;
public:
    Queue(int = 10);
    Queue(const Queue<T>&); // copy constructor
    ~Queue();

    void enqueue(const T&);  // TODO: same here
    T dequeue();

    T get_front();
    void print_queue();
};


//              definition


// default
template<typename T>
Queue<T>::Queue(int s)
    :
    size(s),
    front(0),
    rear(0),
    capacity(0)
{
    queue = new T[size + 1];
}


// copy
template<typename T>
Queue<T>::Queue(const Queue<T>& other)
    :
    size(other.size),
    front(other.front),
    rear(other.rear),
    capacity(other.capacity),
    queue(new T[size + 1])
{
    for(int i = 0; i < size; i++)
    {
        // copying
        queue[i] = other.queue[i];
    }
}


//destructor
template<typename T>
Queue<T>::~Queue()
{
    delete[] queue;
}

template<typename T>
void Queue<T>::enqueue(const T& element)
{
    assert(capacity < size);

    queue[rear++] = element;
    capacity++;

    if(rear > size)
    {
        rear -= size + 1;
    }
}

template<typename T>
T Queue<T>::dequeue()
{
    assert(capacity > 0);

    T element = queue[front++];
    capacity--;

    if(front > size)
    {
        front -= size + 1;
    }

    return element;
}

template<typename T>
T Queue<T>::get_front()
{
    return queue[front];
}

// do i need this?
template<typename T>
void Queue<T>::print_queue()
{
    std::cout << "Queue: ";

    if(rear == 0 && front == 0)
    {
        std::cout << "is empty" << std::endl; 
    }
    else
    {
        for(int i = rear; i >= front; i--)
            std::cout << queue[i] << " ";
        std::cout << std::endl;
    }    
}


#endif  // QUEUE_H