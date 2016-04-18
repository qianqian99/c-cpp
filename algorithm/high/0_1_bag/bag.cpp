#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iterator>
/*
   01背包问题是我在有限的重量之内拿到价值最大的
   物品，而且物品是不能分割的。
              c(i+1, j)   j<w(i)
   c(i, j)   
              max(c(i+1, j),  c(i+1, j-w(i))+vi)  j>=w(i)
*/
class Bag
{
  private:
    int content;
    std::vector<int> value;
    std::vector<int> weigh;
    std::vector<std::vector<int>> c;
  public:
    Bag(const std::initializer_list<int>&, 
        const std::initializer_list<int> &, int);
    int solution_1(int i=0, int j=10);
    int solution_2(int i=0, int j=10);
    void solution_3(int i=0, int j=10);
    void showc() const ;
    void tracback() const;
};
template <typename T>
T max(const T&v1, const T &v2)
{
  return v1 > v2 ? v1 : v2;
}
void Bag::solution_3(int i, int j)
{
  int row = value.size() - 1;
  for (int k=weigh[row]; k<=j; ++k)
  {
    c[row][k] = value[row];
  }
  for (int k=row-1; k>=0; --k)
  {
    for (int w=1; w<=j; ++w) 
    {
      if (w>weigh[k])
        c[k][w] = max(c[k+1][w], c[k+1][w-weigh[k]]+value[k]);
      else
        c[k][w] = c[k+1][w];
    }
  }
}
void Bag::showc() const 
{
  for (auto i : c) 
  {
    for (auto j : i) 
    {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}
/*
   return the max value by the equation
*/
int Bag::solution_1(int i, int j) 
{
  if (i >= value.size())  return 0;
  if (j < weigh[i])  return 0;
  else {
    int max1 = solution_1(i+1, j);
    int max2 = solution_1(i+1, j-weigh[i]) + value[i];
    return max1 > max2 ? max1 : max2;
  }
}
int Bag::solution_2(int i, int j)
{
  if (i >= value.size()) return 0;
  if (j < weigh[i]) return 0;
  else if (c[i][j] > 0)  {
    return c[i][j];
  }
  else 
  {
    int max1 = solution_2(i+1, j);
    int max2 = solution_2(i+1, j-weigh[i]) + value[i];
    c[i][j] = max1 > max2 ? max1 : max2;
    return c[i][j];
  }
}
Bag::Bag(const std::initializer_list<int> &v1, 
         const std::initializer_list<int> &v2, int c) : content(c) 
{
  std::transform(v1.begin(), v1.end(),
      std::back_inserter(weigh), [](int l)->int{return l;});
  std::transform(v2.begin(), v2.end(), 
      std::back_inserter(value), [](int l)->int{return l;});
  this->c.resize(value.size());
  for (int i=0; i<value.size(); ++i) 
  {
    this->c[i].assign(content+1, 0);
  }
}
void Bag::tracback() const
{
  int row = 0;
  int col = content;

  while (row < value.size()-1)
  {
    if (c[row][col] != c[row+1][col])
    {
      std::cout << "num is " << row+1 << " value is " << 
        value[row] << " weigh is " << weigh[row] << std::endl;
      col = col - weigh[row];
    }
    ++row;
  }
  if (c[row][col] != 0) {
      std::cout << "num is " << row+1 << " value is " << 
        value[row] << " weigh is " << weigh[row] << std::endl;
  }
}
int main ()
{
  Bag _01bag({2,2,6,5,4}, {6,3,5,4,6}, 10);
  //std::cout << _01bag.solution_1() << std::endl;
  //std::cout << _01bag.solution_2() << std::endl;
  _01bag.solution_3();
  _01bag.showc();
  _01bag.tracback();
  return 0;
}
