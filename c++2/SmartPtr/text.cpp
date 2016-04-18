#include <iostream>
class HeapTable
{
  public:
    class Node
    {
      public:
        int count;
        void *msg;
        Node *next;
      public:
        Node(void *msg=NULL) : count(0), msg(msg), next(NULL){};
    };
    ~HeapTable(){
      Node *p = phead;
      while (p != NULL) {
        Node * tmp = p->next;
        std::cout << "~Heap over " << p << std::endl;
        p = tmp;
      }
      delete obj;
    }
    void addRef(void *m) {
      Node *p = phead->next;
      while (p != NULL) {
        if (p->msg == m) {
          p->count++;
          return;
        }
        p = p->next;
      }
      Node *tmp = new Node(m);
      std::cout << tmp << std::endl;
      tmp->next = phead->next;
      phead->next = tmp;
    }
    void subRef(void *m) {
      Node *p = phead->next;
      while (p != NULL) {
        if (p->msg == m) {
          p->count --;
          return;
        }
        p = p->next;
      }
    }
    int getRef(void *m) {
      Node *p = phead->next;
      while (p != NULL) {
        if (m == p->msg) {
          return p->count;
        }
        p = p->next;
      }
      return -1;
    }
    void delResource(void *m) {
      Node * prev = phead;
      Node * p = prev->next;
      while (p != NULL) {
        if (m == p->msg) {
          prev->next = p->next;
          std::cout << "over " << p << std::endl;
          delete p;
          return;
        }
        prev = p;
        p = p->next;
      }
    }
    ///bugs
    static HeapTable &getInstance() {
      if (NULL == obj) {
        obj = new HeapTable;
        std::cout << "the down " << obj << std::endl;
      }
      return *obj;
    }
  private:
    Node *phead;
    static HeapTable *obj;
    HeapTable(){
      phead = new Node();
      std::cout << phead << std::endl;
    }
};
HeapTable *HeapTable::obj=NULL;
template <typename T>
class SmartPtr
{
  private:
    T *mptr;
    static HeapTable resource; 
  public:
    SmartPtr(T *p) : mptr(p) {
      std::cout << p << std::endl;
      if (mptr != NULL) {
        addRef();
      }
    }
    SmartPtr(const SmartPtr &s) : mptr(s.mptr) {
      addRef();
    }
    SmartPtr &operator = (const SmartPtr &s) {
      if (getRef() == 0) {
        delResource();
        std::cout << "SmartPtr is over " << mptr << std::endl;
        delete mptr;
      }
      else 
      {
        subRef();
      }
      mptr = s.mptr;
      addRef();
      return *this;
    }
    ~SmartPtr() {
      if (getRef() == 0) {
        delResource();
        std::cout << "SmartPtr is over" << mptr << std::endl;
        delete mptr;
      }
      else
      {
        subRef();
        std::cout << "subRef is called" << std::endl;
      }
    }
    int getRef() {return resource.getRef(mptr);}
    void addRef() {resource.addRef(mptr);}
    void subRef() {resource.subRef(mptr);}
    void delResource() {resource.delResource(mptr);}
};
template <typename T>
HeapTable SmartPtr<T>::resource=HeapTable::getInstance();
int main ()
{
  SmartPtr<int> ptr1(new int);
  SmartPtr<int> ptr2(new int);
  //int *p = new int;
  //SmartPtr<int> ptr3(p);
  //ptr2 = ptr1;
  //SmartPtr<char> pt((char *)p);
  return 0;
}
