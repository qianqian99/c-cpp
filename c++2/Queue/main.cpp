#include <iostream>
#define MAX_POOL_SIZE 10000

template <typename T>
class Queue
{
  private:
    class Node
    {
      public:
        T data;
        Node *next;
        static Node *myPool;
        Node(const T&v, Node *p=NULL) : data(v), next(p){}
        Node() : data(), next(NULL){}
        void *operator new(size_t size) {
          if (myPool == NULL) {
            myPool = (Node *)new char[sizeof(Node)*MAX_POOL_SIZE];
            Node *p = myPool;
            for (int i=0; i<MAX_POOL_SIZE-1; ++i)
            {
              p->next = p+1;
              p = p->next;
            }
            p->next = NULL;
          }
          Node *tmp = myPool;
          myPool = myPool->next;
          return tmp;
        }
        void operator delete(void *p) {
          Node *resp = (Node *)p;
          resp->next = myPool;
          myPool = resp;
        }
    };
    Node *mpfront;
    Node *mprear;
  public:
    Queue();
    ~Queue();
    T &head() {
      if (!empty()) {
        return mpfront->next->data;
      }
    }
    Queue(const Queue &);
    void addQue(const T &);
    void deUqe();
    bool empty() const;
};
template <typename T>
typename Queue<T>::Node * Queue<T>::Node::myPool= NULL;
template <typename T>
Queue<T>::~Queue()
{
  Node *p = mpfront;
  while (p != NULL) {
    Node *tmp = p->next;
    delete p;
    p = tmp;
  }
}
template <typename T>
Queue<T>::Queue(const Queue<T> &que)
{
  Node *p = que.mpfront;
  Node *start = new Node(p->data);
  mpfront = start;
  p  = p->next;
  while (p != NULL) 
  {
    Node *new_node = new Node(p->data);
    start->next = new_node;
    start = start->next;
    p = p->next;
  }
  mprear = start;
}
template <typename T>
Queue<T>::Queue() : mpfront(NULL), mprear(NULL)
{
  mpfront = new Node();
  mprear = mpfront;
}
template <typename T>
void Queue<T>::addQue(const T &val) 
{
  Node *p = new Node(val);
  mprear->next = p;
  mprear = p;
}
template <typename T>
bool Queue<T>::empty() const
{
  return mprear == mpfront;
}
template <typename T>
void Queue<T>::deUqe()
{
  if (empty()) {
    return;
  }
  Node *p = mpfront->next;
  if (mpfront->next == mprear)
  {
    mprear = mpfront;
  }
  mpfront->next = p->next;
  delete p;
}
int main () 
{
  try {
    Queue<int> queue;
    queue.addQue(10);
    queue.addQue(20);
    queue.addQue(30);
    queue.addQue(40);
    queue.addQue(50);
    queue.addQue(60);
    for (int i=6; i>0; --i) {
      std::cout << queue.head() << std::endl;
      queue.deUqe();
    }
  }
  catch(std::bad_alloc())
  {

  }
  return 0;
}
