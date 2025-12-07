#ifndef QUEUE_FACTORY_HPP
#define QUEUE_FACTORY_HPP

#include "Queue.hpp"
#include "LinkedQueue.hpp"
#include "ArrayQueue.hpp"
#include <memory> // For unique_ptr

template <typename T>
class QueueFactory {
public:
    // Method to create the appropriate queue implementation
    // If size is provided (size > 0), returns ArrayQueue.
    // If no size is provided or size <= 0, returns LinkedQueue (dynamic size).
    static Queue<T>* GetQueue(int size = 0) {
        if (size > 0) {
            // Simulation 1: Fixed maximum size specified, use ArrayQueue.
            return new ArrayQueue<T>(size);
        } else {
            // Simulation 2: No maximum size specified, use LinkedQueue.
            return new LinkedQueue<T>();
        }
    }
};

#endif