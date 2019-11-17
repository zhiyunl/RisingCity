//
// Created by zhiyunl on 11/16/19.
//

#include "RBTree.h"


rbNode *RBTree::repair(rbNode *n) {
    return nullptr;
}

rbNode *RBTree::grandP(rbNode *n) {
    return parent(parent(n));
}

rbNode *RBTree::parent(rbNode *n) {
    // handle nullptr
    return n ? n->p : n;
}

rbNode *RBTree::sibling(rbNode *n) {
    // handle nullptr
    if (n == nullptr) return nullptr;
    rbNode *p;
    p = parent(n);
    if (p) return p->l ? p->l : p->r;
    else return nullptr;
}
