#!/usr/bin/python3

import prime

def factorize(number):
    """factorizes a number and returns the factors as a list"""
    factors = []
    if prime.is_prime(number):
        return [number]
    while number > 1:
        for i in range(2, number + 1):
            if ((i == 2 or prime.is_prime(i)) and number % i == 0):
                factors.append(i)
                number = number // i
    return factors




if __name__ == '__main__':
    number = int(input("Number to factor: "))
    factors = factorize(number)
    factors.sort()
    for i in factors:
        print("%d" % i, end=' ')
    print('')
