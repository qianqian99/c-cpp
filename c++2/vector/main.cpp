#include <iostream>
#include <cstring>
#include <cstdlib>
template <typename Type>
class vector{
  private:
    Type *data;
    int size;
    int cur;
  public:
    vector(int size=10);
    vector(const vector<Type> &v);
    ~vector(){
      delete []data;
      cur = 0;
      size = 0;
    };
    vector<Type> &operator = (const vector<Type> &);
    void resize();
    void pop_back();
    void push_back(const Type &);
    Type &operator [] (int pos);
    const Type &operator [] (int pos) const;
    const int &vsize() const;
    class iterator{
      private:
        int pos;
        vector<Type> *const pv;
      public:
        iterator operator + (int pos) const{
          return iterator(pv, this->pos+pos);
        }
        iterator operator - (int pos) const{
          return iterator(pv, this->pos-pos);
        }
        iterator(vector<Type> *p, int loc = 0) : pv(p), pos(loc){}
        bool operator != (const iterator &it) const{
          return it.pos != pos;
        }
        void operator ++ () {
          pos++;
        }
        Type &operator * () {
          return (*pv)[pos];
        }
        const Type &operator *() const {
          return pv[pos];
        }
    };
    iterator begin() {
      return iterator(this);
    }
    iterator end() {
      return iterator(this, cur);
    }
};
template <typename Type>
Type &vector<Type>::operator [] (int pos) {
  return data[pos];
}
template <typename Type>
const Type &vector<Type>::operator [] (int pos) const{
  return data[pos];
}
template <typename Type>
void vector<Type>::pop_back() {
  if (cur <= 0) {return;}
  data[--cur] = 0;
}
template <typename Type> 
void vector<Type>::resize() {
  Type *p = new Type[size*2];
  memcpy(p, data, sizeof(Type)*size);
  delete []data;
  data = p;
  size = size*2;
}
template <typename Type>
void vector<Type>::push_back(const Type &val) {
  if (cur >= size) {
    resize();
  }
  data[cur++] = val;
}
template <typename Type>
vector<Type> &vector<Type>::operator=(const vector<Type> &v) {
  if (data == v.data) {
    return *this;
  }
  delete []data;
  data = new Type[v.size];
  memcpy(data, v.data, sizeof(Type)*v.size);
  size = v.size;
  cur = v.cur;
  return *this;
}
template <typename Type>
vector<Type>::vector(int size) {
  this->size = size;
  cur = 0;
  data = new Type[this->size];
}
template <typename Type>
vector<Type>::vector(const vector<Type> &v) {
  data = new Type[v.size];
  memcpy(data, v.data, sizeof(Type)*v.size);
  size = v.size;
  cur = v.cur;
}
template <typename Type>
const int &vector<Type>::vsize() const{
  return size;
}
template <typename Type> 
void swap(Type &l, Type &r) {
  Type tmp = l;
  l = r;
  r = tmp;
}
// 内敛
template <typename iterator>
void sort(iterator first, iterator end) {
  int k = 0;
  for (iterator i = first; i!=end-1; ++i, ++k){
    for (iterator j=first; j!=end-k-1; ++j) {
      if (*j > *(j+1))
        swap(*j, *(j+1));
    }
  }
}
template <typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, T val) {
  while (first != last) {
    if (val == *first) {
      return first;
    }
    ++first;
  }
  return last;
}
template <typename T>
class Fun{
  public:
    Fun(T val=T()) : val(myval) {}
    bool operator () (const T &b) {
      return a > 50;
    }
  private:
    T myval;
};
template <typename Iterator, typename T, typename Fun> 
Iterator bfind(Iterator first, Iterator last, Fun f) {
  //todo
  while (first != last) {
    if (f(*first)) {
      return first;
    }
    ++first;
  }
  return last;
}
int main() {
  vector<int> v;
  vector<int> v2(3);
  v2.push_back(10);
  v2.push_back(40);
  v2.push_back(30);
  v2.push_back(60);
  v2.push_back(50);
  v2.push_back(3);
  vector<int>::iterator it = v2.begin();
  for (; it!=v2.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  vector<int>::iterator i = v2.begin();
  vector<int>::iterator first = v2.begin();
  vector<int>::iterator last = v2.end();
  sort(first, last);
  for (; i!=v2.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
  std::cout << *bfind(v2.begin(), v2.end(), 10, Fun<int>(50)) << std::endl;
  return 0;
}
