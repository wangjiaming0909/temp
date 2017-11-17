#ifndef _GRAPH2_H_
#define _GRAPH2_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

namespace gra
{
class graph
{
  public:
    graph(int v)
    {
        _v = v;
        _e = 0;
    }
    graph(std::ifstream &is)
    {
        readstring(is);
    }
    int V()
    { //顶点数
        return _v;
    }
    int E()
    { //边的数目
        return _e;
    }
    //向图中添加一条边v-w
    void addEdge(int v, int w)
    {
        // if((int)_adj.size() < std::max(v, w))
        //     _adj.resize(std::max(v, w) + 1);
        _adj[v].insert(_adj[v].begin(), w);
        _adj[w].insert(_adj[w].begin(), v);
        _e++;
    }
    std::list<int> &adj(int v)
    { //和v相邻的所有顶点
        return _adj[v];
    }

  private:
    int _v;                           //顶点数目
    int _e;                           //边的数目
    std::vector<std::list<int>> _adj; //临接表
  private:
    void readstring(std::ifstream &is)
    {
        using namespace std;
        string v, e, text;
        istringstream line;
        getline(is, v);
        getline(is, e);
        _v = stoi(v);
        // _e = stoi(e);
        _adj.resize(_v);
        while (getline(is, text))
        {
            line = istringstream(text);
            string word;
            line >> word;
            int vertex1 = stoi(word);
            line >> word;
            int vertex2 = stoi(word);
            addEdge(vertex1, vertex2);
        }
    }
};
} //namespace gra
#endif // _GRAPH2_H_