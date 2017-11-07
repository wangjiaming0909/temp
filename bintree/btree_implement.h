#ifndef _BTREE_IMPLEMENT_H_
#define _BTREE_IMPLEMENT_H_

template <typename T>
typename BTree<T>::node_pointer 
BTree<T>::search(const T& t){
    node_pointer v = _root;
    _hot = nullptr;
    while(v){
        int r = v->key.search(t);
        // if(){
// 
        // }
    }
}

#endif //_BTREE_IMPLEMENT_H_