#!/usr/bin/env python3
n = 4559
print("n = {}".format(n))


#choose a
import random
import time
random.seed(time.time())

def gcd(a, b):
    if (a < b):
        return gcd(b, a)
    elif (b==0):
        return a
    else:
        return gcd(b, a%b)

while (True):
    #choose a
    while (True):
        a = random.randrange(n)
        if (1 == gcd(a, n)):
            break
    print("\ta = {}".format(a))
    
    #calculate period (r)
    r = 1
    while (True):
        if (1 == (a**r)%n):
            break
        r += 1
    print("\tr = {}".format(r))

    #test r is even and a
    if (0 != r % 2):
        continue
    if (0 == ((a**(r//2))+1) % n):
        continue

    #done
    break

print("a = {}".format(a))
print("r = {}".format(r))

s1 = ((a**(r//2))+1) % n
s2 = ((a**(r//2))-1) % n

print("s1 {} s2 {}".format(s1, s2))

p1 = gcd(s1, n)
p2 = gcd(s2, n)

print("p1 {} p2 {}".format(p1, p2))


