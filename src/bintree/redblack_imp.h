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
    auto x = this->search(e);
    if(!x) return false;
    //先找出x的后继节点
    auto succ = this->successor(x);
    //1, 如果succ 为nullptr,说明当前节点为叶节点(非外部节点)
    //直接查看该节点颜色,并转入相应处理代码
    if(!succ){
        if(x->color == RB_RED){//红色
            _Base_type::remove(e);
            return true;
        }//Black---转入双黑处理
        if(root == x) {//此树为空
            delete root;
            root = nullptr;
        }
       solveDoubleBlack(x);
    }//succ 不为nullptr
    //交换x与succ元素值,不交换颜色
    swap_two_nodes_but_color(x, succ);
    if(succ->color == RB_RED){//如果succ是红色,则可以直接删除
        if(succ == succ->parent->leftChild)
            succ->parent->leftChild = nullptr;
        else 
            succ->parent->rightChild = nullptr;
        delete succ;
        return true;
    }   
    //如果succ是黑色
    if(succ->rightChild && succ->rightChild->color == RB_RED){
        if(succ == succ->parent->leftChild){
            succ->rightChild->color = RB_BLACK;
            succ->parent->leftChild = succ->rightChild;
            succ->rightChild->parent = succ->parent;
        }else{
            succ->rightChild->color = RB_BLACK;
            succ->parent->rightChild = succ->rightChild;
            succ->rightChild->parent = succ->parent;
        }
        delete succ;
    }else//此时,succ是黑色的,且左孩子为null, 右孩子也必为null,为了平衡黑高度
        solveDoubleBlack(succ);
    return true;
}

//解决双红缺陷
template <typename T, typename V>
void RedBlack<T, V>::solveDoubleRed(node_pointer node){
/* 双红缺陷有两种情况
      1, node 的uncle 节点shi黑色
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
            if(!(g->parent == root))
                solveDoubleRed(g);
        }
    }
}

template <typename T, typename V>
void RedBlack<T, V>::solveDoubleBlack(node_pointer x){
    /* x 不会是树根 
       x 的左右都是外部节点
       x 是黑色的
       */
    auto p = x->parent;
    node_pointer s = nullptr;//x的兄弟
    bool left = true;
    if(x == p->leftChild)
        s = p->rightChild;
    else {
        s = p->leftChild;
        left = false;
    }
    node_pointer sl = nullptr, sr = nullptr;
    if(s->leftChild)
        sl = s->leftChild;
    if(s->rightChild)
        sr = s->rightChild;

    if(s->color == RB_BLACK){//s为黑色 进入BB-1, BB-2R, BB-2B
        //进入BB-1, 处理完可以直接退出
        RBColor old_p_color = p->color;
        p->color = RB_BLACK;
        if(sl && sl->color == RB_RED){//s左孩子是红色
            this->rotateAt(sl);
            if(left){
                sl->color = old_p_color;
                p->leftChild = nullptr;
            }else{
                s->color = old_p_color;
                p->rightChild = nullptr;
                sl->color = RB_BLACK;
            }
            delete x;
            return;
        }else if(sr && sr->color == RB_RED){
            this->rotateAt(sr);
            if(left){
                s->color = old_p_color;
                sr->color = RB_BLACK;
                p->leftChild = nullptr;
            }else{
                sr->color = old_p_color;
                p->rightChild = nullptr;
            }
            delete x;
            return;
        }
        if((!sl ||(sl && sl->color == RB_BLACK)) 
        && (!sr || (sr && sr->color == RB_BLACK)) 
        && p->color == RB_RED){//s的左右都是外部节点,进入BB-2R
            p->color = RB_BLACK;
            s->color = RB_RED;
            if(left){
                p->leftChild = nullptr;
            }else{
                p->rightChild = nullptr;
            }
        }else if((!sl ||(sl && sl->color == RB_BLACK))
        && (!sr || (sr && sr->color == RB_BLACK))
        && p->color == RB_BLACK){//p是黑色的,进入BB-2B
            s->color = RB_RED;
            if(left){
                p->leftChild = x->rightChild;
            }else{
                p->rightChild = x->leftChild;
            }
            solveDoubleBlack(p);
        }
    }else{//s为红, 进入BB-3
        // RBColor old_p_color = p->color;
        if(sl){
            this->rotateAt(sl);
            p->color = RB_RED;
            // sl
        }else{
            this->rotateAt(sr);

        }
    }
    delete x;
}

template <typename T, typename V>
void RedBlack<T, V>::swap_two_nodes_but_color(node_pointer l, node_pointer r){
    pair<T, V> temp = l->element;
    l->element.first = r->element.first;
    l->element.second = r->element.second;
    r->element.first = temp.first;
    r->element.second = temp.second;
}
#endif // _REDBLACK_IMP_H_