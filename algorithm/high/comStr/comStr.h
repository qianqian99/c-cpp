#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int max(int, int);
int get_comStr_len(const char *x, const char *y, int m, int n); 
int **get_array(int row, int col);
void ret_array(int **s, int row);
int get_comStr(const char *x, const char *y, int m, int n, int **c, int **l);
void show_array(int **s, int row, int col);
void get_str(const char *s, int **l, int row, int col);
enum Type {
  Up = 1,
  Left = 2,
  Cross = 3
};
