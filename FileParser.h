//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_FILEPARSER_H
#define RISINGCITY_FILEPARSER_H


#include "MyQueue.h"
#include <iostream>

using namespace std;
typedef int PARAMETER;
typedef int TIME;

enum INSTRUCTION_TYPE {//0,   1,     2,       3
    NO, INSERT, PRINT, PRINTRANGE
};

struct Instruction {
    TIME time;
    enum INSTRUCTION_TYPE type;
    PARAMETER bNum1;
    PARAMETER tt_bNum2;

    // constructor
    Instruction(TIME ti, INSTRUCTION_TYPE t, PARAMETER p1, PARAMETER p2 = 0) :
            time(ti), type(t), bNum1(p1), tt_bNum2(p2) {}

    Instruction() = default;
};

class FileParser {
private:
    MyQueue<Instruction> *cmdQueue;
public:
    bool debug;

//    FileParser();

    FileParser() :
            cmdQueue(new MyQueue<Instruction>()), debug(false) {}

    void printCmdList();

    bool readFile(const string &fname);

    Instruction *nextCmd();

    bool hasCmd();

    int cmdTotal();

private:
    static INSTRUCTION_TYPE insParser(const string &ins, PARAMETER para2);

    int lineParser(string str);
};


#endif //RISINGCITY_FILEPARSER_H
