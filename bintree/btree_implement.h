#ifndef _BTREE_IMPLEMENT_H_
#define _BTREE_IMPLEMENT_H_

template <typename T>
typename BTree<T>::node_pointer
BTree<T>::search(const T &t)
{
    node_pointer v = _root;
    _hot = nullptr;
    while (v)
    {
        auto it = Se::binsearch(t, v->key); //返回不大于t的最大元素索引,或者是找到的元素的索引
        //it 就是待插入的位置
        //可能出现it已经超出key的范围,需要做个判断先
        if (size_t(it) < v->key.size() && v->key[it] == t)
        {             //found the element
            return v; //返回该节点，虽然该节点中有好几个元素
        }
        _hot = v; //not found the element, set _hot
        //如果it+1 >= child.size,说明it > key.size, 说明当前节点v中所有元素都小于t,
        // if(size_t(it+1) >= v->child.size())
        // return nullptr;
        v = v->child[it]; //set v to the right child, return to the while loop
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &t)
{
    auto node = search(t);
    if (node)
        return false; //找到了该节点，就return false
    //没有找到元素t，此时_hot是t应该插入的节点，在此节点中查找t应该插入的位置
    auto r = Se::binsearch(t, _hot->key);
    _hot->key.insert(_hot->key.begin() + r, t);
    _hot->child.insert(_hot->child.begin() + r + 1, nullptr);
    _size++;
    solveOverflow(_hot);
    return true;
}

template <typename T>
void BTree<T>::inOrder(void (*visit)(const T &))
{
    if (!_root)
        return;
    _visit = visit;
    _inOrder(_root);
}

template <typename T>
void BTree<T>::_inOrder(node_pointer node)
{
    auto keysize = node->key.size();
    auto childsize = node->child.size();
    for (size_t i = 0; i < childsize; i++)
    {
        if (node->child[i])
        {
            _inOrder(node->child[i]);
        }
        if (i < keysize)
        {
            _visit(node->key[i]);
        }
        else
            break;
    }
}

//分裂
template <typename T>
void BTree<T>::solveOverflow(node_pointer node)
{
    if (size_t(_order) >= node->child.size()) //node的孩子个数小于阶数，没有出现上溢
        return;
    //1, 首先，上溢处理是需要递归向上处理的，
    //向上将一个元素向上移动，可能会导致上一层的节点上溢
    //这个递归向上的过程，通过对solveOverflow函数的递归调用实现
    //2, 选出当前节点的中间节点, d/2,从当前节点删除，d是阶数
    //并将该节点的key以及child数组分裂为两个节点(构造两个的新的节点)
    //设置好指针****
    //3, 将该节点添加到当前节点的parent节点的适当位置,设置好指针
    //4, 处理到达根节点，依然上溢

    //否则，出现了上溢
    int mid_index = _order / 2;    //中间节点的索引
    T temp = node->key[mid_index]; //暂存该将被上移的节点

    //构造1个新的节点，暂存, 右边的还是用之前的node
    //构造一个新的节点时，child数组中存在一个空的指针, 最好先删除
    node_pointer l = new node_type();
    l->child.resize(0);
    //对node中的前mid_index个元素进行删除,以及其之间的child指针
    for (int i = 0; i < mid_index; i++){
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
    if (node->parent){
        auto i = Se::binsearch(temp, node->parent->key);
        node->parent->key.insert(node->parent->key.begin() + i, temp);
        node->parent->child.insert(node->parent->child.begin() + i, l);
        node->parent->child[i] = l;
        l->parent = node->parent;
        solveOverflow(node->parent);
    }
    else{ //如果node已经时根节点，则需要新建一个节点作为根
        auto newroot = new node_type(temp, l, node);
        l->parent = newroot;
        node->parent = newroot;
        _root = newroot;
        newroot->parent = nullptr;
    }
}

template <typename T>
bool BTree<T>::remove(const T &t)
{
    auto node = search(t);
    if (!node)
        return false; //如果没有找到这个元素，返回false
    //找到了这个元素
    //首先先记录下该元素位于node的什么位置，准备与后继交换
    int index_of_e = Se::binsearch(t, node->key);
    /* 1, 这个节点不是叶节点
            找到这个节点的后继，或者前驱，交换位置
            比如，寻找后继
                从node的child[index_of_e + 1]节点开始，向左寻找最小的元素
                该最小元素就是一直向下所寻找到的叶节点,不需要判断是不是最小的
                记下该元素所在的节点
            此时，待删除的元素位于叶节点上，转化为第二种情况
       2, 这个节点是叶节点 
       删除这个节点，删除child[0], 检查是不是Underflow*/
    if (node->child[0])
    { //node不是叶节点
        node_pointer succ = node->child[index_of_e + 1];
        while (succ->child[0]) //有孩子, 接着循环
            succ = succ->child[0];
        //交换
        node->key[index_of_e] = succ->key[0];
        // succ->key[0] = t;
        node = succ;
        index_of_e = 0;
    } //处理完成后，继续进行删除，并且节点已调整完
    //node是叶节点,删除位置为 index_of_e, 且此时node是叶节点, 删除index_of_e之后的child指针
    node->key.erase(node->key.begin() + index_of_e);
    node->child.erase(node->child.begin() + index_of_e + 1);
    solveUnderflow(node);
    return true;
}

template <typename T>
void BTree<T>::solveUnderflow(node_pointer node)
{
    /* 1, 首先，下溢会逐层向上传递，因此需要递归，当退到树根时需要特殊处理
       2, 有  种情况
        1. 有左兄弟，不可以借, 不可以借-> 5
        2.  可以借
        3. 只有右兄弟，不可以借
        4.  可以借
        5. 有两个兄弟，左边不可以借，右边才可以借
        6. 左右都不可以借
            一路向上1, 没有到根
                   2,到根
    */
    //判断是否下溢, node的元素个数小于_order / 2
    //每个节点的元素个数至少是 _order/2 取上整，减一
    //而_order/2 是 _order/2 取下整
    if (node->key.size() >= size_t(_order / 2)) //没有下溢
        return;
    //下溢了
    //定义三个节点，父节点， 左兄弟，右兄弟
    node_pointer p = node->parent;
    node_pointer l = nullptr;
    node_pointer r = nullptr;
    if(!p){//node已经是根
        //此时，node应该是一个空的节点，其第一个child应设置为root，高度减少1
        _root = node->child[0];
        _root->parent = nullptr;
        delete node;
        return;
    }
    //找到node在p中的位置,是指node在p中child中的索引
    // auto index_of_node_in_p_child = Se::binsearch(node->key[0], p->key) + 1;
    auto index_of_node_in_p_child = _search(p->child, node);
    //判断这个index是不是第一个或者最后一个
    //因为如果是第一个或者最后一个会导致下面两个有可能出现数组越界
    if(index_of_node_in_p_child != 0)//判断是不是第一个
         l = p->child[index_of_node_in_p_child - 1]; //左兄弟
    // else
        // node_pointer l = nullptr;//没有左兄弟
    if(size_t(index_of_node_in_p_child) != p->key.size())//node已经是p的最后一个节点， r = nullptr
        r = p->child[index_of_node_in_p_child + 1]; //右兄弟
    // else
        // node_pointer r = nullptr;

    //(1)有左兄弟
    if(l){
        //1,如果左兄弟可以借
        if(l->key.size() > size_t(_order/2)){//必须是大于了，如果是等于，则借出一个导致自己下溢
            //右旋
            //需要两个元素，l的最大值，p->key[index_of_node_in_p_child - 1]
            //往node的最左边插入p->key[index_of_node_in_p_child - 1]
            assert(index_of_node_in_p_child - 1 >= 0);
            node->key.insert(node->key.begin(), p->key[index_of_node_in_p_child - 1]);
            //反正node都是叶节点，随便这个nullptr插入在什么位置都一样
            node->child.insert(node->child.begin(), nullptr);
            //设置p中的中间的元素
            p->key[index_of_node_in_p_child - 1] = l->key[l->key.size()-1];
            //删除l中的最大的元素
            l->child.erase(l->child.end()-1);
            l->key.erase(l->key.end()-1);
            //这里需要return 出去
            return solveUnderflow(p);
        }
        //2, 左兄弟不可以借
    }
    //(2)有右兄弟,此时左兄弟已经判断过了，要是有并且可以借，已经借了,说明没有左兄弟，或者不能借
    if(r){
        //右兄弟可以借
        if(r->key.size() > size_t(_order/2)){
            //左旋
            //设置node
            node->key.push_back(p->key[index_of_node_in_p_child]);
            node->child.push_back(nullptr);
            //设置p
            p->key[index_of_node_in_p_child] = r->key[0];
            //erase r中最小的元素
            r->child.erase(r->child.begin());
            r->key.erase(r->key.begin());
            return solveUnderflow(p);
        }
        //右兄弟也没得借
    }
    //左右都没得借, 找父节点帮忙
    /* 此时，node必然有一个左兄弟，或者右兄弟
       如果有左兄弟，就直接选择左兄弟，不然选择右兄弟 */
    node_pointer brother = l ? l : r;
    //从p中取下一个元素, index是多少取决与我要合并的是左兄弟还是右兄弟
    if(brother == l){//左兄弟,p中的索引就是 index_of_node_in_p_child - 1
        //将p总的中间元素插入brother的最后
        brother->key.push_back(p->key[index_of_node_in_p_child - 1]);
        // brother->child.push_back(nullptr);
        brother->child.push_back(node->child[0]);
        //再插入node中的元素
        for(int i = 0; size_t(i) < node->key.size(); i++){
            brother->key.push_back(node->key[i]);
            brother->child.push_back(nullptr);
        }
        //删除p中的中间元素
        p->key.erase(p->key.begin() + index_of_node_in_p_child - 1);
        p->child.erase(p->child.begin() + index_of_node_in_p_child);
        //释放节点node
        delete node;
    }else{//右兄弟, p中的索引是 index_of_node_in_p_child
        node->key.push_back(p->key[index_of_node_in_p_child]);
        node->child.push_back(nullptr);
        for(int i = 0; size_t(i) < brother->key.size(); i++){
            node->key.push_back(brother->key[i]);
            node->child.push_back(nullptr);
        }
        p->key.erase(p->key.begin() + index_of_node_in_p_child);
        p->child.erase(p->child.begin() + index_of_node_in_p_child + 1);
        delete brother;
    }
    solveUnderflow(p);
}

template <typename T>
int BTree<T>::_search(const vector<node_pointer> &v, node_pointer node){
    if(!node) return -1;
    for(int i = 0; size_t(i) < v.size(); i++){
        if(v[i] == node)
            return i;
    }
    return -1;
}
#endif //_BTREE_IMPLEMENT_H_