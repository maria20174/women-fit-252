#include "queue.h"

void queue_init(Queue* q, IAllocator* alloc) {
    if (q == NULL) {
        return;
    }

    q->alloc = alloc;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void queue_destroy(Queue* q) {
    if (q == NULL || q->alloc == NULL || q->alloc->free == NULL) {
        return;
    }

    while (q->head != NULL) {
        QueueNode* temp = q->head;
        q->head = q->head->next;
        q->alloc->free(q->alloc, temp);
    }

    q->tail = NULL;
    q->size = 0;
    q->alloc = NULL;
}

int queue_push(Queue* q, void* value) {
    if (q == NULL || q->alloc == NULL || q->alloc->alloc == NULL) {
        return -1;
    }

    QueueNode* node = (QueueNode*)q->alloc->alloc(q->alloc, sizeof(QueueNode));

    if (node == NULL) {
        return -1;
    }

    node->data = value;
    node->next = NULL;

    if (q->tail == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }

    q->size++;

    return 0;
}

void* queue_pop(Queue* q) {
    if (q == NULL || q->head == NULL || q->alloc == NULL || q->alloc->free == NULL) {
        return NULL;
    }

    QueueNode* temp = q->head;
    void* value = temp->data;

    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    q->alloc->free(q->alloc, temp);
    q->size--;

    return value;
}

void* queue_peek(Queue* q) {
    if (q == NULL || q->head == NULL) {
        return NULL;
    }

    return q->head->data;
}

int queue_is_empty(Queue* q) {
    if (q == NULL || q->size == 0) {
        return 1;
    }

    return 0;
}


