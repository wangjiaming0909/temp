#ifndef _BTREE_IMPLEMENT_H_
#define _BTREE_IMPLEMENT_H_

template <typename T>
typename BTree<T>::node_pointer 
BTree<T>::search(const T& t){
    node_pointer v = _root;
    _hot = nullptr;
    while(v){
        auto it = Se::binsearch(t, v->key);
        if(it != -1){//found the element
            return v;//返回该节点，虽然该节点中有好几个元素
        }
        _hot = v;//not found the element, set _hot
        v = v->child[it + 1];//set v to the right child, return to the while loop
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &t){
    auto node = search(t);
    if(node) return false;//找到了该节点，就return false
    //没有找到元素t，此时_hot是t应该插入的节点，在此节点中查找t应该插入的位置
    auto r = Se::binsearch(t, _hot->key);
    _hot->key.insert(_hot->key.begin() + r + 1, t);
    _hot->child.insert(_hot->child.begin() + r + 2, nullptr);
    _size++;
    //solveOverfolw(_hot);
    return true;
}
    
#endif //_BTREE_IMPLEMENT_H_