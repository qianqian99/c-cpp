#include<iostream>
#include <vector>
using namespace std;
//x1 x2 x3 x4 | x5
//x1 x2 | x3 x4 x5
//3 * 2
//1 * 4
class Count
{
    private:
        vector<int> data;
        int num;
    public:
        Count(int n) : num(n), data(n)
        {
            data.push_back(1);
            data.push_back(1);
        }
        ~Count(){
            cout << "~Count()" << endl;
        }
        int count(int n)
        {
            if (n <= 1) return 1;
            int sum = 0;
            for (int i=1; i<n; ++i)
            {
                if (data[i] == 0) data[i] = count(i);
                if (data[n-i] == 0) data[n-i] = count(n-i);
                sum += data[i]*data[n-i];
            }
            return sum;
        }
};
int main()
{
    int n = 0;
    cout << "please input the n : ";
    cin >> n;
    Count count(n);
    cout << "the result is " << count.count(n) << endl;
    return 0;
}
