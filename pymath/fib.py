#!/usr/bin/python3

# mit diesem Cache (sprich "Gaschsch") läuft es fast as fuck
fib_cache = {0: 0, 1: 1}

def fib(n):
    if n < 0:
        raise ValueError('n must be >= 0')
    if fib_cache.get(n) != None:
        return fib_cache.get(n)
    result = fib(n - 2) + fib(n - 1)
    fib_cache[n] = result
    return result

if __name__ == '__main__':
    print(fib(40))
