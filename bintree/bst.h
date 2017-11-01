#ifndef _BST_H_
#define _BST_H_
#include "../ds.h"

using namespace ds;
template <typename T, typename V>
class BST : public ds::linkedBinaryTree<pair<T, V>>{
public:
    typedef binaryTreeNode<pair<T, V>>* node_pointer;
    typedef linkedBinaryTree<pair<T, V>> _Base_type;

    BST(node_pointer r) : _Base_type(r){}
    virtual node_pointer search(const T&);
    virtual node_pointer insert(const pair<T, V>&);
    // virtual bool remove(const T&);
    void setparent(node_pointer p);//设置自己的parent
    
    node_pointer min();
    node_pointer max();
    node_pointer successor(node_pointer);
    node_pointer predecessor(node_pointer);

protected:    
    binaryTreeNode<T>* connect34(
        node_pointer, node_pointer, node_pointer,
        node_pointer, node_pointer, node_pointer,
        node_pointer
    );
    node_pointer rotateAt(node_pointer);
    node_pointer _hot;
private:
    node_pointer min(node_pointer);
    node_pointer max(node_pointer);
};


#endif // _BST_H_