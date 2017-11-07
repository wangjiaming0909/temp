#ifndef _BTREE_H_
#define _BTREE_H_
#include "btnode.h"

template <typename T>
class BTree{
public:
    typedef typename BTNode<T>::node_pointer node_pointer;
    typedef BTNode<T>               node_type;
public:
    BTree(int order = 3) : _size(0), _order(order)
    {_root = new node_type();}
    ~BTree(){
        // if(_root) release(_root);
    }
    int order() const {return _order;}
    int size() const {return _size;}
    node_pointer root(){return _root;}
    bool empty() const{return !_root;} 
    node_pointer search(const T&);
protected:
    int _size;//存放的关键码总数
    int _order;//B-树的阶，至少为3-创建时指定，一般不能修改
    node_pointer _root;
    node_pointer _hot;
};

#endif //_BTREE_H_