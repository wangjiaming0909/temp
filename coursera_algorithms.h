#include <iostream>
using namespace std;

namespace coursera{
    //union find
    class unionfind{
    public:
        explicit unionfind(int n){}
        void union_(int p, int q);
        bool connected(int p, int q); 
    };

    class quickfind{
    public:
    //initialize id to its index
        explicit quickfind(int n) : size(n){//初始化        O(N)
            id = new int[n];
            for(int i = 0; i < n; i++)
                *(id+i) = i;
        }
        //
        bool connected(int p, int q){//find O(1)
            return id[p] == id[q];
        }
        //union p to q
        //set id[p] to id[q]
        void union_(int p, int q){  //  union   O(N)
            int x = id[p];
            for(int i = 0; i < size; i++)
                if(id[i] == x)
                    id[i] = id[q];
        }
        ~quickfind(){
            if(id)
                delete[] id;
        }
    private:
        int *id;
        int size;
    };

    class quickunion{
    public:
        explicit quickunion(int i) : size(i){//初始化   O(N)
            id = new int[size];
            for(int i = 0; i < size; i++)
                id[i] = i;
        }
        bool connected(int p, int q){ //find worst is O(N)
            return root(p) == root(q);
        }
        void union_(int p, int q){ //union  O(N+)包括了find的复杂度
            id[root(p)] = id[root(q)];           
        }
        ~quickunion(){
            if(id)
                delete [] id;
        }
    private:
        int root(int i){
            while(id[i] != i)
                i = id[i];
            return i;
        }
    private:
        int *id;
        int size;
    };


    class weightedquickunion{
    public:
        explicit weightedquickunion(int i) : size(i){//初始化  O(N)
            id = new int[size];
            sz = new int[size];
            for(int i = 0; i < size; i++){
                id[i] = i;
                sz[i] = 1;
            }
        }
        void union_(int p, int q){ //union的复杂度主要是root的复杂度
                                   //此法生成的树的高度最高为lg2(N)
                                   //因此  复杂度为 O(lg N)
            int i = root(p);
            int j = root(q);
            if(sz[i] < sz[j]){
                sz[j] += sz[i];
                id[i] = j;
            }else{
                sz[i] += sz[j];
                id[j] = i;
            }
        }
        bool connected(int p, int q){ //O(N)
            return root(p) == root(q);
        }
        ~weightedquickunion(){
            if(id)
                delete [] id;
        }
    private:
    int root(int i){
        while(id[i] != i){
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }
    private:
        int *id;
        int *sz;
        int size;
    };

}