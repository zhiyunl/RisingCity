//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_MYQUEUE_H
#define RISINGCITY_MYQUEUE_H

#define MAX_Q_SIZE 1024
struct queue {
    int data;
    struct node *left;
    struct node *right;
};

class MyQueue {
public:
    struct node **createQueue(int *front, int *rear);

    void enQueue(struct node **queue, int *rear, struct node *new_node);

    struct node *deQueue(struct node **queue, int *front);
};


#endif //RISINGCITY_MYQUEUE_H
