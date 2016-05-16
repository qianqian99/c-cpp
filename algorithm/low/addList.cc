#include <iostream>
#include <vector>
using namespace std;
class SeqList
{
    private:
        int *num;
        int n;
    public:
        SeqList(int n): n(n), num(new int[n]){
            for (int i=0; i<n; ++i)
            {
                num[i] = 1;
            }
        }
        ~SeqList(){delete num;}
        void get_num(int *arr)
        {
            for(int i=1; i<n; ++i)
            {
                for (int j=0; j<i; ++j)
                {
                    if (arr[j] < arr[i]&& num[j] > num[i]-1) num[i] = num[j]+1;
                }
            }
        }
        void get_seq()
        {
            for (int i=0; i<n; ++i)
            {
                cout << num[i] << " ";
            }
            cout << endl;
        }
};
int main()
{
    //           1   1  2  3   4  2   5  6   3  1
    int arr[] = {10, 2, 5, 6, 18, 4, 19, 20, 5, 1};
    SeqList list(sizeof(arr)/sizeof(arr[0]));
    list.get_num(arr);
    list.get_seq();
    return 0;
}
