#include <stdio.h>
int bfind(int *, int, int, int);
void show(int *arr, int n){
  for (int i=0; i<n; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
void merge(int *arr, int m, int k, int n) {
  while (k-1 < n) {
    int p = bfind(arr, m, k, n);
    for (int i=0; i<p-k+1; ++i) {
      int tmp = arr[p];
      for (int j=p-1; j>=m; --j) {
        arr[j+1] = arr[j];
      }
      arr[m] = tmp;
    }
    m = m+p-k+2;
    k = p+1;
  }
}
int bfind(int *arr, int m, int k, int n) {
  int dest = arr[m];
  while (k < n) {
    int mid = ((n-k)>>1) + k;
    if (arr[mid] == dest) {
      return (mid-1);
    }
    else if (arr[mid] > dest) {
      n = mid - 1;
    }
    else {
      k = mid + 1;
    }
  }
  if (arr[k] < dest) {
    return k;
  }
  else {
    return k-1;
  }
}
int main() {
  int arr[] = {4,6,9,10,12,1,3,5,7,11};
  int m = 0;
  int n = sizeof(arr)/sizeof(arr[0]) - 1;
  int k = 5;
  show(arr, n+1);
  merge(arr, m, k, n);
  show(arr, n+1);
  return 0;
}
