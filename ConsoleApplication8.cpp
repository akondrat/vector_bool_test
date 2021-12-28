// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

#include <conio.h>

struct mybool
{
    bool b;
};

template<typename T>
void foo(const char* typeName)
{
    long long minTime = std::numeric_limits<long long>::max();
    int cycles = 10;
#ifdef _DEBUG
    size_t arraySize = (size_t)3;
#else
    size_t arraySize = (size_t)1e9;
#endif

    size_t sizeT = sizeof(T);
    std::cout << typeName << std::endl;
    for( int i = cycles; i--;)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        std::vector<T> v;

        v.reserve(arraySize);

        for( size_t j = arraySize; j--; )
        {
            v.push_back(T());
        }
        auto interval = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
        if( interval < minTime )
        {
            minTime = interval;
            std::cout << "" << minTime << "us";
        }
        std::cout << '.' << std::flush;
    }
    std::cout << std::endl;
}

int main()
{
    foo<int>("int");
    foo<mybool>("mybool");
    foo<bool>("bool");
//    _getch();
}

