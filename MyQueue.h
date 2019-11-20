//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_MYQUEUE_H
#define RISINGCITY_MYQUEUE_H

typedef int ELEMENTTYPE;
#define MAX_Q_SIZE 1024
struct qNode {
    ELEMENTTYPE key[MAX_Q_SIZE];
    ELEMENTTYPE head;// record head
    ELEMENTTYPE tail;// record tail
};

class MyQueue {
public:
    qNode queue;

    qNode *createQ();

    ELEMENTTYPE deQ();

    void enQ(ELEMENTTYPE key);
};


#endif //RISINGCITY_MYQUEUE_H
