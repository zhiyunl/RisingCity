/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:09:14
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:16
 * @Description: 
 */

#include <iostream>
#include "MinHeap.h"
#include "FileParser.h"
#include "MyQueue.h"
#include "RBTree.h"

typedef int KEYTYPE;
using namespace std;

// TODO combine rbNode and mhNode, using one space, manage pointers in rbtree and minheap
// {color, key, }


int queueTest() {
    MyQueue q{};
    q.createQ();
    for (int i = 0; i < 20; i++) q.enQ(i);
    cout << q.deQ() << endl;
    q.enQ(1);
    return 1;
}

int minHeapTest() {
    KEYTYPE arr[2001] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "\n-------------Start Min Heap Test----------" << endl;
    MinHeap myheap{};
    myheap.debug = true;
    myheap.init(arr); // in-place modify
    myheap.insert(10);
    myheap.insert(11);
    myheap.insert(1);
    myheap.insert(4);
    cout << "min is removed!:" << myheap.removeMin() << endl;
    myheap.printHeap();
    return 1;
}

// TODO complete test
int RBTreeTest() {
    cout << "\n-------------Start Red Black Tree Test----------" << endl;
    KEYTYPE rb[] = {5, 1, 2, 3, 4, 6, 7, 8};
    int ilen = sizeof(rb) / sizeof(rb[0]);
    auto *tree = new RBTree<int>();
    tree->debug = false;
    for (int i = 0; i < ilen; i++) {
        tree->rbInsert(rb[i]);
        cout << "== insert: " << rb[i] << endl;
        if (tree->debug) {
            cout << "== result " << endl;
            tree->print();
            tree->rbTraverse();
            cout << endl;
        }
    }
    cout << "==final result== " << endl;
    tree->print();
    return 1;
}

int main(int argc, char const *argv[]) {
    /*
     * Must take in the file_name as argument
     * Must use Min Heap to store, could be a array
     * Must use Red-Black Tree to manage, using node
     * */
    // don't use 1st element to simplify calculation
    // used for in-place minHeap

    string filename = argv[1];
    FileParser parser;
    parser.readFile(filename);
    minHeapTest();
    RBTreeTest();
//    queueTest();
    return 0;
}