#include <iostream>
#include <cstdlib>
enum Type
{
    LEAF,
    BRCH
};
template <typename T, int N>
class Node
{
    protected:
      T data[N+1];
      int num;
      Node *parent;
      Type node_type;
  public:
      typedef T value_type;
      const int Min;
      Node(Type type=LEAF, int n=0, Node *p=NULL)
          :node_type(type), Min(N/2), num(n), parent(p)
      {
          memset(data, 0, sizeof(T)*(N+1));
      }
      virtual bool insert(const T &)=0;
      virtual int min_index() const=0;
      virtual Type get_type() const = 0; 
      virtual T &operator[](int pos)=0;
      virtual const T &operator[](int pos) const=0;
      virtual Node *_next(int i)=0;
      virtual int get_cur_size() const=0;
      virtual Node *_prev() =0;
      virtual Node *_next() =0;
      virtual T insert(int pos, const T&key) =0;
      virtual Node<T, N> *splice()=0;
};
template <typename T, int N>
class Result
{
    private:
        bool tag;
        Node<T, N> *pcur;
        int pos;
    public:
        Result(): tag(false), pcur(NULL), pos(-1){}
        void set_tag(bool t){tag = t;}
        void set_pcur(bool p){pcur = p;}
        void set_pos(int pos){this->pos = pos;}
        bool get_tag()const {return tag;}
        int get_pos() const{return pos;}
        Node<T, N> *get_pcur() {return pcur;}
        const Node<T, N> *get_pcur() const{return pcur;}
};
template <typename T, int N>
class Leaf : public Node<T, N>
{
    private:
        void *ptr[N+1];
        Leaf *prev;
        Leaf *next;
    public:
        const int Max;
        int min_index() const {return 0;}
        Leaf(Type type=LEAF, Node<T, N> *pa=NULL, Leaf<T, N> *p=NULL,
             Leaf<T, N> *n=NULL, int num=0) 
            :Max(N), prev(p), next(n), Node<T, N>(type, num, pa)
        {
            memset(ptr, 0, sizeof(void *)*(N+1));
        }
        T &operator[](int pos) {return Node<T, N>::data[pos];}
        const T &operator[] (int pos) const{return Node<T, N>::data[pos];}
        bool insert(const T &val);
        virtual Type get_node_type() const {return Node<T, N>::node_type;}
        Node<T, N> *_next(int i) {return ptr[i];}
        int get_cur_size() const{return Node<T, N>::num;}
        Node<T, N> *_prev(){return prev;}
        Node<T, N> *_next(){return next;}
        T insert(int pos, const T&key);
        void move_one_elem(int pos)
        {
            int i = Node<T, N>::num-1;
            while (i >= pos)
            {
                Node<T, N>::data[i+1] = Node<T, N>::data[i];
                Node<T, N>::ptr[i+1] = Node<T, N>::ptr[i];
                --i;
            }
        }
        void move(Node<T, N> *pnew)
        {
            int i = Node<T, N>::num/2;
            int j = 0;

            while (i < Node<T, N>::num)
            { 
                pnew->data[j] = Node<T, N>::data[i];
                pnew->ptr[j] = Node<T, N>::ptr[i];
                ++j;
                ++i;
            }
            pnew->ptr[j] = Node<T, N>::ptr[i];
            Node<T, N>::num /= 2;
            pnew->Node<T, N>::num = Node<T, N>::num;
        }
        Node<T, N> *splice();
};
template <typename T, int N>
class Brch : public Node<T, N>
{
    private:
        Node<T, N> *sub[N+1];
    public:
        const int Max;
        Brch(Type type=BRCH, Node<T, N> *pa=NULL, int num=0):Max(N-1),Node<T, N>(type, num, pa) 
        {
            memset(sub, 0, sizeof(void *)*(N+1));
        }
        int min_index() const {return 1;}
        T &operator[](int pos) {return Node<T, N>::data[pos];}
        const T &operator[] (int pos) const{return Node<T, N>::data[pos];}
        virtual Type get_node_type() const {return Node<T, N>::node_type;}
        Node<T, N> *_next(int i) {return sub[i];} 
        int get_cur_size() const{return Node<T, N>::num;}
        Node<T, N> *_prev(){return Node<T, N>::prev;}
        Node<T, N> *_next(){return Node<T, N>::next;}
        bool insert(const T&key);
        T insert(int pos, const T&key);
        Node<T, N> *splice();
};
template <typename T, int N>
T Brch<T, N>::insert(int pos, const T&key)

template <typename T, int N>
bool Brch<T, N>::insert(const T&key)
{
    int i = Node<T, N>::num;
    while (i>=1 && Node<T, N>::data[i]>key) --i;
    insert(i, key);
    if (Node<T, N>::num > Node<T, N>::Max)
    {
        //splice;
    }
    return true;
}
template <typename T, int N>
Node<T, N> *Leaf<T, N>::splice()
{
    Node<T, N> *new_node = new Leaf<T, N>;
    Node<T, N> *n = Node<T, N>::next;
    Node<T, N>::next = new_node;
    new_node->prev = this;
    new_node->next = n;
    if (n != NULL) n->prev = new_node;
    move(new_node);
    if (Node<T, N>::parent == NULL)
    {
        Node<T, N> *new_root = new Brch<T, N>;
        new_node->parent = new_root;
        Node<T, N>::parent = new_root;
        new_root->insert(1, new_node->data[0]);
        return new_root;
    }
    else
    {
        new_node->parent = Node<T, N>::parent;
        Node<T, N>::parent->insert(key);
        return NULL;
    }
}
template <typename T, int N>
T Leaf<T, N>::insert(int pos, const T&key)
{
    move_one_elem(pos);
    Node<T, N>::num++;
    return Node<T, N>::data[pos] = key;
}
template <typename T, int N>
class BTree
{
    private:
        Node<T, N> *proot;
        Node<T, N> *list;
    public:
        BTree() : proot(NULL), list(NULL){}
        Result<T, N> findFromRoot(const T&key);
        Result<T, N> findFromList(const T&key);
        bool insert(const T&key);
};
template <typename T, int N>
bool BTree<T, N>::insert(const T &key)
{
    Result<T, N> res = findFromRoot(key);
    if (res.get_tag() || res.get_pcur() == NULL) return false;
    Node<T, N> *p = res.get_pcur();
    p->insert(res.get_pos(), key);
    if (p->get_cur_size() > Leaf<T, N>::Max)
    {
        //splice
    }
}
template <typename T, int N>
Result<T, N> BTree<T, N>::findFromList(const T&key)
{
    Node<T, N> *p = list;
    Node<T, N> *pr = p;
    int i = p->get_cur_size() -1;
    while (p != NULL && p[i] < key)
    {
        pr = p;
        p = p->_next();
        i = p->get_cur_size();
    }
    Result<T, N> res;
    if (p == NULL)
    {
        res.set_pcur(pr);
        res.set_pos(pr->get_cur_size()-1);
    }
    else
    {
        int i = p->get_cur_size()-1;
        while (i>=p->min_index() && (*p)[i]>key) --i;
        if (p != NULL)
        {
            res.set_pcur(p);
            res.set_pos(i);
            if (i<p->min_index() && p->_prev() != NULL)
            {
                p = p->_prev();
                res.set_pcur(p);
                res.set_pos(p->get_cur_size()-1);
            }
            else if (i>=p->min_index() && (*p)[i] == key) 
            {
                res.set_tag(true);
            }
        }
    }
    return res;
}
    template <typename T, int N>
Result<T, N> BTree<T, N>::findFromRoot(const T&key)
{
    Node<T, N> *p = proot;
    while (p->get_type() != LEAF)
    {
        int i = p->get_cur_size();
        while (i>=p->min_index() && (*p)[i]>key) --i;
        p = p->_next(i);
    }
    Result<T, N> res;
    int i = p->get_cur_size()-1;
    while (i>=p->min_index() && (*p)[i]>key) --i;

    /*
     * 找到       set loc set tag
     * 没有找到   set loc //special occasion
     * */
    if (p != NULL)
    {
        res.set_pcur(p);
        res.set_pos(i);
        if (i<p->min_index() && p->_prev() != NULL)
        {
            p = p->_prev();
            res.set_pcur(p);
            res.set_pos(p->get_cur_size()-1);
        }
        else if (i>=p->min_index() && (*p)[i] == key) 
        {
            res.set_tag(true);
        }
    }
    return res;
}
template <typename T, int N>
bool Leaf<T, N>::insert(const T &val)
{

}
int main()
{
    int array[] = {5, 19, 23, 3, 100, 24, 66, 32, 89, 101, 24, 78};
    ///////////////0   1   2   3   4   5   6   7   8   9   10   11
    BTree<int, 5> *pBtree = new BTree<int, 5>();
    pBtree->findFromRoot(3);
    for (int i=0; i<4; ++i)
        //pnode->insert(array[i]);
    return 0;
}
