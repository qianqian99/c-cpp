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
struct Point{
  int x;
  int y;
};
void len_row(int **l, struct Point *x, struct Point *y, int *plen, int i, int row, int col) {
  int j = 1;
  struct Point tmpX;
  struct Point tmpY;
  int Maxlen = 0;
  int len = 0;
  while (i<=row && j<=col) {
    if (l[i][j] == 3){
      len++;
    }
    else {
      if (len > Maxlen) {
        Maxlen = len;
        tmpY.x = i-1;
        tmpY.y = j-1;
        tmpX.x = i-len;
        tmpX.y = j-len;
      }
      len = 0;
    }
    ++i; ++j;
  }
  if (len != 0) {
    if (len > Maxlen) {
      Maxlen = len;
      tmpY.x = i-1;
      tmpY.y = j-1;
      tmpX.x = i-len;
      tmpX.y = j-len;
    }
  }
  if (Maxlen > *plen) {
    *plen = Maxlen;
    *x = tmpX;
    *y = tmpY;
  }
}

void len_col(int **l, struct Point *x, struct Point *y, int *plen, int j, int row, int col) {
  int i = 1;
  struct Point tmpX;
  struct Point tmpY;
  int Maxlen = 0;
  int len = 0;
  while (i<=row && j<=col) {
    if (l[i][j] == 3){
      len++;
    }
    else {
      if (len > Maxlen) {
        Maxlen = len;
        tmpY.x = i-1;
        tmpY.y = j-1;
        tmpX.x = i-len;
        tmpX.y = j-len;
      }
      len = 0;
    }
    ++i; ++j;
  }
  if (len != 0) {
    if (len > Maxlen) {
      Maxlen = len;
      tmpY.x = i-1;
      tmpY.y = j-1;
      tmpX.x = i-len;
      tmpX.y = j-len;
    }
  }
  if (Maxlen > *plen) {
    *plen = Maxlen;
    *x = tmpX;
    *y = tmpY;
  }
}

void get_seq_str(int **l, int row, int col) {
  struct Point x = {0,0};
  struct Point y = {0,0};
  int len = 0;
  for (int i=1; i<=row; ++i) {
    len_row(l, &x, &y, &len, i, row, col);
  }
  for (int j=2; j<=col; ++j) {
    len_col(l, &x, &y, &len, j, row, col);
  }
  printf("len is %d, start is (%d, %d), end is (%d, %d)\n", len, x.x, x.y, y.x, y.y);
}
int main (){
  //char *s = "ABCBDAB";
  //char *r = "BDCABA";
  char *s = "ABCABC";
  char *r = "DABCABCD";
  int slen = 6;
  int rlen = 8;
  //printf("len is : %d\n", get_comStr_len(s, r, 7, 6));
  int **c = get_array(strlen(s)+1, strlen(r)+1);
  int **l = get_array(strlen(s)+1, strlen(r)+1);
  //printf("len is %d\n", get_comStr(s, r, 7, 6, c, l));
  get_comStr_2(s, r, slen,rlen, c, l);
  //show_array(c, 7+1, 6+1);
  show_array(l, slen+1, rlen+1);
  //get_str(s, l, 7, 6);
  get_seq_str(l, slen, rlen);
  ret_array(c, slen+1);
  ret_array(l, slen+1);
  //char *res = get_com_str(s, r);
}
