#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include "boost/weak_ptr.hpp"
#include "boost/shared_ptr.hpp"
using namespace std;
class Object
{
    public:
        Object(string name, int id):mname(name), mid(id){}
        virtual ~Object(){};
        virtual void handle_msg()
        {
            cout << "name is " << mname << " mid is " << mid << endl;
        }
    private:
        string mname;
        int mid;
};
class Object1 : public Object
{
    public:
        Object1():Object("object1", 1){}
        ~Object1(){}
};
class Object2 : public Object
{
    public:
        Object2():Object("object2", 2){}
        ~Object2(){}
};
class Object3 : public Object
{
    public:
        Object3():Object("object3", 3){}
        ~Object3(){}
};
class Observe
{
    public:
        void add_msg(int id, boost::weak_ptr<Object> wp)
        {
            map<int, vector<boost::weak_ptr<Object> > >::iterator it = mcontrol_msg.find(id);
            if (it == mcontrol_msg.end()) 
            {
                vector<boost::weak_ptr<Object> > vec;
                vec.push_back(wp);
                mcontrol_msg[id] = vec;
            }
            else it->second.push_back(wp);
        }
        void dispatch_msg(int id)
        {
            map<int, vector<boost::weak_ptr<Object> > >::iterator it = mcontrol_msg.find(id);
            if (it == mcontrol_msg.end()) return;
            vector<boost::weak_ptr<Object> >::iterator i = it->second.begin();
            for (; i != it->second.end(); ++i)
            {
                boost::shared_ptr<Object> sp  =  i->lock();
                sp->handle_msg();
            }
        }
    private:
        map<int, vector<boost::weak_ptr<Object> > > mcontrol_msg;
};
int main(int c, char ** v)
{
    boost::shared_ptr<Object> p1(new Object1);
    boost::shared_ptr<Object> p2(new Object2);
    boost::shared_ptr<Object> p3(new Object3);
    Observe ob;
    ob.add_msg(1, p1);
    ob.add_msg(2, p1);
    ob.add_msg(2, p2);
    ob.add_msg(2, p3);
    ob.add_msg(3, p3);
    int id = 0;
    sscanf(v[1], "%d", &id);
    ob.dispatch_msg(id);
    return 0;
}
