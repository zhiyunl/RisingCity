//
// Created by zhiyunl on 11/16/19.
//

#include "RBTree.h"

using namespace std;
//-------------- read only ------------
// TODO bool indicates found or not, in-place return last valid node
rbNode *RBTree::rbSearch(rbNode *n, KEYTYPE key) {
    // search node by key, time O(log)
    // 1. if node is null, return null
    // 2. if n.key < key, goto right, vice verse
    // recursive, just find
    if (n == nullptr) return nullptr;
    else if (n->key == key) return n;
    else return rbSearch((n->key > key) ? n->l : n->r, key);
}

rbNode *RBTree::rbSearch(rbNode *n, KEYTYPE key, rbNode **p) { //use **p to modify pointer
    // search node by key, time O(log)
    // 1. if node is null, return null
    // 2. if n.key < key, goto right, vice verse
    // recursive is no good, use iterative
    // return its own , return parent pointer in-place, if n is root, p is n
    rbNode *tmp = n;
    while (notNull(tmp)) {
        if (tmp->key == key) { // could be multiple same keys.
            *p = isRoot(tmp) ? tmp : parent(tmp);
            return tmp;
        } else {
            *p = tmp; //save parent pointer
            tmp = tmp->key > key ? tmp->l : tmp->r;
        }
    }
    return nullptr;
}

bool RBTree::isRoot(rbNode *n) {
    return parent(n) == nullptr;
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
        rbNode *p = parent(n);
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
        rbNode *gp = grandP(n);
        if (notNull(gp)) return parent(n) == gp->l ? gp->r : gp->l;
    }
    return nullptr;
}

bool RBTree::notNull(rbNode *n) {
    // handle nullptr and null value
    return n && n != nullptr; //n could be NULL or nullptr
}

void RBTree::print(rbNode *p) {
    // if red print color
    // if occurrence > 1, print occur
    // else just key
    cout << "" << p->key;
    if (p->color == RED) cout << "R";
    if (p->occur > 1) cout << "" << p->occur;
    cout << " ";
//    printf("[key=%d,c=%s,n=%d]\t",p->key,colorName(p->color).c_str(),p->occur);
}

void RBTree::rbTraverse(rbNode *n, void (*callback)(rbNode *p)) {
    if (n == nullptr) return;
    rbTraverse(n->l, callback);
    callback(n);
    rbTraverse(n->r, callback);
}

void RBTree::rbTraversePre(rbNode *n, void (*callback)(rbNode *)) {
    if (n == nullptr) return;
    callback(n);
    rbTraversePre(n->l, callback);
    rbTraversePre(n->r, callback);
}

void RBTree::rbTraversePost(rbNode *n, void (*callback)(rbNode *)) {
    if (n == nullptr) return;
    rbTraversePost(n->l, callback);
    rbTraversePost(n->r, callback);
    callback(n);
}

void RBTree::rbTraverseBFS(rbNode *n, void (*callback)(rbNode *)) {
    // use qNode
    // use parent pointer
    int i = 0;
    auto tmp = n;
    while (notNull(tmp)) {
        callback(tmp);
    }
}

//---------------- Write -------------------
// Basics
rbNode *RBTree::lRotate(rbNode *n) {
    // rotate counter-clockwise same as RR rotation for AVL
    // n.right --> root , n --> root.left, n.right.left --> root.left.right, parent.child(l/r) --> root
    // note: n could be root ,when no parent
    if (notNull(n)) {
        auto newroot = n->r;
        n->r = newroot->l;
        newroot->l = n;
        if (!isRoot(n)) {
            auto p = parent(n);
            if (p->l == n) p->l = newroot;
            else p->r = newroot;
        }
        return newroot;
    } else {
        std::cout << "-------rotate null!------" << std::endl;
        return nullptr;
    }
}

rbNode *RBTree::rRotate(rbNode *n) {
    // rotate clockwise same as LL rotation for AVL
    // n.left --> root , n --> root.right, n.left.right --> root.right.left, parent.child(l/r) --> root
    // note: n could be root ,when no parent
    if (notNull(n)) {
        auto newroot = n->l;
        n->l = newroot->r;
        newroot->r = n;
        if (!isRoot(n)) {
            auto p = parent(n);
            if (p->l == n) p->l = newroot;
            else p->r = newroot;
        }
        return newroot;
    } else {
        std::cout << "-------rotate null!------" << std::endl;
        return nullptr;
    }
}

// TODO
rbNode *RBTree::repair(rbNode *n) {
    return nullptr;
}

rbNode *RBTree::rbInit(KEYTYPE *arr) {
    // init tree using multiple insert
    int i = 0;
    while (arr[i]) {
        // use new to init and malloc every time
        auto *p = new rbNode{arr[i++]};
        this->root = rbInsert(this->root, p);
    }
    rbTraverse(this->root, RBTree::print); //&
    return nullptr;
}

// TODO
rbNode *RBTree::rbInsert(rbNode *n, rbNode *p) {
    if (n == nullptr) { //no root
        n = p;
        n->p = nullptr;
        n->color = BLACK;
    } else {
        insert(n, p);
        repair(n);
    }
    return n;
}

rbNode *RBTree::insert(rbNode *n, rbNode *p) {
    // insert p into tree with root=n
    // find next insert place by search
    rbNode *np;
    auto same = rbSearch(n, p->key, &np);
    if (same == nullptr) {// no same key node
        if (np == nullptr) {
            throw "np is null";
        } else if (p->key < np->key) np->l = p;
        else np->r = p;
        p->p = np;
    } else {
        same->occur += p->occur;
    }
    // p is parent of key when key is same, ( n if root)
    return n;
}

std::string RBTree::colorName(color_t color) {
    switch (color) {
        case RED:
            return "R";
        case BLACK:
            return "B";
        default:
            return "NULL";
    }
}







