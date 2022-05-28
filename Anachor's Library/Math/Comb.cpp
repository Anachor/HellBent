///Author: anachor
#include<bits/stdc++.h>
using namespace std;

const int M = 1e9+7;

int power(int a, int p) {
    if (p == 0) return 1;
    int ans = power(a, p/2);
    ans = (1LL*ans * ans)%M;
    if (p%2)    ans = (1LL*ans*a)%M;
    return ans;
}

const int N = 2e5+7;
int fac[N], invfac[N];
void pre() {
    fac[0] = 1;
    for(int i=1; i<N; i++)  fac[i] = (1LL*i*fac[i-1])%M;
    invfac[N-1] = power(fac[N-1], M-2);
    for (int i=N-2; i>=0; i--)  invfac[i] = (1LL*invfac[i+1]*(i+1))%M;
}

int C(int n, int r) {
    if (r<0 || r>n) return 0;
    int denom = (1LL*invfac[r]*invfac[n-r])%M;
    return (1LL*fac[n]*denom)%M;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    pre();
    cout<<C(10, 5)<<endl;
}
