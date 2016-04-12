#include <iostream>
#include <string.h>
class string
{
public:
  class iterator{
    private:
      const string *obj;
      char *str;
    public:
      iterator(const string *p, int pos = 0): obj(p), str(obj->mystr+pos){}
      bool operator != (const iterator &it) const{
        return str != it.str;
      }
      void operator ++ () {
        str++;
      }
      char &operator * (){
        return *str;
      }
      const char &operator * () const {
        return *str;
      }
  };
  iterator begin() const{
    return iterator(this);
  }
  iterator end() const {
    return iterator(this, strlen(mystr));
  }
  string (const char *str = NULL);
  string (const string &str);
  string& operator = (const string &str);
  string operator + (const string &str) const;
  friend std::ostream &operator << (std::ostream &, const string &);
  bool operator == (const string &) const;
  bool operator > (const string &) const;
  bool operator < (const string &) const;
  char &operator [] (int pos);
  const char &operator [] (int pos) const;
  int size() const;
  ~string ();
private:
  char *mystr;
};
const char &string::operator [] (int pos) const {
  return mystr[pos];
}
char &string::operator [] (int pos) {
  return mystr[pos];
}
bool string::operator > (const string &str) const{
  return strcmp(mystr, str.mystr) > 0;
}
bool string::operator < (const string &str) const{
  return strcmp(mystr, str.mystr) < 0;
}
bool string::operator == (const string &str) const{
  return strcmp(mystr, str.mystr) == 0;
}
int string::size() const{
  return strlen(mystr);
}
std::ostream &operator << (std::ostream &out, const string &str) {
  out << str.mystr;
  return out;
}
string string::operator + (const string &str) const {
  char *p = new char[strlen(str.mystr)+strlen(mystr)+1];
  strcpy(p, mystr);
  strcat(p, str.mystr);
  string tmp(p);
  delete p;
  return tmp;
}
string &string::operator = (const string &str) {
  if (str.mystr == mystr) return *this;
  delete mystr;
  mystr = new char[strlen(str.mystr)+1];
  strcpy(mystr, str.mystr);
  return *this;
}
string::string(const string &str) {
  mystr = new char[strlen(str.mystr)+1];
  strcpy(mystr, str.mystr);
}
string::~string() {
  delete mystr;
  mystr = NULL;
}
string::string (const char *str) {
  if (str == NULL) {
    mystr = new char[1];
  }
  else {
    mystr = new char[strlen(str)+1];
    strcpy(mystr, str);
  }
}
int main() {
  string str1;
  string str2 = "hello,";
  string str3 = str2;
  string str4 = str2 + str3;
  string str5 = str4 + "world.";

  int size = str5.size();
  if (str1 == str2) {}
  if (str1 > str2) {}
  if (str1 < str2) {}
  for (int i=0; i<size; ++i) {
    std::cout << str5[i] << " ";
  }
  std::cout << std::endl;



  std::cout << "str1" << str1 << std::endl;
  std::cout << "str2" << str2 << std::endl;
  std::cout << "str3" << str3 << std::endl;
  std::cout << "str4" << str4 << std::endl;
  std::cout << "str5" << str5 << std::endl;
  std::cout << "==============================" << std::endl;

  string::iterator it = str5.begin();
  for (; it!=str5.end(); ++it){
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  return 0;
}
