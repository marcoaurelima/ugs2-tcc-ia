#include <iostream>
#include <array>

int main(int argc, char **argv) 
{
    unsigned SIZE = 6;

    std::array<float, SIZE> arr{1,2,3,4,5,6};


    std::cout << "hello " << arr.back() << std::endl;

    return 0;
}