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
        if(t < p->element.first)//可以先判断是不是已经查找到了，可以较少比较的次数
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
    this->updateHeightAbove(p);
    return p;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer BST<T, V>::successor(node_pointer node){//最多O(h)
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
void BST<T, V>::transplant(node_pointer dest, node_pointer source){
    if(!dest->parent)//dest为根节点
        this->root = source;
    else if(dest == dest->parent->leftChild)//dest作为左孩子
        dest->parent->leftChild = source;
    else dest->parent->rightChild = source;//dest作为右孩子
    if(source)
        source->parent = dest->parent;
}

template <typename T, typename V>
bool BST<T, V>::remove(const T& t){
    auto node = search(t);
    if(!node) return false;
    if(!node->leftChild)//没有左孩子
        transplant(node, node->rightChild);
    else if(!node->rightChild)//meiyou 右孩子
        transplant(node, node->leftChild);
    else{//you 两个孩子
        auto succ = min(node->rightChild);
        if(succ != node->rightChild){//succ不是node的右孩子
            transplant(succ, succ->rightChild);//将succ的右孩子移到succ处
            succ->rightChild = node->rightChild;
            succ->rightChild->parent = succ;
        }
        //如果succ是node的右孩子
        transplant(node, succ);//将succ移动到node
        succ->leftChild = node->leftChild;
        succ->leftChild->parent = succ;
    }
    this->updateHeightAbove(node);
    return true;
}

template <typename T, typename V>
void BST<T, V>::outputRange(const T& low, const T& hi){
    auto low_node = search(low);
    if(!low_node){
        low_node = _hot;
        if(low_node->element.first < low){
            low_node = successor(_hot);
        }
    }
    auto hi_node = search(hi);
    if(!hi_node){
        hi_node = _hot;
        if(hi_node->element.first > hi)
            hi_node = predecessor(_hot);
    }
    binaryTreeNode<pair<T, V>>* tmp = low_node;
    this->visit = myvisit<int, string>;
    while(true){
        this->visit(tmp);
        if(!(tmp = successor(tmp)))
            break;
        else if(tmp == hi_node){
            this->visit(tmp);
            break;
        }
    }
}

template <typename T, typename V>
typename BST<T, V>::node_pointer 
BST<T, V>::rotateAt(node_pointer s){//
    assert(s);
    auto p = s->parent;
    auto g = p->parent;
    assert(p); assert(g);
    if(p == g->leftChild){//右旋
        if(s == p->rightChild){//左旋加右旋
            s->parent = g->parent;
            if(g == g->parent->leftChild)
                g->parent->leftChild = s;
            else
                g->parent->rightChild = s;
            return this->connect34(p, s, g, p->leftChild, s->leftChild, s->rightChild, g->rightChild);
        }else{//右旋
            p->parent = g->parent;
            if(g->parent){
                if(g == g->parent->leftChild) g->parent->leftChild = p;
                else g->parent->rightChild = p;
            }
            return this->connect34(s, p, g, s->leftChild, s->rightChild, p->rightChild, p->rightChild);
        }
    }else{//左旋
        if(s == p->leftChild){//右旋加左旋
            s->parent = g->rightChild;
            return this->connect34(s, g, p, g->leftChild, s->rightChild, s->leftChild, p->rightChild);
        }else{//左旋
            //由于调用的是同一个connect34,因此画个图，调换g，s，调换T0, T3,调换T1,T2
            p->parent = g->parent;
            return this->connect34(g, p, s, s->rightChild, s->leftChild, p->leftChild, g->leftChild);
        }
    }
}

template <typename T, typename V>
typename BST<T, V>::node_pointer 
BST<T, V>::connect34(node_pointer s, node_pointer p, node_pointer g,
    node_pointer t0, node_pointer t1, node_pointer t2, node_pointer t3){
    s->leftChild = t0; s->rightChild = t1; s->parent = p; this->updateHeight(s);
    p->leftChild = s; p->rightChild = g; this->updateHeight(p);
    g->leftChild =t2; g->rightChild = t3; g->parent = p; this->updateHeight(g);
    if(t0) t0->parent = s; 
    if(t1) t1->parent = s; 
    if(t2) t2->parent = g; 
    if(t3) t3->parent = g;
    return p;
}

#endif // _BST_IMP_H_