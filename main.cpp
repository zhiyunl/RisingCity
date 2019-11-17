/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:09:14
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:16
 * @Description: 
 */
// TODO maybe add ui for system

#include <iostream>
#include <fstream>
#include "MinHeap.h"

using namespace std;
typedef int PARAMETER;
typedef int TIME;
enum INSTRUCTION_TYPE {
    NO, INSERT, PRINT, PRINTRANGE
};
struct Instruction {
    TIME time;
    enum INSTRUCTION_TYPE type;
    PARAMETER para1;
    PARAMETER para2;
};
// TODO make cmdList a circular list
struct Instruction cmdList[1000];

void printCmdList() {
    int i = 0;
    while (cmdList[i].type) {
        cout << i + 1 << "th cmd is : ";
        cout << cmdList[i].time << ": " << (cmdList[i].type == INSERT ? "Insert(" : "PrintBuilding(");
        if (cmdList[i].para2) cout << cmdList[i].para1 << "," << cmdList[i].para2 << ")" << endl;
        else cout << cmdList[i].para1 << ")" << endl;
        i++;
    }
}

enum INSTRUCTION_TYPE insParser(const string &ins, PARAMETER para2) {
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

int lineParser(string str) {
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

int readFile(const string &fname) {
    fstream f;
    f.open("../" + fname, ios::in);
    string str;
    if (f.fail()) {
        cout << "error" << endl;
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

int minHeapTest(int *arr) {
    MinHeap myheap{};
    myheap.init(arr); // in-place modify
//    myheap.printHeap();
    myheap.insert(10);
//    myheap.printHeap();
    myheap.insert(11);
//    myheap.printHeap();
    myheap.insert(1);
//    myheap.printHeap();
    myheap.insert(4);
//    myheap.printHeap();
    cout << "min is removed!:" << myheap.removeMin() << endl;
    myheap.printHeap();
    return 1;
}

// TODO init rbtree and print
int RBTreeTest(const int *rb) {

    return 1;
}

int main(int argc, char const *argv[]) {
    /*
     * Must take in the file_name as argument
     * Must use Min Heap to store, could be a array
     * Must use Red-Black Tree to manage, using node
     * */
    // don't use 1st element to simplify calculation
    // used for in-place minHeap
    int arr[2001] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
    int rb[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    string filename = argv[1];
    cout << argv[1] << endl;
    readFile(filename);
    minHeapTest(arr);
    RBTreeTest(rb);
    return 0;
}