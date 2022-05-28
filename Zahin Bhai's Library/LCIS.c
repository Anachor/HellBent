#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 2057
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

/// Longest common increasing subsequence of A and B in O(n * m)
int lcis(int n, int* A, int m, int* B){
    int i, j, l, res, dp[MAX] = {0};

    for (i = 0; i < n; i++){
        for (l = 0, j = 0; j < m; j++){
            if (A[i] == B[j] && dp[j] <= l) dp[j] = l + 1;
            else if (B[j] < A[i] && dp[j] > l) l = dp[j];
        }
    }

    for (i = 0, res = 0; i < m; i++){
        if (dp[i] > res) res = dp[i];
    }
    return res;
}

int main(){

}
