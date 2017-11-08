#ifndef _BTREE_IMPLEMENT_H_
#define _BTREE_IMPLEMENT_H_

template <typename T>
typename BTree<T>::node_pointer 
BTree<T>::search(const T& t){
    node_pointer v = _root;
    _hot = nullptr;
    while(v){
        auto it = Se::binsearch(t, v->key);//返回不大于t的最大元素索引,或者是找到的元素的索引
        //it+1 就是待插入的位置
        if(size_t(it) < v->key.size() && v->key[it] == t){//found the element
            return v;//返回该节点，虽然该节点中有好几个元素
        }
        _hot = v;//not found the element, set _hot
        if(size_t(it+1) >= v->child.size())
            return nullptr;
        v = v->child[it+1];//set v to the right child, return to the while loop
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &t){
    auto node = search(t);
    if(node) return false;//找到了该节点，就return false
    //没有找到元素t，此时_hot是t应该插入的节点，在此节点中查找t应该插入的位置
    auto r = Se::binsearch(t, _hot->key);
    _hot->key.insert(_hot->key.begin() + r + int(bool(_size)), t);
    _hot->child.insert(_hot->child.begin() + r + int(bool(_size)), nullptr);
    _size++;;
    //solveOverfolw(_hot);
    return true;
}

template <typename T>
void BTree<T>::inOrder(void (*visit)(const T&)){
    if(!_root) return;
    _visit = visit;
    _inOrder(_root);
}

template <typename T>
void BTree<T>::_inOrder(node_pointer node){
    auto keysize = node->key.size();
    auto childsize = node->child.size();
    for(size_t i = 0; i < childsize; i++){
        if(node->child[i]){
            _inOrder(node->child[i]);
        }
        if(i < keysize){
            _visit(node->key[i]);
        }else break;
    }
}
    
#endif //_BTREE_IMPLEMENT_H_