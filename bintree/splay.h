#ifndef _SPLSY_H_
#define _SPLSY_H_

template <typename T, typename V>
class Splay : public BST<T, V>{
public:
    typedef BST<T, V> _Base_type;
    typedef typename _Base_type::node_pointer node_pointer;
    
    //由于查找需要将元素上移，因此需要重写search
    node_pointer search(const T&);
    node_pointer insert(const pair<T, V> &);
    bool remove(const T&);
protected:
    node_pointer splay(node_pointer);//伸展至树根
};

#endif // _SPLSY_H_