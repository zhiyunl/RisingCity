//
// Created by zhiyunl on 11/18/19.
//

#ifndef RISINGCITY_BSTREE_H
#define RISINGCITY_BSTREE_H

#include "RBTree.h"

typedef int KEYTYPE;

struct bsNode {
    bsNode *l; // left child
    bsNode *r; // right child
    int key;
};

class BSTree {
    // read only ops
    bsNode node{};
public:
    bsNode *bsSearch(bsNode *n, KEYTYPE key);

    void bsTraverse(bsNode *n, void (*callback)(bsNode *p));

    void bsPrint(bsNode *n);
};


#endif //RISINGCITY_BSTREE_H
