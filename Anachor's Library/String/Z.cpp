///Source: cp-algo(?)

#include<bits/stdc++.h>
using namespace std;


///Z[i] = LCP(s, s[i....])
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i=1; i<n; i++) {
        if (i<=r)   z[i] = min(r-i+1, z[i-l]);
        while (i+z[i]<n && s[i+z[i]] == s[z[i]])    z[i]++;
        if (i+z[i]-1>r)   l = i, r = i+z[i]-1;
    }
    z[0] = s.size();
    return z;
}


///https://old.yosupo.jp/problem/zalgorithm
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin>>s;

    for (int x: z_function(s))  cout<<x<<" ";
    cout<<endl;
}
