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

//持久性
//删除或者插入进行的旋转次数为O(1)
/*
    1, 根为黑色
    2, 外部节点是黑的
    3, 其余节点: 若为红色, 则只能有黑孩子(红之子,之父比为黑色), 不能有两个连续的红色节点
    4, 所有外部节点到根的路径上黑色节点数目相同(黑深度相同)
*/
//红黑树对应一颗(2,4)B树(4阶B树), 每个超级节点有 1-3 个节点
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