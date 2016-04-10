#include "comStr.h"
/*
s[m] == r[n] len ++; --m, --n;
s[m] != r[n] max{}
*/
int get_comStr_len(const char *x, const char *y, int m, int n) {
  if (m == 0 || n == 0) return 0;
  if (x[m-1] == y[n-1]) return get_comStr_len(x, y, m-1, n-1) + 1;
  else return max(get_comStr_len(x, y, m-1, n), get_comStr_len(x, y, m, n-1));
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
int get_comStr(const char *x, const char *y, int m, int n, int **c, int **l){
  if (m == 0 || n == 0) return 0;
  if (x[m-1] == y[n-1])  {
    l[m][n] = Cross;
    if (c[m-1][n-1] == 0) 
      c[m-1][n-1] = get_comStr(x, y, m-1, n-1, c, l);
    return (c[m][n] = c[m-1][n-1]+1);
  }
  else {
    if (c[m-1][n] == 0) c[m-1][n] = get_comStr(x, y, m-1, n, c, l);
    if (c[m][n-1] == 0) c[m][n-1] = get_comStr(x, y, m, n-1, c, l);
    if (c[m][n-1] < c[m-1][n]) {
      c[m][n] = c[m-1][n];
      l[m][n] = Up;
    }
    else {
      c[m][n] = c[m][n-1];
      l[m][n] = Left;
    }
    return c[m][n];
  }
}
void get_comStr_2(const char *x, const char *y, int m, int n, int **c, int **l) {
  for (int i=0; i<=m; ++i) c[i][0] = 0;
  for (int i=0; i<=n; ++i) c[0][i] = 0;

  for (int i=1; i<=m; ++i) {
    for (int j=1; j<=n; ++j) {
      if (x[i-1] == y[j-1]) {
        c[i][j] = c[i-1][j-1] + 1;
        l[i][j]  = Cross;
      }
      else {
        if (c[i-1][j] > c[i][j-1]) {
          l[i][j] = Up;
          c[i][j] = c[i-1][j];
        }
        else {
          l[i][j] = Left;
          c[i][j] = c[i][j-1];
        }
      }
    }
  }
}
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
void ret_array(int **s, int row) {
  for (int i=0; i<row; ++i) {
    free(s[i]);
  }
  free(s);
}
int max(int l, int r) {
  return l>r?l:r;
}
void get_str(const char *s, int **l, int row, int col) {
  while (row !=0 && col != 0) {
    if (l[row][col] == Up) {
      --row;
    }
    else if (l[row][col] == Cross) {
      --col;
      --row;
      printf("%c ", s[row]);
    }
    else if (l[row][col] == Left) {
      --col;
    }
  }
}
int main (){
  char *s = "ABCBDAB";
  char *r = "BDCABA";
  //printf("len is : %d\n", get_comStr_len(s, r, 7, 6));
  int **c = get_array(strlen(s)+1, strlen(r)+1);
  int **l = get_array(strlen(s)+1, strlen(r)+1);
  //printf("len is %d\n", get_comStr(s, r, 7, 6, c, l));
  get_comStr_2(s, r, 7,6, c, l);
  show_array(c, 7+1, 6+1);
  show_array(l, 7+1, 6+1);
  get_str(s, l, 7, 6);
  ret_array(c, 7+1);
  ret_array(l, 7+1);
  //char *res = get_com_str(s, r);
}
