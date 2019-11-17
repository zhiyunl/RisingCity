//
// Created by zhiyunl on 11/16/19.
//

#include <zconf.h>
#include "RBTree.h"


rbNode *getParent(rbNode *n) {
    return n == nullptr ? nullptr : n->p;
}

RBTree::rbNode *RBTree::repair(RBTree::rbNode *n) {
    return nullptr;
}

RBTree::rbNode *RBTree::grandP(RBTree::rbNode *n) {
    return parent(parent(n));
}

RBTree::rbNode *RBTree::parent(RBTree::rbNode *n) {
    // handle nullptr
    return n ? n->p : n;
}

RBTree::rbNode *RBTree::sibling(RBTree::rbNode *n) {
    // handle nullptr
    if (n == nullptr) return nullptr;
    rbNode *p;
    p = parent(n);
    if (p) return p->l ? p->l : p->r;
    else return nullptr;
}
