//
// Created by zhiyunl on 11/19/19.
//

#include <malloc.h>
#include "MyQueue.h"

// TODO a general queue
/*UTILITY FUNCTIONS*/
struct node **MyQueue::createQueue(int *front, int *rear) {
    struct node **queue =
            (struct node **) malloc(sizeof(struct node *) * MAX_Q_SIZE);

    *front = *rear = 0;
    return queue;
}

void MyQueue::enQueue(struct node **queue, int *rear, struct node *new_node) {
    queue[*rear] = new_node;
    (*rear)++;
}

struct node *MyQueue::deQueue(struct node **queue, int *front) {
    (*front)++;
    return queue[*front - 1];
}