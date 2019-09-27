#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const unsigned long long base = 1995433697ULL;
const unsigned long long fuck = 1000000007ULL;

int n, m, r, c;
char str[2010][2010], pattern[2010][2010];
unsigned long long pattern_hash, P[2010], F[2010], ar[2010];

void Pregenerate(){
    int i, j;

    pattern_hash = 0;
    for (i = 0; i < r; i++){
        unsigned long long res = 0;
        for (j = 0; j < c; j++) res = (res * fuck) + pattern[i][j];
        pattern_hash = (pattern_hash * base) + res;
    }
}

int Solve(){
    int i, j, res = 0;
    unsigned long long x = 0, y;

    for (i = 0; i < r; i++) x = (x * base) + ar[i];
    for (i = 0; i < n; i++){
        if ((i + r) > n) break;
        if (x == pattern_hash) res++;

        y = (x - (P[r - 1] * ar[i]));
        x = (y * base) + ar[i + r];
    }

    return res;
}

int main(){
    int i, j, k, l;

    P[0] = F[0] = 1;
    for (i = 1; i < 2010; i++){
        P[i] = P[i - 1] * base;
        F[i] = F[i - 1] * fuck;
    }

    while (scanf("%d %d %d %d", &r, &c, &n, &m) != EOF){
        for (i = 0; i < r; i++) scanf("%s", pattern[i]);
        for (i = 0; i < n; i++) scanf("%s", str[i]);

        int res = 0;
        Pregenerate();
        for (i = 0; i < n; i++){
            unsigned long long res = 0;
            for (j = 0; j < c; j++) res = (res * fuck) + str[i][j];
            ar[i] = res;
        }

        for (j = 0; j < m; j++){
            if ((j + c) > m) break;

            res += Solve();
            for (i = 0; i < n; i++){
                unsigned long long x = ar[i];
                x = x - (F[c - 1] * str[i][j]);
                ar[i] = (x * fuck) + str[i][j + c];
            }
        }

        printf("%d\n", res);
    }
    return 0;
}
