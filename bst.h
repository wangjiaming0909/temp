#ifndef _BST_H_
#define _BST_H_
#include "ds.h"

using namespace ds;
template <typename T>
class BST : public ds::linkedBinaryTree<T>{
public:
    // virtual binaryTreeNode<T> *search(const T&);
    // virtual binaryTreeNode<T> *insert(const T&);
    // virtual bool remove(const T&);
protected:    
    binaryTreeNode<T>* connect34(
        binaryTreeNode<T>*, binaryTreeNode<T> *, binaryTree<T>*,
        binaryTreeNode<T>*, binaryTreeNode<T>*, binaryTreeNode<T>*,
        binaryTreeNode<T>*
    );
    binaryTreeNode<T>* rotateAt(binaryTreeNode<T> *x);
    binaryTreeNode<T> *_hot;
};


#endif // _BST_H_