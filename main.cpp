/*
 * @Author: zhiyunl
 * @Date: 2019-10-21 15:09:14
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 18:39:16
 * @Description: 
 */

#include <iostream>
#include "BuildCity.h"

using namespace std;

int main(int argc, char const *argv[]) {
    /*
     * Must take in the file_name as argument
     * Must use Min Heap to store, could be a array
     * Must use Red-Black Tree to manage, using node
     * */
    FileParser myParser{}; // process input and convert to cmd

    ofstream out("output_file.txt");
    auto *coutbuf = cout.rdbuf();
    DEBUG debug = PRINTDEBUG; // debug
    string filename = argv[1];
    if (debug == NODEBUG) {
        // redirect file to output.txt
        cout.rdbuf(out.rdbuf());
    }
    if (!myParser.readFile(filename)) {
        cout << "fail" << endl;
        return 0;
    }
    BuildCity builder;
    builder.initBuilder(debug, &myParser);
    return builder.timeLine();
}
