#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
class Move
{
    private:
        vector<vector<int> > arr;
    public:
        Move() : arr(9)
        {
            arr[0].push_back(6);
            arr[0].push_back(8);
            arr[0].push_back(9);
            arr[1].push_back(7);
            arr[2].push_back(3);
            arr[3].push_back(9);
            arr[5].push_back(6);
            arr[5].push_back(9);
            arr[6].push_back(8);
            arr[6].push_back(9);
            arr[8].push_back(9);
        }
        bool is_exist(int first, int second)
        {
            if (first > second)
            {
                vector<int>::iterator it = arr[second].begin();
                while (it != arr[second].end())
                {
                    if (first == *it) return true;
                    ++it;
                }
                return false;
            }
            else if (first < second)
            {
                vector<int>::iterator it = arr[first].begin();
                while (it != arr[first].end())
                {
                    if (second == *it) return true;
                    ++it;
                }
                return false;
            }
        }
        void add(char *s, int first, int res)
        {
            int second = 0;
            sscanf(s, "%d", &second);
            bool tag = false;
            if (first+second == res)
            {
                cout << "ok" << endl;
            }
            else
            {
                int ldest = res - second;
                if (is_exist(ldest, first))
                {
                    cout << ldest << "+" << second << "=" << res << endl;
                    tag = true;
                }
                int rdest = res - first;
                if (is_exist(rdest, second))
                {
                    cout << first << "+" << rdest << "=" << res << endl;
                    tag = true;
                }
                if (!tag) 
                {
                    cout << "no" << endl;
                }
            }
        }
        void mul(char *s, int first, int res)
        {
            int second = 0;
            sscanf(s, "%d", &second);
            bool tag = false;
            if (first*second == res)
            {
                cout << "ok" << endl;
            }
            else
            {
                int ldest = res / second;
                if (is_exist(ldest, first))
                {
                    cout << ldest << "*" << second << "=" << res << endl;
                    tag = true;
                }
                int rdest = res / first;
                if (is_exist(rdest, second))
                {
                    cout << first << "*" << rdest << "=" << res << endl;
                    tag = true;
                }
                if (!tag)
                {
                    cout << "no" << endl;
                }
            }
        }
        void sub(char *s, int first, int res)
        {
            int second = 0;
            sscanf(s, "%d", &second);
            bool tag = false;
            if (first-second == res)
            {
                cout << "ok" << endl;
            }
            else
            {
                int ldest = res + second;
                if (is_exist(ldest, first))
                {
                    cout << ldest << "-" << second << "=" << res << endl;
                    tag = true;
                }
                int rdest = res + first;
                if (is_exist(rdest, second))
                {
                    cout << first << "-" << rdest << "=" << res << endl;
                    tag = true;
                }
                if (!tag)
                {
                    cout << "no" << endl;
                }
            }
        }
        void div(char *s, int first, int res)
        {
            int second = 0;
            sscanf(s, "%d", &second);
            bool tag = false;
            if (first/second == res)
            {
                cout << "ok" << endl;
            }
            else
            {
                int ldest = res * second;
                if (is_exist(ldest, first))
                {
                    cout << ldest << "/" << second << "=" << res << endl;
                    tag = true;
                }
                int rdest = first / res;
                if (is_exist(rdest, second))
                {
                    cout << first << "/" << rdest << "=" << res << endl;
                    tag = true;
                }
                if (!tag)
                {
                    cout << "no" << endl;
                }
            }
        }
 
        void move(char *str)
        {
            int num1 = 0;
            sscanf(str, "%d", &num1);
            char *s = strrchr(str, '=');
            int res = 0;
            sscanf(s+1, "%d", &res);
            s = NULL;
            if (s=strchr(str, '+'))
            {
                add(s+1, num1, res);
                return;
            }
            if (s=strchr(str, '-'))
            {
                sub(s+1, num1, res);
                return;
            }
            if (s=strchr(str, '*'))
            {
                mul(s+1, num1, res);
                return;
            }
            if (s=strchr(str, '/'))
            {
                div(s+1, num1, res);
                return;
            }
        }
};
int main()
{
    char expr[128] = "";
    cin >> expr;
    Move move;
    move.move(expr);
}
