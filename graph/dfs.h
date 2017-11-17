#ifndef _DFS_H_
#define _DFS_H_

namespace gra
{

class dfs
{
public:
  dfs(graph &g, int s, int size)
  {
    _marked.resize(size);
    _dfs(g, s);
    cout << endl;
  }
  bool marked(int w) { return _marked[w]; }
  int count() { return _count; }

private:
  void _dfs(graph &g, int v)
  {
    _marked[v] = true;
    std::cout << v << " " << std::flush;
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