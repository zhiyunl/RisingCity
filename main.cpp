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
FileParser parser;
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

typedef rbNode<int> Node;

Node *workPicker() {
    // choose building from min heap and red black tree
    Node *node = new Node(1, RED, nullptr, nullptr, nullptr, 1);
    return node;
}


int workOn(Node *n) {
    // do work here
    // deduct at max five days, and return days
    // modify minheap and red black tree
    int days = 0;
    days += 5;
    return days;
}

enum State {
    INIT, WORK, DONE, FAIL
};


void printFinish() {
    ;
}

void printFailure() {
    ;
}

bool timeLine() {
    // manage using finite state machine
    int global = 0;
    int cnt = 0;
    enum State state = INIT;
    while (true) {
        switch (state) {
            case INIT://init state
                cnt = parser.loadCmd(cnt);
                if (cnt) {
                    cout << "successfully loaded " << cnt << " instructions" << endl;
                    state = WORK;
                } else {
                    cout << "No input command" << endl;
                    state = FAIL;
                }
                break;
            case WORK://spin in WORK
                if (cnt > 0) {
                    global += workOn(workPicker());
                    cnt--;
                    cout << "Worked 5 days" << endl;
                } else state = DONE;
                break;
            case DONE:
                printFinish();
                return true;
            case FAIL:
                printFailure();
                return false;
        }
    }
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

    if (!parser.readFile(filename)) cout << "fail" << endl;
    else {
//        minHeapTest();
//        RBTreeTest();
//    queueTest();
        timeLine();
    }

    return 0;
}