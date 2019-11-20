/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:09:14
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:16
 * @Description: 
 */
// TODO maybe add ui for system

#include <iostream>
#include "MinHeap.h"
#include "RBTree.h"
#include "FileParser.h"
#include "MyQueue.h"

using namespace std;

int queueTest() {
    MyQueue q{};
    q.createQ();
    for (int i = 0; i < 20; i++) q.enQ(i);
    cout << q.deQ() << endl;
    q.enQ(1);
    return 1;
}

int minHeapTest(KEYTYPE *arr) {
    cout << "\n-------------Start Min Heap Test----------" << endl;
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

// TODO complete test
int RBTreeTest(KEYTYPE *rb) {
    cout << "\n-------------Start Red Black Tree Test----------" << endl;
    RBTree rbt{};
    rbt.rbInit(rb);
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
    KEYTYPE arr[2001] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
    KEYTYPE rb[10] = {5, 3, 4, 2, 8};
    string filename = argv[1];
    cout << "Input File name is: " << argv[1] << endl;
    FileParser parser;
//    parser.readFile(filename);
//    minHeapTest(arr);
//    RBTreeTest(rb);
    queueTest();
    return 0;
}