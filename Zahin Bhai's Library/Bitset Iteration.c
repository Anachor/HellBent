#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char bithash[67];

void init(){
    int i;
    for (i = 0; i < 64; i++) bithash[(1ULL << i) % 67] = i;
}

void iterate(unsigned long long x){
    while (x){
        unsigned long long y = (x & -x);
        int i = bithash[y % 67];
        x ^= y;
        printf("%d\n", i);
    }
}

int main(){
    init();
    unsigned long long x = 0b100000001011000100100101001010101001010100;
    iterate(x);
    return 0;
}
