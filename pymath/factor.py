#!/usr/bin/python3

from prime import *

def factorize(number):
    """factorizes a number and returns the factors as a list"""
    factors = []
    if is_prime(number):
        return [number]
    while number > 1:
        for i in range(2, number + 1):
            if ((i == 2 or is_prime(i)) and number % i == 0):
                factors.append(i)
                number = number // i
    return factors

def map_list(lst):
    """maps a list: key = element, value = number of element's occurences"""
    mp = {}
    for i in lst:
        e = mp.get(i)
        if e == None:
            mp[i] = 1
        else:
            mp[i] = e + 1
    return mp

if __name__ == '__main__':
    number = int(input("Number to factor: "))
    factors = factorize(number)
    map_list(factors)
    factors.sort()
    for i in factors:
        print("%d" % i, end=' ')
    print('')
