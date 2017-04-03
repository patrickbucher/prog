#!/usr/bin/python3

def gcd(u, v):
    if v != 0:
        return gcd(v, u % v)
    else:
        return u

def gcd_iter(u, v):
    while v:
        t,u = u,v
        v = t % v
    return abs(u)

if __name__ == '__main__':
    print(gcd(39, 91)) # 13
    print(gcd_iter(39, 91)) # 13
