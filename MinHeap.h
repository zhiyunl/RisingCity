//
// Created by zhiyunl on 10/21/19.
//

#ifndef RISINGCITY_MINHEAP_H
#define RISINGCITY_MINHEAP_H


class MinHeap {

public:
    int len;
    int *heap;
    int init(int *arr);
    int insert(int x);
    int heapify(int index);
    int heapify();
    int removeMin();
    int decreaseKey(int index,int d);
//    int
};


#endif //RISINGCITY_MINHEAP_H
