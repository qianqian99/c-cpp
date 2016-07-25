#include <functional>
int main()
{
    bind1st(greater<int>(), 13);
    return 0;
}
