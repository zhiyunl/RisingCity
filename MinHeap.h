/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:08:53
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:33
 * @Description: 
 */


#ifndef RISINGCITY_MINHEAP_H
#define RISINGCITY_MINHEAP_H

#include "RBTree.h"

struct mhNode {
    mhNode() = default;

    int tt;// total time
    int et;//executed time
    int bNum; // building number
    rbNode *rbn; //points to rbNode
};

class MinHeap {
public:
    bool debug = false;

    int len = 0; // indicates heap length, point to last element
    mhNode heap[2001]{};// don't use first node.
    int init(mhNode *arr); // init minheap using array
    // insert node into heap
    mhNode *insert(mhNode *n);

    // heapify upwards, after insert
    mhNode *heapifyUp(int mylen);

    // heapify downwards, after remove
    mhNode *heapifyDn();

    // remove min element from heap
    void removeMin();

    // print out the node by index
    void mhPrintNode(int index);

    // print whole heap
    void printHeap();

    // cannot use math.pow, so created pow from scratch
    static int pow(int base, int exp);

    // switch the node p with root
    void switchRoot(mhNode *p);
#define lChild(heap, index)  (heap[n*2])
#define rChild(heap, index)  (heap[n*2+1])
#define mhParent(heap, index)  (heap[n/2])
};


#endif //RISINGCITY_MINHEAP_H
