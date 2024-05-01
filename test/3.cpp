#include "src.hpp"
#if defined (_UNORDERED_MAP_)  || (defined (_LIST_)) || (defined (_MAP_)) || (defined (_SET_)) || (defined (_UNORDERED_SET_))||(defined (_GLIBCXX_MAP)) || (defined (_GLIBCXX_UNORDERED_MAP))
BOOM :)
#endif
#include <iostream>

void test1() {
    ESet<int> s, s1, s2, s3;
    ESet<int>::iterator it = s.find(0);
    if (it != s.end()) std::cout << "Wrong!" << std::endl;
    for (int i = 0; i < 10; i++) {
        s.emplace(i);
    }
    do {
        auto it2 = it--;
        if (it2 == s.end())
            std::cout << *it << std::endl;
        else
            std::cout << *it << " " << *it2 << std::endl;
        auto it3 = --it2;
        if (it != it2 || it2 != it3)
            std::cout << "Wrong!" << std::endl;
    } while (it != s.begin());

    it = s.find(0);
    it = it = it;
    s = s = s;
    s1 = s = s2 = s3 = s;
    ESet<int> s4 = s;
    s4.emplace(2333);
    if(s4.find(2333)==s4.end())std::cout<<"Wrong!"<<std::endl;
    if(s.find(2333)!=s.end())std::cout<<"Wrong!"<<std::endl;
    s3=std::move(s4);
    ESet<int> s5=s3;
    if(s3.find(2333)==s3.end())std::cout<<"Wrong!"<<std::endl;
    ESet<int> s6=std::move(s3);
    s5.emplace(666);
    if(s6.find(666)!=s6.end())std::cout<<"Wrong!"<<std::endl;
    s6=s5;
    if(s6.find(666)==s6.end())std::cout<<"Wrong!"<<std::endl;
    if (s.size() != 10) std::cout << "Wrong!" << std::endl;
    if (it != s.begin() || it != s.find(0) || it == s.end()
        || it == s1.begin() || it == s1.find(0))
        std::cout << "Wrong!" << std::endl;
    s2.emplace(100);
    if (s2.find(100) == s2.end() || s3.find(100) != s3.end()) std::cout << "Wrong!" << std::endl;

    while (it != s.end()) {
        auto it2 = it++;
        if (it == s.end())
            std::cout << *it2 << std::endl;
        else
            std::cout << *it << " " << *it2 << std::endl;
        auto it3 = ++it2;
        if (it != it2 || it2 != it3)
            std::cout << "Wrong!" << std::endl;
    }
    for (int i = 1; i < 10; i += 2) {
        bool b = s.erase(i);
        if (!b)std::cout << "Wrong!" << std::endl;
    }
    for (; it != s.end(); it++) {
        std::cout << *it << std::endl;
    }
    if (typeid(s.find(0)) != typeid(ESet<int>::iterator))std::cout << "Wrong!" << std::endl;
    if (typeid(*s.begin()) != typeid(const int))std::cout << "Wrong!" << std::endl;
}

int main() {
    test1();
}