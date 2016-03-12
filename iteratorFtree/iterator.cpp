#include <iostream>
#include <stack>
#include <utility>
#define END '#'
template <typename Type>
class Node{
    public:
        Node *left;
        Type data;
        Node *right;
        Node(Node *l, Type data, Node *r) :left(l), data(data), right(r){}
        ~Node(){}
};
template <typename Type>
class Tree{
    private:
        Node<Type> *root;    
    private:
        Node<Type> *create(const Type *&msg);
        void print_prev(Node<Type> *) const;
    public:
        Tree(const Type *);
        void prev_print() const;
        Node<Type> *get_root() const {return root;}
        Tree()=default;
        ~Tree(){}
};
template <typename T>
void Tree<T>::print_prev(Node<T> *root) const {
    if (root != nullptr){
        std::cout << root->data << " ";
        print_prev(root->left);
        print_prev(root->right);
    }
}
template <typename T>
void Tree<T>::prev_print() const{
    if (root == nullptr){
        return;
    }
    else{
        print_prev(root);
    }
}
template <typename T>
Node<T> *Tree<T>::create(const T *&msg){
    Node<T> *new_node = nullptr;
    if (*msg != END){
        T tmp = *msg;
        Node<T> *l = create(++msg);
        Node<T> *r = create(++msg);
        new_node = new Node<T>(l, tmp, r);
    }
    return new_node;
}
template <typename Type>
Tree<Type>::Tree(const Type *msg):root(nullptr){
    if (msg != nullptr){
        root = create(msg);
    }
}
//////////////////////////////////////////////////////////////////

template <typename T>
class TreeItertor{
    protected:
        Tree<T> &tree;
        Node<T> *ptr;
    public:
        TreeItertor(Tree<T> &t) : tree(t), ptr(nullptr){}
        ~TreeItertor(){}
        bool is_over(){ return ptr == nullptr;}
        virtual void get_start() = 0; 
        virtual T operator*() const= 0;
        virtual void operator++() = 0;
};

template<typename T>
class PrevIterator : public TreeItertor<T>{
    private:
        std::stack<Node<T> *> st;
        using TreeItertor<T>::ptr;
        using TreeItertor<T>::tree;
    public:
        PrevIterator(Tree<T> &t) : TreeItertor<T>(t){}
        ~PrevIterator(){}
        virtual T operator*() const override;
        virtual void operator++() override;
        virtual void get_start()  override;
};
template <typename T>
T PrevIterator<T>::operator*() const {
    return ptr->data ;
}
template <typename T>
void PrevIterator<T>::get_start(){
    TreeItertor<T>::ptr = TreeItertor<T>::tree.get_root();
    if (ptr != nullptr){
        st.push(ptr);
    }
    operator++();
}
template <typename T>
void PrevIterator<T>::operator++(){
    if (st.empty()){
        ptr = nullptr;
        return;
    }
    else{
        ptr = st.top(); st.pop();

        if (ptr->right != nullptr){
            st.push(ptr->right);
        }
        if (ptr->left != nullptr){
            st.push(ptr->left);
        }
    }
}

template<typename T>
class MidIterator : public TreeItertor<T>{
    protected:
        std::stack<std::pair<Node<T> *, int>> st;
        using TreeItertor<T>::ptr;
        using TreeItertor<T>::tree;
    public:
        MidIterator(Tree<T> &t) : TreeItertor<T>(t){}
        ~MidIterator(){}
        virtual T operator*() const override{
            return ptr->data;
        }
        virtual void operator++() override{
            while (!st.empty()){
                auto i = st.top(); st.pop();
                if (i.second == 1){
                    i.second++;
                    st.push(i);
                    if (i.first->left != nullptr){
                        st.push({i.first->left, 1});
                    }
                }
                else if (i.second == 2){
                    ptr = i.first;
                    if (i.first->right != nullptr){
                        st.push({i.first->right, 1});
                    }
                    return;
                }
            }
            ptr = nullptr;
        }
        virtual void get_start()  override{
            ptr = tree.get_root();
            if (ptr != nullptr){
                st.push({ptr, 1});
            }
            operator++();
        }
};

void Print(TreeItertor<char> & it){
    it.get_start();
    do{
        std::cout << *it << " ";
        ++it;
    }while (!it.is_over());
}

//////////////////////////////////////////////////////////////////////
//last traverse
//
//

template<typename T>
class LastIterator : public TreeItertor<T>{
    protected:
        std::stack<std::pair<Node<T> *, int>> st;
        using TreeItertor<T>::ptr;
        using TreeItertor<T>::tree;
    public:
        LastIterator(Tree<T> &t) : TreeItertor<T>(t){}
        ~LastIterator(){}
        virtual T operator*() const override{
            return ptr->data;
        }
        virtual void operator++() override{
            while (!st.empty()){
                auto i = st.top(); st.pop();
                if (i.second == 1){
                    ++i.second; st.push(i);
                    if (i.first->left != nullptr){
                        st.push({i.first->left, 1});
                    }
                }
                else if (i.second == 2){
                    ++i.second; st.push(i);
                    if (i.first->right != nullptr){
                        st.push({i.first->right, 1});
                    }
                }
                else {
                    ptr = i.first;
                    return;
                }
            }
           ptr = nullptr;
        }

        virtual void get_start()  override{
            ptr = tree.get_root();
            if (ptr != nullptr){
                st.push({ptr, 1});
            }
            operator++();
        }
};

///////////////////////////////////////////////////////////////////
//
//
//
//

template<typename T>
class OtherMidIterator : public MidIterator<T>{
    private:
        std::stack<Node<T> *> st;
        using TreeItertor<T>::ptr;
        using TreeItertor<T>::tree;
        Node<T> *p;
    public:
        OtherMidIterator(Tree<T> &t) : MidIterator<T>(t){}
        ~OtherMidIterator(){}
        virtual void operator++() override{
            while (p != nullptr){
                st.push(p);
                p = p->left;
            }
            if (st.empty()){
                ptr = nullptr;
                return;
            }
            else {
                p = st.top(); st.pop();
                ptr = p;
                p = p->right;
            }
        }
        virtual void get_start()  override{
            p = tree.get_root();
            operator++();
        }

};
template<typename T>
class OtherLastIterator : public LastIterator<T>{
    private:
        std::stack<Node<T> *> st;
        using TreeItertor<T>::ptr;
        using TreeItertor<T>::tree;
        Node<T> *p;
    public:
        OtherLastIterator(Tree<T> &t) : LastIterator<T>(t){}
        ~OtherLastIterator(){}
        virtual void operator++() override{
            while (true){
                while (p != nullptr)    {
                    st.push(p);
                    p = p->left;
                }
                if (st.empty()) {
                    ptr=nullptr;
                    return;
                }
                p = st.top();
                if (p->right == nullptr || p->right == ptr){
                    st.pop();
                    ptr = p;
                    p = nullptr;
                    return;
                }
                else {
                    p = p->right;
                }
            }

        }
        virtual void get_start()  override{
            p = tree.get_root();
            operator++();
        }

};






int main(){
    Tree<char> tree("ABC##DE##F##G#H##");
    //tree.prev_print();
    PrevIterator<char> prev(tree);
    MidIterator<char> mid(tree);
    LastIterator<char> last(tree);
    OtherMidIterator<char> omid(tree);
    OtherLastIterator<char> olast(tree);
    Print(prev);
    std::cout << "\n";
    Print(mid);
    std::cout << "\n";
    Print(omid);
    std::cout << "\n";
    Print(last);
    std::cout << "\n";
    Print(olast);
    return 0;
}








