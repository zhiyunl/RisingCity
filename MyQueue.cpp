//
// Created by zhiyunl on 11/19/19.
//

#include "MyQueue.h"
#include "FileParser.h"

// a general qNode API is created
template
class MyQueue<int>;

template
class MyQueue<Instruction>;

// circular list
// [  head=first element tail=last element+1         ]
// len = tail-head
// store into tail%MAX_Q_SIZE
// fetch head
template<class QUEUETYPE>
void MyQueue<QUEUETYPE>::createQ() {
    // this->queue;
//    head = 0;
//    tail = 0;
    ;

}

template<class QUEUETYPE>
QUEUETYPE *MyQueue<QUEUETYPE>::deQ() {
    if (head >= tail) {
        return nullptr;
    } else return &queue[head++];
}

template<class QUEUETYPE>
void MyQueue<QUEUETYPE>::enQ(QUEUETYPE key) {
    if (qLen() < MAX_Q_SIZE) {
        queue[tail++ % MAX_Q_SIZE] = key;
//        memcpy(&key, &queue[tail++ % MAX_Q_SIZE], sizeof(key));
    }
}

template<class QUEUETYPE>
int MyQueue<QUEUETYPE>::qLen() {
    return tail - head;
}

//template<class QUEUETYPE>
//MyQueue<QUEUETYPE>::MyQueue() {
//    queue=new QUEUETYPE[MAX_Q_SIZE]{};
//    head=0;
//    tail=0;
//}

