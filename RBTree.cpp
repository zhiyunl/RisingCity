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
    return notNull(n) ? nullptr : n->p;
}

rbNode *RBTree::sibling(rbNode *n) {
    // 1. when n is null, return null
    // 2. when parent is null, return null, n is root
    // 3. else, has sibling
    //    if n is p.left, return p.right; vice verse
    if (notNull(n)) {
        rbNode *p;
        p = parent(n);
        if (notNull(p)) return n == p->l ? p->l : p->r;
    }
    return nullptr;
}

rbNode *RBTree::uncle(rbNode *n) {
    // 1. when n is null, return null
    // 2. when grandparent null, return null (root is either n or parent(n))
    // 3. else, has uncle
    //    if parent is gp.left, return right; vice verse
    if (notNull(n)) {
        rbNode *gp;
        gp = grandP(n);
        if (notNull(gp)) return parent(n) == gp->l ? gp->r : gp->l;
    }
    return nullptr;
}

bool RBTree::notNull(rbNode *n) {
    // handle nullptr
    return !n && n != nullptr; //n could be NULL or nullptr
}

rbNode *RBTree::rbInit(int *arr) {
    // init tree using multiple insert
    int i = 0;
    while (arr[i]) {
        rbInsert(&(this->node), arr[i]);
    }
    rbPrint(&this->node);
    return nullptr;
}
