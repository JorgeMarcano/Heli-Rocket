#include "log.h"

#define MAX_Q_SIZE  10

typedef struct QNode {
    DataLog* data;
    struct QNode* next;
    struct QNode* prev;
} QNode;

volatile uint qSize = 0;
volatile QNode* head;
volatile QNode* tail;

volatile bool logging = false;

// Dequeue Data from Queue
void dequeueData();

// Initialize logging SD card
void initLog();

// Add to Async Storing Queue
void addLogData(DataLog* data) {
    QNode* newNode = malloc(sizeof(QNode));
    newNode->data = data;
    newNode->prev = 0;
    newNode->next = head;

    if (!qSize) {
        tail = newNode;
    }

    qSize++;

    if (!logging)
        finishAsync();
}

// Done Async Interrupt
void finishAsync() {
    dequeueData();

    if (!qSize) {
        logging = false;
        return;
    }

    // TODO: start next tail async
}

// Dequeue Data from Queue
void dequeueData() {
    if (!qSize)
        return;

    QNode* temp = tail->prev;
    free(tail->data);
    free(tail);
    tail = temp;
    qSize--;

    if (!qSize)
        head = 0;
}