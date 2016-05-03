#include <cstdlib>
#include <cstring>
#include <iostream>
enum Type
{
    LEAF,
    BRCH
};
template <typename T, int N>
class Brch;
template <typename T, int N>
class Leaf;
template <typename T, int N>
class Node
{
    public:
        T data[N+1];
        int num;
        Brch<T, N> *parent;
        Type node_type;
        typedef T value_type;
        const int Min;

/*funtion*/
        virtual Type get_node_type()const =0;
        virtual Brch<T, N> *splice()=0;
        Node(Type type=LEAF, int n=0, Brch<T, N> *p=NULL)
            :node_type(type), num(0), parent(p), Min(N/2)
        {
            memset(data, 0, sizeof(T)*(N+1));
        }
        virtual void insert(const T&, Node *){}; 
};
template <typename T, int N>
class Leaf : public Node<T, N>
{
    public:
        void *ptr[N+1];
        Leaf *prev;
        Leaf *next;
        const int Max;
/*function*/
        Leaf(Type type=LEAF, Brch<T, N> *pa=NULL, Leaf *pr=NULL, Leaf *ne=NULL, int num=0)
            :Max(N), prev(pr), next(ne), Node<T, N>(type, num, pa)
        {
            memset(ptr, 0, sizeof(void *)*(N+1));
        }
        Type get_node_type() const{return LEAF;}
        Brch<T, N> *splice();
};
template <typename T, int N>
class Brch : public Node<T, N>
{
    public:
        const int Max;
        Node<T, N> *sub[N+1];
/*function*/

        Brch(Type type=BRCH, Brch *pa=NULL, int num=0)
            :Max(N-1), Node<T, N>(type, num, pa)
        {
            memset(sub, 0, sizeof(void *)*(N+1));
        }
        Type get_node_type() const{return BRCH;}
        void insert(const T&key, Node<T, N> *right);
        Brch<T, N> *splice();
};
template <typename T, int N>
class Result
{
    public:
        bool tag;
        Leaf<T, N> *pcur;
        int pos;
/*function*/

        Result():tag(false), pcur(NULL), pos(0)
    {}
};
template <typename T, int N>
class BTree
{
    private:
        Node<T, N> *proot;
        Leaf<T, N> *list;
    public:
        BTree() : proot(NULL), list(NULL) {}
        bool insert(const T&key, void *);
        Result<T, N> find_root(const T&);
        void insert(Leaf<T, N> *p, int pos, const T&key, void *ptr);
        void show() const;
};

