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
    a.pushBack(-2);
    a.pushBack(3);
    a.pushBack(1);
    a.pushBack(-5);
    a.pushBack(6);
    show(a);
    MyVector b = a.sortedSquares(a, SortedStrategy::Rising);
    show(b);
}
