#include<bits/stdc++.h>
using namespace std;

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i=1; i<n; i++) {
        if (i<=r)   z[i] = min(r-i+1, z[i-l]);
        while (i+z[i]<n && s[i+z[i]] == s[z[i]])    z[i]++;
        if (i+z[i]-1>r)   l = i, r = i+z[i]-1;
    }
    return z;
}


///Solves SPOJ QUERYSTR
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin>>t;
    while (t--) {
        string s;
        cin>>s;
        int n = s.size();
        reverse(s.begin(), s.end());
        vector<int> ans = z_function(s);
        ans[0] = n;

        int q;
        cin>>q;
        while (q--) {
            int x;
            cin>>x;
            x = n-x;
            cout<<ans[x]<<"\n";
        }
    }
}
