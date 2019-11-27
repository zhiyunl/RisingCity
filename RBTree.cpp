//
// Created by zhiyunl on 11/16/19.
//
#include "RBTree.h"
#include <iostream>
#include "MinHeap.h"
#include <exception>

using namespace std;

//int RBTreeTest() {
//    cout << "\n-------------Start Red Black Tree Test----------" << endl;
//    KEYTYPE rb[] = {5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12};
//    int ilen = sizeof(rb) / sizeof(rb[0]);
//
//    KEYTYPE *node = nullptr;
////    auto tree = new RBTree<int>();
//    myTree->debug = true;
//    for (int i = 0; i < ilen; i++) {
////        tree->rbInsert(rb[i]);
////        node=new Instruction(i,INSERT,i*2,rb[i]);
//        node = new KEYTYPE{i * 20, 0, i * 5};
//        myTree->rbInsert(node);
////        cout << "== insert: " << rb[i] << endl;
//        if (myTree->debug) {
//            cout << "== result " << endl;
//            myTree->print();
//            myTree->rbTraverse();
//            cout << endl;
//        }
//    }
//    cout << "==final result== " << endl;
//    myTree->print();
////    tree->rbSearch(1);
//    myTree->rbRemove(node);
//    myTree->print();
//    return 1;
//}

RBTree::RBTree() {
    ro = nullptr;
    debug = false;
}


RBTree::~RBTree() {
    ;
}


void RBTree::rbInit(RBKEY *arr) {
    ;
}


rbNode *RBTree::parent(rbNode *n) {
    return n ? n->pa : nullptr;
}


rbNode *RBTree::grandP(rbNode *n) {
    return parent(parent(n));
}


rbNode *RBTree::sibling(rbNode *n) {
    // 1. when n is null, return null
    // 2. when parent is null, return null, n is root
    // 3. else, has sibling
    //    if n is pa.left, return pa.right; vice verse
    if (n) {
        rbNode *p = parent(n);
        if (p) return n == p->l ? p->l : p->r;
    }
    return nullptr;
}


rbNode *RBTree::uncle(rbNode *n) {
    // 1. when n is null, return null
    // 2. when grandparent null, return null (root is either n or parent(n))
    // 3. else, has uncle
    //    if parent is gp.left, return right; vice verse
    if (n) {
        rbNode *gp = grandP(n);
        if (gp) return parent(n) == gp->l ? gp->r : gp->l;
    }
    return nullptr;
}

//// -------------print-----------------

void RBTree::_print_(rbNode *node) const {
    // if red print color
    // if occurrence > 1, print occur
    // else just key
    std::cout << "" << node->key->bNum;
    if (node->color == RED) std::cout << "R";
//    if (node->occur > 1) std::cout << "(" << node->occur << ")";
    std::cout << " ";
//    printf("[key=%d,c=%s,n=%d]\t",pa->key,_colorName_(pa->color).c_str(),pa->occur);
}

//public func

void RBTree::rbTraverse() {
    _rbTraverse_(this->ro);
}


void RBTree::rbTraversePre() {
    _rbTraversePre_(this->ro);
}


void RBTree::rbTraversePost() {
    _rbTraversePost_(this->ro);
}

// private func, recursive

void RBTree::_rbTraverse_(rbNode *tree) const {
    if (tree == nullptr) return;
    _rbTraverse_(tree->l);
    _print_(tree);
    _rbTraverse_(tree->r);
}


void RBTree::_rbTraversePre_(rbNode *tree) const {
    if (tree == nullptr) return;
    _print_(tree);
    _rbTraversePre_(tree->l);
    _rbTraversePre_(tree->r);
}


void RBTree::_rbTraversePost_(rbNode *tree) const {
    if (tree == nullptr) return;
    _rbTraversePost_(tree->l);
    _rbTraversePost_(tree->r);
    _print_(tree);
}

///--------------print----------------
///--------------search---------------

rbNode *RBTree::_rbSearch_(rbNode *tree, RBKEY key) const {
    // search node by key, time O(log)
    // 1. if node is null, return null
    // 2. if n.key < key, goto right, vice verse
    // recursive, just find
    if (tree == nullptr) return nullptr;
    else if (tree->key->bNum == key->bNum) return tree;
    else return _rbSearch_((tree->key->bNum > key->bNum) ? tree->l : tree->r, key);
}

//public

rbNode *RBTree::rbSearch(RBKEY key, int mode) {
    // mode 0 return null if yes, mode 1, return successor
    return mode == 0 ? _rbSearch_(ro, key) : _rbSearchIter_(ro, key);
}

rbNode *RBTree::_rbSearchIter_(rbNode *tree, RBKEY key) const {
    // return right nearest key if no such node found
    // last right parent
    rbNode *tmp = nullptr; // save last tree value
    // normal search
    while (tree && tree->key->bNum != key->bNum) {
        tmp = tree;
        tree = key->bNum > tree->key->bNum ? tree->r : tree->l;
    }
    if (tree == nullptr) { // not found
        while (tmp != nullptr) { // has parent node
            // tmp is not left child, go up
            tmp = tmp->pa;
            if (tmp == nullptr) {// last tmp is already root, still not found
                break;
            } else if (tmp->l->pa == tmp) { // last tmp is left child
                tree = tmp->l;// found
            } else; //go up
        }
    }
    return tree;
}

// find max node in subtree

rbNode *RBTree::_maxNode_(rbNode *tree) {
    while (tree->r) tree = tree->r;
    return tree;
}

// find minimum in subtree

rbNode *RBTree::_minNode_(rbNode *tree) {
    while (tree->l) tree = tree->l;
    return tree;
}

// below are used for replace degree 2 node

rbNode *RBTree::_priorNode_(rbNode *tree) {
    // find the predecessor,
    // 1. if left exists, max in left subtree
    // 2. go upwards until the first node who has right child.
    if (tree->l) return _maxNode_(tree->l);
    rbNode *p = tree->pa;
    while (p && tree == p->l) {
        // p is not null, tree is left child, continue
        tree = p;
        p = p->pa;
    }
    return p;
}


rbNode *RBTree::_postNode_(rbNode *tree) {
    // find the successor,
    // 1. if right exists, min in right subtree
    // 2. go upwards until the first node who has left child.
    if (tree->r) return _minNode_(tree->r);
    rbNode *p = tree->pa;
    while (p && tree == p->r) {
        // p is not null, tree is left child, continue
        tree = p;
        p = p->pa;
    }
    return p;
}


void RBTree::lRotate(rbNode *&root, rbNode *n) {
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
    rbNode *p = n->r;
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


void RBTree::rRotate(rbNode *&root, rbNode *n) {
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
    rbNode *p = n->l;
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


void RBTree::rbInsert(RBKEY key) {
    // possibly this could fail!
    auto n = new rbNode(key, BLACK); // delete in remove
    key->rbn = n;
    _insert_(this->ro, n);
    // without repair, it's correct
    _repairInsert_(this->ro, n);
//    if (this->debug) {
//        std::cout << "\n------ins: rbInsert-------\n";
//        rbTraverse(); //&
//    }
}


void RBTree::_insert_(rbNode *&root, rbNode *&n) {
    // insert p into tree with root=n
    // find next insert place by search
    // could be null when root
    auto *p = root;
    rbNode *pp = nullptr; // register p
    while (p) { // search iteratively like a bst
        pp = p;
        if (n->key->bNum == p->key->bNum) {
            // TODO inserting same bNum, exit and print
            cout << "Inserting Same Building Number" << endl;
            throw std::exception();
            break;
        } else p = n->key->bNum > p->key->bNum ? p->r : p->l;
    }
    n->pa = pp; // find the insert position parent
    if (pp) {
        // decide whether left child or right child
        if (n->key->bNum > pp->key->bNum) pp->r = n;
        else pp->l = n;
    } else root = n;// when parent of insertion is null, that's root
    n->color = RED;//default insert color is red, repair later
}


void RBTree::_repairInsert_(rbNode *&root, rbNode *&n) {
    // allow function call recursively
    rbNode *p = parent(n);
    if (!p) { // parent doesn't exists
        _inCaseRoot_(root, n); // n is root node,set black
    } else if (p->color == BLACK) { ; // no two consecutive red, no repair
        if (this->debug) cout << "case 2:no need on key=" << n->key->bNum << endl;
    } else if (uncle(n) && uncle(n)->color == RED) {
        // has red uncle and red parent
        // flip color, recursively running repair
        if (this->debug) cout << "case 3: flip on key=" << n->key->bNum << endl;
        _inCaseXYr_(root, n); // recursive step
    } else {
        // when uncle is black, LL LR RR RL
        if (this->debug) cout << "case 4:rotate on key=" << n->key->bNum << endl;
        _inCaseXYb_(root, n);
    }
}


void RBTree::print(rbNode *tree, RBKEY key, lr_t dir) {
    // recursively pre order print tree and relationship
    if (tree != nullptr) {
        if (dir == ROOT)    // root
            std::cout << tree->key->bNum << "(B) is root" << std::endl;
        else {               // subtree
            std::cout << tree->key->bNum << (tree->color == RED ? "(R)" : "(B)") \
 << " is " << key->bNum << "'s " << \
             (dir == RIGHT ? "right" : "left") << std::endl;
        }
        print(tree->l, tree->key, LEFT); //left
        print(tree->r, tree->key, RIGHT);
    }
}


void RBTree::print() {
    if (this->ro != nullptr)
        print(this->ro, this->ro->key, ROOT);
}


void RBTree::_inCaseRoot_(rbNode *&root, rbNode *&n) {
    n->color = BLACK; // black root
    if (this->debug) cout << "case 1:root insert on key=" << n->key->bNum << endl;
}


void RBTree::_inCaseXYr_(rbNode *&root, rbNode *&n) {
    // parent and uncle are red, flip color
    n->pa->color = BLACK;
    uncle(n)->color = BLACK;
    grandP(n)->color = RED;
    // repeat upwards, two step
    auto *gp = grandP(n);
    _repairInsert_(root, gp);
}


void RBTree::_inCaseXYb_(rbNode *&root, rbNode *&n) {
    // 1. no uncle, same as uncle is black
    // 2. uncle is black, pa=gp.left and pa.left=n, LL
    // 3. .. pa=gp.ro and pa.ro = n, rr
    // 4. .. pa=gp.l and pa.ro = n, lr
    // 5. .. pa=gp.ro and pa.l = n. rl
    // rotate LL,RR,LR,RL in parent
    // LR means lRotate on p then rRotate on gp
    // RL means rRotate on p then lRotate on gp
    rbNode *gp = parent(n->pa);
    // LR first step
    if (!gp) { // gp is null, do nothing
        if (this->debug) cout << "case 4.1:no gp on key=" << n->key->bNum << endl;
    } else if (n == n->pa->r && n->pa == gp->l) { //LRb, same as LR
        // first step of LR
        if (this->debug) cout << "case 4.2:LR step1 on key=" << n->key->bNum << endl;
        lRotate(root, n->pa);
        if (this->debug) print();
        n = n->l;
    } else if (n == n->pa->l && n->pa == gp->r) { // RLb, same as RL
        // first step of RL
        if (this->debug) cout << "case 4.3:RL step1 on key=" << n->key->bNum << endl;
        rRotate(root, n->pa);
        if (this->debug) print();
        n = n->r;
    }
    gp = parent(n->pa);
    if (n == n->pa->l) {// LL or second step of LR
        if (this->debug) cout << "case 4.4:R rotation on key=" << n->pa->key->bNum << endl;
        rRotate(root, gp);
        if (this->debug) print();
    } else { // RR or second step of RL
        if (this->debug) cout << "case 4.5:L rotation on key=" << n->pa->key->bNum << endl;
        lRotate(root, gp);
        if (this->debug) print();
    }
    // color change
    n->pa->color = BLACK;
    if (gp) gp->color = RED;
}


void RBTree::_repairRemove_(rbNode *&root, rbNode *n, rbNode *p) {
    // remove has many cases
    // basically, 1.
    rbNode *sib;
    while ((!n || n->color == BLACK) && n != root) {
        if (p->l == n) {
            sib = p->r;
            if (sib->color == RED) {
                // Case 1: sibling of x is red
                sib->color = BLACK;
                p->color = RED;
                lRotate(root, p);
                sib = p->r;
            }
            if ((!sib->l || sib->l->color == BLACK) &&
                (!sib->r || sib->r->color == BLACK)) {
                // Case 2: black sibling, its children are black
                sib->color = RED;
                n = p;
                p = parent(n);
            } else {
                if (!sib->r || sib->r->color == BLACK) {
                    // Case 3: sib is black, sib left red, right black
                    sib->l->color = BLACK;
                    sib->color = RED;
                    rRotate(root, sib);
                    sib = p->r;
                }
                // Case 4: sib is black, sib .right red
                sib->color = p->color;
                p->color = BLACK;
                sib->r->color = BLACK;
                lRotate(root, p);
                n = root;
                break;
            }
        } else {
            sib = p->l;
            if (sib->color == RED) {
                // Case 1: sib is red
                sib->color = BLACK;
                p->color = RED;
                rRotate(root, p);
                sib = p->l;
            }
            if ((!sib->l || sib->l->color == BLACK) &&
                (!sib->r || sib->r->color == BLACK)) {
                // Case 2: sib is black, sib children are black
                sib->color = RED;
                n = p;
                p = parent(n);
            } else {
                if (!sib->l || sib->l->color == BLACK) {
                    // Case 3: sib is black, sib left red, right black
                    sib->r->color = BLACK;
                    sib->color = RED;
                    lRotate(root, sib);
                    sib = p->l;
                }
                // Case 4:  sib is black, sib .right red
                sib->color = p->color;
                p->color = BLACK;
                sib->l->color = BLACK;
                rRotate(root, p);
                n = root;
                break;
            }
        }
    }
    if (n)
        n->color = BLACK;
}


bool RBTree::_remove_(rbNode *&root, rbNode *n) {
    // when n has both children
    if ((n->l != nullptr) && (n->r != nullptr)) {
        _rmCase1_(root, n);
    } else {
        _rmCase2_(root, n);
    }
    return true;
}


bool RBTree::rbRemove(RBKEY key) {
//    rbNode *node = rbSearch(key, 0);
    rbNode *node = key->rbn;
    if (node != nullptr)
        return _remove_(ro, node);
    else return false;
}

rbNode *RBTree::priorNode(rbNode *tree) {
    return _priorNode_(tree);
}

rbNode *RBTree::postNode(rbNode *tree) {
    return _postNode_(tree);
}

void RBTree::_rmCase1_(rbNode *&root, rbNode *n) {
    // both children exist
    rbNode *rep_r, *p;
    color_t c;
    p = parent(n);
    // find the successor node
    rbNode *rep = _postNode_(n);// replace node if deleting a degree 2 node
    // parent -> rep
    if (p) {// node is not root
        if (p->l == n)
            p->l = rep;
        else
            p->r = rep;
    } else root = rep;// replace root if n is root

    // child is replace's right,the one to be modify
    // replace  has no left child, because its a successor
    rep_r = rep->r; // save rep.right
    c = rep->color; // save color of rep
    p = parent(rep);
    if (p == n) { // rep only has right child
        p = rep; // just connect
    } else { // has left child
        if (rep_r) rep_r->pa = p;// rep -> p
        p->l = rep_r; //p -> rep
        rep->r = n->r; // child pointer
        n->r->pa = rep;
    }
    // do replace
    rep->pa = n->pa;
    rep->color = n->color;
    rep->l = n->l;
    n->l->pa = rep;

    if (c == BLACK) // Rb0 case 1 py is black
        _repairRemove_(root, rep_r, p);
    else; // Rb0 case 2 py is red
    delete n;
}

void RBTree::_rmCase2_(rbNode *&root, rbNode *n) {
    // only one child of deleted node
    rbNode *child, *p;
    color_t c;
    child = (n->l) ? n->l : n->r;
    p = parent(n);
    c = n->color;// save color
    if (child) child->pa = p; //child -> p
    if (p) {// not root
        if (p->l == n) p->l = child;
        else p->r = child;
    } else root = child;
    if (c == BLACK)
        _repairRemove_(root, child, p);
    delete n;

}