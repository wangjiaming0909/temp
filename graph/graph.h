/*************************************************************************
	> File Name: graph.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 Nov 2017 11:14:26 AM CST
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H

typedef enum{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
}VStatus;

typedef enum{
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
}EType;

template <typename Tv, typename Te>
class graph{
private:

public:
//顶点
    int n;//顶点总数
    virtual int insert ( Tv const& ) = 0; //插入顶点，返回编号
    virtual Tv remove ( int ) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex ( int ) = 0; //顶点v的数据（该顶点的确存在）
    virtual int inDegree ( int ) = 0; //顶点v的入度（该顶点的确存在）
    virtual int outDegree ( int ) = 0; //顶点v的出度（该顶点的确存在）
    virtual int firstNbr ( int ) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr ( int, int ) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus& status ( int ) = 0; //顶点v的状态
    virtual int& dTime ( int ) = 0; //顶点v的时间标签dTime
    virtual int& fTime ( int ) = 0; //顶点v的时间标签fTime
    virtual int& parent ( int ) = 0; //顶点v在遍历树中的父亲
    virtual int& priority ( int ) = 0; //顶点v在遍历树中的优先级数
  // 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e; //边总数
    virtual bool exists ( int, int ) = 0; //边(v, u)是否存在
    virtual void insert ( Te const&, int, int, int ) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove ( int, int ) = 0; //删除顶点v和u之间的边e，返回该边信息
    virtual EType & type ( int, int ) = 0; //边(v, u)的类型
    virtual Te& edge ( int, int ) = 0; //边(v, u)的数据（该边的确存在）
    virtual int& weight ( int, int ) = 0; //边(v, u)的权重
// 算法
    // void bfs ( int ); //广度优先搜索算法
    // void dfs ( int ); //深度优先搜索算法
    // void bcc ( int ); //基于DFS的双连通分量分解算法
    // Stack<Tv>* tSort ( int ); //基于DFS的拓扑排序算法
    // void prim ( int ); //最小支撑树Prim算法
    // void dijkstra ( int ); //最短路径Dijkstra算法                                                                     
    // template <typename PU> void pfs ( int, PU ); //优先级搜索框架
};

#endif
