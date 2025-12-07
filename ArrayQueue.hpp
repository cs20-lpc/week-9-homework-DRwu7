#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include "Queue.hpp"
#include <iostream>
using namespace std;

template <typename T>
class ArrayQueue : public Queue<T> {
    private:
        // the array that contains the elements
        T* buffer;

        // the maximum size of the queue
        int maxSize;

        // front and back pointers
        int frontPos, backPos;

        // copy the state of the argument queue to `this`
        void copy(const ArrayQueue<T>&);

    public:
        // constructor with maximum size as argument
        ArrayQueue(int size = 100);

        // copy constructor
        ArrayQueue(const ArrayQueue<T>&);

        // overloaded assignment operator
        ArrayQueue<T>& operator=(const ArrayQueue<T>&);

        // destructor
        virtual ~ArrayQueue();

        // return the element at the back of the queue
        virtual T back() const override;

        // remove all elements in the queue, resetting to the initial state
        virtual void clear() override;

        // remove the front element from the queue
        virtual void dequeue() override;

        // add the argument to the back of the queue
        virtual void enqueue(const T&) override;

        // return the element at the front of the queue
        virtual T front() const override;

        // return the current length of the queue
        virtual int getLength() const override;

        // determine if the queue currently empty
        virtual bool isEmpty() const override;

        // check if queue is full
        bool isFull() const;
};

#include "ArrayQueue.tpp"
#endif