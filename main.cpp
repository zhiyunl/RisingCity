/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:09:14
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:16
 * @Description: 
 */

#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "FileParser.h"
#include "MyQueue.h"
#include "RBTree.h"

typedef mhNode KEYTYPE;
using namespace std;

int picker = 1; // index for the new worker node in minHeap, default = root node
// a var save for mhNode currently working on
//rbNode worker;// not pointer because it's already remove from rbtree and minheap
mhNode workermhn{0, 0, 0}; // save worker.key
int debug = false; // debug
int global = 0; //global timer
auto myTree = new RBTree(); // rbTree
MinHeap myheap{}; //minHeap
FileParser myParser; // process input and convert to cmd

enum State {
    FAIL, INIT, HASCMD, INSERT_J, PICK_J, WORK1DAY, REINSERT, END_J, DONE
};

mhNode *fromIns2Heap(Instruction *ins) {
    // parser Instruction make it mhNode
    if (ins->type == INSERT) {
        return new mhNode{ins->para2, 0, ins->para1};
    }
    return nullptr;
}

void pickRecusive(int i) {
    // pre order
    if (myheap.heap[picker].bNum > myheap.heap[i].bNum) picker = i;// pick smallest building num
    if (i * 2 > myheap.len) {
        return;
    } else if (myheap.heap[i].et == myheap.heap[i * 2].et)
        pickRecusive(i * 2);
    if (i * 2 + 1 > myheap.len) {
        return;
    } else if (myheap.heap[i].et == myheap.heap[i * 2 + 1].et)
        pickRecusive(i * 2 + 1);
}

// TODO pick a node to work on
void workPicker() {
    // choose building from min heap and red black tree
//    Instruction *node = new Node(1, RED, nullptr, nullptr, nullptr, 1);
//    Instruction *node{};
    picker = 1; // init picker
    pickRecusive(1); // pick start from root=1
    // switch with root then do remove min
    // TODO pointers
    // get rbn pointer by search for bNum
    // back it up in worker; mhNode in workermhn
    workermhn = myheap.heap[picker]; // this is same as memcpy
//    worker = *myTree->rbRemove(&myheap.heap[picker]);
    myTree->rbRemove(&myheap.heap[picker]);
//    worker.key = &workermhn; // pointer changed to local var
    myheap.switchRoot(&myheap.heap[picker]);// changed into delete min
    myheap.removeMin(); // worker saves the mhNode
}

int workdays = 0; // count for at most 5 days

// TODO modify nodes
void workOn(mhNode *mhn) {
    // do work here
    // deduct at max five days, and return days
    // modify minheap and red black tree
    mhn->et += 1; // excuted time increment
    workdays++; // counter increment
    global++; //
}

void printOne(mhNode *mhn) {
    cout << "(" << mhn->bNum << "," << global << ")";
}

void printFinish(mhNode *mhn) {
    cout << "(" << mhn->bNum << "," << global << ")" << endl;
}

void printFailure() {
    cout << "failed" << endl;
    throw;
}

void insertCMD(Instruction *ins) {
    mhNode *mhn = fromIns2Heap(ins);
    // first insert heap, get pointer of newly inserted node
    if (myTree->rbSearch(mhn, 0) != nullptr) {
        cout << "error, same building num" << endl;
        return;
    }
    // only  insert like a normal heap, need heapifyUp
    mhn = myheap.insert(*mhn);
    // manage pointer in rbInsert
    // insert the pointer into rbtree
    myTree->rbInsert(mhn);
    myheap.heapifyUp();
    // pointer from rbNode to mhNode is maintained
}

void printBuilding(Instruction *ins) {
    // handle two kind print function
    if (ins->type == PRINT) { ;
        cout << "print 1 building:\n";
        auto p = myTree->rbSearch(new mhNode{1, 0, ins->para1}, 0);
        // search using building num in red black tree
        if (p != nullptr) {
            if (debug) cout << "PrintBuilding ";
            printFinish(p->key);
        } else {
            cout << "No such building" << endl;
        }
    } else if (ins->type == PRINTRANGE) {
        // if if not found, return right nearest node
        // not working
        auto p = myTree->rbSearch(new mhNode{1, 0, ins->para1}, 1);
        // search using building num in red black tree
        if (p == nullptr) cout << "No such building" << endl;
        else if (debug) cout << "PrintBuildings ";
        while (p != nullptr && p->key->bNum <= ins->para2) {// not null and less than bNum2
            printOne(p->key);
            p = myTree->postNode(p);// find next
            if (p != nullptr && p->key->bNum <= ins->para2) cout << ",";
            else cout << endl;
        }
    } else return;
}

void reinsert(mhNode *mhn) {
    if (myTree->rbSearch(mhn, 0) != nullptr) {
        cout << "error, same building num" << endl;
        return;
    }
    // only  insert like a normal heap, need heapifyUp
    mhn = myheap.insert(*mhn);
    // manage pointer in rbInsert
    // insert the pointer into rbtree
    myTree->rbInsert(mhn);
    myheap.heapifyUp();
    // pointer from rbNode to mhNode is maintained
}

bool endJudge() {
    return !myParser.hasCmd() && myheap.len <= 0;
}

bool timeLine() {
    // manage using finite state machine
    Instruction *next = nullptr;
    enum State state = INIT;
    while (true) {
        switch (state) {
            case FAIL:
                printFailure();
                return false;
            case INIT:
                if (myParser.hasCmd()) {
                    if (debug) cout << "successfully loaded " << myParser.cmdTotal() << " instructions" << endl;
                    state = HASCMD;
                } else {
                    cout << "No input command" << endl;
                    state = FAIL;
                }
                break;
            case HASCMD:
                next = myParser.nextCmd();
                if (debug) {
                    if (next == nullptr) cout << "***no element***" << std::endl;
                    else cout << "loaded next" << endl;
                }
                state = INSERT_J;
                break;
            case INSERT_J: // judge whether insert the cmd into tree
                if (next != nullptr && next->time <= global) {
                    if (next->type == INSERT) insertCMD(next);
                    else printBuilding(next);
                    state = HASCMD;
                } else state = PICK_J;
                break;
            case PICK_J: // judge whether pick a new instruction from the tree
                if (workermhn.bNum == 0) workPicker();
                state = WORK1DAY;
                break;
            case WORK1DAY:
                workOn(&workermhn);
                if (debug) cout << "worked 1 day" << endl;
                // pare1 is building number, para2 is time
                if (workermhn.et >= workermhn.tt) { //judge whether it's finished ahead
                    if (debug) {
                        if (workdays == 5) cout << "finished exact 5 days" << endl;
                        else cout << "finished ahead" << endl;
                    }
                    printFinish(&workermhn);
                    workdays = 0;
                    state = END_J;
                } else if (workdays >= 5) { //finish 5 days
                    if (debug) cout << "finished 5 days,put back" << endl;
                    workdays = 0;
                    state = REINSERT;
                } else state = INSERT_J; //
                break;
            case REINSERT:
                reinsert(&workermhn);
                workermhn.bNum = 0; // clear workermhn
                state = INSERT_J;
                break;
            case END_J:
                if (endJudge()) state = DONE;
                else {
                    workermhn.bNum = 0;
                    state = INSERT_J;
                }
                break;
            case DONE:
//                printFinish(&workermhn);
                return true;
        }
    }
}

void initMain() {
    myheap.debug = debug;
    myTree->debug = debug;
}

ofstream out("output.txt");
auto *coutbuf = cout.rdbuf();

int main(int argc, char const *argv[]) {
    /*
     * Must take in the file_name as argument
     * Must use Min Heap to store, could be a array
     * Must use Red-Black Tree to manage, using node
     * */
    // don't use 1st element to simplify calculation
    // used for in-place minHeap
    string filename = argv[1];
    myParser.debug = debug;
    if (!debug) {
        // redirect file to output.txt
        cout.rdbuf(out.rdbuf());
    }
    if (!myParser.readFile(filename)) cout << "fail" << endl;
    else {
        initMain();
        timeLine();
    }
//    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    return 0;
}

//int RBTreeTest() {
//    cout << "\n-------------Start Red Black Tree Test----------" << endl;
//    KEYTYPE rb[] = {5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12};
//    int ilen = sizeof(rb) / sizeof(rb[0]);
//
//    KEYTYPE *node = nullptr;
////    auto tree = new RBTree<int>();
//    myTree->debug = true;
//    for (int i = 0; i < ilen; i++) {
////        tree->rbInsert(rb[i]);
////        node=new Instruction(i,INSERT,i*2,rb[i]);
//        node = new KEYTYPE{i * 20, 0, i * 5};
//        myTree->rbInsert(node);
////        cout << "== insert: " << rb[i] << endl;
//        if (myTree->debug) {
//            cout << "== result " << endl;
//            myTree->print();
//            myTree->rbTraverse();
//            cout << endl;
//        }
//    }
//    cout << "==final result== " << endl;
//    myTree->print();
////    tree->rbSearch(1);
//    myTree->rbRemove(node);
//    myTree->print();
//    return 1;
//}

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