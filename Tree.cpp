/*
 * @Author: zhiyunl
 * @Date: 2019-11-16 23:52:47
 * @LastEditors: zhiyunl
 * @LastEditTime: 2019-11-16 23:55:05
 * @Description: 
 */

#include<iostream>

using namespace std;


class Node {
public:
    Node(int val) : _val(val) {}

    int val() { return _val; }

    void add(Node *temp) {
        if (temp->val() > _val) {
            if (_rchild)
                _rchild->add(temp);
            else {
                _rchild = temp;
            }
        } else {
            if (_lchild)
                _lchild->add(temp);
            else {
                _lchild = temp;
            }
        }
    }

    void print() {
        for (int ix = 0; ix < _level; ++ix) cout << ' ';
        cout << _val << endl;
        ++_level;
        if (_lchild) {
            _lchild->print();
            --_level;
        }
        if (_rchild) {
            _rchild->print();
            --_level;
        }
    }

private:
    int _val;
    Node *_lchild;
    Node *_rchild;
    static int _level;
};

int Node::_level = 0;

class Tree {
public:
    Tree() : _root(0) {}

    void add(int val) {
        Node *temp = new Node(val);
        if (!_root)
            _root = temp;
        else
            _root->add(temp);
    }

    void print() {
        if (!_root)
            return;
        _root->print();
    }

private:
    Node *_root;
};

int main() {
    Tree tree;
    tree.add(5);
    tree.add(9);
    tree.add(1);
    tree.add(7);
    tree.add(5);
    tree.add(14);
    tree.print();
}