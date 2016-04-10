#include <stdio.h>


int FindValue(int *ar, int len, int value){
  int left = 0;
  int right = len -1 ;
  while (left <= right){
    int mid = (right + left)/2;
    if (ar[mid] == value){
      return mid;
    }
    if (ar[mid] > value){
      right = mid -1;
    }
    else{
      left = mid + 1;
    }
  }
  return -1;
}
int main(){
  int ar[] = {12,23,34,45,56,67,78,89,90,100};

  int n = sizeof(ar)/sizeof(ar[0]);
  int pos = FindValue(ar, n, 167);
  printf("%d\n", pos);
  return 0;
}
