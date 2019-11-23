//
// Created by zhiyunl on 11/16/19.
//
#include "RBTree.h"
#include <iostream>
#include "MinHeap.h"

using namespace std;

// when using  , compiler generate class automatically
// possible type of RBKEY is listed below,
// otherwise, there will be error


RBTree::RBTree() : ro(NULL) {
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

//rbNode *RBTree::rbSearchIter(RBKEY key) {
//    return _rbSearchIter_(this->ro, key);
//}

// private, iteratively search node by key

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
    auto n = new rbNode(key, BLACK, nullptr, nullptr, nullptr);
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
            // deal with same key by adding a occur
//            p->occur += n->occur;
            throw;
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
    rbNode *p = parent(n);
    if (!p) { // parent doesn't exists
        inCase1(root, n); // n is root node,set black
    } else if (p->color == BLACK) {  // no two consecutive red, no repair
//        inCase2(root,n);
        if (this->debug) cout << "case 2:no need on key=" << n->key->bNum << endl;
    } else if (uncle(n) && uncle(n)->color == RED) {
        // has red uncle and red parent
        // flip color, recursively running repair
        if (this->debug) cout << "case 3: flip on key=" << n->key->bNum << endl;
        inCase3(root, n);
    } else {
        // LL LR RR RL,
        if (this->debug) cout << "case 4:rotate on key=" << n->key->bNum << endl;
        inCase4(root, n);
    }
}


void RBTree::print(rbNode *tree, RBKEY key, lr_t dir) {
    // recursively pre order print tree and relationship
    if (tree != NULL) {
        if (dir == ROOT)    // root
            std::cout << tree->key->bNum << "(B) is root" << std::endl;
        else {               // subtree
            std::cout << tree->key->bNum << (tree->color == RED ? "(R)" : "(B)") \
 << " is " << key << "'s " << \
             (dir == RIGHT ? "right" : "left") << std::endl;
        }
        print(tree->l, tree->key, LEFT); //left
        print(tree->r, tree->key, RIGHT);
    }
}


void RBTree::print() {
    if (this->ro != NULL)
        print(this->ro, this->ro->key, ROOT);
}


void RBTree::inCase1(rbNode *&root, rbNode *&n) {
    n->color = BLACK; // black root
    if (this->debug) cout << "case 1:root insert on key=" << n->key->bNum << endl;
}


void RBTree::inCase2(rbNode *&root, rbNode *&n) {
    ;
}


void RBTree::inCase3(rbNode *&root, rbNode *&n) {
    // parent and uncle are red, flip color
    n->pa->color = BLACK;
    uncle(n)->color = BLACK;
    grandP(n)->color = RED;
    // repeat upwards, two step
    auto *gp = grandP(n);
    _repairInsert_(root, gp);
}


void RBTree::inCase4(rbNode *&root, rbNode *&n) {
    // complicated
    // 1. no uncle, same as uncle is black
    // 2. uncle is black, pa=gp.left and pa.left=n, LL
    // 3. .. pa=gp.ro and pa.ro = n, rr
    // 4. .. pa=gp.l and pa.ro = n, lr
    // 5. .. pa=gp.ro and pa.l = n. rl
    // rotate LL,RR,LR,RL in parent
    // LR means lrotate on p then rrotate on gp
    // RL means rtotate on p then lrotate on gp
//    rbNode  *p = parent(n);
    rbNode *gp = parent(n->pa);
    // LR first step
    if (!gp) {
        // when gp is null, no lr or rl
        ;
        if (this->debug) cout << "case 4.1:no gp on key=" << n->key->bNum << endl;
    } else if (n == n->pa->r && n->pa == gp->l) {
        // n is right child and p is left child, LR
        if (this->debug) cout << "case 4.2:LR step1 on key=" << n->key->bNum << endl;
        lRotate(root, n->pa);
        if (this->debug) print();
        n = n->l;
    } else if (n == n->pa->l && n->pa == gp->r) {
        // RL first step
        if (this->debug) cout << "case 4.3:RL step1 on key=" << n->key->bNum << endl;
        rRotate(root, n->pa);
        if (this->debug) print();
        n = n->r;
    }
//    p = parent(n);
    gp = parent(n->pa);
    // LL or second step of LR
    if (n == n->pa->l) {
        if (this->debug) cout << "case 4.4:R rotation on key=" << n->pa->key->bNum << endl;
        rRotate(root, gp);
        if (this->debug) print();
    } else {    // RR or second step of RL
        if (this->debug) cout << "case 4.5:L rotation on key=" << n->pa->key->bNum << endl;
        lRotate(root, gp);
        if (this->debug) print();
    }
    // color change
    n->pa->color = BLACK;
    if (gp) gp->color = RED;
}


void RBTree::_repairRemove_(rbNode *&root, rbNode *n, rbNode *p) {
    rbNode *other;

    while ((!n || rb_is_black(n)) && n != root) {
        if (p->l == n) {
            other = p->r;
            if (other->color == RED) {
                // Case 1: x的兄弟w是红色的
                other->color = BLACK;
                p->color = RED;
                lRotate(root, p);
                other = p->r;
            }
            if ((!other->l || rb_is_black(other->l)) &&
                (!other->r || rb_is_black(other->r))) {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                n = p;
                p = parent(n);
            } else {
                if (!other->r || rb_is_black(other->r)) {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->l);
                    rb_set_red(other);
                    rRotate(root, other);
                    other = p->r;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, p->color);
                rb_set_black(p);
                rb_set_black(other->r);
                lRotate(root, p);
                n = root;
                break;
            }
        } else {
            other = p->l;
            if (other->color == RED) {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(p);
                rRotate(root, p);
                other = p->l;
            }
            if ((!other->l || rb_is_black(other->l)) &&
                (!other->r || rb_is_black(other->r))) {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                n = p;
                p = parent(n);
            } else {
                if (!other->l || rb_is_black(other->l)) {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->r);
                    rb_set_red(other);
                    lRotate(root, other);
                    other = p->l;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, p->color);
                rb_set_black(p);
                rb_set_black(other->l);
                rRotate(root, p);
                n = root;
                break;
            }
        }
    }
    if (n)
        rb_set_black(n);
}


rbNode *RBTree::_remove_(rbNode *&root, rbNode *n) {
    rbNode *child, *p;
    color_t c;
    if ((n->l != nullptr) && (n->r != nullptr)) {
        rbNode *rep = n;
        rep = rep->r;
        while (rep->l != nullptr)
            rep = rep->l;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (parent(n)) {
            if (parent(n)->l == n)
                parent(n)->l = rep;
            else
                parent(n)->r = rep;
        } else
            // "node节点"是根节点，更新根节点。
            root = rep;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = rep->r;
        p = parent(rep);
        // 保存"取代节点"的颜色
        c = rep->color;

        // "被删除节点"是"它的后继节点的父节点"
        if (p == n) {
            p = rep;
        } else {
            // child不为空
            if (child)
                rb_set_parent(child, p);
            p->l = child;

            rep->r = n->r;
            rb_set_parent(n->r, rep);
        }

        rep->pa = n->pa;
        rep->color = n->color;
        rep->l = n->l;
        n->l->pa = rep;

        if (c == BLACK)
            _repairRemove_(root, child, p);

//        delete n;
        return n;
    }

    if (n->l != nullptr)
        child = n->l;
    else
        child = n->r;

    p = n->pa;
    // 保存"取代节点"的颜色
    c = n->color;

    if (child)
        child->pa = p;

    // "node节点"不是根节点
    if (p) {
        if (p->l == n)
            p->l = child;
        else
            p->r = child;
    } else
        root = child;

    if (c == BLACK)
        _repairRemove_(root, child, p);
//    delete n;
    return n;
}


rbNode *RBTree::rmCase(rbNode *n, rmcase_t c) {
    return nullptr;
}


rbNode *RBTree::replace(rbNode *n, rbNode *child) {
    return nullptr;
}


rbNode *RBTree::rbRemove(RBKEY key) {
    rbNode *node = rbSearch(key, 0);
    if (node != nullptr)
        return _remove_(ro, node);
    else return nullptr;
}

rbNode *RBTree::priorNode(rbNode *tree) {
    return _priorNode_(tree);
}

rbNode *RBTree::postNode(rbNode *tree) {
    return _postNode_(tree);
}


