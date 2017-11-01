#ifndef _BST_H_
#define _BST_H_
#include "ds.h"

using namespace ds;
template <typename T, typename V>
class BST : public ds::linkedBinaryTree<pair<T, V>>{
public:
    BST(binaryTreeNode<pair<T, V>> *r) : linkedBinaryTree<pair<T, V>>(r){}
    virtual binaryTreeNode<pair<T, V>> *search(const T&) const;
    // virtual binaryTreeNode<T> *insert(const T&);
    // virtual bool remove(const T&);
protected:    
    binaryTreeNode<T>* connect34(
        binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>> *, binaryTree<pair<T, V>>*,
        binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>>*, binaryTreeNode<pair<T, V>>*,
        binaryTreeNode<pair<T, V>>*
    );
    binaryTreeNode<pair<T, V>>* rotateAt(binaryTreeNode<pair<T, V>> *x);
    binaryTreeNode<pair<T, V>>* _hot;
};

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
    return NULL;
}

#endif // _BST_H_