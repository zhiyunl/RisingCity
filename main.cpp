//
// Created by zhiyunl on 10/21/19.
//

#include <iostream>
#include <fstream>
#include "MinHeap.h"


using namespace std;
#define INSERT 1
#define PRINT 2
void callFunc(int fIndex, int *argv[]){
    switch(fIndex){
        case INSERT: insert(argv[0],argv[1],argv[1]);break;
        case PRINT : printBuilding(argv[0]);break;
        default:break;
    }
}
// TODO finish the file parser
int myParser(string str){
    int i=0;

    while(str[i]){
        while(str[i]!=':'){

        }
    }
}


int main(int argc, char const *argv[]) {
    // don't use 1st element to simplify calculation
    int arr[2001] = {0, 2, 3, 4, 5, 6, 7, 8, 9};
    /*
     * Must take in the file_name as argument
     * Must use Min Heap to store
     * Must use Red-Black Tree to manage
     * */
    string filename=argv[1];
    cout << argv[1] << endl;
    fstream f;
    f.open("../"+filename,ios::in);
    string str;
    if(f.fail()){
        cout << "error"<<endl;
    }else{
        while(f){
            getline(f,str);
            cout << str <<  endl;
        }
        myParser(str);
        f.close();
    }
    MinHeap myheap{};
    myheap.init(arr);
    myheap.insert(10);
    myheap.insert(11);
    myheap.insert(1);
    myheap.insert(4);
    cout << myheap.removeMin();
    return 0;
}