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


using namespace std;


int myParser(const string &str) {
    int i = 0;
//    while(str[i]){
//
//    }
    return 0;
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
            cout << str << endl;
        }
        myParser(str);
        f.close();
    }
    return 1;
}

int minHeapTest(int *arr) {
    MinHeap myheap{};
    myheap.init(arr); // in-place modify
    myheap.insert(10);
    myheap.insert(11);
    myheap.insert(1);
    myheap.insert(4);
    cout << myheap.removeMin();
    return 1;
}

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
    //used for in-place minHeap
    int arr[2001] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
    const int *rb = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    string filename = argv[1];
    cout << argv[1] << endl;
    readFile(filename);
    minHeapTest(arr);
    RBTreeTest(rb);
    return 0;
}