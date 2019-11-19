//
// Created by zhiyunl on 11/19/19.
//

#ifndef RISINGCITY_FILEPARSER_H
#define RISINGCITY_FILEPARSER_H

#include <fstream>
#include <iostream>

using namespace std;
typedef int PARAMETER;
typedef int TIME;
enum INSTRUCTION_TYPE {
    //0,   1,     2,       3
            NO, INSERT, PRINT, PRINTRANGE
};
struct Instruction {
    TIME time;
    enum INSTRUCTION_TYPE type;
    PARAMETER para1;
    PARAMETER para2;
};

class FileParser {
public:
    void printCmdList();

    enum INSTRUCTION_TYPE insParser(const string &ins, PARAMETER para2);

    int lineParser(string str);

    int readFile(const string &fname);
};


#endif //RISINGCITY_FILEPARSER_H
