//
// Created by zhiyunl on 11/24/19.
//

#include "BuildCity.h"


mhNode *BuildCity::fromIns2Heap(Instruction *ins) {
    // parser Instruction make it mhNode
    static mhNode q;
    if (ins->type == INSERT) {
        q = {ins->bNum1, 0, ins->tt_bNum2};
        return &q; //  to be delete
    }
    return nullptr;
}

void BuildCity::pickRecursive(int i) {
    // pre order
    if (myheap.heap[picker].bNum > myheap.heap[i].bNum) picker = i;// pick smallest building num
    if (i * 2 > myheap.len) {
        return;
    } else if (myheap.heap[i].et == myheap.heap[i * 2].et)
        pickRecursive(i * 2);
    if (i * 2 + 1 > myheap.len) {
        return;
    } else if (myheap.heap[i].et == myheap.heap[i * 2 + 1].et)
        pickRecursive(i * 2 + 1);
}

void BuildCity::workPicker() {
    // choose building from min heap and red black tree
    if (myheap.len > 0) { // has building waiting in heap
        picker = 1; // init picker
        // o(log), pick smallest bNum and smallest et in heap
        pickRecursive(1); // pick start from root=1
        // TODO don't remove rbNode until finish
        // myTree->rbRemove(worker); // remove from rbtree
        // switch with root then do remove min
        myheap.switchRoot(&myheap.heap[picker]);// changed into delete min, O(1)
        worker = &myheap.heap[1];// already at root
        // keep min on heap, after work, remove and reinsert heapify
//        myheap.removeMin(); // worker saves the mhNode
    } else picker = 0; // no pick
}

void BuildCity::atWork(mhNode *mhn) {
    // do work here
    // deduct at max five days, and return days
    // modify minheap and red black tree
    mhn->et += 1; // excuted time increment
    workdays++; // counter increment
    global++; //
}

void BuildCity::printOne(mhNode *mhn) {
    cout << "(" << mhn->bNum << "," << mhn->et << "," << mhn->tt << ")";
}

void BuildCity::printNone() {
    cout << "(0,0,0)" << endl;
}

void BuildCity::printFinish(mhNode *mhn) {
    cout << "(" << mhn->bNum << "," << global << ")" << endl;
}

void BuildCity::printFailure() {
    cout << "failed" << endl;
    throw std::exception();
}

void BuildCity::insertCMD(Instruction *ins) {
    static mhNode *mhn;
    mhn = fromIns2Heap(ins);
    // first insert heap, get pointer of newly inserted node
// TODO when insert same building num, should exit. handled in red-black tree
//    if (myTree->rbSearch(mhn, 0) != nullptr) {
//        cout << "error, same building num" << endl;
//        return;
//    }
    // only  insert like a normal heap, need heapifyUp
    mhn = myheap.insert(mhn);
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

bool BuildCity::printBuilding(Instruction *ins) {
    // handle two kind print function
    static mhNode q;
    q = {ins->bNum1, 0, 1};
    static rbNode *p = nullptr;
    if (ins->type == PRINT) { ;
        if (debug) cout << "print 1 building:\n";
        p = myTree->rbSearch(&q, 0);
        // search using building num in red black tree
        if (p != nullptr) {
            if (debug) cout << "PrintBuilding ";
            printFinish(p->key);
        } else printNone();
    } else if (ins->type == PRINTRANGE) {
        // if not found, return right nearest node
        // not working
        p = myTree->rbSearch(&q, 1);
        // search using building num in red black tree
        if (p == nullptr) printNone();
        else if (debug) cout << "PrintBuildings ";
        // TODO don't change into in-order traversal, debug this
        while (p != nullptr && p->key->bNum <= ins->tt_bNum2) {// not null and less than bNum2
            printOne(p->key);
            p = myTree->postNode(p);// find next
            if (p != nullptr && p->key->bNum <= ins->tt_bNum2) cout << ",";
            else cout << endl;
        }
    } else return false;
    return true;
}

void BuildCity::reinsert(mhNode *mhn) {
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

bool BuildCity::endJudge() {
    return !myParser->hasCmd() && myheap.len <= 0;
}

bool BuildCity::timeLine() {
    // manage using finite state machine
    Instruction *next = nullptr;
    enum State state = INIT;
    while (true) {
        switch (state) {
            case FAIL:
                printFailure();
                return false;
            case INIT:
                if (myParser->hasCmd()) {
                    if (debug) cout << "successfully loaded " << myParser->cmdTotal() << " instructions" << endl;
                    state = DAY_BEGIN;
                } else {
                    cout << "No input command" << endl;
                    state = FAIL;
                }
                break;
            case DAY_BEGIN: // start from loading information
                state = HAS_CMD;
                break;
            case HAS_CMD:
                next = myParser->nextCmd();
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
                    state = HAS_CMD;
                } else state = PICK_J;
                break;
            case PICK_J: // judge whether pick a new instruction from the tree
                if (worker == nullptr) workPicker();
                // verify picker
                if (picker > 0) state = AT_WORK;
                else {// no building waiting in heap,
                    global++;//increment global timer
                    state = END_J; // go back to wait for cmd
                }
                break;
            case AT_WORK:
                atWork(worker);
                // before is under global=0
                // TODO global timer ++ after this line, so this separates the day
                //  first insert day is 0, means day one, time already pass 1,

                if (debug >= LEVEL1) cout << "worked 1 day" << endl;
                // pare1 is building number, tt_bNum2 is time
                if (worker == nullptr) throw exception();
                if (worker->et >= worker->tt) { //judge whether it's finished ahead
                    if (debug) {
                        if (workdays == 5) cout << "finished exact 5 days" << endl;
                        else cout << "finished ahead" << endl;
                    }
                    printFinish(worker);
                    // TODO, after finish, remove worker from heap and rbtree
                    myTree->rbRemove(worker);
                    myheap.removeMin();// actually we make sure worker is at min
                    // clear worker later
                    workdays = 0;
                    state = END_J;
                } else if (workdays >= 5) { //finish 5 days
                    if (debug) cout << "finished 5 days,put back bNum=" << worker->bNum << endl;
                    workdays = 0;
                    state = REINSERT;
                } else state = INSERT_J; //
                break;
            case DAY_END:
                break;
            case REINSERT:
                // TODO remove from heap, reinsert, heapify
                //  don't remove and insert, just heapify
                reinsert(worker);// actually decreaseKey + heapify Down
                for (; newInsert > 0; newInsert--) { // handle up to five new insert during the middle of construction
                    // heapify new inserted node using a fifo scheme.
                    myheap.heapifyUp(myheap.len - newInsert + 1);// for the new inserted node in the middle
                }
                worker = nullptr; // clear worker
                state = INSERT_J;
                break;
            case END_J:
                if (endJudge()) state = DONE;
                else {
                    worker = nullptr;
                    state = INSERT_J;
                }
                break;
            case DONE:
//                printFinish(worker);
                return true;
        }
    }
}

bool BuildCity::initBuilder(DEBUG deb, FileParser *bParser) {
    if (bParser && myTree) myParser = bParser;
    else return false;
    switch (deb) {
        case LEVEL3:
            myheap.debug = myTree->debug = bParser->debug = true;
            break;
        case LEVEL2:
            bParser->debug = myTree->debug = true;
            myheap.debug = false;
            break;
        case LEVEL1:
            bParser->debug = true;
            myTree->debug = myheap.debug = false;
            break;
        case PRINTDEBUG:
            bParser->debug = myTree->debug = myheap.debug = false;
            break;
        default:
        case NODEBUG:
            bParser->debug = myTree->debug = myheap.debug = false;
            break;
    }
    return true;
}


