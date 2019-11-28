/*
 * @Author: zhiyunl
 * @Date: 2019-11-16 22:21:59
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-27 22:26:20
 * @Description: 
 */


#ifndef RISINGCITY_RBTREE_H
#define RISINGCITY_RBTREE_H

typedef struct mhNode *RBKEY;

enum color_t {
    BLACK, RED
};
enum lr_t {
    ROOT, LEFT, RIGHT
};


struct rbNode {
    RBKEY key; // RBKEY is mhNode*, points to mhTree
    color_t color;
    rbNode *pa; // parent
    rbNode *l; // left child
    rbNode *r; // right child
    rbNode(RBKEY val, color_t c) :
            key(val), color(c), pa(), l(), r() {}
};

// ---------------
// NOTE
// use sentinel node to represent leaf node can save marginal run time, instead of null
// use one sentinel node to represent all NIL across the whole tree
// source:https://en.wikipedia.org/wiki/Sentinel_node#Second_version_using_a_sentinel_node
// ---------------

class RBTree {
public:
    bool debug; // true to print tree
private:
    rbNode *ro; // save root pointer
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
    // init a red-black tree using array
    static void rbInit(RBKEY *arr); //use
    // get grandparent
    static rbNode *grandP(rbNode *n);
    //get parent
    static rbNode *parent(rbNode *n);
    // get sibling
    static rbNode *sibling(rbNode *n);
    // get uncle
    static rbNode *uncle(rbNode *n);

    // search by key, mode: 0 is normal, 1: return node or its successor
    rbNode *rbSearch(RBKEY key, int mode);
    // top level, manage insert conditions, create node
    void rbInsert(RBKEY key);

    // top level, call _remove_ and pass this->root to it.
    bool rbRemove(RBKEY key);

    //print the rbtree for debug
    void print();

    // find the prior node by sequence
    static rbNode *priorNode(rbNode *tree);

    // find the successor/post node by sequence
    rbNode *postNode(rbNode *tree);
private:
    // low level print
    void _print_(rbNode *node) const;
    // in order
    void _rbTraverse_(rbNode *tree) const;
    // pre order
    void _rbTraversePre_(rbNode *tree) const;
    // post order
    void _rbTraversePost_(rbNode *tree) const;

    // low level search recursively
    rbNode *_rbSearch_(rbNode *tree, RBKEY key) const;

    // low level search iteratively
    rbNode *_rbSearchIter_(rbNode *tree, RBKEY key) const;

    // find the maximum node in the tree
    static rbNode *_maxNode_(rbNode *tree);

    // find the minimum
    static rbNode *_minNode_(rbNode *tree);
    static rbNode *_priorNode_(rbNode *tree);
    static rbNode *_postNode_(rbNode *tree);

    // do left rotation
    static void lRotate(rbNode *&root, rbNode *n);

    // do right rotation
    static void rRotate(rbNode *&root, rbNode *n);
    // lower level, just insert
    void _insert_(rbNode *&root, rbNode *&n);

    // control repair process after insert
    void _repairInsert_(rbNode *&root, rbNode *&n);

    // low level remove
    bool _remove_(rbNode *&root, rbNode *n);

    // control repair process after remove
    void _repairRemove_(rbNode *&root, rbNode *n, rbNode *p);

    // print tree either left first or right first
    static void print(rbNode *tree, RBKEY key, lr_t dir);

    // insert repair, case: n is root
    void _inCaseRoot_(rbNode *&root, rbNode *&n);

    // insert repair, case XYr
    void _inCaseXYr_(rbNode *&root, rbNode *&n);

    // insert repair, case XYb
    void _inCaseXYb_(rbNode *&root, rbNode *&n);

    // remove repair, case degree 2 node
    void _rmCase1_(rbNode *&root, rbNode *n);

    // remove repair, case else
    void _rmCase2_(rbNode *&root, rbNode *n);
};


#endif //RISINGCITY_RBTREE_H
