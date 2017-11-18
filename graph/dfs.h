
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
    void _dfs(graph &g, int v){
        _marked[v] = true;
        std::cout << v << " " << std::flush;
        _count++;
        for (auto w : g.adj(v)){
            if (!marked(w))
            _dfs(g, w);
        }
    }

private:
    std::vector<int> _marked;
    int _count;
};

class CC{
public:
    CC(graph &g){
        _marked.resize(g.V());
        _id.resize(g.V());
        for(int s = 0; i < g.V(); i++){
            if(!_marked[s]){
                _dfs(g, s);
                count++;
            }
        }
    }
    bool connected(int v, int w){
        return _id[v] == _id[w];
    }
    int count(){
        return _count;
    }
    int id(int v){
        return _id[v];
    }
private:
    void _dfs(graph &g, int s){
        _marked[s] = true;
        _id[s] = count;
        for(auto w : g.adj(s)){
            if(!_marked[w])
                _dfs(g, w);
        }
    }
private:
    std::vector<int> _marked;
    std::vector<int> _id;
    int _count;
};
}

#endif // _DFS_H_