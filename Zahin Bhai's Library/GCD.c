#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int gcd(int u, int v){
    int t;

    while (v){
        t = u;
        u = v;
        v = t % v;
    }

    if (u < 0) u = 0 - u;
    return u;
}

long long gcd(long long u, long long v){
    long long t;

    while (v){
        t = u;
        u = v;
        v = t % v;
    }

    if (u < 0) u = 0 - u;
    return u;
}

int gcd(int a, int b){
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

long long gcd(long long a, long long b){
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

unsigned long long gcd(unsigned long long u, unsigned long long v){
    if (!u) return v;
    if (!v) return u;
    if (u == 1 || v == 1) return 1;

    int shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do{
        v >>= __builtin_ctzll(v);
        if (u > v)
            v ^= u ^= v ^= u;
        v = v - u;
    } while (v);

    return u << shift;
}

unsigned int gcd(unsigned int u, unsigned int v){
    if (!u) return v;
    if (!v) return u;
    if (u == 1 || v == 1) return 1;

    int shift = __builtin_ctz(u | v);
    u >>= __builtin_ctz(u);
    do{
        v >>= __builtin_ctz(v);
        if (u > v)
            v ^= u ^= v ^= u;
        v = v - u;
    } while (v);

    return u << shift;
}

int gcd(int u, int v){
    if (!u || !v) return (u | v);

    int d, shift;
    for (shift = 0; !((u | v) & 1); shift++){
        u >>= 1;
        v >>= 1;
    }

    while (!(u & 1)) u >>= 1;
    do{
        while (!(v & 1)) v >>= 1;
        if (u < v) v -= u;
        else{
            d = u - v;
            u = v;
            v = d;
        }
        v >>= 1;
    }
    while (v);

    return (u << shift);
}

int gcd(int a, int b){
    if (!a) return b;
    else return gcd(b, a % b);
}

long long gcd(long long a, long long b){
    if (!a) return b;
    else return gcd(b, a % b);
}

int main(){
}
