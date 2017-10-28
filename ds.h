#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

//2,返回数组a[0:n-1]的数值个数
namespace ds{
template <class T, size_t N>
constexpr size_t count(const T (&)[N] ){//数组的引用const T(&t)[N]
    return N;
}
//3,给数组begin-end-1赋值value
template <class T, size_t N>
void fill(T(&t)[N], size_t begin, size_t end, const T &value){
    size_t nums = (end - begin);
    if(end > N) throw range_error("out of array range");
    for(size_t i = 0; i < nums; i++){
        t[begin + i] = value;
    }
}
//遍历可以打印的数组
template <class T, size_t N>
void visitarray(const T(&t)[N]){
    for(size_t i = 0; i < N; i++){
        cout << t[i] << " ";
    }
    cout << endl;
}
//4  T只能是数字
template <class T, size_t N>
T inner_product(const T(&t1)[N], const T(&t2)[N]){
    T r = 0;
    for(size_t i = 0; i < N; i++){
        r += t1[i] * t2[i];
    }
    return r;
}
//19
//非递归计算n!
long long int jiecheng(int t){
    long long int temp = 1;
    for(; t!= 0; t--)
        temp *= t;
    return temp;
}
//20
//递归计算斐波纳挈数
int fibonacci(int n){
    if(0 == n)
        return 1;
    else if(1 == n)
        return 2;
    else
        return  fibonacci(n - 1) + fibonacci(n - 2);
}
//20 非递归计算斐波那契数
int fibonacci2(int f0, int f1, int n){
    vector<int> v(n + 1);
    v[0] = f0;
    v[1] = f1;
    for(int i = 2; i < n + 1; i++){
        v[i] = v[i-1] + v[i-2];
    }
    return v[n];
}

//21
//递归  x是奇数 f(x)=f(3x+1), x是偶数，f(x)=x/2
int fx(int x){
    return (0 == x % 2) ? x/2 : fx(3*x+1);
}
// min

/*-----------------------------tree--------------------------*/
//二叉树节点类型
template <class T>
struct binaryTreeNode{
    T element;
    binaryTreeNode *leftChild, *rightChild;

    binaryTreeNode(): leftChild(nullptr), rightChild(nullptr){}
    binaryTreeNode(const binaryTreeNode& theElement) : 
        element(theElement), leftChild(nullptr), rightChild(nullptr){}
    binaryTreeNode( const T& theElement, 
                    binaryTreeNode *theLeftChild, 
                    binaryTreeNode *theRightChild)
       : element(theElement), leftChild(theLeftChild), rightChild(theRightChild){}
};

//binaryTree abstract data structure
template <class T>
class binaryTree{
public:
    virtual ~binaryTree() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*) (T*)) = 0;
    virtual void inOrder(void (*)(T*)) = 0;
    virtual void postOrder(void (*)(T*)) = 0;
    virtual void levelOrder(void (*)(T*)) = 0;
};
template <class T>
void myvisit(binaryTreeNode<T> *);

//linked binaryTree
template <class T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T>>{
public:
    linkedBinaryTree() : root(nullptr), treeSize(0){}
    linkedBinaryTree(const linkedBinaryTree &lbt) : root(lbt.root), treeSize(lbt.treeSize){}
    linkedBinaryTree(binaryTreeNode<T> *r) : root(r), treeSize(0){}
    ~linkedBinaryTree(){erase();}
    bool empty()const {return treeSize == 0;}
    int size() const {return treeSize;}
    void preOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        preOrder3(root);
    }
    void inOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        inOrder2(root);
    }
    void postOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        postOrder2(root);
    }
    void levelOrder(void (*)(binaryTreeNode<T> *)){
        visit = myvisit;
        levelOrder(root);
    }
    void erase(){
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    bool operator==(const linkedBinaryTree &bt){
        return compare(root, bt.root);
    }
    void swap_trees();//swap all the left and right child in the tree 
    // size_t max_nodes_level();
    // int height() const;
private:
    binaryTreeNode<T>   *root;
    int                 treeSize;
    static void (*visit) (binaryTreeNode<T> *);//静态变量需要初始化
private:
    static void preOrder(binaryTreeNode<T> *t);
    static void preOrder2(binaryTreeNode<T> *t);
    static void preOrder3(binaryTreeNode<T> *t);
    static void inOrder(binaryTreeNode<T> *t);
    static void inOrder2(binaryTreeNode<T> *t);
    static void postOrder(binaryTreeNode<T> *t);
    static void postOrder2(binaryTreeNode<T> *);
    static void levelOrder(binaryTreeNode<T> *);
    static void dispose(binaryTreeNode<T> *t){delete t;}
    bool compare(binaryTreeNode<T> *ltn, binaryTreeNode<T> *rtn);
    void swap_trees(binaryTreeNode<T> *);
    int height(binaryTreeNode<T> *);
    static void visitalongleftbranch(binaryTreeNode<T> *, stack<binaryTreeNode<T>*> &);
    static void goalongleftbranch(binaryTreeNode<T> *, stack<binaryTreeNode<T> *> &);
    static void goalongleftbranch2(binaryTreeNode<T> *, stack<binaryTreeNode<T> *> &);
};

template <class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T> *) = myvisit;

template <class T>
void linkedBinaryTree<T>::swap_trees(){
    swap_trees(root);
}

template <class T>
void linkedBinaryTree<T>::swap_trees(binaryTreeNode<T> *tn){
    if(!tn)
        return;
    if(!tn->leftChild && !tn->rightChild)
        return;
    else{
        swap_trees(tn->leftChild);
        swap_trees(tn->rightChild);
        auto node = tn->leftChild;
        tn->leftChild = tn->rightChild;
        tn->rightChild = node;
    }
       
} 

template <class T>
bool linkedBinaryTree<T>::compare(binaryTreeNode<T> *ltn, binaryTreeNode<T> *rtn){//时间复杂度与先序遍历相同
    if(ltn == NULL && rtn == NULL)
        return true;
    else if(ltn->element == rtn->element){
        if(compare(ltn->leftChild, rtn->leftChild))
            if(compare(ltn->rightChild, rtn->rightChild))
                return true;
    }
    return false;
}

template <class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        linkedBinaryTree<T>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

//非递归版本，自定义栈  版本1
template <class T>
void linkedBinaryTree<T>::preOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T>*> s;
    binaryTreeNode<T> *node;
    s.push(t);
    while(!s.empty()){
        assert(!s.empty());
        node = s.top();
        s.pop();
        visit(node);
        if(node->rightChild != nullptr)
            s.push(node->rightChild);
        if(node->leftChild != nullptr)
            s.push(node->leftChild);
    }
}

//给此函数一个root node, 和一个栈，
//访问次节点，右节点入栈，将此节点置换成左节点
template <typename T>
void linkedBinaryTree<T>::visitalongleftbranch(binaryTreeNode<T> *tt, stack<binaryTreeNode<T>*> &s){
    binaryTreeNode<T> *t = tt;
    while(t){
        visit(t);
        if(t->rightChild)//如果不判断空，则会插入空的元素，pop时，耽误时间
            s.push(t->rightChild);
        t = t->leftChild;
    }   
}
//非递归版本， 自定义栈 版本2
template <typename T>
void linkedBinaryTree<T>::preOrder3(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    while(true){
        visitalongleftbranch(t, s);
        if (s.empty())
            break;
        t = s.top();
        s.pop();
    }
}

template <typename T>
void linkedBinaryTree<T>::goalongleftbranch(binaryTreeNode<T> *t, stack<binaryTreeNode<T> *> &s){
    binaryTreeNode<T> *tt = t;
    while(tt){
        s.push(tt);
        tt = tt->leftChild;
    }
}


//非递归版本的中序遍历
template <typename T>
void linkedBinaryTree<T>::inOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    while(true){
        if(t) goalongleftbranch(t, s);
        if(s.empty()) break;
        t = s.top();
        s.pop();
        visit(t);
        t = t->rightChild;
    }
}

template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        inOrder(t->leftChild);
        linkedBinaryTree<T>::visit(t);
        inOrder(t->rightChild);
    }
}

template <typename T>
void linkedBinaryTree<T>::goalongleftbranch2(binaryTreeNode<T> *t, stack<binaryTreeNode<T>*> &s){
    binaryTreeNode<T> *tt = t;
    while(tt){
        s.push(tt);
        if(tt->rightChild) s.push(tt->rightChild);
        tt = tt->leftChild;
    }
}
template <typename T>
void linkedBinaryTree<T>::postOrder2(binaryTreeNode<T> *t){
    stack<binaryTreeNode<T> *> s;
    while(true){
        if(t)
            goalongleftbranch(t, s);
        if(s.top()->rightChild){
            t = s.top()->rightChild;
            continue;
        }
        if(s.empty()) break;
        t = s.top();
        visit(t);
        s.pop();
        t = nullptr;
    }
}

template <class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<T>::visit(t);
    }
}

template <class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T> *t){
    if(t == NULL)
        return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if(hl > hr)
        return ++hl;
    else
        return ++hr;
}

template <class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T> *t){
    queue<binaryTreeNode<T>*> q;
    while(t != NULL){
        visit(t);
        if(t->leftChild != NULL)
            q.push(t->leftChild);
        if(t->rightChild != NULL)
            q.push(t->rightChild);
        try{t = q.front();}
        catch(...){
            return ;
        }
        q.pop();
    }
}

// size_t max_nodes_level(){//max_width
//     queue<binaryTreeNode<T> *> q;

// }


template <class E>
void myvisit(binaryTreeNode<E> *x){
    std::cout << x->element << " " << std::flush;
}
/*--------------------------数组描述的二叉树----------------------------*/
//遍历数组描述的二叉树
template <class T>
class array_BT{
public:
    array_BT(const vector<pair<T, bool>> &p) : v(std::move(p)){
        setheight();
    }
    array_BT(const array_BT &abt) : v(abt.v), h(abt.h){}
    void preOrder();
    void inOrder();
    void postOrder();
    void levelOrder();
    void print_v_addr(){
        cout << &v << endl;
    }
    size_t height(){return h;}
private:
    void setheight(){
        h = log2(v.size()) + 1;
    }
    
    void visit(size_t it);
    void preOrder(size_t it);
    void inOrder(size_t);
    void postOrder(size_t);
private:
    vector<pair<T, bool>> v;
    size_t h;
};
/*------preOrder------*/
template <class T>
void array_BT<T>::preOrder(){
    preOrder(0);
}
template <class T>
void array_BT<T>::preOrder(size_t it){
    auto leftchild = it * 2 + 1;
    auto rightchild = leftchild + 1;
    visit(it);
    if(leftchild < v.size())
        preOrder(leftchild);
    if(rightchild < v.size())
        preOrder(rightchild);
}
/*------preOrder------*/
/*------INOrder------*/
template <class T>
void array_BT<T>::inOrder(){
    inOrder(0);    
}
template <class T>
void array_BT<T>::inOrder(size_t it){
    auto leftchild = it*2 + 1;
    auto rightchild = leftchild + 1;
    if(leftchild < v.size())
        inOrder(leftchild);
    visit(it);
    if(rightchild < v.size())
        inOrder(rightchild);
}
/*------INOrder------*/
/*------postOrder------*/
template <class T>
void array_BT<T>::postOrder(){
    postOrder(0);
}

template <class T>
void array_BT<T>::postOrder(size_t it){
    auto leftchild = it*2 + 1;
    auto rightchild = leftchild + 1;
    if(leftchild < v.size())
        postOrder(leftchild);
    if(rightchild < v.size())
        postOrder(rightchild);
    visit(it);
}

/*------postOrder------*/
/*------levelOrder------*/
template <class T>
void array_BT<T>::levelOrder(){
    for(size_t it = 0; it < v.size(); it++)
        visit(it);
}
/*------levelOrder------*/
//visit
template <class T>
void array_BT<T>::visit(size_t it){
    if(v[it].second == false)
        return ;
    cout << v[it].first << " ";
}

/*-----------------------------tree--------------------------*/
}

