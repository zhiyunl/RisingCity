/*
 * @Author: zhiyunl
 * @Date: 2019-11-19 22:21:58
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-27 22:26:08
 * @Description: 
 */


#ifndef RISINGCITY_MYQUEUE_H
#define RISINGCITY_MYQUEUE_H

//typedef int QUEUETYPE;
#define MAX_Q_SIZE 2000

template<class QUEUETYPE>
class MyQueue {
private:
    QUEUETYPE queue[MAX_Q_SIZE];
    int head;// record head
    int tail;// record tail
public:
    void createQ();// create an empty queue
    QUEUETYPE *deQ();// dequeue operation
    void enQ(QUEUETYPE key);// enqueue operation
    int qLen();// reuturn queue length
};


#endif //RISINGCITY_MYQUEUE_H
