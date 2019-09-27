/*
CodeChef - CHEFAOR
You are given an array A of integers and an integer K. Your goal
is to divide the array into K consecutive disjoint non-empty
groups, so that any array element belongs to exactly one group.
The cost of such a group equals to the value of bitwise OR of
all elements in the group. The cost of array for some particular
group division equals to the sum of costs for all the groups.
You have to find the maximal achievable cost of the given array.
O(NKlogN)
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll dp[5001][5001];
ll cost[5001][5001];

ll a[5001];


void calculate(int level, int L, int R, int idL, int idR)
{
    int md = (L+R)/2;

    int j, k = idL;
    dp[level][md] = 0;

    for (j = idL; j <= idR && j < md; j++) {
        if (dp[level-1][j]+cost[j+1][md]>dp[level][md]) {
            dp[level][md] = dp[level-1][j]+cost[j+1][md];
            k = j;
        }
    }

    if (L <= md-1) calculate(level, L, md-1, idL, k);
    if (md+1 <= R) calculate(level, md+1, R, k, idR);
}


int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, k;

        scanf("%d %d", &n, &k);

        int i, j;
        for (i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            dp[1][i] = dp[1][i-1] | a[i];
        }

        for (i = 1; i <= n; i++) {
            cost[i][i] = a[i];
            for (j = i+1; j <= n; j++) {
                cost[i][j] = cost[i][j-1] | a[j];
            }
        }

        for (i = 2; i <= k; i++) calculate(i, i, n, i-1, n-1);

        printf("%lld\n", dp[k][n]);
    }



    return 0;
}
