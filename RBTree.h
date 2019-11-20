//
// Created by zhiyunl on 11/16/19.
//

#ifndef RISINGCITY_RBTREE_H
#define RISINGCITY_RBTREE_H

#include <iostream>
#include "BSTree.h"

typedef int KEYTYPE;
enum color_t {
    BLACK, RED
};
enum lr_t {
    LEFT, RIGHT
};
enum icase_t {
    i1, i2, i3, i4, i5
};
enum rmcase_t {
    rm1, rm2, rm3, rm4, rm5, rm6
};

struct rbNode {
    rbNode *p; // parent
    rbNode *l; // left child
    rbNode *r; // right child
    color_t color;
    KEYTYPE key;
    int occur; //add count to deal with multiple same key nodes

    rbNode(KEYTYPE val) {
        color = RED;
        key = val;
        occur = 1;
        l = nullptr;
        r = nullptr;
    }

    rbNode() {
        ;
    }
};

// ---------------
// NOTE
// use sentinel node to represent leaf node can save marginal run time, instead of null
// use one sentinel node to represent all NIL across the whole tree
// source:https://en.wikipedia.org/wiki/Sentinel_node#Second_version_using_a_sentinel_node
// ---------------
class RBTree {
public:
    bool notNull(rbNode *n);

    bool isRoot(rbNode *n);

    rbNode *root;

    rbNode *rbInit(KEYTYPE *arr); //use

    rbNode *grandP(rbNode *n);

    rbNode *parent(rbNode *n);

    rbNode *sibling(rbNode *n);

    rbNode *uncle(rbNode *n);

    rbNode *lRotate(rbNode *n);

    rbNode *rbSearch(rbNode *n, KEYTYPE key, rbNode **p);

    rbNode *rbSearch(rbNode *n, KEYTYPE key);

    rbNode *rRotate(rbNode *n);

    // top level, manage insert conditions
    rbNode *rbInsert(rbNode *n, rbNode *p);

    // lower level, just insert
    rbNode *insert(rbNode *n, rbNode *p);

    rbNode *repair(rbNode *n);

    rbNode *iCase(rbNode *n, icase_t c);

    rbNode *rbRemove(rbNode *n, KEYTYPE key);

    rbNode *rmCase(rbNode *n, rmcase_t c);

    rbNode *rmNode2(rbNode *n, rbNode *rm);

    rbNode *replace(rbNode *n, rbNode *child);

    rbNode *rmNode1(rbNode *n);

    rbNode *rmNode0(rbNode *n);

    void rbTraverse(rbNode *n, void (*callback)(rbNode *p));

    void rbTraversePre(rbNode *n, void (*callback)(rbNode *p));

    void rbTraversePost(rbNode *n, void (*callback)(rbNode *p));

    void rbTraverseBFS(rbNode *n, void (*callback)(rbNode *p));

    static void print(rbNode *p);

    static std::string colorName(color_t color);
};


#endif //RISINGCITY_RBTREE_H
