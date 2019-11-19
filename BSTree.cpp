//
// Created by zhiyunl on 11/18/19.
//
#include <iostream>
#include "BSTree.h"

bsNode *BSTree::bsSearch(bsNode *n, KEYTYPE key) {
    // search node by key, time O(logn)
    // 1. if node is null, return null
    // 2. if n.key < key, goto right, vice verse
    if (n == nullptr) return nullptr;
    else if (n->key == key) return n;
    else return bsSearch((n->key > key) ? n->l : n->r, key);
}

void BSTree::bsTraverse(bsNode *n, void (*callback)(bsNode *p) = nullptr) {
    // in order traverse tree, and print out may be
    // recursive
    if (n == nullptr) return;
    bsTraverse(n->l, callback);
    callback(n);
    bsTraverse(n->r, callback);
}

void BSTree::bsPrint(bsNode *n) {
    std::cout << n->key << std::endl;
}
