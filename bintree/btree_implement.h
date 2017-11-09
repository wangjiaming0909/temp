#ifndef _BTREE_IMPLEMENT_H_
#define _BTREE_IMPLEMENT_H_

template <typename T>
typename BTree<T>::node_pointer 
BTree<T>::search(const T& t){
    node_pointer v = _root;
    _hot = nullptr;
    while(v){
        auto it = Se::binsearch(t, v->key);//返回不大于t的最大元素索引,或者是找到的元素的索引
        //it 就是待插入的位置
        //可能出现it已经超出key的范围,需要做个判断先
        if(size_t(it) < v->key.size() && v->key[it] == t){//found the element
            return v;//返回该节点，虽然该节点中有好几个元素
        }
        _hot = v;//not found the element, set _hot
        //如果it+1 >= child.size,说明it > key.size, 说明当前节点v中所有元素都小于t,
        // if(size_t(it+1) >= v->child.size())
            // return nullptr;
        v = v->child[it];//set v to the right child, return to the while loop
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &t){
    auto node = search(t);
    if(node) return false;//找到了该节点，就return false
    //没有找到元素t，此时_hot是t应该插入的节点，在此节点中查找t应该插入的位置
    auto r = Se::binsearch(t, _hot->key);
    _hot->key.insert(_hot->key.begin() + r, t);
    _hot->child.insert(_hot->child.begin() + r + 1, nullptr);
    _size++;;
    solveOverflow(_hot);
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
    
//分裂
template <typename T>
void BTree<T>::solveOverflow(node_pointer node){
    if(size_t(_order) >= node->child.size())//node的孩子个数小于阶数，没有出现上溢
        return ;
    //1, 首先，上溢处理是需要递归向上处理的，
    //向上将一个元素向上移动，可能会导致上一层的节点上溢
    //这个递归向上的过程，通过对solveOverflow函数的递归调用实现
    //2, 选出当前节点的中间节点, d/2,从当前节点删除，d是阶数
    //并将该节点的key以及child数组分裂为两个节点(构造两个的新的节点)
    //设置好指针****
    //3, 将该节点添加到当前节点的parent节点的适当位置,设置好指针
    //4, 处理到达根节点，依然上溢

    //否则，出现了上溢
    int mid_index = _order / 2;//中间节点的索引
    T temp = node->key[mid_index];//暂存该将被上移的节点
    
    //构造1个新的节点，暂存, 右边的还是用之前的node
    //构造一个新的节点时，child数组中存在一个空的指针, 最好先删除
    node_pointer l = new node_type();
    l->child.resize(0);
    //对node中的前mid_index个元素进行删除,以及其之间的child指针
    for(int i = 0; i < mid_index; i++){
        l->child.push_back(node->child[0]);
        node->child.erase(node->child.begin());
        l->key.push_back(node->key[0]);
        node->key.erase(node->key.begin());
    }
    //还剩下mid_index之气的指针没有添加到l中，添加之后，从node中删除
    l->child.push_back(node->child[0]);
    node->child.erase(node->child.begin());
    //再删除mid_index 节点, 且此元素的值已经保存下来了
    node->key.erase(node->key.begin());
    //添加parent中
    if(node->parent){
        auto i = Se::binsearch(temp, node->parent->key);
        node->parent->key.insert(node->parent->key.begin() + i + 1, temp);
        node->parent->child.insert(node->parent->child.begin() + i+2, node);
        node->parent->child[i+1] = l;
        l->parent = node->parent;
        solveOverflow(node->parent);
    }else{//如果node已经时根节点，则需要新建一个节点作为根
        auto newroot = new node_type(temp, l, node);
        l->parent = newroot;
        node->parent = newroot;
        _root = newroot;
    }
}

template <typename T>
void BTree<T>::solveUnderflow(node_pointer node){

}
#endif //_BTREE_IMPLEMENT_H_