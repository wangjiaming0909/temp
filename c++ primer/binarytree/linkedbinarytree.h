#ifndef _LINKED_BINARY_TREE_H_
#define _LINKED_BINARY_TREE_H_
#include "binarytree.h"
#include <stack>
#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T>>{
public:
    linkedBinaryTree() : root(nullptr), treeSize(0){}
    linkedBinaryTree(const linkedBinaryTree &lbt) : root(lbt.root), treeSize(lbt.treeSize){}
    linkedBinaryTree(binaryTreeNode<T> *r) : root(r), treeSize(0){}
    ~linkedBinaryTree(){erase();}
    bool empty()const {return treeSize == 0;}
    int size() const {return treeSize;}
    void preOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        preOrder3(root);
    }
    void inOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        inOrder2(root);
    }
    void postOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        postOrder(root);
    }
    void levelOrder(void (*)(binaryTreeNode<T> *)){
        visit = myvisit;
        levelOrder(root);
    }
    void erase(){
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    bool operator==(const linkedBinaryTree &bt){
        return compare(root, bt.root);
    }
    void swap_trees();//swap all the left and right child in the tree 
    // size_t max_nodes_level();
    int height() const;
protected:
    binaryTreeNode<T>   *root;
    int                 treeSize;
    static void (*visit) (binaryTreeNode<T> *);//静态变量需要初始化
private:
    static void preOrder(binaryTreeNode<T> *t);
    static void preOrder2(binaryTreeNode<T> *t);
    static void preOrder3(binaryTreeNode<T> *t);
    static void inOrder(binaryTreeNode<T> *t);
    static void inOrder2(binaryTreeNode<T> *t);
    static void postOrder(binaryTreeNode<T> *t);
    static void postOrder2(binaryTreeNode<T> *);
    static void levelOrder(binaryTreeNode<T> *);
    static void dispose(binaryTreeNode<T> *t){delete t;}
    bool compare(binaryTreeNode<T> *ltn, binaryTreeNode<T> *rtn);
    void swap_trees(binaryTreeNode<T> *);
    int height(binaryTreeNode<T> *) const;
    static void visitalongleftbranch(binaryTreeNode<T> *, stack<binaryTreeNode<T>*> &);
    static void goalongleftbranch(binaryTreeNode<T> *, stack<binaryTreeNode<T> *> &);
    static void goalongleftbranch2(binaryTreeNode<T> *, stack<binaryTreeNode<T> *> &);
    
};  


template <class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T> *) = myvisit;

template <class T>
void linkedBinaryTree<T>::swap_trees(){
    swap_trees(root);
}

template <class T>
void linkedBinaryTree<T>::swap_trees(binaryTreeNode<T> *tn){
    if(!tn)
        return;
    if(!tn->leftChild && !tn->rightChild)
        return;
    else{
        swap_trees(tn->leftChild);
        swap_trees(tn->rightChild);
        auto node = tn->leftChild;
        tn->leftChild = tn->rightChild;
        tn->rightChild = node;
    }
       
} 

template <class T>
bool linkedBinaryTree<T>::compare(binaryTreeNode<T> *ltn, binaryTreeNode<T> *rtn){//时间复杂度与先序遍历相同
    if(ltn == NULL && rtn == NULL)
        return true;
    else if(ltn->element == rtn->element){
        if(compare(ltn->leftChild, rtn->leftChild))
            if(compare(ltn->rightChild, rtn->rightChild))
                return true;
    }
    return false;
}

template <class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        linkedBinaryTree<T>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

//非递归版本，自定义栈  版本1
template <class T>
void linkedBinaryTree<T>::preOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T>*> s;
    binaryTreeNode<T> *node;
    s.push(t);
    while(!s.empty()){
        assert(!s.empty());
        node = s.top();
        s.pop();
        visit(node);
        if(node->rightChild != nullptr)
            s.push(node->rightChild);
        if(node->leftChild != nullptr)
            s.push(node->leftChild);
    }
}

//给此函数一个root node, 和一个栈，
//访问次节点，右节点入栈，将此节点置换成左节点
template <typename T>
void linkedBinaryTree<T>::visitalongleftbranch(binaryTreeNode<T> *tt, stack<binaryTreeNode<T>*> &s){
    binaryTreeNode<T> *t = tt;
    while(t){
        visit(t);
        if(t->rightChild)//如果不判断空，则会插入空的元素，pop时，耽误时间
            s.push(t->rightChild);
        t = t->leftChild;
    }   
}
//非递归版本， 自定义栈 版本2
template <typename T>
void linkedBinaryTree<T>::preOrder3(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    while(true){
        visitalongleftbranch(t, s);
        if (s.empty())
            break;
        t = s.top();
        s.pop();
    }
}

template <typename T>
void linkedBinaryTree<T>::goalongleftbranch(binaryTreeNode<T> *t, stack<binaryTreeNode<T> *> &s){
    binaryTreeNode<T> *tt = t;
    while(tt){
        s.push(tt);
        tt = tt->leftChild;
    }
}


//非递归版本的中序遍历
template <typename T>
void linkedBinaryTree<T>::inOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    while(true){
        if(t) goalongleftbranch(t, s);
        if(s.empty()) break;
        t = s.top();
        s.pop();
        visit(t);
        t = t->rightChild;
    }
}

template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        inOrder(t->leftChild);
        linkedBinaryTree<T>::visit(t);
        inOrder(t->rightChild);
    }
}

template <typename T>
void linkedBinaryTree<T>::goalongleftbranch2(binaryTreeNode<T> *t, stack<binaryTreeNode<T>*> &s){
    binaryTreeNode<T> *tt = t;
    while(tt){
        s.push(tt);
        if(tt->rightChild) s.push(tt->rightChild);
        tt = tt->leftChild;
    }
}
/*
template <typename T>
void linkedBinaryTree<T>::postOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    bool first = true;
    bool second = true;
    while(true){
        if(t)
            goalongleftbranch(t, s);
        if(s.top()->rightChild && first && second){
            t = s.top()->rightChild;
            continue;
        }
        first = false;
        if(s.empty()) break;
        t = s.top();
        visit(t);
        s.pop();
        t = nullptr;
    }
}
*/

template <class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<T>::visit(t);
    }
}

template <class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T> *t) const{
    if(t == NULL)
        return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if(hl > hr)
        return ++hl;
    else
        return ++hr;
}

template <class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T> *t){
    queue<binaryTreeNode<T>*> q;
    while(t != NULL){
        visit(t);
        if(t->leftChild != NULL)
            q.push(t->leftChild);
        if(t->rightChild != NULL)
            q.push(t->rightChild);
        try{t = q.front();}
        catch(...){
            return ;
        }
        q.pop();
    }
}

// size_t max_nodes_level(){//max_width
//     queue<binaryTreeNode<T> *> q;

// }
template <typename T>
int linkedBinaryTree<T>::height() const{
    return height(root);
}

template <class E>
void myvisit(binaryTreeNode<E> *x){
    std::cout << x->element << " " << std::flush;
}



#endif //_LINKED_BINARY_TREE_H_