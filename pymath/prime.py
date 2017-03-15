#!/usr/bin/python3

primes = {}

def is_prime(number):
    cached = primes.get(number)
    if cached != None:
        return cached
    if number <= 1:
        primes[number] = False
        return primes[number]
    for i in range(2, number // 2 + 1):
        if number % i == 0:
            primes[number] = False
            return primes[number]
    primes[number] = True
    return primes[number]


def get_primes(lower_in, upper_ex):
    primes = []
    for i in range(lower_in, upper_ex):
        if is_prime(i):
            primes.append(i)
    return primes


if __name__ == '__main__':
    for i in range(1, 100):
        if is_prime(i):
            print("%d is a prime number" % i)
