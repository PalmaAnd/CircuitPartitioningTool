#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include "gate.h"
#include "connection.h"

/**
 * @brief A object representing a Queue which allows the user to add or remove elements from the queue. Similar to the
 * Queue defined in AlgoDat.
 */
class Queue {

public:
    /**
     * @brief Creates a queue element with the given capacity
     *
     * @param capacity The maximum capacity of elements the queue can hold
     * @return A pointer on the created queue
    */
    Queue(int cap) {
        capacity = cap;
        start = 0;
        size = 0;
        end = capacity - 1;
        array.reserve(capacity);
        array.resize(capacity);  // Ich musste das hier machen.  reserve macht den nutzbaren Vector nicht größer.  Rade
    }

    /**
     * @brief Checks if the queue is empty
     *
     * @param queue The queue to check
     * @return true if the queue is empty, otherwise false
     */
    bool isEmpty() const;

    /**
     * @brief Adds an element at the end of the given queue
     *
     * @param queue The queue
     * @param item The item that will be added at the end
     */
    void enqueue(int item);

    /**
     * @brief Removes the first element of the queue
     *
     * @param queue The queue
     * @return The first item of the queue
     */
    int dequeue();

private:
    /* Start index of the queue */
    int start;
    /* End index of the queue */
    int end;
    /* Current size of the queue/ How many elements are currently in the Queue. */
    int size;
    /* Maximum capacity of the queue */
    int capacity;
    /* Array storing queue elements */
    std::vector<int> array;
};

#endif //QUEUE_H
