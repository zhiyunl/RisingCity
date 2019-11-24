//
// Created by zhiyunl on 11/16/19.
//

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
    RBKEY key;
    color_t color;
    rbNode *pa; // parent
    rbNode *l; // left child
    rbNode *r; // right child

//    rbNode(RBKEY val, color_t c, rbNode *p, rbNode *l, rbNode *r) :
//            key(val), color(c), pa(p), l(l), r(r) {}
    rbNode(RBKEY val, color_t c) :
            key(val), color(c), pa(), l(), r() {}
//    rbNode() = default;
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
    // bfs
//    void rbTraverseBFS();

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

    //
    rbNode *rbSearch(RBKEY key, int mode);

//    rbNode  *rbSearchIter(RBKEY key);

    // top level, manage insert conditions, create node
    void rbInsert(RBKEY key);

    bool rbRemove(RBKEY key);

    void print();

    static rbNode *priorNode(rbNode *tree);

    static rbNode *postNode(rbNode *tree);

private:
    // print
    void _print_(rbNode *node) const;

    // in order
    void _rbTraverse_(rbNode *tree) const;

    // pre order
    void _rbTraversePre_(rbNode *tree) const;

    // post order
    void _rbTraversePost_(rbNode *tree) const;
    // bfs
//    void rbTraverseBFS(rbNode  *tree) const;

    rbNode *_rbSearch_(rbNode *tree, RBKEY key) const;

    rbNode *_rbSearchIter_(rbNode *tree, RBKEY key) const;

    static rbNode *_maxNode_(rbNode *tree);

    static rbNode *_minNode_(rbNode *tree);

    static rbNode *_priorNode_(rbNode *tree);

    static rbNode *_postNode_(rbNode *tree);

    static void lRotate(rbNode *&root, rbNode *n);

    static void rRotate(rbNode *&root, rbNode *n);

    // lower level, just insert
    static void _insert_(rbNode *&root, rbNode *&n);

    void _repairInsert_(rbNode *&root, rbNode *&n);

    static bool _remove_(rbNode *&root, rbNode *n);

    static void _repairRemove_(rbNode *&root, rbNode *n, rbNode *p);

    static void print(rbNode *tree, RBKEY key, lr_t dir);

    void inCase1(rbNode *&root, rbNode *&n);

    static void inCase2(rbNode *&root, rbNode *&n);

    void inCase3(rbNode *&root, rbNode *&n);

    void inCase4(rbNode *&root, rbNode *&n);

    static void rmCase1(rbNode *&root, rbNode *n);

    static void rmCase2(rbNode *&root, rbNode *n);

//    rbNode *findRoot(rbNode *n)
};


#endif //RISINGCITY_RBTREE_H
