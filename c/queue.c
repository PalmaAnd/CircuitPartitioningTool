#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "gate.h"
#include "connection.h"

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fputs ("Problem occurred while allocating memory for Queue\n", stderr);
        exit(1);
    }
    queue->capacity = capacity;
    queue->start = queue->size = 0;
    queue->end = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (queue->array == NULL) {
        free(queue);
        fputs ("Problem occurred while allocating memory for Queue\n", stderr);
        exit(1);

    }
    return queue;
}

bool isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    queue->end = (queue->end + 1) % queue->capacity;
    queue->array[queue->end] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    int item = queue->array[queue->start];
    queue->start = (queue->start + 1) % queue->capacity;
    queue->size--;
    return item;
}