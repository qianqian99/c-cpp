#include <iostream>
using namespace std;
class Base
{
    public:
        virtual void show(){}
};
class Der : public Base
{
    //public:
    private:
        void show(){std::cout << "Der\n";}
};

/*
 * 重载
 * 覆盖
 * 隐藏
 * 
 *RTTI *   Base/Der
 *0
 *
 *
 * 更改虚函数表
 * 更改RTTI指针  *p的类型
 *
 *
 * mov ecx, dwptr[p]
 * mov eax, dwptr[exc]
 * call eax
 * 寄存器的内容只有在运行时才知道
 * i
 *
 *
 *
 * 静多态: template 多态
 * 动多态
 * 内敛函数没地址
 *
 * 有对象才能有vfptr
 * 构造不能
 *
 * 静态函数不需要对象
 * 不能
 *
 *
 * 基类指针指向在堆上的派生类的对象
 *
 * private:
 * public:
 * 只是在编译时的限制
 *
 * 默认参数在编译
 * 与积累有关
 *
 *
 * 什么时候触发多态
 *
 *
 *
 * 总结*/

int main()
{
    Base *p = new Der;
    p->show();
    return 0;
}
