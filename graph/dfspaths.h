#ifndef _DEPTHFIRST_PATHS_H_
#define _DEPTHFIRST_PATHS_H_
#include <stack>

namespace gra
{
class dfspath
{
  public:
    dfspath(graph &g, int s, int size)
    {
        _marked.resize(size);
        for (int i = 0; i < size; i++)
        {
            _marked[i] = false;
        }
        _edgeto.resize(size);
        for (int i = 0; i < size; i++)
        {
            _edgeto[i] = INT_MAX;
        }
        _s = s;
        _dfs(g, _s);
        cout << endl;
    }
    bool haspathto(int v)
    {
        return _marked[v];
    }
    std::stack<int> pathto(int v)
    {
        std::stack<int> path;
        if (!_marked[v])
            return path;
        for (int x = v; x != _s; x = _edgeto[x])
            path.push(x);
        path.push(_s);
        return path;
    }

  private:
    void _dfs(graph &g, int s)
    {
        _marked[s] = true;
        std::cout << s << " " << std::flush;
        for (auto w : g.adj(s))
        {
            if (!_marked[w])
            {
                _edgeto[w] = s;
                _dfs(g, w);
            }
        }
    }

  private:
    std::vector<bool> _marked;
    std::vector<int> _edgeto; //从起点到一个顶点的已知路径的最后一个顶点
    int _s;                   //起点
};

} //namespace gra
#endif // _DEPTHFIRST_PATHS_H_