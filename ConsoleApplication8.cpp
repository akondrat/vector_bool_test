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
    constexpr bool operator <(const mybool& b2) const noexcept { return b < b2.b; }
};

template<typename T>
void foo(const char* typeName)
{
    
    int cycles = 10;
#ifdef _DEBUG
    size_t arraySize = (size_t)4;
#else
    size_t arraySize = (size_t)1e9;
#endif

    std::cout <<  typeName << std::endl;
    bool dummyBoolResult = false;
    long long minTime = std::numeric_limits<long long>::max();
    std::vector<T> v;
    v.reserve(arraySize);
    for( size_t j = arraySize; j--; )
    {
        v.push_back(T());
    }
    for( int i = cycles; i--;)
    {

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        
        auto middle = arraySize / 2u;
        for( size_t j = middle; j--;)
        {
            const auto& value0 = v[j];
            const auto& value1 = v[middle + j];
            dummyBoolResult |= value0 < value1;
        }

        auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
      
        if( interval < minTime )
        {
            minTime = interval;
            std::cout << std::endl << minTime << "ms";
        }

        std::cout << '.' << std::flush;
    }
    std::cout << dummyBoolResult << "\n\n" << std::flush;
}

int main()
{
    foo<int>("int");
    foo<mybool>("mybool");
    foo<bool>("bool");
//    _getch();
}

