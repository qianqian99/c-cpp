#include <iostream>
#include <cstring>
template <typename T>
class vector{
  private:
    T *pData;
    int cur;
    int size;
  public:
    vector(int num =0) : cur(0) {
      if (num == 0) {
        pData = new T[1];
        size = 1;
      }
      else {
        pData = new T[num];
        size = num;
      }
    }
    vector(const vector &v) {
      pData = new T[v.size];
      size = v.size;
      cur = v.cur;
      memcpy(pData, v.pData, sizeof(T)*cur);
    }
    vector &operator = (const vector &v) {
      delete pData;
      pData = new T[v.size];
      size = v.size;
      cur = v.cur;
      memcpy(pData, v.pData, sizeof(T)*cur);
      return *this;
    }
    void resize() {
      T *p = new T[size*2];
      memcpy(p, pData, sizeof(T)*cur);
      delete pData;
      pData = p;
      size *= 2;
    }
    vector &push_back(const T& val) {
      if (cur >= size) {
        resize();
      }
      pData[cur++] = val;
      return *this;
    }
    vector &pop_back() {
      if (cur >= 0) {
        cur--;
      }
      return *this;
    }
    T &operator [] (int pos) {
      return pData[pos];
    }
    const T& operator[] (int pos) const {
      return pData[pos];
    }
    ~vector(){
      delete []pData;
      cur = 0;
      size = 0;
    }
    class Citerator{
      private:
        vector *const pvct;
        int cur;
      public:
        typedef T value_type;
        Citerator(vector * pv, int pos=0) : pvct(pv), cur(pos){}
        ~Citerator() {}
        Citerator &operator++() {
          cur++;
          return *this;
        }
        Citerator &operator -- () {
          cur--;
          return *this;
        }
        bool operator < (const Citerator &i) const {
          return cur < i.cur;
        }
        T &operator *() {
          return (*pvct)[cur];
        }
        Citerator operator + (int pos) const{
          return Citerator(pvct, pos+cur);
        }
        Citerator operator - (int pos) const{
          return Citerator(pvct, cur-pos);
        }
        bool operator != (const Citerator &o) const {
          return cur != o.cur;
        }
    };
    Citerator begin() {
      return Citerator(this);
    }
    Citerator end() {
      return Citerator(this, cur);
    }
    typedef Citerator iterator;
};
template <typename Iterator>
void sort(Iterator first, Iterator last) {
  int k = 0;
  for (Iterator i=first; i!=last-1; ++i, ++k) {
    for (Iterator j=first; j!=last-1-k; ++j) {
      if (*j > *(j+1)) {
        typename Iterator::value_type val = *j;
        *j = *(j+1);
        *(j+1) = val;
      }
    }
  }
}
template <typename Iterator, typename Compare> 
void sort(Iterator first, Iterator last, Compare com) {
  int k = 0;
  for (Iterator i=first; i!=last-1; ++i, ++k) {
    for (Iterator j=first; j!=last-1-k; ++j) {
      if (com(*j, *(j+1))) {
        typename Iterator::value_type val = *j;
        *j = *(j+1);
        *(j+1) = val;
      }
    }
  }
}
template <typename Iterator, typename Compare>
Iterator qsort(Iterator first, Iterator last, Compare compare) {
  typename Iterator::value_type tmp = *first;
  Iterator start = first;
  ++first;
  --last;
  while (first < last) {
    while (!compare(*first, tmp)) 
      ++first;
    while (compare(*last, tmp))
      --last;
    if (first < last) {
      typename Iterator::value_type t_val = *first;
      *first = *last;
      *last = t_val;
      ++first;
      --last;
    }
  }
  typename Iterator::value_type val = *last;
  *last = tmp;
  *start = val;
  return last;
}
template <typename Iterator, typename Compare>
void quick_sort(Iterator first, Iterator last, Compare compare) {
  if (first < last) {
    Iterator mid = qsort(first, last, compare);
    quick_sort(first, mid-1, compare);
    quick_sort(mid+1, last, compare);
  }
}
class Func{
  private:
    int val;
  public:
    Func(int v) : val(v){}
    bool operator () (int v) {
      return v == val;
    }
};
template <typename Iterator, typename Fun>
int count(Iterator first, Iterator last, Fun func) {
  int res = 0;
  for (; first!=last; ++first) {
    if (func(*first)) {
      ++res;
    }
  }
  return res;
}
class Compare{
  public:
    bool operator () (int l, int r) {
      return l>r;
    }
};
int main (){
  vector<int> v;
  v.push_back(3);
  v.push_back(7);
  v.push_back(2);
  v.push_back(5);
  v.push_back(11);
  v.push_back(11);
  v.push_back(11);
  v.push_back(11);
  v.push_back(9);
  //sort(v.begin(), v.end());
  //sort(v.begin(), v.end(), Compare());
  quick_sort(v.begin(), v.end(), Compare());
  for (vector<int>::iterator it = v.begin();
      it != v.end(); ++it)
  {
        std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << count(v.begin(), v.end(), Func(11)) << std::endl;
  return 0;
}
