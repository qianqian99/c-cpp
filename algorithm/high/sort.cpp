#include <iostream>
#include <cstdio>
#include <initializer_list>
#include <cstring>
template <typename Type, int Size>
class Arr{
  private:
    Type data[Size];
    int size;
  private:
    void quick_sort(Type *, int, int);
    int partition(Type *, int, int);
    void merge(Type *, Type *a, int);
    void merge_pass(Type *out, Type *a, int left, int, int);
    void swap(Type &v1, Type &v2) {
      Type v = v1;
      v1 = v2;
      v2 = v;
    }
    void copy(Type *out, Type *a, int out_start, int a_start, int len) {
      for (int i=0; i<len; ++i) {
        out[out_start++] = a[a_start++];
      }
    }
  public:
    Arr() : size(0) {
      memset(data, 0, sizeof(data));
    }
    Arr(std::initializer_list<int> l){
      size = 0;
      memset(data, 0, sizeof(data));
      for (auto e : l){
        data[size++] = e;
      }
    }
    void show() {
      for (int i=0; i<size; ++i) {
        std::cout << data[i] << " ";
      }
      std::cout << std::endl;
    }
    void qsort() {
      quick_sort(data, 0, size-1);
    }
    void msort() {
      Type *b = new Type[size];
      int s = 1;
      while (1) {
        merge(b, data, s);
        s <<= 1;
        if (s >= size) {
          copy(data, b, 0, 0, size);
          break;
        }
        merge(data, b, s);
        s <<= 1;
        if (s >= size) break;
      }
      delete b;
    }
};
template <typename Type, int Size>
int Arr<Type, Size>::partition(Type *a, int left, int right){
  Type tmp = a[left];
  while (left < right){
    while (a[right] >= tmp) --right;
    if (left < right) { 
      swap(a[right], a[left++]);
    }
    else break;
    while (a[left] < tmp) ++left;
    if (left < right) {
      swap(a[left], a[right--]);
    }
    else break;
  }
  return left;
}
template <typename Type, int Size>
void Arr<Type, Size>::quick_sort(Type *a, int left, int right) {
  if (left < right) {
    int mid = partition(a, left, right);
    quick_sort(a, left, mid-1);
    quick_sort(a, mid+1, right);
  }
}
template <typename Type, int Size>
void Arr<Type, Size>::merge_pass(Type *out, Type *a, int left, int rend, int s) {
  int lend = left + s;
  int right = lend;
  int k = left;
  while (left < lend && right < rend) {
    out[k++] = a[left] < a[right] ? a[left++] : a[right++];
  }
  copy(out, a, k, left, lend-left);
  copy(out, a, k, right, rend-right);
}
template <typename Type, int Size> 
void Arr<Type, Size>::merge(Type *out, Type *a, int s) {
  if (s >= 1) {
    int i = 0;
    for (i=0; i+s<size; i += 2*s) {
      int end = i+2*s > size ? size : i+2*s;
      merge_pass(out, a, i, end, s);
    }
    copy(out, a, i, i, size-i);
  }
}
int main(){
  Arr<int, 15> arr{44, 5, 99, 33, 17, 3, 19, 44, 33, 5, 27, 17};
  arr.show();
  arr.msort();
  arr.show();
  return 0;
}
