from gmpy2 import mpz, is_zero, is_bpsw_prp, powmod
from numba import jit,prange
from multiprocessing import Pool

@jit(parallel=True)
def ll(n):
    two = mpz(2)
    s = two*two
    div = two**n-1
    for i in prange(2,n):
        s = powmod(s,two,div)
        s -= 2
    if(not is_zero(s)):
        raise Exception("Not Prime")

@jit(parallel = True)
def trialfac(n,mod):
    s = mpz(1)
    for i in map(int,bin(n)[2:]):
        s = s*s
        if(i):
            s*=2
        s %= mod
    if(s == 1):
        raise Exception("Divisible by {}".format(mod))

@jit(parallel = True)
def mersfac(n):
    if(not (n%2 and n%3 and n%5 and n%7 and n%11 and n%13)):
        raise Exception("Not Prime")
    for i in prange(18,102,6):
        trialfac(n,i-1)
        trialfac(n,i+1)

def isprime(n):
    if(not is_bpsw_prp(n)):
        raise Exception("Not Prime")

def Mersenne(n):
    try:
        isprime(n)
        mersfac(n)
        ll(n)
        print('M',n, "                ")
    except:
        print('M',n, end = "\r")

def multimain():
    with Pool(12) as p:
        count = 0
        while True:
            count += 108
            p.imap(Mersenne,[count-1, count+1] + [count+5, count+7] + [count+11, count+13] + [count+17, count+19] + [count+23, count+25] + [count+29, count+31] +\
                            [count+35, count+37] + [count+41, count+43] + [count+47, count+49] + [count+53, count+55] + [count+59, count+61] + [count+65, count+67] +\
                            [count+35+36, count+37+36] + [count+41+36, count+43+36] + [count+47+36, count+49+36] + [count+53+36, count+55+36] + [count+59+36, count+61+36] + [count+65+36, count+67+36])
        

if __name__ == "__main__":
    multimain()