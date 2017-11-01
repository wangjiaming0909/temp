#ifndef _BST_H_
#define _BST_H_
#include "ds.h"

using namespace ds;
template <typename T, typename V>
class BST : public ds::linkedBinaryTree<pair<T, V>>{
public:
    BST(binaryTreeNode<pair<T, V>> *r) : linkedBinaryTree<pair<T, V>>(r){}
    virtual binaryTreeNode<pair<T, V>> *search(const T&) const;
    virtual binaryTreeNode<pair<T, V>> *insert(const pair<T, V>&);
    // virtual bool remove(const T&);
protected:    
    binaryTreeNode<T>* connect34(
        binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>> *, binaryTree<pair<T, V>>*,
        binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>>*,
        binaryTreeNode<pair<T, V>>*
    );
    binaryTreeNode<pair<T, V>>* rotateAt(binaryTreeNode<pair<T, V>> *x);
    binaryTreeNode<pair<T, V>>* _hot;
private:
    // pair<binaryTreeNode<pair<T, V>>, bool> search(const pair<T, V> &p);
};

// template <typename T, typename V>
// pair<binaryTreeNode<pair<T, V>>, bool> BST<T, V>::search(const pair<T, V> &p){
//     auto t = search(p.first);
// }
template <typename T, typename V>
binaryTreeNode<pair<T, V>>* BST<T, V>::search(const T& t) const{
    binaryTreeNode<pair<T, V>> *p = this->root;
    while(p != NULL){
        if(t < p->element.first)
            p = p->leftChild;
        else
            if(t > p->element.first)
                p = p->rightChild;
            else
                return p;
    }
    _hot = const_cast<binaryTreeNode<pair<T, V>>*>(p);
    return NULL;
}
    
template <typename T, typename V>
binaryTreeNode<pair<T, V>>* BST<T,V>::insert(const pair<T, V>& t){
    auto p = search(t.first);
    if(p) {
        p->element.second = t.second;
        return p;
    }
    p = new binaryTreeNode<pair<T, V>>(t, nullptr, nullptr);
    if(t.first < _hot->element.first)
        _hot->leftChild = p;
    else
        _hot->rightChild = p;
}
#endif // _BST_H_