/*************************************************************************
 > File Name: fibo.cpp
 > What I should do is fighting !!! 
 > hgg 
 > Created Time: 2016年03月15日 星期二 20时06分21秒
 ************************************************************************/

#include <iostream>
#include <vector>
class Fibo{
    private:
        int internal(int prev, int next, int end){
            if (end <= 0){
                return next;
            }
            else {
                return internal(next, prev+next, end-1);
            }
        }
    public:
        int getFibo(int num){
            if (num <= 1) {
                return 1;
            }
            else {
                return getFibo(num-1) + getFibo(num-2);
            }
        }
        int getFibo2(int num){
           return  internal(1,1,num-1);
        }
        int getFibo3(int num){
            std::vector<int> v;
            v.push_back(1);
            v.push_back(1);
            num -= 2;
            while (num >= 0){
                auto it  = v.end() - 1;
                v.push_back(*it+*(it-1));
                num--;
            }
            return v.back();
        }
};
int main(){
    Fibo fibo;
    for (int i=0; i<=100; ++i){
        std::cout << fibo.getFibo3(i) << std::endl;
    }
    return 0;
}
