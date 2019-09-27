#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 12
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define hash(ar)  dp[ar[0]][ar[1]][ar[2]][ar[3]][ar[4]][ar[5]]
#define lexic(ar) pos[ar[0]][ar[1]][ar[2]][ar[3]][ar[4]][ar[5]]

char ar[MAX];
int n, m, counter, factorial[MAX];
int last[1 << MAX], dp[MAX][MAX][MAX][MAX][MAX][MAX], pos[MAX][MAX][MAX][MAX][MAX][MAX];

void backtrack(int i, int bitmask, int flag){
    if (i == m){
        if (flag & 1) hash(ar) = ++counter;
        if (flag & 2) lexic(ar) = last[bitmask]++;
        return;
    }

    int j;
    for (j = 0; j < n; j++){
        if (!(bitmask & (1 << j))){
            ar[i] = j;
            backtrack(i + 1, bitmask | (1 << j), flag);
        }
    }
}

void Generate(){
    int i, j;
    clr(ar), clr(last);
    counter = 0, m = n >> 1, factorial[0] = 1;
    for (i = 1; i < MAX; i++) factorial[i] = factorial[i - 1] * i;

    if (n & 1){
        backtrack(0, 0, 1);
        m++;
        backtrack(0, 0, 2);
        m--;
    }
    else backtrack(0, 0, 3);
}

int F(int P[MAX]){
    int i, a = 0, b = 0;
    char A[6] = {0}, B[6] = {0};
    for (i = 0; i < m; i++) A[a++] = P[i];
    for (i = m; i < n; i++) B[b++] = P[i];
    return ((hash(A) - 1) * factorial[b]) + lexic(B) + 1;
}

int main(){
    int i, j, P[MAX];

    while (scanf("%d", &n) != EOF){
        Generate();
        for (i = 0; i < n; i++) scanf("%d", &P[i]);
        for (i = 0; i < n; i++) P[i]--;
        int res = F(P);
        printf("%d\n", res);
    }
    return 0;
}
