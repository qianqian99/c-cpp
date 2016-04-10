/*************************************************************************
 > File Name: permutation.cpp
 > What I should do is fighting !!! 
 > hgg 
 > Created Time: 2016年03月13日 星期日 09时04分38秒
 >
 > 利用的是重复元素的访问来打印元素
 > 这是新的体会
 ************************************************************************/

#include <iostream>
#include <vector>
class Solution {
    private:
        template <typename Type>
        void swap(Type &l, Type &r){
            Type tmp = l;
            l = r;
            r = tmp;
        }
        template <typename T>
        void traverse(const T &val){
            for (auto const t : val){
                std::cout << t << " ";
            }
            std::cout << std::endl;
        }
    public:
        template <typename Type>
        void permutation(Type &val, int k = 0) {
            if (k == val.size()){

                traverse(val);
            }
            for (int i=k; i<val.size(); ++i){
                swap(val[k], val[i]);
                permutation(val, k+1);
                swap(val[k], val[i]);
            }
        }
};

int main() {
    Solution s;
    std::vector<char> v{'A', 'B', 'C', 'D'};
    s.permutation(v);
    return 0;
}
