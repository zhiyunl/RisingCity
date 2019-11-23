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
//    mhNode(int i, int i1, int i2);
    mhNode() = default;

    int tt;
    int et;
    int bNum; // the only key to check a node
};

class MinHeap {

public:
    bool debug;
    int len; // point to last element
    mhNode heap[2000];

    int init(mhNode *arr);

    mhNode *insert(mhNode n);

    mhNode *heapifyUp();

    mhNode *heapifyDn();

//    mhNode removeMin(RBTree* &n);// no need to keep pointer, just value
    void removeMin();

//    int decreaseKey(int index, int d);
    void mhRrintNode(int index);

    void printHeap();

    static int pow(int base, int exp);

    void switchRoot(mhNode *p); // switch root with kids that has same et, decide by rbTree buildingNum
#define lChild(heap, index)  (heap[n*2])
#define rChild(heap, index)  (heap[n*2+1])
#define mhParent(heap, index)  (heap[n/2])
};


#endif //RISINGCITY_MINHEAP_H
