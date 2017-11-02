#ifndef _AVL_H_
#define _AVL_H_

#define bacFac(x) (((x)->leftChild)->height() - ((x)->rightChild->height()))
#define balanced(x) (bacFac(x) == 0)
#define AVLBalanced(x) ((-2 < bacFac(x)) && (bacFac(x) < 2))
template <typename T, typename V>
class AVL : public BST<T, V>{
public:
    typedef typename BST<T, V>::node_pointer node_pointer;
    typedef BST<T, V> _Base_type;

    //构造函数
    AVL(node_pointer root) : _Base_type(root){}
    node_pointer insert(const T&);
    bool remove(const T&);
    //search接口可以直接继承
private:
};


#endif // _AVL_H_