#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/**
 * @brief Queue which allows the user to add or remove elements from the queue. Similar to the
 * Queue defined in AlgoDat.
 * @param start Start index of the queue
 * @param end End index of the queue
 * @param size Current size of the queue/ How many elements are currently in the Queue.
 * @param capacity Maximum capacity of the queue
 * @param array Pointer to the array storing queue elements
 */
typedef struct {
    int start;
    int end;
    int size;
    int capacity;
    int* array;
} Queue;

/**
 * @brief Creates a queue element with the given capacity
 *
 * @param capacity The maximum capacity of elements the queue can hold
 * @return A pointer on the created queue
 */
Queue* createQueue(int capacity);

/**
 * @brief Checks if the queue is empty
 *
 * @param queue The queue to check
 * @return true if the queue is empty, otherwise false
 */
bool isEmpty(Queue* queue);

/**
 * @brief Adds an element at the end of the given queue
 *
 * @param queue The queue
 * @param item The item that will be added at the end
 */
void enqueue(Queue* queue, int item);


/**
 * @brief Removes the first element of the queue
 *
 * @param queue The queue
 * @return The first item of the queue
 */
int dequeue(Queue* queue);

#endif //QUEUE_H
