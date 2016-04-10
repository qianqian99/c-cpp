/*************************************************************************
 > File Name: divide.cpp
 > What I should do is fighting !!! 
 > hgg 
 > Created Time: 2016年03月13日 星期日 10时20分26秒
 ************************************************************************/

#include <iostream>
#include <vector>
class Solution{
    void traverse(){
        for (int e : v){
            std::cout << e << " ";
        }
        std::cout << std::endl;
    } 
    public:
        void devide(int num){
            for (int i=1; i<num; ++i){
                partition(num-i, i);
            }
        }
};

int main(){
    Solution s;
    s.devide(6);
}
