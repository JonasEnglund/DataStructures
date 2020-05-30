#include <iostream>
#include <MyVector.h>

void show(MyVector &link)
{
    for(size_t i = 0; i < link.size(); ++i)
        std::cout << link[i] << ' ';
    std::cout << std::endl;

    std::cout << link.size() << std::endl;
    std::cout << link.capacity() << std::endl;
    for(size_t i = 0; i < 20; ++i)
        std::cout << '-';
    std::cout << std::endl;
}

int main()
{
    MyVector a;
    MyVector b;
    b.pushBack(4);
    b.pushBack(6);
    b.pushBack(8);
    b.pushBack(5);
    b.pushBack(2);
    a.pushBack(3);
    a.pushBack(3);
    a.pushBack(3);
    a.pushBack(3);
    a.pushBack(3);
    a.pushBack(3);
    a.pushBack(3);
    show(a);
    show(b);
    a.insert(3, b);
    show(a);
}
