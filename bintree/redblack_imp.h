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
    node = new node_type(e, RB_RED, -1, nullptr, nullptr, _hot);//黑高度为-1， 颜色为红色
    if(_hot->element.first > e.first)
        _hot->leftChild = node;
    else
        _hot->rightChild = node;

    if(_hot->color == RB_RED)
       solveDoubleRed(node);
    treeSize++;
    return node ? node : _hot->parent;
}

template <typename T, typename V>
bool RedBlack<T, V>::remove(const T& e){
    
    return true;
}

//解决双红缺陷
template <typename T, typename V>
void RedBlack<T, V>::solveDoubleRed(node_pointer node){
/* 双红缺陷有两种情况
      1, node 的uncle 节点时黑色
        则只需进行一次一次或者两次旋转， 调整两个节点颜色完成重平衡
        且此法是一次性完成，不平衡不会向上传递
        可套用avl树中的3+4重构算法, 重构完后，调整两个节点颜色
      2, node 的uncle节点是红色
        无需重构，旋转
        只需简单调整3个节点的颜色,而且 node颜色不用变, 调整另外三个接点就ok了
       */
    //u是黑色的
    node_pointer p = node->parent;//必为红
    node_pointer g = p->parent;//必为黑
    node_pointer u = nullptr;
    if(p == g->leftChild) u = g->rightChild;//为了计算出u是g的左还是右孩子
    else u = g->leftChild;//虽然给u赋值了,但是不一定就不是nullptr了
    if(!u || u->color == RB_BLACK){
        //此时,u为黑色的,但是,u可能是外部节点
        // 旋转的部分交由bst的rotate完成,具体需要哪种旋转也交给rotate自己判断
        // 自己只需要负责改变2个节点的颜色
        //分2种情况,见那张纸
        g->color = RB_RED;
        if((node == p->leftChild && p == g->leftChild) || 
            (node == p->rightChild && p == g->rightChild))
            p->color = RB_BLACK;
        else
            node->color = RB_BLACK;
        //旋转
        // g->parent = 
        this->rotateAt(node);
    }else{//u是红色的
        //由于此前,u和p都是红色节点,g为黑色节点,u, p的黑高度比现在少了1, 因为现在自己是黑色的了
        u->color = RB_BLACK; u->height2++;
        p->color = RB_BLACK; p->height2++;
        //g如果是根节点,则不可以将g改为红色, 但此时,不更改根节点的颜色,也不会导致黑高度变化
        if(g != root){
            g->color = RB_RED;
            solveDoubleRed(g);
        }
    }
}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleBlack(node_pointer node){
    
}
#endif // _REDBLACK_IMP_H_