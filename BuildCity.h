/*
 * @Author: zhiyunl
 * @Date: 2019-11-20 22:21:54
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-27 22:25:22
 * @Description: 
 */

#ifndef RISINGCITY_BUILDCITY_H
#define RISINGCITY_BUILDCITY_H

#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "FileParser.h"
#include "RBTree.h"

enum DEBUG {
    NODEBUG, PRINTDEBUG, LEVEL1, LEVEL2, LEVEL3
};

enum State {
    FAIL, INIT, DAY_BEGIN, TIMER_J, CMDTYPE_J, PICK_J, AT_WORK, DAY_END, REINSERT, END_J, DONE
};

class BuildCity {
private:
    DEBUG debug = NODEBUG; // debug
public:
    int picker = 1; // index for the new worker node in minHeap
    mhNode *worker = nullptr; // save worker pointers
    int global = 0; //global timer
    RBTree *myTree = new RBTree(); // rbTree pointer
    MinHeap myheap{}; //minHeap 
    FileParser *myParser = nullptr; // Fileparser pointer
    int newInsert = 0;// count number of new insert during working
    // convert instructions to heap node
    static mhNode *fromIns2Heap(Instruction *ins); // ins: instruction to parser
    // pick building recursively until the lowest et and bNum is found
    void pickRecursive(int i); // i: index
    // manage and call pickRecursive func
    void workPicker(); // set picker index
    int workdays = 0; // count for at most 5 days
    // et increment
    void atWork(mhNode *mhn);// mhn: the node to work on
    // print one building
    static void printOne(mhNode *mhn);// mhn: the node to print
    // when not found, print(0,0,0) 
    static void printNone();

    // print the building when it finishes
    void printFinish(mhNode *mhn);// mhn: the node to print
    // when system fail, print error message
    static void printFailure();

    // insert the node into minheap and rbtree
    void insertCMD(Instruction *ins);// ins: instruction to insert
    // manage and call print* func
    bool printBuilding(Instruction *ins);// ins: instruction to print
    // reinsert the node back 
    void reinsert(mhNode *mhn);// mhn: node to insert
    // judge if the city is finished
    bool endJudge();// return true if finished 
    // main loop of the construction
    bool timeLine();

    // init everything
    bool initBuilder(DEBUG deb, FileParser *bParser);// deb: debug option
};


#endif //RISINGCITY_BUILDCITY_H
