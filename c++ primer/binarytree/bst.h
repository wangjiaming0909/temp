#ifndef _BST_H_
#define _BST_H_
#include "linkedbinarytree.h"

template <typename T>
class BST : public linkedBinaryTree<T>{
public:
    BST() : linkedBinaryTree<T>(){}
    BST(binaryTreeNode<T>* t) : root(t), treeSize(1){} 
    ~BST() {}
    bool empty() const{return treeSize == 0;}
    int size() const{return treeSize;}
    void preOrder(void (*thevisit)(binaryTreeNode<T>*)){
        visit = thevisit;
        preOrder(root);
    }
private:
    binaryTreeNode<T> *root;
    int treeSize;
    static void (*visit)(binaryTreeNode<T> *);
    void preOrder(binaryTreeNode<T> *); 
};

template <typename T>
void (*BST<T>::visit)(binaryTreeNode<T> *) = myvisit;

template <typename T>
void BST<T>::preOrder(binaryTreeNode<T> *t){
    visit(t);
    preOrder(t->leftChild);
    preOrder(t->rightChild);
}
#endif // _BST_H_