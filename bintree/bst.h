#ifndef _BST_H_
#define _BST_H_
#include "../ds.h"

using namespace ds;

#define hasLC(node) ((node)->leftChild)
#define hasRC(node) ((node)->rightChild)
#define hasOneChild(node) \
    ((hasLC(node) && (!hasRC(node))) || (hasRC(node) && (!hasLC(node))))
#define hasC(node)  (hasLC(node) || hasRC(node))
#define isLeaf(node) (!hasC(node))
#define hasBothChild (hasLC(node) && hasRC(node))

template <typename T, typename V>
class BST : public ds::linkedBinaryTree<pair<T, V>>{
public:
    typedef binaryTreeNode<pair<T, V>>* node_pointer;
    typedef linkedBinaryTree<pair<T, V>> _Base_type;

    BST(node_pointer r) : _Base_type(r){}
    virtual node_pointer search(const T&);
    virtual node_pointer insert(const pair<T, V>&);
    virtual bool remove(const T&);
    void setparent(node_pointer p);//设置自己的parent
    
    node_pointer min();
    node_pointer max();
    node_pointer successor(node_pointer);
    node_pointer predecessor(node_pointer);
    void outputRange(const T& low, const T& hi);//输出在low和hi范围内的元素

protected:    
    binaryTreeNode<T>* connect34(
        node_pointer, node_pointer, node_pointer,
        node_pointer, node_pointer, node_pointer,
        node_pointer
    );
    void transplant(node_pointer dest, node_pointer source);
    node_pointer rotateAt(node_pointer);
    node_pointer _hot;
private:
    node_pointer min(node_pointer);
    node_pointer max(node_pointer);
};


#endif // _BST_H_