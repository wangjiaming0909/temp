#ifndef _BFS_H_
#define _BFS_H_
#include <queue>
#include <stack>
#include <vector>
namespace gra{

class bfs{
public:
    bfs(graph &g, int s, int size){
        _marked.resize(size);
        _edgeto.resize(size);
        _s = s;
        _bfs(g, s);
    }
    void _bfs(graph &g, int s){
        _marked[s] = true;
        std::queue<int> q;
        q.push(s);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(auto w : g.adj(v)){
                if(!_marked[w]){
                    _edgeto[w] = v;
                    _marked[w] = true;
                    q.push(w);
                }
            }
        }
    }
    bool haspathto(int v){
        return _marked[v];
    }
    //同dfspath,定义一个栈,逐个将edgeto[x]push进栈,返回该栈
    std::stack<int> pathto(int v){
        std::stack<int> path;
        if(!_marked[v])
            return path;
        for(int x = v; x != _s; x = _edgeto[x])
            path.push(x);
        path.push(_s);
        return path;
    }

private:
    std::vector<bool> _marked;
    std::vector<int> _edgeto;
    int _s;
    
};
}

#endif // _BFS_H_