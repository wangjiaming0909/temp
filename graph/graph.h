#ifndef _GRAPH_H
#define _GRAPH_H

#include <stack>
#include <queue>

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;

typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te>
class graph {
 private:
  void reset() {
    for (int i = 0; i < num_v; i++) {
      status(i) = UNDISCOVERED;
      dtime(i) = ftime(i) = -1;
      parent(i) = -1;
      priority(i) = INT_MAX;
      for (int j = 0; j < num_v; j++)
        if (exists(i, j)) type(i, j) = UNDETERMINED;
    }
  }

 public:
//顶点
  int num_v;                           //顶点总数
  int num_e;                           //边总数
  virtual int insert(Tv const &) = 0;  //插入顶点，返回编号
  virtual Tv remove(int) = 0;  //删除顶点及其关联边，返回该顶点信息
  virtual Tv &vertex(int) = 0;     //顶点v的数据（该顶点的确存在）
  virtual int inDegree(int) = 0;   //顶点v的入度（该顶点的确存在）
  virtual int outDegree(int) = 0;  //顶点v的出度（该顶点的确存在）
  virtual int firstNbr(int) = 0;   //顶点v的首个邻接顶点
  virtual int nextNbr(int, int) = 0;  //顶点v的（相对于顶点j的）下一邻接顶点
  virtual VStatus &status(int) = 0;  //顶点v的状态
  virtual int &dtime(int) = 0;       //顶点v的时间标签dTime
  virtual int &ftime(int) = 0;       //顶点v的时间标签fTime
  virtual int &parent(int) = 0;      //顶点v在遍历树中的父亲
  virtual int &priority(int) = 0;    //顶点v在遍历树中的优先级数
// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
  virtual bool exists(int, int) = 0;  //边(v, u)是否存在
  virtual void insert(Te const &, int, int,
                      int w = 0) = 0;  //在顶点v和u之间插入权重为w的边e
  virtual Te remove(int, int) = 0;  //删除顶点v和u之间的边e，返回该边信息
  virtual EType &type(int, int) = 0;  //边(v, u)的类型
  virtual Te &edge(int, int) = 0;  //边(v, u)的数据（该边的确存在）
  virtual int &weight(int, int) = 0;  //边(v, u)的权重
// 算法
  void bfs(int s) {                     //广度优先搜索算法
    reset();
    int clock = 0;
    int v = s;
    do
      if (UNDISCOVERED == status(v)){
        BFS(v, clock);
        cout << endl;
      }
    while (s != (v = (++v % num_v)));
  }
  void BFS(int v, int &clock){
    std::queue<int> q;
    status(v) = DISCOVERED;
    std::cout << v << " ";
    q.push(v);
    while(!q.empty()){
      int v = q.front();
      q.pop();
      dtime(v) = ++clock;
      for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
        if(UNDISCOVERED == status(u)){
          status(u) = DISCOVERED;
          std::cout << u << " ";
          q.push(u);
          type(v, u) = TREE;
          parent(u) = v;
        }else{
          type(v, u) = CROSS;
        }
      status(v) = VISITED;
    }
  }
  void dfs(int v){//深度优先搜索算法
    reset();
    for(int i = 0; i < num_v; i++){
      if(UNDISCOVERED == status(v))
        ;   
    }
  } 
  void DFS(int, int &);
  void bcc(int);  //基于DFS的双连通分量分解算法
  void BCC(int, int &, std::stack<int> &);
  std::stack<Tv> *tsort(int);  //基于DFS的拓扑排序算法
  void prim(int);              //最小支撑树Prim算法
  void dijkstra(int);          //最短路径Dijkstra算法
  template <typename PU>
  void pfs(int, PU);  //优先级搜索框架
  template <typename PU>
  void PFS(int, PU);

  bool TSORT(int, int &, std::stack<Tv> *);
};

#endif
