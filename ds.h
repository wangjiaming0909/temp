#include <iostream>
#include <cassert>
#include <vector>
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
    virtual ~binaryTree();
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*) (T*)) = 0;
    virtual void inOrder(void (*)(T*)) = 0;
    virtual void postOrder(void (*)(T*)) = 0;
    virtual void levelOrder(void (*)(T*)) = 0;
};

//linked binaryTree
template <class T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T>>{
public:
    linkedBinaryTree() : root(nullptr), treeSize(0){}
    ~linkedBinaryTree(){erase();}
    bool empty()const {return treeSize == 0;}
    int size() const {return treeSize;}
    void preOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        preOrder(root);
    }
    void inOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        inOrder(root);
    }
    void postOrder(void (*thevisit)(binaryTreeNode<T> *)){
        visit = thevisit;
        postOrder(root);
    }
    void levelOrder(void (*)(binaryTreeNode<T> *));
    void erase(){
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const;
private:
    binaryTreeNode<T>   *root;
    int                 treeSize;
private:
    static void (*visit) (binaryTreeNode<T> *);
    static void preOrder(binaryTreeNode<T> *t);
    static void inOrder(binaryTreeNode<T> *t);
    static void postOrder(binaryTreeNode<T> *t);
    static void dispose(binaryTreeNode<T> *t){delete t;}
    int height(binaryTreeNode<T> *);
};

template <class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        linkedBinaryTree<T>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}
template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t){
    if(t != NULL){
        inOrder(t->leftChild);
        linkedBinaryTree<T>::viist(t);
        inOrder(t->rightChild);
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

//遍历数组描述的二叉树
template <class T>
class array_BT{
public:
    array_BT(const vector<pair<T, bool>> &p){
        v = std::move(p);
        setheight();
    }
    void preOrder();
    void inOrder();
    void postOrder();
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
    if(leftchild <= v.size())
    preOrder(leftchild);
    if(rightchild <= v.size())
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
    if(leftchild <= v.size())
        inOrder(leftchild);
    visit(it);
    if(rightchild <= v.size())
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
    if(leftchild <= v.size())
        postOrder(leftchild);
    if(rightchild <= v.size())
        postOrder(rightchild);
    visit(it);
}

/*------postOrder------*/

template <class T>
void array_BT<T>::visit(size_t it){
    if(v[it].second == false)
        return ;
    cout << v[it].first << " " << ends;
}

/*-----------------------------tree--------------------------*/
}

