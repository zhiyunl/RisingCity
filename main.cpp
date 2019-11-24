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
#include "RBTree.h"

typedef mhNode KEYTYPE;
using namespace std;
enum State {
    FAIL, INIT, HASCMD, INSERT_J, PICK_J, WORK1DAY, REINSERT, END_J, DONE
};
enum DEBUG {
    NODEBUG, PRINTDEBUG, LEVEL1, LEVEL2, LEVEL3
};
int picker = 1; // index for the new worker node in minHeap, default = root node
// a var save for mhNode currently working on
//rbNode worker;// not pointer because it's already remove from rbtree and minheap
mhNode *workermhn = nullptr; // save worker.key
int global = 0; //global timer
auto myTree = new RBTree(); // rbTree
MinHeap myheap{}; //minHeap
FileParser myParser; // process input and convert to cmd
DEBUG debug = NODEBUG; // debug

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
    if (myheap.len > 0) { // has building waiting in heap
        picker = 1; // init picker
        // o(log), pick smallest bNum and smallest et in heap
        pickRecusive(1); // pick start from root=1
        // TODO don't remove rbNode until finish
        // myTree->rbRemove(workermhn); // remove from rbtree
        // switch with root then do remove min
        myheap.switchRoot(&myheap.heap[picker]);// changed into delete min, O(1)
        workermhn = &myheap.heap[1];// already at root
        // keep min on heap, after work, remove and reinsert heapify
//        myheap.removeMin(); // worker saves the mhNode
    } else picker = 0; // no pick
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
    cout << "(" << mhn->bNum << "," << mhn->et << "," << mhn->tt << ")";
}

void printNone() {
    cout << "(0,0,0)" << endl;
}

void printFinish(mhNode *mhn) {

    cout << "(" << mhn->bNum << "," << global << ")" << endl;
}

void printFailure() {
    cout << "failed" << endl;
    throw std::exception();
}

int newInsert = 0;// at most five, could be five insert during the currently working days.
void insertCMD(Instruction *ins) {
    mhNode *mhn = fromIns2Heap(ins);
    // first insert heap, get pointer of newly inserted node
// TODO when insert same building num, should exit. handled in red-black tree
//    if (myTree->rbSearch(mhn, 0) != nullptr) {
//        cout << "error, same building num" << endl;
//        return;
//    }
    // only  insert like a normal heap, need heapifyUp
    mhn = myheap.insert(*mhn);
    // manage pointer in rbInsert
    // insert the pointer into rbtree
    myTree->rbInsert(mhn);
    newInsert++;
    if (workdays == 0) {
        // no currently working projects, just insert and heapify
        myheap.heapifyUp(myheap.len);
        newInsert--;
    }
    // pointer from rbNode to mhNode is maintained
}

void printBuilding(Instruction *ins) {
    // handle two kind print function
    if (ins->type == PRINT) { ;
        if (debug) cout << "print 1 building:\n";
        auto p = myTree->rbSearch(new mhNode{1, 0, ins->para1}, 0);
        // search using building num in red black tree
        if (p != nullptr) {
            if (debug) cout << "PrintBuilding ";
            printFinish(p->key);
        } else printNone();
    } else if (ins->type == PRINTRANGE) {
        // if if not found, return right nearest node
        // not working
        auto p = myTree->rbSearch(new mhNode{1, 0, ins->para1}, 1);
        // search using building num in red black tree
        if (p == nullptr) printNone();
        else if (debug) cout << "PrintBuildings ";
        // TODO don't change into in-order traversal, debug this
        while (p != nullptr && p->key->bNum <= ins->para2) {// not null and less than bNum2
            printOne(p->key);
            p = myTree->postNode(p);// find next
            if (p != nullptr && p->key->bNum <= ins->para2) cout << ",";
            else cout << endl;
        }
    } else return;
}

void reinsert(mhNode *mhn) {
    // only  insert like a normal heap, need heapifyUp
    // just a decrease key,heapify down
    // pointer is already managed during
    // TODO no need
//    myheap.removeMin(); // save removed node
//    mhn = myheap.insert(*mhn);
    // manage pointer in rbInsert
    // insert the pointer into rbtree
//    myTree->rbInsert(mhn);
//    myheap.heapifyUp();
    myheap.heapifyDn();
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
                if (debug >= LEVEL1) {
                    if (next == nullptr) cout << "***no element***" << std::endl;
                    else cout << "loaded next" << endl;
                }
                state = INSERT_J;
                break;
            case INSERT_J: // judge whether insert the cmd into tree
                if (next != nullptr && next->time <= global) {
                    if (next->type == INSERT)
                        insertCMD(next);// TODO print should be the beginning of the day, finish should be end
                    else printBuilding(next); //command to be finished today won't print out
                    state = HASCMD;
                } else state = PICK_J;
                break;
            case PICK_J: // judge whether pick a new instruction from the tree
                if (workermhn == nullptr) workPicker();
                // verify picker
                if (picker > 0) state = WORK1DAY;
                else {// no building waiting in heap,
                    global++;//increment global timer
                    state = INSERT_J; // go back to wait for cmd
                }
                break;
            case WORK1DAY:
                workOn(workermhn);
                // before is under global=0
                // TODO global timer ++ after this line, so this separates the day
                //  first insert day is 0, means day one, time already pass 1,

                if (debug >= LEVEL1) cout << "worked 1 day" << endl;
                // pare1 is building number, para2 is time
                if (workermhn == nullptr) throw exception();
                if (workermhn->et >= workermhn->tt) { //judge whether it's finished ahead
                    if (debug) {
                        if (workdays == 5) cout << "finished exact 5 days" << endl;
                        else cout << "finished ahead" << endl;
                    }
                    printFinish(workermhn);
                    // TODO, after finish, remove worker from heap and rbtree
                    myTree->rbRemove(workermhn);
                    myheap.removeMin();// actually we make sure worker is at min
                    // clear workermhn later
                    workdays = 0;
                    state = END_J;
                } else if (workdays >= 5) { //finish 5 days
                    if (debug) cout << "finished 5 days,put back bNum=" << workermhn->bNum << endl;
                    workdays = 0;
                    state = REINSERT;
                } else state = INSERT_J; //
                break;
            case REINSERT:
                // TODO remove from heap, reinsert, heapify
                //  don't remove and insert, just heapify
                reinsert(workermhn);// actually decreaseKey + heapify Down
                for (; newInsert > 0; newInsert--) { // handle up to five new insert during the middle of construction
                    // heapify new inserted node using a fifo scheme.
                    myheap.heapifyUp(myheap.len - newInsert + 1);// for the new inserted node in the middle
                }
                workermhn = nullptr; // clear workermhn
                state = INSERT_J;
                break;
            case END_J:
                if (endJudge()) state = DONE;
                else {
                    workermhn = nullptr;
                    state = INSERT_J;
                }
                break;
            case DONE:
//                printFinish(workermhn);
                return true;
        }
    }
}

void initMain() {
    switch (debug) {
        case LEVEL3:
            myheap.debug = myTree->debug = myParser.debug = true;
            break;
        case LEVEL2:
            myParser.debug = myTree->debug = true;
            myheap.debug = false;
            break;
        case LEVEL1:
            myParser.debug = true;
            myTree->debug = myheap.debug = false;
            break;
        case PRINTDEBUG:
            myParser.debug = myTree->debug = myheap.debug = false;
            break;
        default:;
        case NODEBUG:
            myParser.debug = myTree->debug = myheap.debug = false;
            break;
    }
}

ofstream out("output_file.txt");
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
    if (debug == NODEBUG) {
        // redirect file to output.txt
        cout.rdbuf(out.rdbuf());
    }
    initMain();
    if (!myParser.readFile(filename)) cout << "fail" << endl;
    else {

        timeLine();
    }
//    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    return 0;
}
