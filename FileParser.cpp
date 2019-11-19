//
// Created by zhiyunl on 11/19/19.
//
#include "FileParser.h"

// TODO make cmdList a circular list
struct Instruction cmdList[1000];

void FileParser::printCmdList() {
    int i = 0;
    while (cmdList[i].type) {
        cout << i + 1 << "th cmd is : ";
        cout << cmdList[i].time << ": " << (cmdList[i].type == INSERT ? "Insert(" : "PrintBuilding(");
        if (cmdList[i].para2) cout << cmdList[i].para1 << "," << cmdList[i].para2 << ")" << endl;
        else cout << cmdList[i].para1 << ")" << endl;
        i++;
    }
}

enum INSTRUCTION_TYPE FileParser::insParser(const string &ins, PARAMETER para2) {
    enum INSTRUCTION_TYPE type = INSERT; // init in case wrong command
    switch (ins[0]) {
        case 'I':
            if (ins == "Insert") type = INSERT;
            break;
        case 'P':
            if (ins == "PrintBuilding") type = para2 ? PRINTRANGE : PRINT;
            break;
        default:
            cout << "wrong instruction" << endl;
            break;
    }
    return type;
    // return ins=="Insert"?INSERT:PRINT;
}

int cmdCnt = 0;

int FileParser::lineParser(string str) {
    int i = 0;
    TIME time = 0;
    int state = 0;
    int head = 0;
    PARAMETER para1 = 0, para2 = 0;
    string ins;
    // e.g. "100: Insert(50,20)"
    while (str[i]) { //until end
        switch (state) {
            case 0: // get time
                if (str[i] == ':') {
                    ++state;
                    head = i + 1;
                } else time = time * 10 + str[i] - '0'; // (1*10+0)*10+0 = 100, minus ascii value
                ++i;
                break;
            case 1: // get instruction before "("
                if (str[i] == '(') {
                    ++state;
                    ins = str.substr(head + 1, i - head - 1);
                }
                ++i;
                break;
            case 2: // first para
                if (str[i] == ',') ++state;
                else if (str[i] == ')') state += 2;
                else para1 = para1 * 10 + str[i] - '0';
                ++i;
                break;
            case 3: // second para
                if (str[i] == ')') ++state;
                else para2 = para2 * 10 + str[i] - '0';
                ++i;
                break;
            default:
                cout << "wrong" << endl;
                break;
        }
    }
    cmdList[cmdCnt++] = {time, insParser(ins, para2), para1, para2};
    return 1;
}

int FileParser::readFile(const string &fname) {
    cout << "-------------Read input file-----------" << endl;
    fstream f;
    f.open(fname, ios::in);
    string str;
    if (f.fail()) {
        throw "Failed to open input file!!!";
    } else {
        while (f) {
            getline(f, str);
            lineParser(str);
            cout << str << endl;
        }
        f.close();
    }
    cout << "print cmd list\n";
    printCmdList();
    return 1;
}