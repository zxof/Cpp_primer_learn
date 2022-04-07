#include<iostream>
#include<string>

typedef double Money;
class Person{
    friend std::istream &read(std::istream&, Person&);
private:
    std::string name;
    std::string address;
    const static int num =1;

public:
    Person()=default;
     int getNum(){
        return num;
    }
    Person(const std::string &na):name(na){}
    Person(const std::string &na,const std::string &ad):name(na),address(ad){}
};
std::istream &read(std::istream&, Person&);