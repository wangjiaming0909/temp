#ifndef _SEARCH_H_
#define _SEARCH_H_
namespace Se{
    
template <typename T, typename V>
int _binsearch(T &t, std::vector<V> &v, int lo, int hi){
    int mid = 0;
    bool left_or_right = false;//false represents left
    while(lo <= hi){
        mid = (lo + hi) >> 1;
        if(t == v[mid]) return mid;//找到, 先判断其实很耗费时间
        else if(t < v[mid]){
            hi = mid - 1;//在左边一半区域
            left_or_right = false;
        } 
        else{//其实在每次到这儿的时候, 都已经比较了两次之后了, 因此向右时复杂度会增加
            lo = mid + 1;//在右边一半区域
            left_or_right = true;
        }
    }
    if(left_or_right){//right
        return mid + 1;
    }else{//left
        return mid;
    }
}
    
template <typename T, typename V>
int binsearch(T &t, std::vector<V> & v){
    if(v.size() == 0) return 0;//the first to insert elements
    return _binsearch(t, v, 0, v.size() - 1);
}

}

#endif //_SEARCH_H_