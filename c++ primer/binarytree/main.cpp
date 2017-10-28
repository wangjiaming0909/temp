#include <iostream>
// #include "linkedbinarytree.h"
#include "bst.h"
#include <vector>
using namespace std;

int main(){
    binaryTreeNode<string> *root = new binaryTreeNode<string>;
    binaryTreeNode<string> *l1 = new binaryTreeNode<string>;
    binaryTreeNode<string> *l2 = new binaryTreeNode<string>;
    binaryTreeNode<string> *ll1 = new binaryTreeNode<string>;
    binaryTreeNode<string> *ll2 = new binaryTreeNode<string>;
    binaryTreeNode<string> *ll3 = new binaryTreeNode<string>;
    binaryTreeNode<string> *ll4 = new binaryTreeNode<string>;
    binaryTreeNode<string> *ll5 = new binaryTreeNode<string>;
    root->element = "1";
    l1->element = "2";
    l2->element = "3";
    ll1->element = "4";
    ll2->element = "5";
    ll3->element = "6";
    ll4->element = "7";
    ll5->element = "8";
    root->leftChild = l1;
    root->rightChild = l2;
    l1->leftChild = ll1;
    l1->rightChild = ll2;
    l2->rightChild = ll3;
    ll1->rightChild = ll4;
    ll4->leftChild = ll5;
    
    BST<string> lbt(root);
    cout << lbt.height();
    cout << endl;
    return 0;
}