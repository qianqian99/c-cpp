#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int **get_array(int row, int col) {
  int **res = (int **)malloc(sizeof(int *)*row);
  if (res == NULL) exit(-1);
  for (int i=0; i<row; ++i) {
    res[i] = (int *)malloc(sizeof(int)*col);
    if (res[i] == NULL) exit(-1);
    memset(res[i], 0, sizeof(res[i][0])*col);
  }
  return res;
}
int hits(int **s, int **b, int *matrix, int i, int j) {
  if (i > j) return -1;
  if (i == j) return 0;
  int h = 0;
  if (s[i+1][j] > 0) h = s[i+1][j];
  else h = hits(s, b, matrix, i+1 ,j);
  s[i][j] = h + matrix[i-1]*matrix[i]*matrix[j];
  b[i][j] = i;
  for (int k=i+1; k<j; ++k) {    //my bugs 1 k<=j
    int h1 = 0;
    int h2 = 0;
    if (s[i][k] > 0) h1 = s[i][k];
    else h1 = hits(s, b, matrix, i, k);
    if (s[k+1][j] > 0) h2 = s[k+1][j];
    else h2 = hits(s, b, matrix, k+1, j);
    int tmp =  h1 + h2 + matrix[i-1]*matrix[k]*matrix[j];
    if (tmp < s[i][j]) {
      s[i][j] = tmp;
      b[i][j] = k;
    }
  }
  return s[i][j];
}
void show_array(int **s, int row, int col) {
  for (int i=1; i<row; ++i) {
    for (int j=1; j<col; ++j) {
      printf("%6d", s[i][j]);
    }
    printf("\n");
  }
  printf("****************************************************************\n");
}
void ret_array(int **s, int row) {
  for (int i=0; i<row; ++i) {
    free(s[i]);
  }
  free(s);
}
void hits_2(int **s, int **b, int *matrix, int size) {
  for (int i=1; i<=size; ++i) s[i][i] = 0;
  for (int n=2; n<=size; ++n) {
    for (int i=1, j=n; j<=size; ++i, ++j) {    
      for (int k=i; k<j; ++k) {
        int min = s[i][k]  + s[k+1][j] + matrix[i-1]*matrix[k]*matrix[j];
        if (s[i][j] == 0 || s[i][j] > min) {
          s[i][j] = min;
          b[i][j] = k;
        }
      }
    }
  }
}
int get_hits(int *matrix, int size) {
  int **s = get_array(size, size);    // 0 不用
  int **b = get_array(size, size);
  //int res = hits(s, b, matrix, 1, size-1);
  hits_2(s, b, matrix, size-1);
  show_array(s, size, size);
  show_array(b, size, size);
  ret_array(s, size);
  ret_array(b, size);
  return 0;
}

int main() {
  int matrix[] = {30, 35, 15, 5, 10, 20, 25};
  int res = get_hits(matrix, sizeof(matrix)/sizeof(matrix[0]));
 // printf("times : %d\n", res);
}
