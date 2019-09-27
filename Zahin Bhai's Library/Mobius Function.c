#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 666666
#define MAX 10000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int len = 0, prime[LEN];
char mu[MAX] = {0}, flag[MAX] = {0};

/// mu[1] = 1, mu[n] = 0 if n has a squared prime factor,
/// mu[n] = 1 if n is square-free with even number of prime factors
/// mu[n] = -1 if n is square-free with odd number of prime factors

void Mobius(){
    mu[1] = 1;
    int i, j, k;

    for (i = 2; i < MAX; i++){
        if (!flag[i]) mu[i] = -1, prime[len++] = i;
        for (j = 0; j < len && (k = i * prime[j]) < MAX; j++){

            flag[k] = true;
            if (!(i % prime[j])){
                mu[k] = 0;
                break;
            }
            else mu[k] -= mu[i];
        }
    }
}

void Mobius(){ /// Simplified NlogN version
    int i, j;

    mu[1] = 1;
    for (i = 1; i < MAX; i++){
        for (j = i + i; j < MAX; j += i){
            mu[j] -= mu[i];
        }
    }
}

void Mobius(){ /// Simplified version optimized
    int i, j;

    mu[1] = 1;
    for (i = 1; i < MAX; i++){
        if (mu[i]){
            for (j = i + i; j < MAX; j += i){
                mu[j] -= mu[i];
            }
        }
    }
}

int main(){
    Mobius();
}
