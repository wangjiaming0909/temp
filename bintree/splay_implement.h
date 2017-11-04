#ifndef _SPLAY_H_IMPLEMENT_
#define _SPLAY_H_IMPLEMENT_

//从节点V开始逐层伸展
template <typename T, typename V>
typename Spaly<T, V>::node_pointer
Splay<T, V>::splay(node_pointer v){
    if(!v) return nullptr; 
    node_pointer p; node_pointer g;
    while((p = v->parent) && (g = p->parent)){//自下而上，反复对*v做双层伸展
        node_pointer gg = g->parent;
        if(){//如果v作为左孩子
            if(){//p作为左孩子
                
            }else{//p作为右孩子

            }
        }else{//v作为右孩子，
            if(){//p作为左孩子

            }else{//p作为右孩子

            }
        }
        if(!gg) v->parent = nullptr;//如果此轮伸展前，g已经是根节点了，则v伸展之后是根节点
        else//调整v的parent节点为gg的左或者右孩子
    }
    //处理最后g为nullptr，但是p不是的情况，需要进行最后一次单层旋转
}

#endif // _SPLAY_H_IMPLEMENT_