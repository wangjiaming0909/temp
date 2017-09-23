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
        quickunion(int i) : size(i){
            id = new int[size];
            for(int i = 0; i < size; i++)
                id[i] = i;
        }
        bool connected(int p, int q){
            return root(p) == root(q);
        }
        void union_(int p, int q){
            id[root(p)] = id[root(q)];           
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

}