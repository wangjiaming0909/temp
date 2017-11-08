#ifndef _SEARCH_H_
#define _SEARCH_H_
namespace Se{
    
template <typename T, typename V>
int _binsearch(T &t, std::vector<V> &v, int lo, int hi){
    int mid = 0;
    while(lo < hi){
        mid = (lo + hi) >> 1;
        if(t == v[mid]) return mid;//找到
        else if(t < v[mid]) hi = mid;//在左边一半区域
        else lo = mid + 1;//在右边一半区域
    }
    if(v[mid] > t)
        return -1;
    return mid;//返回不大于待查找的元素的最大的元素索引
}
    
template <typename T, typename V>
int binsearch(T &t, std::vector<V> & v){
    if(v.size() == 0) return 0;
    return _binsearch(t, v, 0, v.size() - 1);
}

}

#endif //_SEARCH_H_