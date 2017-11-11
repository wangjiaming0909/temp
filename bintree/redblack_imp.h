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

    if(_hot == RB_RED)
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

//解决双红缺陷
template <typename T, typename V>
void RedBlack<T, V>::solveDoubleBlack(node_pointer node){
    /* 双红缺陷有两种情况
      1, node 的uncle 节点时黑色
        则只需进行一次一次或者两次旋转， 调整两个节点颜色完成重平衡
        且此法是一次性完成，不平衡不会向上传递
        可套用avl树中的3+4重构算法, 重构完后，调整两个节点颜色
      2, node 的uncle节点是红色
        无需重构，旋转
        只需简单调整3个节点的颜色,而且 node颜色不用变, 调整另外三个接点就ok了
       */
    if(node){
        
    }
    
}
#endif // _REDBLACK_IMP_H_