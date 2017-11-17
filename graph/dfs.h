#ifndef _DFS_H_
#define _DFS_H_

namespace gra
{

class dfs
{
  public:
    dfs(graph &g, int s) { _dfs(g, s); }
    bool marked(int w) { return _marked[w]; }
    int count() { return _count; }

  private:
    void _dfs(graph &g, int v)
    {
        _marked.resize(v+1);
        _marked[v] = true;
        std::cout << v << " ";
        _count++;
        for (auto w : g.adj(v))
        {
            if (!marked(w))
                _dfs(g, w);
        }
    }

  private:
    std::vector<int> _marked;
    int _count;
};
}

#endif // _DFS_H_