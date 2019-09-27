#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long gray_code(long long x){
    return x ^ (x >> 1);
}

long long inverse_gray_code(long long x){
    long long h = 1, res = 0;
    do{
        if (x & 1) res ^= h;
        x >>= 1, h = (h << 1) + 1;
    } while (x);
    return res;
}

int main(){

}
