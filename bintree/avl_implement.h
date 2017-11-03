#ifndef _AVL_IMPLEMENT_H_
#define _AVL_IMPLEMENT_H_


//找到第一个失衡的节点，此节点必定是g，
//在此节点处进行旋转，重新分布节点
template <typename T, typename V>
typename AVL<T, V>::node_pointer AVL<T, V>::insert(const pair<T, V>& p){
    auto node = search(p->first); 
    if(node){//如果这个节点已经存在了，就更新这个节点
        node->element.second = p.second;
        return node;
    } 
    auto g = _hot->parent;//没有找到该节点,插入
    if(p->first < _hot->element.first){
        auto newnode = new binaryTreeNode<pair<T, V>>(p, nullptr, nullptr, _hot);
        _hot->leftChild = newnode;
    }else{
        auto newnode = new binaryTreeNode<pair<T, V>>(p, nullptr, nullptr, _hot);
        _hot->rightChild = newnode;
    }
    this->updateHeightAbove(_hot);
    for(; g; g = g->parent){
        if(!balanced(g))//发现一个失衡的祖先节点, 旋转
            ratateAt(g);
    }
}

template <typename T, typename V>
bool AVL<T, V>::remove(const T& t){

}

#endif //_AVL_IMPELEMENT_H_