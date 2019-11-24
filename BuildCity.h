//
// Created by zhiyunl on 11/24/19.
//

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
    FAIL, INIT, DAY_BEGIN, HAS_CMD, INSERT_J, PICK_J, AT_WORK, DAY_END, REINSERT, END_J, DONE
};

class BuildCity {
private:
    DEBUG debug = NODEBUG; // debug
public:
    int picker = 1; // index for the new worker node in minHeap, default = root node
    mhNode *worker = nullptr;
    int global = 0; //global timer
    RBTree *myTree = new RBTree(); // rbTree
    MinHeap myheap{}; //minHeap
    FileParser *myParser = nullptr; // process input and convert to cmd
    int newInsert = 0;// at most five, could be five insert during the currently working days.

    static mhNode *fromIns2Heap(Instruction *ins);

    void pickRecursive(int i);

    void workPicker();

    int workdays = 0; // count for at most 5 days
    void atWork(mhNode *mhn);

    static void printOne(mhNode *mhn);

    static void printNone();

    void printFinish(mhNode *mhn);

    static void printFailure();

    void insertCMD(Instruction *ins);

    bool printBuilding(Instruction *ins);

    void reinsert(mhNode *mhn);

    bool endJudge();

    bool timeLine();

    bool initBuilder(DEBUG deb, FileParser *bParser);
};


#endif //RISINGCITY_BUILDCITY_H
