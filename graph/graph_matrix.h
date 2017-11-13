/*************************************************************************
	> File Name: graph_matrix.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 Nov 2017 11:11:57 AM CST
 ************************************************************************/

#ifndef _GRAPH_MATRIX_H
#define _GRAPH_MATRIX_H
#include <vector>


template <typename Tv>
struct Vertex{
    Tv data;
    int inDegree;
    int outDegree;
    VStatus status;
    int dtime, ftime;
    int parent;
    int priority;
    Vertex(const Tv &d = (Tv)0) : data(d), inDegree(0), outDegree(0),
        status(UNDISCOVERED), dtime(-1), ftime(-1),
        parent(-1), priority(INT_MAX){}
};

template <typename Te>
struct Edge{
    Te data;
    int weight;
    EType type;
    Edge(const Te& d, int w) : data(d), weight(w), type(UNDETERMINED){}
};

template <typename Tv, typename Te>
class Graph_Matrix : public Graph<Te, Te>{
private:
    std::vector<std::vector<Tv>> v;//顶点
    std::vector<std::vector<Edge<Te>* >> e;//边
public:
    Graph_Matrix(){n = e = 0;}
    ~Graph_Matrix(){
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                delete E[j][k];
    }
    virtual Tv& vertex(int i){return v[i].data;}//数据
    virtual int inDegree(int i){return v[i].inDegree;}//入度
    virtual int outDegree(int i){return v[i].outDegree;}//出度
    virtual int firstNbr(int i){return nextNbr(i, n);}//首个邻接顶点
};

#endif
