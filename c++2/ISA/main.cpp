#include <iostream>
/*不能跨域重载
 * void Base::show(int);
 * void Der::show();
 * can't call show(10);
 * */

class Base
{
    public:
        void show(int a) {std::cout << "Base::show(int)\n";}
};
class Der : public Base
{
    public:
        using Base::show;  //  this的不同
        void show() {std::cout << "Der::show()\n";}
};

/*1.0000000000400836 W _ZN3Der4showEv
 *0000000000400816 W _ZN4Base4showEi
 *可以理解为this的不同也可以理解为作用域的不同
 *2.0000000000400836 W Der::show()
 *0000000000400816 W Base::show(int)
 * */
int main()
{
    Der d;
    Base b;
    b.show(3);
    d.show(3);
    d.show();
    return 0;
}
