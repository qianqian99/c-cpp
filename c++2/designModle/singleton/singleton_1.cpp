#include <iostream>
class Singleton{
  private:
    static Singleton instance;
    Singleton(){}
    Singleton(const Singleton &o) {}
  public:
    static Singleton *get_instance(){
      return &instance;
    }
};
Singleton Singleton::instance;


int main() {
  Singleton *pobj = Singleton::get_instance();
  std::cout << pobj << std::endl;
  Singleton *pobj1 = Singleton::get_instance();
  std::cout << pobj1 << std::endl;
  Singleton *pobj2 = Singleton::get_instance();
  std::cout << pobj2 << std::endl;
  return 0;
}
