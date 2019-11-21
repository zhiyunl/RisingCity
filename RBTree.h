//
// Created by zhiyunl on 11/16/19.
//

#ifndef RISINGCITY_RBTREE_H
#define RISINGCITY_RBTREE_H

#include <iostream>
//#include "BSTree.h"

//typedef int KEY;
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

template<class KEY>
struct rbNode {
    rbNode *pa; // parent
    rbNode *l; // left child
    rbNode *r; // right child
    color_t color;
    KEY key;
    int occur; //add count to deal with multiple same key nodes

    rbNode(KEY val, color_t c, rbNode *p, rbNode *l, rbNode *r, int occur) :
            key(val), color(c), pa(), l(l), r(r), occur() {}

};

// ---------------
// NOTE
// use sentinel node to represent leaf node can save marginal run time, instead of null
// use one sentinel node to represent all NIL across the whole tree
// source:https://en.wikipedia.org/wiki/Sentinel_node#Second_version_using_a_sentinel_node
// ---------------
template<class KEY>
class RBTree {
public:
    bool debug; // true to print tree

private:
    rbNode<KEY> *ro; // save root pointer


//    // 前序遍历"红黑树"
//    void preOrder(RBTNode <T> *tree) const;
//
//    // 中序遍历"红黑树"
//    void inOrder(RBTNode <T> *tree) const;
//
//    // 后序遍历"红黑树"
//    void postOrder(RBTNode <T> *tree) const;

public:
    // constructor
    RBTree();

    // destructor
    ~RBTree();

    // in order
    void rbTraverse();

    // pre order
    void rbTraversePre();

    // post order
    void rbTraversePost();
    // bfs
//    void rbTraverseBFS();

    // init a red-black tree using array
    void rbInit(KEY *arr); //use
    // get grandparent
    rbNode<KEY> *grandP(rbNode<KEY> *n);

    //get parent
    rbNode<KEY> *parent(rbNode<KEY> *n);

    // get sibling
    rbNode<KEY> *sibling(rbNode<KEY> *n);

    // get uncle
    rbNode<KEY> *uncle(rbNode<KEY> *n);

    //
    rbNode<KEY> *rbSearch(KEY key);

    rbNode<KEY> *rbSearchIter(KEY key);

    // top level, manage insert conditions, create node
    void rbInsert(KEY key);

    void print();

private:
    // print
    void _print_(rbNode<KEY> *node) const;

    // in order
    void _rbTraverse_(rbNode<KEY> *tree) const;

    // pre order
    void _rbTraversePre_(rbNode<KEY> *tree) const;

    // post order
    void _rbTraversePost_(rbNode<KEY> *tree) const;
    // bfs
//    void rbTraverseBFS(rbNode<KEY> *tree) const;

    rbNode<KEY> *_rbSearch_(rbNode<KEY> *tree, KEY key) const;

    rbNode<KEY> *_rbSearchIter_(rbNode<KEY> *tree, KEY key) const;

    rbNode<KEY> *_maxNode_(rbNode<KEY> *tree);

    rbNode<KEY> *_minNode_(rbNode<KEY> *tree);

    rbNode<KEY> *_priorNode_(rbNode<KEY> *tree);

    rbNode<KEY> *_postNode_(rbNode<KEY> *tree);

    void lRotate(rbNode<KEY> *&root, rbNode<KEY> *n);

    void rRotate(rbNode<KEY> *&root, rbNode<KEY> *n);


    // lower level, just insert
    void _insert_(rbNode<KEY> *&root, rbNode<KEY> *&n);

    void _repairInsert_(rbNode<KEY> *&root, rbNode<KEY> *&n);

//    rbNode<KEY> *rmNode(rbNode<KEY> *p); // use this.root
//
//    void *rbRemove(rbNode<KEY> *&root, rbNode<KEY> *n);
//
//    void *repairRemove(rbNode<KEY> *&root, rbNode<KEY> *n);

//    <KEY> *rmCase(rbNode *n, rmcase_t c);
//
//    rbNode<KEY> *rmNode2(rbNode *n, rbNode *rm);
//
//    rbNode *replace(rbNode *n, rbNode *child);
//
//    rbNode *rmNode1(rbNode *n);
//
//    rbNode *rmNode0(rbNode *n);
    void print(rbNode<KEY> *tree, KEY key, int direction);


//    static std::string _colorName_(color_t color);

    void inCase1(rbNode<KEY> *&root, rbNode<KEY> *&n);

    void inCase2(rbNode<KEY> *&root, rbNode<KEY> *&n);

    void inCase3(rbNode<KEY> *&root, rbNode<KEY> *&n);

    void inCase4(rbNode<KEY> *&root, rbNode<KEY> *&n);

//    rbNode *findRoot(rbNode *n);
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r, p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r, c)  do { (r)->color = (c); } while (0)
};


#endif //RISINGCITY_RBTREE_H
