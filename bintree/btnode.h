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
        key.insert(key.begin(), e);
        child.insert(child.begin(), lc);
        child.insert(1 + child.begin(), rc);
        if(lc) lc->parent = this;
        if(rc) rc->parent = this;
    }
};


#endif //_BTNODE_H_