//
// Created by zhiyunl on 11/16/19.
//

#ifndef RISINGCITY_RBTREE_H
#define RISINGCITY_RBTREE_H

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
    rbNode *l; // left sibling
    rbNode *r; // right sibling
    color_t color; //
    int key;
};

class RBTree {
    rbNode node{};

    rbNode *grandP(rbNode *n);

    rbNode *parent(rbNode *n);

    rbNode *sibling(rbNode *n);

    rbNode *uncle(rbNode *n);

    rbNode *lRotate(rbNode *n);

    rbNode *rRotate(rbNode *n);

    rbNode *rbInsert(rbNode *n, int key);

    rbNode *insert(rbNode *n, int key);

    rbNode *repair(rbNode *n);

    rbNode *iCase(rbNode *n, icase_t c);

    rbNode *rbRemove(rbNode *n, int key);

    rbNode *rmCase(rbNode *n, rmcase_t c);

    rbNode *rmNode2(rbNode *n, rbNode *rm);

    rbNode *replace(rbNode *n, rbNode *child);

    rbNode *rmNode1(rbNode *n);

    rbNode *rmNode0(rbNode *n);

    void printRBTree(rbNode *n);
};


#endif //RISINGCITY_RBTREE_H
