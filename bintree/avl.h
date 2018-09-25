#ifndef _AVL_H_
#define _AVL_H_

#define bacFac(x) (stature((x)->leftChild) - stature((x)->rightChild))
#define balanced(x) (bacFac(x) == 0)
#define AVLBalanced(x) ((-2 < bacFac(x)) && (bacFac(x) < 2))
#define tallchild(x) (stature((x)->leftChild) > stature((x)->rightChild) \
? (x)->leftChild : (x)->rightChild)

template <typename T, typename V>
class AVL : public BST<T, V>{
public:
    typedef typename BST<T, V>::node_pointer node_pointer;
    typedef BST<T, V> _Base_type;
    using _Base_type::_hot;

    //构造函数
    AVL(node_pointer root) : _Base_type(root){}
    node_pointer insert(const pair<T, V> &);
    bool remove(const T&);
    //search接口可以直接继承
};


#endif // _AVL_H_