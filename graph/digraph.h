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
        _hascycle = false;
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
//只是检测有没有环,有环就之后每一次dfs都直接return,因为已经设置_hascycle = true了
    void _dfs(digraph &g, int s){
        //从s开始的路径上,首先将其的_onStack设置为true,
        //当在此路径上,遇到某一个已经设置了_onStack则说明构成了一个环
        _onStack[s] = true;
        _marked[s] = true;
        for(auto w : g.adj(s)){
            if(_hascycle)
                return;
            else if(!_marked[w]){
                _edgeTo[w] = s;
                _dfs(g, w);
            }else if(_onStack[w]){
                _hascycle = true;
                for(int i = s; i != w; i = _edgeTo[i])
                    _cycle.push(i);
                _cycle.push(w);
            }
        }
        _onStack[s] = false;//到此处说明当前节点已经访问完毕了,且当前节点以及当前节点指向的所有节点的集合中没有构成环,因此将其设置为false,
    }
private:
    std::vector<bool>   _marked;
    std::vector<int>    _edgeTo;
    std::stack<int>     _cycle;
    std::vector<bool>   _onStack;
    bool                _hascycle;
};


class DepthFirstOrder{
public:
    DepthFirstOrder(digraph &g){
        _marked.resize(g.V());
        for(int i = 0; i < g.V(); i++){
            if(!_marked[i])
                _dfs(g, i);
        }
    }
    std::queue<int> pre(){return _pre;}
    std::queue<int> post(){return _post;}
    std::stack<int> reversepost(){return _reversepost;}
private:
    void _dfs(digraph &g, int s){
        _pre.push(s);
        _marked[s] = true;
        for(auto w : g.adj(s)){
            if(!_marked[w]){
                _dfs(g, w);
            }
        }
        _post.push(s);
        _reversepost.push(s);
    }
private:
    std::queue<int>     _pre;
    std::queue<int>     _post;
    std::stack<int>     _reversepost;
    std::vector<int>    _marked;
};

class Topological{
public:
    //首先检查该有向图是否包含环,如果包含环直接返回空
    //如果不包含,则取得深度优先搜索的顶点逆后序,即为拓扑排序
    Topological(digraph &g){
        directedCycle cycleFinder(g);
        _hasCycle = cycleFinder.hasCycle();
        if(!_hasCycle){
            DepthFirstOrder dfs(g);
            _order = dfs.reversepost();
        }
    }
    std::stack<int> order(){
        if(_hasCycle) return std::stack<int>();
        return _order;
    }
private:
    std::stack<int>     _order;
    bool                _hasCycle;    
};

class KosarajuSCC{
public:
    KosarajuSCC(digraph &g){
        _marked.resize(g.V());
        _id.resize(g.V());
        _count = 0;
        digraph tmp = g.reverse();
        DepthFirstOrder order(tmp);
        for(auto w = order.reversepost().top(); !order.reversepost().empty(); order.reversepost().pop()){
            if(!_marked[w]){
                _dfs(g, w);
                _count++;
            }
        }
    }
    bool strongly_connected(int v, int w){return _id[v] == _id[w];}
    int id(int v){return _id[v];}
    int count(){return _count;}
private:
    void _dfs(digraph &g, int s){
        _marked[s] = true;
        _id[s] = _count;
        for(auto w : g.adj(s))
            if(!_marked[w])
                _dfs(g, w);
    }
private:
    std::vector<int> _marked;
    std::vector<int> _id;//强联通分量的标志符
    int  _count;//强联通分量的数量
};  
}//namespace gra

#endif // _DIGRAPH_H_