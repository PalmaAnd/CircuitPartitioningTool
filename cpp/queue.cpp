#include "queue.h"

using namespace std;

bool Queue::isEmpty() const {
    return size == 0;
}

void Queue::enqueue(int item) {
    end = (end + 1) % capacity;
    array[end] = item;
    size++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }
    int item = array[start];
    start = (start + 1) % capacity;
    size--;
    return item;
}
