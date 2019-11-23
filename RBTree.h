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
    rbNode *pa; // parent
    rbNode *l; // left child
    rbNode *r; // right child
    color_t color;
    RBKEY key;

    rbNode(RBKEY val, color_t c, rbNode *p, rbNode *l, rbNode *r) :
            key(val), color(c), pa(), l(l), r(r) {}

    rbNode() = default;

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
    void rbInit(RBKEY *arr); //use
    // get grandparent
    rbNode *grandP(rbNode *n);

    //get parent
    rbNode *parent(rbNode *n);

    // get sibling
    rbNode *sibling(rbNode *n);

    // get uncle
    rbNode *uncle(rbNode *n);

    //
    rbNode *rbSearch(RBKEY key, int mode);

//    rbNode  *rbSearchIter(RBKEY key);

    // top level, manage insert conditions, create node
    void rbInsert(RBKEY key);

    rbNode *rbRemove(RBKEY key);

    void print();

    rbNode *priorNode(rbNode *tree);

    rbNode *postNode(rbNode *tree);

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

    rbNode *_maxNode_(rbNode *tree);

    rbNode *_minNode_(rbNode *tree);

    rbNode *_priorNode_(rbNode *tree);

    rbNode *_postNode_(rbNode *tree);

    void lRotate(rbNode *&root, rbNode *n);

    void rRotate(rbNode *&root, rbNode *n);

    // lower level, just insert
    void _insert_(rbNode *&root, rbNode *&n);

    void _repairInsert_(rbNode *&root, rbNode *&n);

    rbNode *_remove_(rbNode *&root, rbNode *n);

    void _repairRemove_(rbNode *&root, rbNode *n, rbNode *p);

    void print(rbNode *tree, RBKEY key, lr_t dir);


//    static std::string _colorName_(color_t color);

    void inCase1(rbNode *&root, rbNode *&n);

    void inCase2(rbNode *&root, rbNode *&n);

    void inCase3(rbNode *&root, rbNode *&n);

    void inCase4(rbNode *&root, rbNode *&n);

//    rbNode *findRoot(rbNode *n)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r, p)  do { (r)->pa = (p); } while (0)
#define rb_set_color(r, c)  do { (r)->color = (c); } while (0)
};


#endif //RISINGCITY_RBTREE_H
