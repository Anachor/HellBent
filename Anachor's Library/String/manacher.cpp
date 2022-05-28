///Source: cp-algo, anachor (ispalin)

#include<bits/stdc++.h>
using namespace std;

///0-based indexing
///p[0][i] is the maximum length of half palindrome around half index i
///p[1][i] is the maximum length of half palindrome around characters i

struct Manacher {
    vector<int> p[2];
    Manacher(const string &s) {
        int n = s.size();
        p[0].resize(n+1); p[1].resize(n);

        for (int z=0; z<2; z++)
            for (int i=0, l=0, r=0; i<n; i++) {
                int t = r-i+!z;
                if (i<r) p[z][i] = min(t, p[z][l+t]);
                int L = i-p[z][i], R = i+p[z][i]-!z;
                while (L>=1 && R+1<n && s[L-1] == s[R+1])   p[z][i]++, L--, R++;
                if (R>r) l=L, r=R;
            }
    }

    bool ispalin(int l, int r) {
        int mid = (l+r+1)/2, sz = r-l+1;
        return 2*p[sz%2][mid]+sz%2 >= sz;
    }
};

///Solves https://old.yosupo.jp/problem/enumerate_palindromes
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin>>s;
    int n = s.size();

    Manacher solver(s);

    int ans = 0;
    for (int i=0; i<2*n-1; i++) {
        if (i%2==0)     cout<<1+2*solver.p[1][i/2]<<" ";
        else            cout<<2*solver.p[0][i/2+1]<<" ";
    }

}
