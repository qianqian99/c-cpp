#include "B+.h"
/*
 * Function of Btree
 * */
template <typename T, int N>
void BTree<T, N>::insert(Leaf<T, N> *p, int pos, const T&key, void *ptr)
{
    for (int i=p->num; i > pos+1; --i)
    {
        p->data[i] = p->data[i-1];
        p->ptr[i]  = p->ptr[i-1];
    }
    p->data[pos+1] = key;
    p->ptr[pos+1] = ptr;
    p->num++;
}
template <typename T, int N>
Result<T, N> BTree<T, N>::find_root(const T&key)
{
    Node<T, N> *p = proot;
    while (p->get_node_type() != LEAF)
    {
        int i = p->num;
        p->data[0] = key;
        while (p->data[i] > key) --i;
        p = ((Brch<T, N>*)p)->sub[i];
    }
    Leaf<T, N> *pleaf = (Leaf<T, N> *)p;
    int j = pleaf->num-1;
    while (pleaf->data[j] > key && j>=0) --j;
    Result<T, N> res;
    if (j == -1 && pleaf->prev != NULL) 
    {
        res.pcur = pleaf->prev;
        res.pos = res.pcur->num-1;
    }
    else if (pleaf->data[j] == key) res.tag = true;
    else 
    {
        res.pcur = pleaf;
        res.pos = j;
    }
    return res;
}

template <typename T, int N>
bool BTree<T, N>::insert(const T&key, void *ptr)
{
    /*tree is tmpty*/
    if (proot == NULL)
    {
        proot = list = new Leaf<T, N>;
        list->data[0] = key;
        list->ptr[0] = ptr;
        list->node_type = LEAF;
        list->num++;
        return true;
    }
    Result<T, N> res = find_root(key);
    /*find or error*/
    if (res.tag || res.pcur == NULL) return false;

    insert(res.pcur, res.pos, key, ptr);
    if (res.pcur->num > res.pcur->Max)
    {
        Brch<T, N> *p = res.pcur->splice();
        if (p != NULL) proot = p;
    }
    return true;
}
template <typename T, int N>
void BTree<T, N>::show() const
{
    Leaf<T, N> *p = list;
    while (p != NULL)
    {
        for (int i=0; i<p->num; ++i)
        {
            std::cout << p->data[i] << " ";
        }
        std::cout << std::endl;
         p = p->next;
    }
}
/*
 * Function of Leaf
 * */
template <typename T, int N>
Brch<T, N> *Leaf<T, N>::splice()
{
    Leaf<T, N> *pleaf = new Leaf<T, N>;
    /*move elem*/
    int i = Node<T, N>::Min+1;
    int j = 0;
    for (; i<=Max; ++i, ++j)
    {
        pleaf->data[j] = Node<T, N>::data[i];
        pleaf->ptr[j]  = ptr[i];
    }
    /*prev next*/
    Leaf<T, N> *p = next;
    next = pleaf;
    pleaf->prev = this;
    pleaf->next = p;
    if (p != NULL) p->prev = pleaf;

    /*num*/
    pleaf->num = Node<T, N>::Min+1;
    Node<T, N>::num = Max-Node<T, N>::Min;

    /*parent*/
    if (Node<T, N>::parent == NULL)
    {
        Brch<T, N> *s = new Brch<T, N>;
        s->data[1] = pleaf->data[0];
        s->sub[0] = this;
        s->sub[1] = pleaf;
        this->parent = s;
        pleaf->parent = s;
        s->num++;
        return s;
    }
    else
    {
        Node<T, N>::parent->insert(pleaf->data[0], pleaf);
        if  (Node<T, N>::parent->num > Node<T, N>::parent->Max)
        {
            return Node<T, N>::parent->splice();
        }
        return NULL;
    }
}

/*
 * Function of Brch
 * */
template <typename T, int N>
Brch<T, N> *Brch<T, N>::splice()
{
    //num parent do so d1 s1 d2 s2     d3    s3 d4 s4 d5 s5 d6 s6
    //
    Brch<T, N> *new_node = new Brch<T, N>;
    int i = Node<T, N>::Min+1;
    int j = 0;
    new_node->sub[j] = sub[i];
    i++;
    j++;
    while (i <= Max)
    {
        new_node->data[j] = Node<T, N>::data[i];
        new_node->sub[j]  = sub[i];
        ++i;
        ++j;
    }
    //new root
    if (Node<T, N>::parent == NULL)
    {
        Brch<T, N> *s = new Brch<T, N>;
        s->data[1] = new_node->data[0];
        s->sub[0] = this;
        s->sub[1] = new_node;
        this->parent = s;
        new_node->parent = s;
        s->num++;
        return s;
    }
    else
    {
        Node<T, N>::parent->insert(new_node->data[0], new_node);
        if  (Node<T, N>::parent->num > Node<T, N>::parent->Max)
        {
            return Node<T, N>::parent->splice();
        }
        return NULL;
    }
}
template <typename T, int N>
void Brch<T, N>::insert(const T&key, Node<T, N> *right)
{
    int i = Node<T, N>::num;
    while (i>0 && Node<T, N>::data[i]>key)
    {
        Node<T, N>::data[i+1] = Node<T, N>::data[i];
        sub[i+1] = sub[i];
        --i;
    }
    Node<T, N>::data[i+1] = key;
    sub[i+1] = right;
    Node<T, N>::num++;
    right->parent = this;
}
int main()
{
    char array[] = "qwertyuiopasdfghjkl123zxcvbnm6789450";
    BTree<char, 5> *ptree = new BTree<char, 5>;
    for (int i=0; i<sizeof(array)/sizeof(array[0]); ++i)
        ptree->insert(array[i], 0x0);
    ptree->show();
    return 0;
}
