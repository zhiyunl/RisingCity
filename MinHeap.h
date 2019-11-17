/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:08:53
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:33
 * @Description: 
 */


#ifndef RISINGCITY_MINHEAP_H
#define RISINGCITY_MINHEAP_H


class MinHeap {

public:
    int len;
    int *heap;

    int init(int *arr);

    int insert(int key);

    int heapify(int index);

    int heapify();

    int removeMin();

    int decreaseKey(int index, int d);

    void printHeap();
//    int
};


#endif //RISINGCITY_MINHEAP_H
