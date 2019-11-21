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
    MyQueue<int> q{};
    q.createQ();
    for (int i = 0; i < 20; i++) {
//        auto *n = new Instruction(i, INSERT, i * 10);
        q.enQ(i);
    }
//    cout << q.deQ() << endl;
//    q.enQ();
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

// TODO pick a node to work on
Node *workPicker() {
    // choose building from min heap and red black tree
    Node *node = new Node(1, RED, nullptr, nullptr, nullptr, 1);
    return node;
}

// TODO modify nodes
int days = 0;

int workOn(Node *n) {
    // do work here
    // deduct at max five days, and return days
    // modify minheap and red black tree
    days += 5;
    return days;
}


int global = 0;

void printFinish() {
    cout << "Total Time is: " << global << endl;
}

void printFailure() {
    ;
}

enum State {
    INIT, LOAD, WORK, DONE, FAIL
};

bool timeLine() {
    // manage using finite state machine
    Instruction *next{};
    int cnt = 0;
    enum State state = INIT;
    while (true) {
        switch (state) {
            case INIT://init state
                cnt = parser.cmdTotal();
                if (cnt) {
                    cout << "successfully loaded " << cnt << " instructions" << endl;
                    state = WORK;
                } else {
                    cout << "No input command" << endl;
                    state = FAIL;
                }
                break;
                //spin in load and work
            case LOAD:
                if (parser.hasCmd()) *next = parser.nextCmd();
//                if()
                state = WORK;
                break;
            case WORK:
                if (cnt > 0) {
                    global += workOn(workPicker());
                    cnt--;
                    cout << "Worked 5 days" << endl;
                    state = LOAD;
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
    parser.debug = true;
    if (!parser.readFile(filename)) cout << "fail" << endl;
    else {
//        minHeapTest();
//        RBTreeTest();
        queueTest();
//        timeLine();
    }

    return 0;
}