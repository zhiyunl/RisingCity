/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:08:53
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:40
 * @Description: 
 */
#include <iostream>
#include <cmath>
#include "MinHeap.h"

/*
 * use array to represent min heap
 * */
int MinHeap::init(int *arr) {
    /*
     * since min binary heap is a complete binary tree,
     * so we just use sequential order for its storage*/
    int i = 0;
    heap = arr;
    while (arr[++i] != 0);
    len = i - 1;// len point to last node.
    if (this->debug) printHeap();
    return 0;
}

int MinHeap::insert(int key) {
    /*
     * insert next to last node, heapify by compare it with parents,
     * swap if needed,
     * recursively*/
    // get where is last node
//    len=sizeof(heap)/sizeof(heap[0]); // not working for pointer
//    len=0;
//    for (int i = 0; heap[i] ; ++i) {
//        len=i+1;
//    }
    heap[++len] = key;
    heapify(len);
    if (this->debug) printHeap();
    return 0;
}

int MinHeap::heapify(int index) {
    /* also called Percolation Up
     * compare parent and x, if parent is smaller, done
     * else, swap p_x and x
     * continuously until reach root or first node that satisfy 1st condition*/
    int p_x;
    p_x = index / 2;
    while (heap[p_x] > heap[index]) {
        // swap
        int tmp;
        tmp = heap[p_x];
        heap[p_x] = heap[index];
        heap[index] = tmp;
        // update parent and x
        p_x /= 2;
        index /= 2;
    }
    if (this->debug) printHeap();
    return 0;
}

int MinHeap::heapify() {
    /* also called Percolation Down
     * get min of left child and right child,
     * if parent is smaller than min, done
     * else, swap parent and min node
     * continuously until reach leaf or first node that satisfy condition*/
    int index = 1;
    int base = heap[1];
    while (true) {
        index *= 2;
        index += (heap[index] < heap[index + 1]) ? 0 : 1; // choose left or right child
        if (heap[index] == 0 || base < heap[index]) {
            // stop when reach leaf or insert node > children
            heap[index / 2] = base;
            break;
        } else heap[index / 2] = heap[index];
    }
    if (this->debug) printHeap();
    return 0;
}

int MinHeap::removeMin() {
    /*
     * remove root node,
     * percolation down using last node*/
    int min = heap[1];
    heap[1] = heap[len];
    heap[len] = 0;
    heapify();// percolation down
    len--;
    if (this->debug) printHeap();
    return min;
}

int MinHeap::decreaseKey(int index, int d) {
    heap[index] -= d;
    // TODO finish decrease Key
//   need to check if child is smaller than parent
//   if so, need a percolation up

    return heap[index];
}

void MinHeap::printHeap() {
    int i = 1;
    int level = 1;
    // first element is not used!
    std::cout << std::endl << "---------" << std::endl;
    while (heap[i]) { //complete binary tree
        // first row is 1 2>=2^1
        // second row is 2 3 4>=2^2
        // third row is 4 5 6 7 8>=2^3
        // ...
        if (i >= pow(2, level)) {
            std::cout << std::endl;
            level++;
        }
        std::cout << heap[i++] << "\t";
    }
    std::cout << std::endl << "---------" << std::endl;
}

