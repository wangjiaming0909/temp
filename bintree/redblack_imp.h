#ifndef _REDBLACK_IMP_H_
#define _REDBLACK_IMP_H_


template <typename T, typename V>
int RedBlack<T, V>::updateHeight(node_pointer node){
    node->height2 = std::max(stature(node->leftChild), stature(node->rightChild));
    return IsBlack(node) ? node->height2++ : node->height2;
}

template <typename T, typename V>
typename RedBlack<T, V>::node_pointer 
RedBlack<T, V>::insert(const element_type &e){
    node_pointer node = _Base_type::search(e.first);//首先查找该元素
    if(node)//if 找到该节点，更新该节点信息
        node->element.second = e.second;
    //否则，创建新节点，插入
    node = new node_type(e, RB_BLACK, -1, nullptr, nullptr, _hot);//黑高度为-1， 颜色为红色
    if(_hot->element.first > e.first)
        _hot->leftChild = node;
    else
        _hot->rightChild = node;
    solveDoubleRed(node);
    treeSize++;
    return node ? node : _hot->parent;
}

template <typename T, typename V>
bool RedBlack<T, V>::remove(const T& e){

    return true;
}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleRed(node_pointer node){

}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleBlack(node_pointer node){

}
#endif // _REDBLACK_IMP_H_