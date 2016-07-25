#include "boost/shared_ptr.hpp"
#include <iostream>
#include "boost/weak_ptr.hpp"
int main()
{
    int *p = new int;
    boost::shared_ptr<int> sp(p);
    std::cout << sp.use_count() << " " <<  std::endl;
    boost::shared_ptr<int> sp2(p);
    std::cout << sp.use_count() << " " << sp2.use_count() << std::endl;
    return 0;
}
