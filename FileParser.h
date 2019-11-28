/*
 * @Author: zhiyunl
 * @Date: 2019-11-19 22:21:56
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-27 22:25:44
 * @Description: 
 */

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
    enum INSTRUCTION_TYPE type;// INSERT/PRINT
    PARAMETER bNum1;// building number or building number1
    PARAMETER tt_bNum2;// total time for a building or building number 2
    Instruction(TIME ti, INSTRUCTION_TYPE t, PARAMETER p1, PARAMETER p2 = 0) :
            time(ti), type(t), bNum1(p1), tt_bNum2(p2) {}
    Instruction() = default;
};

class FileParser {
private:
    MyQueue<Instruction> *cmdQueue;// pointer for the queue
public:
    bool debug;
    FileParser() :
            cmdQueue(new MyQueue<Instruction>()), debug(false) {}

    void printCmdList();// print out all instructions from file
    // main func, read input file and parse it
    bool readFile(const string &fname);

    // get next instruction from queue
    Instruction *nextCmd();

    bool hasCmd();// check if has instruction in the queue
    int cmdTotal();// return total cmd in queue
private:
    // check the instruction in file and parse it, save it. 
    static INSTRUCTION_TYPE insParser(const string &ins, PARAMETER para2);

    // parse a whole line in file
    int lineParser(string str);
};


#endif //RISINGCITY_FILEPARSER_H
