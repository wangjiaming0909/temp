#ifndef BINARYTREE_H_
#define BINARYTREE_H_

//二叉树节点类型
template <class T>
struct binaryTreeNode{
    T element;
    binaryTreeNode *leftChild, *rightChild;

    binaryTreeNode(): leftChild(nullptr), rightChild(nullptr){}
    binaryTreeNode(const binaryTreeNode& theElement) : 
        element(theElement), leftChild(nullptr), rightChild(nullptr){}
    binaryTreeNode( const T& theElement, 
                    binaryTreeNode *theLeftChild, 
                    binaryTreeNode *theRightChild)
       : element(theElement), leftChild(theLeftChild), rightChild(theRightChild){}
};

template <class T>
class binaryTree{
public:
	virtual ~binaryTree() = default;
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void (*) (T*)) = 0;
	virtual void inOrder(void (*)(T*)) = 0;
	virtual void postOrder(void (*)(T*)) = 0;
	virtual void levelOrder(void (*)(T*)) = 0;
};

template <class T>
void myvisit(binaryTreeNode<T> *);


#endif /* BINARYTREE_H_ */
