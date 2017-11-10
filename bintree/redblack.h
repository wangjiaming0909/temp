#ifndef _REDBLACK_H_
#define _REDBLACK_H_

template <typename T, typename V>
class RedBlack : public BST<T, V>{
public:
    typedef typename BST<T, V>::node_pointer node_pointer;
    typedef pair<T, V> element_type;
    node_pointer insert(const element_type &);
    bool remove(const T&);
protected:
    int updateHeight(node_pointer);
    void solveDoubleRed(node_pointer);
    void solveDoubleBlack(node_pointer);
};


#endif // _REDBLACK_H_