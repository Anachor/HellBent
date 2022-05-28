///Source: Vule gesi :(
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL mod(LL a, LL m) {
    LL ans = a%m;
    return ans < 0 ? ans+m : ans;
}

///Sum(floor((ax+b)/m)) for i=0 to n-1, (n,m >= 0)
LL floorSum(LL n, LL m, LL a, LL b) {
    LL ra = mod(a, m), rb = mod(b, m), k = (ra*n+rb);
    LL ans = ((a-ra)/m) * n*(n-1)/2 + ((b-rb)/m) * n;
    if (k < m)  return ans;
    return ans + floorSum(k/m, ra, m, k%m);

}

///Solves https://judge.yosupo.jp/problem/sum_of_floor_of_linear
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    while (t--) {
        int n, m, a, b;
        cin>>n>>m>>a>>b;
        cout<<floorSum(n, m, a, b)<<"\n";
    }
}
