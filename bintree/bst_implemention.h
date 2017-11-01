#ifndef _BST_IMP_H_
#define _BST_IMP_H_


template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::min(){
    return min(this->root);
}

template <typename T, typename V>   
typename BST<T, V>::node_pointer BST<T, V>::max(){
    return max(this->root);
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::min(node_pointer node){
    while(node->leftChild)
        node = node->leftChild;
    return node;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::max(node_pointer node){
    while(node->rightChild)
        node = node->rightChild;
    return node;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::search(const T& t){
    node_pointer p = this->root;
    while(p != NULL){
        this->_hot = p;
        if(t < p->element.first)
            p = p->leftChild;
        else
            if(t > p->element.first)
                p = p->rightChild;
            else
                return p;
    }
    return NULL;
}
    
template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T,V>::insert(const pair<T, V>& t){
    auto p = search(t.first);
    if(p) {
        p->element.second = t.second;
        return p;
    }
    p = new binaryTreeNode<pair<T, V>>(t, nullptr, nullptr);
    if(t.first < _hot->element.first)
        _hot->leftChild = p;
    else
        _hot->rightChild = p;
    p->parent = _hot;
    return p;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::successor(node_pointer node){
    //如果node有右子树，则其后继肯定是其右子树的最左边节点
    if(node->rightChild)
        return min(node->rightChild);
    /*
        如果右子树为空，则，需要向上查找
        1, 如果当前是父节点的左节点，进入while循环，直接退出，因为其父节点就是successor
        2, 如果但前时父节点的右节点，则向上查找，可能向左，或向右，向左的不符合，因为小于当前节点
            应该找到第一个向右的节点，即判断条件node == y->rightChild
        3, 如果向上查到，遇到根节点，且不是右节点，则说明，当前节点没有后继
    */
    auto y = node->parent;       
    //当不是右节点时，说明已经找到了successor
    while(y && node == y->rightChild){//只要不是根节点或者当前节点是y的右节点, 
        node = y;
        y = node->parent;
    }
    return y;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::predecessor(node_pointer node){
    if(node->leftChild)//如果有左孩子，那其左孩子就是前驱
        return max(node->leftChild);
    auto y = node->parent;//左孩子为空
    while(y && node == y->leftChild){
        node = y;
        y = node->parent;
    }
    return y;
}

//remove,选用后继替换当前节点
/*分为2种情况
1, t只有一个孩子，或者没有孩子，直接将自己替换为孩子
2, t有两个孩子，找到t的后继y，如果y是t的右孩子，则直接用y替换t
                          如果y不是t的右孩子，首先y必定没有左孩子，
                          用y的右孩子替换y，y的右孩子的父亲是y的父亲
                          将y替换t，将y的左孩子设置为t的左孩子，y的右孩子设置为t的右孩子
                          y的parent设置为t的parent
*/
template <typename T, typename V>
bool BST<T, V>::remove(const T& t){
    node_pointer r = nullptr;//备用根节点
    auto node = search(t);
    if(!node)//node not found 
        return false;
    //t只有一个孩子，或者没有孩子，直接将自己替换为孩子
    if(!node->leftChild){//不需要管其右孩子是否有节点，直接移植就可以
        node->rightChild->transplantTo(node);
        r = node->rightChild;
    }
    else if(!node->rightChild){
        node->leftChild->transplantTo(node);
        r = node->leftChild;
    }
    else{//node有两个孩子
        auto succ = min(node->rightChild);//后继
        if(succ->parent == node)//y是t的右孩子
            succ->transplantTo(node);
        else{//y不是t的右孩子
            //将y的右孩子移植到y的位置
            succ->rightChild->transplantTo(succ);
            succ->transplantTo(node);
            r = succ;
        }       
        succ->leftChild = node->leftChild;
        succ->rightChild = node->rightChild;
        // node->leftChild->parent = succ;
        // node->rightChild->parent = succ;
    }
    this->dispose(node);
    if(this->root == node)
        this->root = r;
    return true;
}

#endif // _BST_IMP_H_