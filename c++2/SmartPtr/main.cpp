#include <iostream>
template <typename T>
class SmartPtr
{
  private:
    T *mptr;
    int *pnum;
  public:
    SmartPtr(T *p) : mptr(p), pnum(new int){
      *pnum = 0;
    }
    SmartPtr(const SmartPtr &o) : mptr(o.mptr), pnum(o.pnum) {
      ++(*pnum);
    }
    T &operator *()
    {
      return *mptr;
    }
    const T &operator * () const
    {
      return *mptr;
    }
    T *operator -> ()
    {
      return mptr;
    }
    const T *operator -> () const
    {
      return mptr;
    }
    ~SmartPtr(){
      if (*pnum != 0) {
        --(*pnum);
        std::cout << "Smart ptr is over" << std::endl;
      }
      else
      {
        delete mptr;
        delete pnum;
        std::cout << "delete obj" << std::endl;
      }
    }
    SmartPtr &operator = (const SmartPtr &o)
    {
      if ((*pnum) == 0) {
        delete mptr;
        delete pnum;
      }
      else --(*pnum);
      mptr = o.mptr;
      pnum = o.pnum;
      ++(*pnum);
      return *this;
    }
};
class Text
{
  public:
    void show() {std::cout << "hello" << std::endl;}
};
int main ()
{
  SmartPtr<int> ptr1(new int);
  SmartPtr<int> ptr2(new int);
  SmartPtr<int> ptr3(ptr1);
  ptr2 = ptr1;
  SmartPtr<Text> ptr4(new Text);
  return 0;
}
