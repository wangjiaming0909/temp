#ifndef _DIGRAPH_H_
#define _DIGRAPH_H_

namespace gra{

class digraph{
public:
    digraph(int v){
        _v = v;
        _e = 0;
        _adj.resize(v);
    }
    digraph(ifstream &is){
        _v = 0;
        _e = 0;
        _readstring(is);
    }
    int E(){return _e;}
    int V(){return _v;}
    std::vector<int> adj(int v){return _adj[v];}
    void addedge(int from, int to){
        _adj[from].insert(_adj[from].begin(), to);
        _e++;//边增加一个
    }
    digraph reverse(){
        digraph reversed_graph(_v);
        for(int i = 0; i < _v; i++){
            for(auto w : _adj[i])
                reversed_graph.addedge(w, i);
        }
        return reversed_graph;
    }
private:
    void _readstring(ifstream &is){
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
            istringstream line2(text);
            string word;
            line2 >> word;
            int vertex1 = stoi(word);
            line2 >> word;
            int vertex2 = stoi(word);
            addedge(vertex1, vertex2);
        }
    }
private:
    int _e;                             //边的数目
    int _v;                             //顶点数目
    std::vector<std::vector<int>> _adj; //临接表
};

//解决单点连通性的问题
class directedDFS{
public:
    directedDFS(digraph &g, int s){
        _marked.resize(g.V());
        _dfs(g, s);
    }
    //if v is marked 说明根到v是可达的
    bool marked(int v){return _marked[v];}

private:
    void _dfs(digraph &g, int s){
        _marked[s] = true;
        for(auto w : g.adj(s)){
            if(!_marked[w])
                _dfs(g, w);
        }
    }
private:
    std::vector<bool> _marked;
};

//寻找有向图中的环
class directedCycle{
public:
    directedCycle(digraph &g){
        _marked.resize(g.V());
        _edgeTo.resize(g.V());
        _onStack.resize(g.V());
        for(int i = 0; i < g.V(); i++){
            if(!_marked[i])
                _dfs(g, i);
        }
    }
    stack<int> cycle(){
        return _cycle;
    }
    bool hasCycle(){return _hascycle;}
private:
    void _dfs(digraph &g, int s){
        _onStack[s] = true;
        _marked[s] = true;
        _cycle.push(s);
        for(auto w : g.adj(s)){
            if(_hascycle)
                return;
            else if(!_marked[w]){
                _edgeTo[w] = s;
                _dfs(g, w);
            }else if(_onStack[w]){
                _hascycle = true;
                for(int i = s; i != w; i = _edgeTo[i]){
                    _cycle.push(i);
                }
            }
        }
    }
private:
    std::vector<bool>   _marked;
    std::vector<int>    _edgeTo;
    std::stack<int>     _cycle;
    std::vector<bool>   _onStack;
    bool                _hascycle;
};

}//namespace gra

#endif // _DIGRAPH_H_