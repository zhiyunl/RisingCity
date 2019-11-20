//
// Created by zhiyunl on 11/19/19.
//

#include <malloc.h>
#include "MyQueue.h"

// TODO a general qNode

qNode *MyQueue::deQ(MyQueue **queue, qNode *head) {
    (*head)++;
    return queue[*head - 1];
}

void MyQueue::enQ(qNode **queue, qNode *rear, qNode *new_node) {
    queue[*rear] = new_node;
    (*rear)++;
}

struct qNode **MyQueue::createQ(qNode *head, qNode *tail) {
    qNode **queue =
            (struct qNode **) malloc(sizeof(struct qNode *) * MAX_Q_SIZE);
    *head = *tail = 0;
    return queue;
}
