#include <iostream>

int fib(int n)
{
    if (n < 2) {
        return 1;
    } else {
        return fib(n - 2) + fib(n - 1);
    }
}

int main()
{
    std::cout << fib(40) << std::endl;
    return 0;
}
