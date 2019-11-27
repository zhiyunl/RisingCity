/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:08:53
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:40
 * @Description: 
 */
#include <iostream>
#include "MinHeap.h"

using namespace std;

//int minHeapTest() {
//    KEYTYPE arr[20] = {2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
//    cout << "\n-------------Start Min Heap Test----------" << endl;
//    myheap.debug = true;
//    myheap.init(arr); // in-place modify
//    myheap.removeMin();
//    myheap.insert({20, 30, 40});
////    myheap.printHeap();
//    return 1;
//}

/*
 * use array to represent min heap
 * */
int MinHeap::init(mhNode *arr) {
    /*
     * since min binary heap is a complete binary tree,
     * so we just use sequential order for its storage*/
    while (arr[len].bNum != 0) {
        // heap start from 1 not 0;
        //heap[len+1] = arr[len];
        insert(&arr[len]);
//        len++; // handled in insert
    }
// last element
//    if (debug) printHeap();
    return 0;
}

mhNode *MinHeap::insert(mhNode *n) {
    /*
     * insert next to last node, heapify by compare it with parents,
     * swap if needed,
     * recursively*/
    // get where is last node
    if (debug) cout << "--insert----" << endl;
    //TODO modify heap - rbtree pointer outside
    heap[++len] = *n;
    if (debug) {
        cout << "before heapify:" << endl;
        printHeap();
    }
    // TODO do heapify outside
//    p = heapifyUp();
//    cout << p << endl;
    return &heap[len];
}

mhNode *MinHeap::heapifyUp(int mylen) {
    /* also called Percolation Up
     * compare parent and x, if parent is smaller, done
     * else, swap p_x and x
     * continuously until reach root or first node that satisfy 1st condition*/
    static mhNode base;
    int index = mylen;
    int p_x = index / 2;
    base = heap[mylen];
    while (true) {
        if (p_x > 0) {
            if (base.et > heap[p_x].et) {
                // at least child of root, stop when insert node > parent
                base.rbn->key = &heap[index];
                heap[index] = base;
//                index=p_x; // for return
                break;
            } else { // pull parent node down
                heap[p_x].rbn->key = &heap[index];
                heap[index] = heap[p_x];
            }
            index = p_x;
            p_x /= 2;
        } else {
            //TODO before do this, modify corresponding rbNode pointer
            base.rbn->key = &heap[index];
            heap[index] = base;
            break;
        }
    }

    // by the time it breaks, index is the new insert final pos
    if (debug) {
        cout << "after hepifyup:" << endl;
        printHeap();
    }
    return &heap[index];// return pointer to this node
}

mhNode *MinHeap::heapifyDn() {
    /* also called Percolation Down
     * get min of left child and right child,
     * if parent is smaller than min, done
     * else, swap parent and min node
     * continuously until reach leaf or first node that satisfy condition*/
    static mhNode base;
    int index = 1;
    int x_child = index * 2;
    base = heap[1];// start from root
    while (true) {
        if (x_child <= len) {
            // right child could be zero,
            if (heap[x_child + 1].bNum != 0)
                x_child += (heap[x_child].et < heap[x_child + 1].et) ? 0 : 1; // choose left or right child
            if (heap[x_child].bNum == 0 || base.et < heap[x_child].et) {
                // stop when reach leaf or insert node < children
                base.rbn->key = &heap[index];
                heap[index] = base;
                break;
            } else {
                heap[x_child].rbn->key = &heap[index];
                heap[index] = heap[x_child];
            }
            index = x_child;
            x_child *= 2;
        } else {
            base.rbn->key = &heap[index];
            heap[index] = base;
            break;
        }
    }
    if (debug) {
        cout << "after heapify down:" << endl;
        printHeap();
    }
    return &heap[index / 2];// last new node pos
}

void MinHeap::removeMin() {
    /*
     * remove root node,
     * percolation down using last node*/
    if (debug) {
        cout << "----remove min----" << endl;
        printHeap();
    }
//    mhNode min = heap[1];
    if (len > 1) {
        heap[1] = heap[len];// replace with last key
        heap[1].rbn->key = &heap[1]; // update pointer
    }
    // delete last node
    heap[len].bNum = 0;
    heap[len].et = 0;
    heap[len].tt = 0;
    heap[len].rbn = nullptr; // clear mh - rb
    len--;
    if (len < 0) {
        throw std::exception();
    } else if (len == 0) return;
    if (debug) {
        cout << "before heapify" << endl;
        printHeap();
    }
    // handle new pointer for rbtree
    // TODO, do outside
    heapifyDn();// percolation down
//    return min;
}

//int MinHeap::decreaseKey(int index, int d) {
//    heap[index] -= d;
//    // TODO finish decrease Key
////   need to check if child is smaller than parent
////   if so, need a percolation up
//
//    return heap[index];
//}

// Exponentiation by squaring
int MinHeap::pow(int base, int exp) {
    int result = 1;
    while (true) {
        if (exp & 1) result *= base;
        exp >>= 1;
        if (!exp) break;
        base *= base;
    }
    return result;
}

void MinHeap::mhPrintNode(int index) {
    std::cout << " [" << heap[index].bNum << "," << heap[index].et << "," << heap[index].tt << "] ";
}

void MinHeap::printHeap() {
    int i = 1;
    int level = 1;
    // first element is not used!
    std::cout << "\n---------" << std::endl;
    while (heap[i].bNum) { //complete binary tree
        // first row is 1 2>=2^1
        // second row is 2 3 4>=2^2
        // third row is 4 5 6 7 8>=2^3
        // ...
        if (i >= pow(2, level)) {
            std::cout << std::endl;
            level++;
        }
        mhPrintNode(i++);
    }
    std::cout << "\n---------" << std::endl;
}

void MinHeap::switchRoot(mhNode *p) {
    // find smallest building num child that have same et with root
    // bfs traversal, just one by one
    // TODO change to not O(n), already found by picker
//    if (heap[2].bNum == 0) return;
//    for (int i = 2; i < len + 1; i++) {
//        if (heap[1].et == heap[i].et && min->bNum > heap[i].bNum) {
//            min = &heap[i];
//        }
//    }
    static mhNode q;
    // TODO pointer of picker node and root change
    if (len <= 1) { //at most 1 element
        return;
    } else {
        q = *p;
        *p = heap[1];
        heap[1] = q;
        // every node pointer to correct rbn
        // maintain rbn - heap
        p->rbn->key = p;
        heap[1].rbn->key = &heap[1];
    }

}

