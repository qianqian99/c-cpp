/*************************************************************************
 > File Name: TT.cpp
 > What I should do is fighting !!! 
 > hgg 
 > Created Time: 2016年03月19日 星期六 13时24分34秒
 ************************************************************************/
//    threading an binary tree
//    through cpp
//     including prev, mid, last
#include <iostream>

template <typename T>
class MidIterator;
template <typename T>
class LastIterator;
template <typename T>
class PrevIterator;

template <typename T>
class Tree{
    private:
        enum Tag{CHILD, LINK};
        struct Node{
            Node *left, *right;
            Tag ltag, rtag;
            T data;
            Node(Node *l, Node *r, T d) : left(l), right(r), ltag(CHILD), rtag(CHILD), data(d){}
            ~Node(){}
        };
        T End='#';
        Node *root;
        ////////////////////////////////////////////////////
        Node *create(const T *&str);
    public:
        typedef Node Node;
        Tree(const T *val);
        ~Tree(){}
        ///////////////////////friend
        friend class MidIterator<T>;
        //friend class LastIterator<T>;
        //friend class PrevIterator<T>;
};
////////////////////////////////////////////////////////
template <typename T>
typename Tree<T>::Node *Tree<T>::create(const T *&str){
    if (*str != End){
        T tmp = *str;
        Node *ltree = create(++str);
        Node *rtree = create(++str);
        return new Node(ltree, rtree, tmp);
    }
    return nullptr;
}
template <typename T>
Tree<T>::Tree(const T *val){
    if (val != nullptr){
        root = create(val);
    }
}
/////////////////////////////////////////////////////////////
template <typename T>
class TreeIterator{
    private:
    protected:
        Tree<T> &root;
        typename Tree<T>::Node *Ptr = nullptr;
    public:
        virtual ~TreeIterator(){};
        TreeIterator(const T *val) : root(*(new Tree<T>(val))){}
        virtual T operator*() const{
            return TreeIterator<T>::Ptr->data;
        }
        virtual TreeIterator &operator++() = 0;
        virtual TreeIterator &operator--() = 0;
};
//////////////////////////////////////////////////////////////////
template <typename T>
class MidIterator : public TreeIterator<T>{
    private:
        ////////////////////////////////func
        void mid_thread(typename Tree<T>::Node *root, typename Tree<T>::Node *&prev);
    protected:
    public:
        MidIterator(const T *val);
        ~MidIterator(){}
        bool is_end() const{
            return TreeIterator<T>::Ptr != nullptr;
        }
        void begin() {
            TreeIterator<T>::Ptr = first(TreeIterator<T>::root.root);
        }
        void rbegin() {
            TreeIterator<T>::Ptr = last(TreeIterator<T>::root.root);
        }
        virtual TreeIterator<T> &operator++() override{
            if (TreeIterator<T>::Ptr->rtag == Tree<T>::LINK) TreeIterator<T>::Ptr = TreeIterator<T>::Ptr->right;
            else TreeIterator<T>::Ptr = first(TreeIterator<T>::Ptr->right);
            return *this;
        }
        virtual TreeIterator<T> &operator--() override {
            if (TreeIterator<T>::Ptr->ltag == Tree<T>::LINK) TreeIterator<T>::Ptr = TreeIterator<T>::Ptr->left;
            else TreeIterator<T>::Ptr = last(TreeIterator<T>::Ptr->left);
            return *this;
        }
        typename Tree<T>::Node *
            first(typename Tree<T>::Node *root){
                while (root != nullptr && root->ltag != Tree<T>::LINK){
                    root = root->left;
                }
                return root;
            }
        typename Tree<T>::Node *
            last(typename Tree<T>::Node *root){
                while (root->rtag != Tree<T>::LINK){
                    root = root->right;
                }
                return root;
            }

};
template <typename T>
void MidIterator<T>::mid_thread(typename Tree<T>::Node *root, typename Tree<T>::Node *&prev){
    if (root != nullptr){
        mid_thread(root->left, prev);
        if (root->left == nullptr){
            root->left = prev;
            root->ltag = Tree<T>::LINK;
        }
        if (prev != nullptr && prev->right == nullptr){
            prev->right = root;
            prev->rtag = Tree<T>::LINK;
        }
        prev = root;
        mid_thread(root->right, prev);
    }
}
template <typename T>
MidIterator<T>::MidIterator(const T *val) : TreeIterator<T>(val){
    typename Tree<T>::Node *prev = nullptr;
    mid_thread(TreeIterator<T>::root.root, prev);
    prev->rtag = Tree<T>::LINK;
}
int main(){
    const char *str = "ABC##DE###F#H##";
    MidIterator<char> mt(str);
    mt.begin();
    for (; mt.is_end(); ++mt){
        std::cout << *mt << " ";
    }
    std::cout << "\n";
    mt.rbegin();
    for (; mt.is_end(); --mt){
        std::cout << *mt << " ";
    }
    return 0;
}
