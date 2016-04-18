#include <iostream>
#include <vector>

template <typename Type>
class iterator{
  public:
    virtual Type &operator * () = 0;
    virtual const Type &operator * () const = 0;
    virtual bool operator != (const iterator<Type> &it) = 0;
    virtual void operator ++ () = 0;
    virtual ~iterator(){};
};

template <typename Type>
class dIterator : public iterator<Type>{
  private:
    std::vector<Type> *obj;
    int pos;
  public:
    dIterator(std::vector<Type> *p = NULL, int size = 0) : obj(p) {
      pos = size;
    }
    ~dIterator(){}
    virtual Type &operator *() {
      return (*obj)[pos];
    }
    virtual const Type &operator *() const {
      return (*obj)[pos];
    }
    virtual bool operator != (const dIterator<Type> &it) {
      return it.pos != pos;
    }
    virtual void operator ++ () {
      pos++;
    }
};
template <typename Type>
class Mydata{
  private :
    std::vector<Type> data;
  public:
    iterator<Type> &begin() {
      dIterator<Type> *p = new dIterator<Type>(&data);
      return *p;
    }
    iterator<Type> &end() {
      dIterator<Type> *end = new dIterator<Type>(&data, data.size());
      return *end;
    }
    void insert(const Type &d) {
      data.push_back(d);
    }
};
int main(int argc, char *argv[])
{
  Mydata<int> data;
  data.insert(10);
  data.insert(20);
  data.insert(30);
  data.insert(40);
  data.insert(50);
  data.insert(60);


  for (iterator<int> &it = data.begin(); it!=data.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  return 0;
}
