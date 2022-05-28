#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int popcount(int x){
    int counter = 0;
    __asm__ volatile("POPCNT %1, %0;"
        :"=r"(counter)
        :"r"(x)
        :
    );
    return counter;
}

int lzcount(int x){
    int counter = 0;
    __asm__ volatile("LZCNT %1, %0;"
        :"=r"(counter)
        :"r"(x)
        :
    );
    return counter;
}

/// Returns i if x = 2^i and 0 otherwise
int bitscan(unsigned int x){
    __asm__ volatile("bsf %0, %0" : "=r" (x) : "0" (x));
    return x;
}

double fsqrt(double x){ /// Also works for long double
    __asm__ volatile("fsqrt" : "+t" (x));
    return x;
}

int gcd(int a, int b){
    int res;
    __asm__ volatile(
                      "movl %1, %%eax;"
                      "movl %2, %%ebx;"
                      "repeat_%=:\n"
                      "cmpl $0, %%ebx;"
                      "je terminate_%=\n;"
                      "xorl %%edx, %%edx;"
                      "idivl %%ebx;"
                      "movl %%ebx, %%eax;"
                      "movl %%edx, %%ebx;"
                      "jmp repeat_%=\n;"
                      "terminate_%=:\n"
                      "movl %%eax, %0;"

                      : "=g"(res)
                      : "g"(a), "g"(b)
                      : "eax", "ebx", "edx"

    );
    return res;
}

int main(){
    printf("%d\n", lzcount(13));
    return 0;
}
