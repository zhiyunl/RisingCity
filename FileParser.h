//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_FILEPARSER_H
#define RISINGCITY_FILEPARSER_H

#include <iostream>
#include "MyQueue.h"

//#define MAX_I_SIZE 2000
using namespace std;
typedef int PARAMETER;
typedef int TIME;
enum INSTRUCTION_TYPE {//0,   1,     2,       3
    NO, INSERT, PRINT, PRINTRANGE
};

struct Instruction {
    TIME time;
    enum INSTRUCTION_TYPE type;
    PARAMETER para1;
    PARAMETER para2;

    // constructor
    Instruction(TIME ti, INSTRUCTION_TYPE t, PARAMETER p1, PARAMETER p2 = 0) :
            time(ti), type(t), para1(p1), para2(p2) {}

    Instruction() = default;
};

class FileParser {
public:
    MyQueue<Instruction> *cmdQueue;
    bool debug;

    FileParser();
    void printCmdList();

    static enum INSTRUCTION_TYPE insParser(const string &ins, PARAMETER para2);

    int lineParser(string str);

    bool readFile(const string &fname);

    Instruction *nextCmd();

    bool hasCmd();

    int cmdTotal();
};


#endif //RISINGCITY_FILEPARSER_H
