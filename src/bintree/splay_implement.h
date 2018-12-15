#ifndef _SPLAY_H_IMPLEMENT_
#define _SPLAY_H_IMPLEMENT_

//从节点V开始逐层伸展
template <typename T, typename V>
typename Splay<T, V>::node_pointer
Splay<T, V>::splay(node_pointer v){
    if(!v) return nullptr; 
    node_pointer p; node_pointer g;
    while((p = v->parent) && (g = p->parent)){//自下而上，反复对*v做双层伸展
        node_pointer gg = g->parent;
        if(v == p->leftChild){//如果v作为左孩子
            if(p == g->leftChild){//p作为左孩子
                // g->leftChild = p->rightChild;
                // g->parent = p;
                // p->rightChild = g;
                // p->parent = v;
                // p->leftChild = v->rightChild;
                // v->rightChild = p;
                v->parent = g->parent;
                p->leftChild = v->rightChild;
                v->rightChild = g;
                g->parent = v;
                g->leftChild = p;
                p->parent = g;

            }else{//p作为右孩子
                v->parent = g->parent;
                g->rightChild = v->leftChild;
                v->leftChild = g;
                g->parent = v;
                p->leftChild = v->rightChild;
                p->parent = v;
                v->rightChild = p;
            }
        }else{//v作为右孩子，
            if(p == g->leftChild){//p作为左孩子
               v->parent = g->parent;
               p->rightChild = v->leftChild;
               g->leftChild = v->rightChild;
               p->parent = v;
               v->leftChild = p;
               g->parent = v;
               v->rightChild = g; 
            }else{//p作为右孩子
                v->parent = g->parent;
                g->parent = v;
                p->parent= g;
                g->rightChild = p;
                p->rightChild = v->leftChild;
                v->leftChild = g;
            }
        }
        if(!gg) v->parent = nullptr;//如果此轮伸展前，g已经是根节点了，则v伸展之后是根节点
        else//调整v的parent节点为gg的左或者右孩子
            if(g == gg->leftChild) gg->leftChild = v;
            else gg->rightChild = v;
    }
    //处理最后g为nullptr，但是p不是的情况，需要进行最后一次单层旋转
    v->parent = nullptr;
    if(!p) return v;//p也是空，说明v已经时root了
    p->parent = v;
    if(v == p->leftChild){
        p->leftChild = v->rightChild;
        v->rightChild = p;
    }else{
        p->rightChild = v->leftChild;
        v->leftChild = p;
    }
    return v;
}

template <typename T, typename V>
typename Splay<T, V>::node_pointer
Splay<T, V>::search(const T& t){
    auto p = _Base_type::search(t);
    if(!p){//没有找到
        splay(_hot);
        root = _hot;
        return nullptr;
    }else{//找到
        splay(p);
        root = p;
        return root;
    }
}

template <typename T, typename V>
typename Splay<T, V>::node_pointer
Splay<T, V>::insert(const pair<T, V> &p){
    if(!this->root)
        return this->root = new binaryTreeNode<pair<T, V>>(p, nullptr, nullptr, nullptr);//树为空
    auto node = search(p.first);//search完成后，无论时找到或者没有找到，_hot都已经被移动到了root处
    if(!node){//目标节点不存在与树中
        auto newnode = new binaryTreeNode<pair<T, V>>(p, nullptr, nullptr, nullptr);
        if(root->element.first < p.first){
            newnode->rightChild = root->rightChild;
            if(root->rightChild) root->rightChild->parent = newnode;
            root->parent = newnode;
            root->rightChild = nullptr;
            newnode->leftChild = root;
        }else{
            newnode->parent = nullptr;
            newnode->leftChild = root->leftChild;
            if(root->leftChild) root->leftChild->parent = newnode;
            root->leftChild = nullptr;
            root->parent = newnode;
            newnode->rightChild = root;
        }
        root = newnode;
    }else//存在与源树中，则更新节点的第二个域的值
        this->root->element.second = p.second;
    return root;
}

template <typename T, typename V>
bool Splay<T, V>::remove(const T &t){
    if(!root){//树为空
        return false;
    }
    auto node = search(t);
    if(!node){//没有找到
        return false;
    }
    auto oldroot = root;
    //found the element
    //此时，此元素已经被移动到了root处
    if(!root->leftChild){//root没有左子树
        root = root->rightChild;
        root->rightChild->parent = nullptr;
        delete root;
    }else if(!root->rightChild){//没有右子树
        root = root->leftChild;
        root->rightChild->parent = nullptr;
        delete root;
    }else{//root 同时存在左和右子树
        node_pointer ltree = root->leftChild;
        ltree->parent = nullptr;
        root->leftChild = nullptr;//暂时切除左子树
        root = root->rightChild;
        root->parent = nullptr;
        search(oldroot->element.first);//为了将右子树的最小元素一定到根,且该节点没有左子树，因为他时最小的

        root->leftChild = ltree;
        ltree->parent = root;
    }
    delete oldroot;
    if(!root) this->updateHeight(root);
    return true;
}
#endif // _SPLAY_H_IMPLEMENT_