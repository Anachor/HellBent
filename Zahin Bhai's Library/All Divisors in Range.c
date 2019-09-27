#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define optimize(str) __attribute__((optimize(str)))

short len[MAX];
int L[MAX], *divisors[MAX];

void Generate(){
    int i, j, k, c, d, x;

    len[0] = len[1] = L[0] = L[1] = 1;
    for (i = 4; i < MAX; i++, i++) len[i] = 2;

    for (i = 3; (i * i) < MAX; i += 2){
        if (!len[i]){
            for (j = (i * i), d = i << 1; j < MAX; j += d){
                if (!len[j]) len[j] = i;
            }
        }
    }

    for (i = 2; i < MAX; i++){
        if (!len[i]) L[i] = i;
        else{
            L[i] = len[i];
            x = L[i /len[i]];
            if (x > L[i]) L[i] = x;
        }
    }

    divisors[1] = (int *) malloc(sizeof(int));
    divisors[1][0] = 1, len[1] = 1;

    for (i = 2; i < MAX; i++){
        c = 0, k = i;
        while (k > 1 && L[k] == L[i]){
            c++;
            k /= L[k];
        }

        len[i] = (c + 1) * len[k];
        divisors[i] = (int *) malloc(sizeof(int) * len[i]);

        for (x = 1, j = 0, len[i] = 0; j <= c; j++, x *= L[i]){
            for (d = 0; d < len[k]; d++){
                divisors[i][len[i]++] = divisors[k][d] * x;
            }
        }
    }
}

int main(){
    Generate();
    return 0;
}
