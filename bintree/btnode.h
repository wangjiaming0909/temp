#ifndef _BTNODE_H_
#define _BTNODE_H_
#include <vector>

template <typename T>
struct BTNode{
    typedef BTNode<T> *node_pointer;

    node_pointer parent;
    std::vector<T> key;
    std::vector<node_pointer> child;//指向孩子节点的指针
    BTNode() : parent(nullptr){child.insert(child.begin(), nullptr);}
    BTNode(T e, node_pointer lc = nullptr, node_pointer rc = nullptr)
    : parent(nullptr){
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if(lc) lc->parent = this;
        if(rc) rc->parent = this;
    }
};


#endif //_BTNODE_H_