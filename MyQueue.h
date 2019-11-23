//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_MYQUEUE_H
#define RISINGCITY_MYQUEUE_H

//typedef int QUEUETYPE;
#define MAX_Q_SIZE 2000

template<class QUEUETYPE>
class MyQueue {
public:
    QUEUETYPE queue[MAX_Q_SIZE];
//    MyQueue();
    int head;// record head

    int tail;// record tail

    void createQ();

    QUEUETYPE *deQ();

    void enQ(QUEUETYPE key);

    int qLen();
};


#endif //RISINGCITY_MYQUEUE_H
