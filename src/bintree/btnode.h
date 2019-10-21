#ifndef _BTNODE_H_
#define _BTNODE_H_
#include <vector>
#include <ostream>

template <typename T>
struct BTNode {
using node_pointer = BTNode<T>*;

node_pointer parent;
std::vector<T> key;
std::vector<node_pointer> child;  //指向孩子节点的指针

BTNode() : parent(nullptr) 
{ 
    child.insert(child.begin(), nullptr); 
}

BTNode(T e, node_pointer lc = nullptr, node_pointer rc = nullptr) : parent(nullptr) 
{
    key.insert(key.begin(), e);
    child.insert(child.begin(), lc);
    child.insert(1 + child.begin(), rc);
    if (lc) lc->parent = this;
    if (rc) rc->parent = this;
}

void dump(std::ostream& os)
{
    if(key.size() == 0) return;
    for(size_t i = 0; i < key.size(); i++)
    {
        os << key[i] << " ";
    }
    os << " -> ";
}

};

#endif  //_BTNODE_H_
