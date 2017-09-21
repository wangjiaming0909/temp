#include <iostream>
using namespace std;

namespace coursera{
    //union find
    class unionfind{
    public:
        unionfind(int n){}
        void union_(int p, int q);
        bool connected(int p, int q); 
    };

    class quickfind{
    public:
    //initialize id to its index
        quickfind(int n) : size(n){
            id = new int[n];
            for(int i = 0; i < n; i++)
                *(id+i) = i;
        }
        //
        bool connected(int p, int q){
            return id[p] == id[q];
        }
        //union p to q
        //set id[p] to id[q]
        void union_(int p, int q){
            for(int i = 0; i < size; i++)
                if(id[i] == id[p])
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

}