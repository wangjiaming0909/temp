#ifndef _DS_VECTOR_H_
#define _DS_VECTOR_H_

namespace ds{

#define DEFAULT_CAPACITY = 3
//vector 在删除的过程中, 删除一个区间的复杂度取决于被删除的范围之后的元素个数
template <typename T>
class vector{
public:
    using Rank = int;
    vector(int c = DEFAULT_CAPACITY){
        elem_ = new T[]
    }
private:
    int Rank size_;
    int capacity_;
    T* elem_;

/*
    size()
    get(r)
    put(r, e)
    insert(r, e)
    remove(r)
    find(e)
    search(e)
*/


}

}
#endif // _DS_VECTOR_H_