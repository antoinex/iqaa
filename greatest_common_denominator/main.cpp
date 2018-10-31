/*
 * @file     : main.cpp
 * @author   : antoinex
 * 
 * @question :
 *      Write a function to calculate the Greatest Common Denominator (GCD) of 2 numbers.
 */

#include <iostream>

int gcd(int x, int y);

int main()
{
    std::cout << "gcd of 2 and 4 = " << gcd(2, 4) << std::endl;
    std::cout << "gcd of 4 and 2 = " << gcd(4, 2) << std::endl;
    std::cout << "gcd of 6 and 9 = " << gcd(6, 9) << std::endl;
    std::cout << "gcd of 496 and 28 = " << gcd(496, 28) << std::endl;

    return 0;
}

int gcd(int x, int y)
{
    if (x == 0)
    {
        return y;
    }

    return gcd(y % x, x);
}