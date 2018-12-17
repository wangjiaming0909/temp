#ifndef _REDBLACK_H_
#define _REDBLACK_H_



#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (! IsBlack(p))
/*
 #define BlackHeightUpdated(x) ( \
//     (stature((x).leftChild) == stature((x).rightChild)) &&\
//     ((x).height)
// )
*/

template <typename T, typename V>
class RedBlack : public BST<T, V>{
public:
    typedef typename BST<T, V>::node_pointer node_pointer;
    typedef BST<T, V> _Base_type;
    typedef pair<T, V> element_type;
    typedef typename BST<T, V>::node_type node_type;
    using _Base_type::_hot;
    using _Base_type::treeSize;
    using _Base_type::root;

    RedBlack(node_pointer root) : _Base_type(root){}
    node_pointer insert(const element_type &);
    bool remove(const T&);
protected:
    int updateHeight(node_pointer);
    void solveDoubleRed(node_pointer);
    void solveDoubleBlack(node_pointer);
    void swap_two_nodes_but_color(node_pointer l, node_pointer r);
};


#endif // _REDBLACK_H_