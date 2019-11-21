//
// Created by zhiyunl on 11/16/19.
//
#include "RBTree.h"
#include <iostream>
using namespace std;

// when using template, compiler generate class automatically
// possible type of KEY is listed below,
// otherwise, there will be error
template
class RBTree<int>;

template
class RBTree<float>;

template
class RBTree<char>;

template
struct rbNode<int>;
template
struct rbNode<char>;
template
struct rbNode<float>;

template<class KEY>
RBTree<KEY>::RBTree():ro(NULL) {
    ro = nullptr;
    debug = false;
}

template<class KEY>
RBTree<KEY>::~RBTree() {
    ;
}

template<class KEY>
void RBTree<KEY>::rbInit(KEY *arr) {
    ;
}


template<class KEY>
rbNode<KEY> *RBTree<KEY>::parent(rbNode<KEY> *n) {
    return n ? n->pa : nullptr;
}

template<class KEY>
rbNode<KEY> *RBTree<KEY>::grandP(rbNode<KEY> *n) {
    return parent(parent(n));
}

template<class KEY>
rbNode<KEY> *RBTree<KEY>::sibling(rbNode<KEY> *n) {
    // 1. when n is null, return null
    // 2. when parent is null, return null, n is root
    // 3. else, has sibling
    //    if n is pa.left, return pa.right; vice verse
    if (n) {
        rbNode<KEY> *p = parent(n);
        if (p) return n == p->l ? p->l : p->r;
    }
    return nullptr;
}

template<class KEY>
rbNode<KEY> *RBTree<KEY>::uncle(rbNode<KEY> *n) {
    // 1. when n is null, return null
    // 2. when grandparent null, return null (root is either n or parent(n))
    // 3. else, has uncle
    //    if parent is gp.left, return right; vice verse
    if (n) {
        rbNode<KEY> *gp = grandP(n);
        if (gp) return parent(n) == gp->l ? gp->r : gp->l;
    }
    return nullptr;
}

//// -------------print-----------------
template<class KEY>
void RBTree<KEY>::_print_(rbNode<KEY> *node) const {
    // if red print color
    // if occurrence > 1, print occur
    // else just key
    std::cout << "" << node->key;
    if (node->color == RED) std::cout << "R";
    if (node->occur > 1) std::cout << "(" << node->occur << ")";
    std::cout << " ";
//    printf("[key=%d,c=%s,n=%d]\t",pa->key,_colorName_(pa->color).c_str(),pa->occur);
}

//public func
template<class KEY>
void RBTree<KEY>::rbTraverse() {
    _rbTraverse_(this->ro);
}

template<class KEY>
void RBTree<KEY>::rbTraversePre() {
    _rbTraversePre_(this->ro);
}

template<class KEY>
void RBTree<KEY>::rbTraversePost() {
    _rbTraversePost_(this->ro);
}

// private func, recursive
template<class KEY>
void RBTree<KEY>::_rbTraverse_(rbNode<KEY> *tree) const {
    if (tree == nullptr) return;
    _rbTraverse_(tree->l);
    _print_(tree);
    _rbTraverse_(tree->r);
}

template<class KEY>
void RBTree<KEY>::_rbTraversePre_(rbNode<KEY> *tree) const {
    if (tree == nullptr) return;
    _print_(tree);
    _rbTraversePre_(tree->l);
    _rbTraversePre_(tree->r);
}

template<class KEY>
void RBTree<KEY>::_rbTraversePost_(rbNode<KEY> *tree) const {
    if (tree == nullptr) return;
    _rbTraversePost_(tree->l);
    _rbTraversePost_(tree->r);
    _print_(tree);
}

///--------------print----------------
///--------------search---------------
template<class KEY>
rbNode<KEY> *RBTree<KEY>::_rbSearch_(rbNode<KEY> *tree, KEY key) const {
    // search node by key, time O(log)
    // 1. if node is null, return null
    // 2. if n.key < key, goto right, vice verse
    // recursive, just find
    if (tree == nullptr) return nullptr;
    else if (tree->key == key) return tree;
    else return _rbSearch_((tree->key > key) ? tree->l : tree->r, key);
}

//public
template<class KEY>
rbNode<KEY> *RBTree<KEY>::rbSearch(KEY key) {
    return _rbSearch_(this->ro, key);
}

template<class KEY>
rbNode<KEY> *RBTree<KEY>::rbSearchIter(KEY key) {
    return _rbSearchIter_(this->ro, key);
}

// private, iteratively search node by key
template<class KEY>
rbNode<KEY> *RBTree<KEY>::_rbSearchIter_(rbNode<KEY> *tree, KEY key) const {
    while (tree && tree->key != key) {
        tree = key > tree->key ? tree->r : tree->l;
    }
    return tree;
}

// find max node in subtree
template<class KEY>
rbNode<KEY> *RBTree<KEY>::_maxNode_(rbNode<KEY> *tree) {
    while (tree->r) tree = tree->r;
    return tree;
}

// find minimum in subtree
template<class KEY>
rbNode<KEY> *RBTree<KEY>::_minNode_(rbNode<KEY> *tree) {
    while (tree->l) tree = tree->l;
    return tree;
}

// below are used for replace degree 2 node
template<class KEY>
rbNode<KEY> *RBTree<KEY>::_priorNode_(rbNode<KEY> *tree) {
    // find the predecessor,
    // 1. if left exists, max in left subtree
    // 2. go upwards until the first node who has right child.
    if (tree->l) return _maxNode_(tree->l);
    rbNode<KEY> *p = tree->pa;
    while (p && tree == p->l) {
        // p is not null, tree is left child, continue
        tree = p;
        p = p->pa;
    }
    return p;
}

template<class KEY>
rbNode<KEY> *RBTree<KEY>::_postNode_(rbNode<KEY> *tree) {
    // find the successor,
    // 1. if right exists, min in right subtree
    // 2. go upwards until the first node who has left child.
    if (tree->r) return _minNode_(tree->r);
    rbNode<KEY> *p = tree->pa;
    while (p && tree == p->r) {
        // p is not null, tree is left child, continue
        tree = p;
        p = p->pa;
    }
    return p;
}

template<class KEY>
void RBTree<KEY>::lRotate(rbNode<KEY> *&root, rbNode<KEY> *n) {
    /*
     *                n.pa                                  n.pa
     *            n                                    n.ro(p)
     *     n.l          n.ro(p)          ----->      n       n.ro.ro
     *            n.ro.l      n.ro.ro            n.l   n.ro.l
     *
     * */
    // rotate counter-clockwise same as RR rotation for AVL
    // n.right --> p , n --> p.left, n.right.left --> root.left.right, parent.child(l/ro) --> root
    // note: n could be root ,when no parent
    rbNode<KEY> *p = n->r;
    n->r = p->l;
    if (p->l) {// when left child of p is null, no need for parent pointer
        p->l->pa = n;
    }
    p->pa = n->pa;
    if (!n->pa) root = p; // when n have no parent, it's root, update root
    else if (n->pa->l == n) { // n is left child, set p as the same
        n->pa->l = p;
    } else n->pa->r = p; // vice versa
    p->l = n; // from p to n
    n->pa = p; // from n to p
}

template<class KEY>
void RBTree<KEY>::rRotate(rbNode<KEY> *&root, rbNode<KEY> *n) {
    /*
     *        n.pa                      n.pa
     *             n                        n.l(p)
     *      n.l(p)   n.ro  ----->      n.l.l        n
     * n.l.l    n.l.ro                        n.l.ro   n.ro
     *
     * */
    // rotate clockwise same as LL rotation for AVL
    // n.left --> root , n --> root.right, n.left.right --> root.right.left, parent.child(l/ro) --> root
    // note: n could be root ,when no parent
    rbNode<KEY> *p = n->l;
    n->l = p->r;
    if (p->r) {// when left child of p is null, no need for parent pointer
        p->r->pa = n;
    }
    p->pa = n->pa;
    if (!n->pa) root = p; // when n have no parent, it's root, update root
    else if (n->pa->l == n) { // n is left child, set p as the same
        n->pa->l = p;
    } else n->pa->r = p; // vice versa
    p->r = n; // from p to n
    n->pa = p; // from n to p
}

template<class KEY>
void RBTree<KEY>::rbInsert(KEY key) {
    // possibly this could fail!
    auto n = new rbNode<KEY>(key, BLACK, nullptr, nullptr, nullptr, 1);
    _insert_(this->ro, n);
    // without repair, it's correct
    _repairInsert_(this->ro, n);
//    if (this->debug) {
//        std::cout << "\n------ins: rbInsert-------\n";
//        rbTraverse(); //&
//    }
}

template<class KEY>
void RBTree<KEY>::_insert_(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    // insert p into tree with root=n
    // find next insert place by search
    // could be null when root
    auto *p = root;
    rbNode<KEY> *pp = nullptr; // register p
    while (p) { // search iteratively like a bst
        pp = p;
        if (n->key == p->key) {
            // deal with same key by adding a occur
            p->occur += n->occur;
            break;
        } else p = n->key > p->key ? p->r : p->l;
    }
    n->pa = pp; // find the insert position parent
    if (pp) {
        // decide whether left child or right child
        if (n->key > pp->key) pp->r = n;
        else pp->l = n;
    } else root = n;// when parent of insertion is null, that's root
    n->color = RED;//default insert color is red, repair later
}

template<class KEY>
void RBTree<KEY>::_repairInsert_(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    rbNode<KEY> *p = parent(n);
    if (!p) { // parent doesn't exists
        inCase1(root, n); // n is root node,set black
    } else if (p->color == BLACK) { ; // no two consecutive red, no repair
//        inCase2(root,n);
        if (this->debug) cout << "case 2:no need on key=" << n->key << endl;
    } else if (uncle(n) && uncle(n)->color == RED) {
        // has red uncle and red parent
        // flip color, recursively running repair
        if (this->debug) cout << "case 3: flip on key=" << n->key << endl;
        inCase3(root, n);
    } else {
        // LL LR RR RL,
        if (this->debug) cout << "case 4:rotate on key=" << n->key << endl;
        inCase4(root, n);
    }
}

template<class KEY>
void RBTree<KEY>::print(rbNode<KEY> *tree, KEY key, int direction) {
    if (tree != NULL) {
        if (direction == 0)    // root
            std::cout << tree->key << "(B) is root" << std::endl;
        else {               // subtree
            std::cout << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") \
 << " is " << key << "'s " << \
             (direction == 1 ? "right child" : "left child") << std::endl;
        }
        print(tree->l, tree->key, -1);
        print(tree->r, tree->key, 1);
    }
}

template<class KEY>
void RBTree<KEY>::print() {
    if (this->ro != NULL)
        print(this->ro, this->ro->key, 0);
}

template<class KEY>
void RBTree<KEY>::inCase1(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    n->color = BLACK; // black root
    if (this->debug) cout << "case 1:root insert on key=" << n->key << endl;
}

template<class KEY>
void RBTree<KEY>::inCase2(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    ;
}

template<class KEY>
void RBTree<KEY>::inCase3(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    // parent and uncle are red, flip color
    n->pa->color = BLACK;
    uncle(n)->color = BLACK;
    grandP(n)->color = RED;
    // repeat upwards, two step
    auto *gp = grandP(n);
    _repairInsert_(root, gp);
}

template<class KEY>
void RBTree<KEY>::inCase4(rbNode<KEY> *&root, rbNode<KEY> *&n) {
    // complicated
    // 1. no uncle, same as uncle is black
    // 2. uncle is black, pa=gp.left and pa.left=n, LL
    // 3. .. pa=gp.ro and pa.ro = n, rr
    // 4. .. pa=gp.l and pa.ro = n, lr
    // 5. .. pa=gp.ro and pa.l = n. rl
    // rotate LL,RR,LR,RL in parent
    // LR means lrotate on p then rrotate on gp
    // RL means rtotate on p then lrotate on gp
//    rbNode<KEY> *p = parent(n);
    rbNode<KEY> *gp = parent(n->pa);
    // LR first step
    if (!gp) {
        // when gp is null, no lr or rl
        ;
        if (this->debug) cout << "case 4.1:no gp on key=" << n->key << endl;
    } else if (n == n->pa->r && n->pa == gp->l) {
        // n is right child and p is left child, LR
        if (this->debug) cout << "case 4.2:LR step1 on key=" << n->key << endl;
        lRotate(root, n->pa);
        if (this->debug) print();
        n = n->l;
    } else if (n == n->pa->l && n->pa == gp->r) {
        // RL first step
        if (this->debug) cout << "case 4.3:RL step1 on key=" << n->key << endl;
        rRotate(root, n->pa);
        if (this->debug) print();
        n = n->r;
    }
//    p = parent(n);
    gp = parent(n->pa);
    // LL or second step of LR
    if (n == n->pa->l) {
        if (this->debug) cout << "case 4.4:R rotation on key=" << n->pa->key << endl;
        rRotate(root, gp);
        if (this->debug) print();
    } else {    // RR or second step of RL
        if (this->debug) cout << "case 4.5:L rotation on key=" << n->pa->key << endl;
        lRotate(root, gp);
        if (this->debug) print();
    }
    // color change
    n->pa->color = BLACK;
    if (gp) gp->color = RED;
}
