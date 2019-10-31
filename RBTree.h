//
// Created by Zhiyun Ling on 10/28/19.
//

#ifndef RISINGCITY_RBTREE_H
#define RISINGCITY_RBTREE_H

#define KEYTYPE char
#define NODETYPE rbNode*
#define XYr 1
#define LLb 2
#define LRb 3
#define RRb 4
#define RLb 5
#define Rb0b 11
#define Rb0r 12
#define Rb11 13
#define Rb12 14
#define Rb2 15
#define Rr0 16
#define Rr11 17
#define Rr12 18
#define Rr2 19

struct rbNode{
    enum {r, b} color;
    KEYTYPE key;
    struct rbNode* left, right, parent;
};

class RBTree {
public:
    int search(KEYTYPE key);
    void rrRotate(void);
    void llRotate(void);
    void lrRrotate(void);
    void rlRotate(void);
    int checkTwoRed(NODETYPE gp, NODETYPE pp, NODETYPE p);
    void insert(KEYTYPE key);
    void deleteNode(KEYTYPE key);
    int checkRebalance(NODETYPE X, NODETYPE c, NODETYPE n);
    void rebalance(void);
};


#endif //RISINGCITY_RBTREE_H
