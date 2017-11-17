#ifndef _GRAPH_MATRIX_H
#define _GRAPH_MATRIX_H
#include <vector>

template <typename Tv>
struct Vertex
{
    Tv data;          //数据
    int inDegree;     //入度
    int outDegree;    //出度
    VStatus status;   //状态
    int dtime, ftime; // d and t time
    int parent;       //前一个节点
    int priority;     //优先级,给topological sort 用的?
    Vertex(const Tv &d = (Tv)0)
        : data(d),
          inDegree(0),
          outDegree(0),
          status(UNDISCOVERED),
          dtime(-1),
          ftime(-1),
          parent(-1),
          priority(INT_MAX) {}
};

template <typename Te>
struct Edge
{
    Te data;    //数据
    int weight; //权重
    EType type; //边的类型
    Edge(const Te &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class Graph_Matrix : public graph<Tv, Te>
{
  private:
    std::vector<Vertex<Tv>> v;              //顶点
    std::vector<std::vector<Edge<Te> *>> e; //边
  public:
    Graph_Matrix()
    { //初始化,边和顶点个数都是
        this->num_v = this->num_e = 0;
    }
    ~Graph_Matrix()
    { //逐条清除边
        for (int j = 0; j < this->num_v; j++)
            for (int k = 0; k < this->num_v; k++)
                delete e[j][k];
    }
    virtual Tv &vertex(int i) { return v[i].data; }         //数据
    virtual int inDegree(int i) { return v[i].inDegree; }   //入度
    virtual int outDegree(int i) { return v[i].outDegree; } //出度
    virtual int firstNbr(int i)
    {
        return nextNbr(i, this->num_v);
    } //首个邻接顶点
    virtual VStatus &status(int i) { return v[i].status; }
    virtual int nextNbr(int i, int j)
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }
    virtual int &dtime(int i) { return v[i].dtime; }
    virtual int &ftime(int i) { return v[i].ftime; }
    virtual int &parent(int i) { return v[i].parent; }
    virtual int &priority(int i) { return v[i].priority; }
    virtual int insert(const Tv &thevertex)
    { //插入一个顶点
        //新增一个节点:
        /* 1,
为每一个已经存在的节点新增一个可能与其相连的边,即e[i]新增一个为nullptr的元素
2, 节点个数加1
3, 为新增的节点添加一个数组,即为e增加一个元素,且每个元素都是nullptr
4, 在v的数组中添加这个节点 */
        for (int i = 0; i < this->num_v; i++)
        {
            e[i].push_back(nullptr); //
        }
        this->num_v++;
        e.push_back(vector<Edge<Te> *>(this->num_v, (Edge<Te> *)nullptr));
        v.push_back(Vertex<Tv>(thevertex));
        return 0;
    }
    virtual Tv remove(int i)
    {
        //删除一个节点
        /* 1, 删除该节点出的所有边
   2, 删除所有其他节点到该节点的边
   3, 删除该节点 */
        for (int j = 0; j < this->num_v; j++)
            if (e[i][j] != nullptr)
                delete e[i][j];
        for (int j = 0; j < this->num_v; j++)
        {
            if (e[j][i] != nullptr)
                delete e[j][i];
            e[j].erase(e[j].begin() + i);
        }
        auto re = v.erase(v.begin() + i);
        return re->data;
    }
    //边
    virtual bool exists(int i, int j)
    {
        return (0 <= i) && (i < this->num_v) && (0 <= j) && (j < this->num_v) &&
               e[i][j] != NULL;
    }
    virtual void insert(Te const &te, int i, int j, int k)
    { //最后一个参数是权重
        if(exists(i, j)) return ;
        e[i][j] = new Edge<Te>(te, k);
        this->num_e++;
        v[i].outDegree++;
        v[j].inDegree++;
    }
    virtual Te remove(int i, int j)
    {
        //删除顶点i和j之间的边
        Te ebak = edge(i, j);
        delete e[i][j];
        e[i][j] = nullptr;
        this->num_e--;
        v[i].outDegree--;
        v[j].inDegree--;
        return ebak;
    }
    virtual EType &type(int i, int j) {return e[i][j]->type;}
    virtual Te &edge(int i, int j) {return e[i][j]->data;}
    virtual int &weight(int i, int j) {return e[i][j]->weight;}
};

#endif
