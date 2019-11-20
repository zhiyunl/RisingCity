//
// Created by zhiyunl on 11/19/19.
//

#include "MyQueue.h"
#include <iostream>

// TODO a general qNode
// circular list
// [  head=first element tail=last element+1         ]
// len = tail-head
// store into tail%MAX_Q_SIZE
// fetch head
qNode *MyQueue::createQ() {
    // this->queue;
    queue.head = queue.tail = 0;
    return &queue;
}

ELEMENTTYPE MyQueue::deQ() {
    if (queue.head >= queue.tail) {
        std::cout << "***no element***" << std::endl;
        throw std::exception();
    }
    return queue.key[queue.head++];
}

void MyQueue::enQ(ELEMENTTYPE key) {
    if (queue.tail - queue.head < MAX_Q_SIZE) {
        queue.key[queue.tail++ % MAX_Q_SIZE] = key;
    }
}

