/*
 * @Author: zhiyunl
 * @Date: 2019-11-19 02:12:21
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-27 22:25:59
 * @Description: 
 */

#include "MyQueue.h"
#include "FileParser.h"

// when using  , compiler generate class automatically
// possible type of RBKEY is listed below,
// otherwise, there will be error
template
class MyQueue<int>;

template
class MyQueue<Instruction>;

//int queueTest() {
//    MyQueue<int> q{};
//    q.createQ();
//    for (int i = 0; i < 20; i++) {
////        auto *n = new Instruction(i, INSERT, i * 10);
//        q.enQ(i);
//    }
////    cout << q.deQ() << endl;
////    q.enQ();
//    return 1;
//}

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

