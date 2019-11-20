//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_MYQUEUE_H
#define RISINGCITY_MYQUEUE_H

typedef int ELEMENTTYPE;
#define MAX_Q_SIZE 1024
struct qNode {
    ELEMENTTYPE key;
    ELEMENTTYPE *left;// record head
    ELEMENTTYPE *right;// record tail
};

class MyQueue {
public:
    qNode *queue;

    struct qNode **createQ(qNode *head, qNode *tail);

    void enQ(qNode **queue, qNode *rear, qNode *new_node);

    struct node *deQ(struct node **queue, qNode *head);
};


#endif //RISINGCITY_MYQUEUE_H
