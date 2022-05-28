///Source: Folklore

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+9, K = 18;
int st[K][N], a[N], lg[N];

void buildRMQ(int n) {
    for(int i=1; i<=n; i++) st[0][i] = a[i];

    for(int k=1; k<K; k++)
        for(int i=1; i+(1<<k)-1<=n; i++)
            st[k][i] = min(st[k-1][i],st[k-1][i+(1<<(k-1))]);

    for(int i=2; i<=n; i++)      lg[i] = lg[i/2]+1;
}

int query (int i , int j) {
    int k = lg[j-i+1];
    return min(st[k][i],st[k][j-(1<<k)+1]);
}
