#!/usr/bin/env python3

import random, string

def randomrep(n):
    start = random.randint((n + 1) // 2, n)
    s = ''.join([random.choice(string.ascii_lowercase) for i in range(start)])
    s = s + s[0:(n - len(s))]
    pos = random.randint(0, start - 1)
    s = s[:pos] + random.choice(string.ascii_lowercase) + s [pos + 1:]
    return s

def hyperrep(n):
    if (n < 10):
        return random.choice(string.ascii_lowercase) *n
    frac = random.randint(2, 4)
    rem = frac * random.randint(1,5) + n % frac
    return hyperrep((n - rem) // frac) * frac + ''.join([random.choice(string.ascii_lowercase) for i in range(rem)])

def hyperrep_end(n):
    frac = random.randint(2, 5)
    s = hyperrep(n // frac) * frac
    pos = random.randint(0, n // frac)
    return s[:pos] + random.choice(string.ascii_lowercase) + s [pos+1:]

def fail(n):
    s = ''.join([random.choice(string.ascii_lowercase) for i in range(n)])
    return s + s[0]

convert = {"random":randomrep, "repet":hyperrep_end, "fail":fail}
args = input().split()

s = convert[args[0]](int(args[1]))
print(len(s))
print(s)
