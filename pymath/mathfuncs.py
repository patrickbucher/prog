#!/usr/bin/python3

from factor import *

def lcm(a, b):
    """calculates the least common multiple of the given numbers"""
    factors_a = map_list(factorize(a))
    factors_b = map_list(factorize(b))
    lcm_factors = {}
    for k in factors_a.keys():
        lcm_factors[k] = factors_a[k]
    for k in factors_b.keys():
        if lcm_factors.get(k) == None:
            lcm_factors[k] = factors_b[k]
        elif lcm_factors[k] < factors_b[k]:
            lcm_factors[k] = factors_b[k]

    lcm = 1
    for k in lcm_factors:
        lcm *= k ** lcm_factors[k]

    return lcm

def gcd(a, b):
    """calculates the greatest common divisor of the given numbers"""
    factors_a = map_list(factorize(a))
    factors_b = map_list(factorize(b))
    gcd_factors = {}
    for k in factors_a.keys():
        b_factor = factors_b.get(k)
        if b_factor == None:
            continue
        if factors_a[k] < factors_b[k]:
            gcd_factors[k] = factors_a[k]
        else:
            gcd_factors[k] = factors_b[k]

    gcd = 1
    for k in gcd_factors:
        gcd *= k ** gcd_factors[k]

    return gcd

if __name__ == '__main__':
    a = int(input("enter a positive number: "))
    b = int(input("enter another positive number: "))
    print("least common multiple of %d and %d is %d" % (a, b, lcm(a, b)))
    print("greatest common divisor of %d and %d is %d" % (a, b, gcd(a, b)))
