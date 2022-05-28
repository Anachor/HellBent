#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const int n = 10;
const long long INF = 0x7FFFFFFFFFFFFFFF;
const int coins[] = {0, 1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000}; /// 1 based indexing for coins

long long res, counter[44], sum[44]; /// counter[i] = number of coins of type i

void backtrack(int i, long long p, long long c){ /// Complexity 2^n
    if (p == 0 && c < res) res = c; /// Change min to max here
    if (i == 0 || p <= 0) return;

    long long k, x = 0;
    if ((p - sum[i - 1]) > x) x = p - sum[i - 1];
    k = (x / coins[i]) + (x % coins[i] != 0);
    if (k <= counter[i]) backtrack(i - 1, p - k * coins[i], c + k);
    if (++k <= counter[i]) backtrack(i - 1, p - k * coins[i], c + k); /// Do this multiple times if WA (around 5 or 10 should do)
}

/// Minimum number of coins required to make s from coin values and count of coin values
/// -1 if no solution

long long solve(long long s){
    int i, j;
    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + coins[i] * counter[i];

    res = INF;
    backtrack(n, s, 0);
    if (res == INF) res = -1;
    return res;
}

int main(){
    return 0;
}
