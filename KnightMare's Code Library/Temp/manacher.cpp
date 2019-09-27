#include<bits/stdc++.h>
#define VI vector<int>
using namespace std;

///0-based indexing
///p[0][i] is the maximum length of half palindrome around half index i
///p[1][i] is the maximum length of half palindrome around characters i
VI p[2];

void manacher(const string s) {
	int n = s.size();
	p[0] = VI(n+1);
	p[1] = VI(n);

	for (int z=0; z<2; z++)
        for (int i=0, l=0, r=0; i<n; i++)
        {
            int t = r - i + !z;
            if (i<r) p[z][i] = min(t, p[z][l+t]);
            int L = i-p[z][i], R = i+p[z][i] - !z;
            while (L>=1 && R+1<n && s[L-1] == s[R+1])
                p[z][i]++, L--, R++;
            if (R>r) l=L, r=R;
        }
}

bool ispalin(int l, int r)
{
    int mid = (l+r+1)/2;
    int sz = r-l+1;
    bool b = sz%2;
    int len = p[b][mid];
    len = 2*len + b;
    return len>=sz;
}

int main()
{
    int n;
    cin>>n;

    string s;
    cin>>s;

    manacher(s);

    int ans = 0;
    for (int i=0; i<=n; i++)    ans = max(ans, p[0][i]*2);
    for (int i=0; i<n; i++)     ans = max(p[1][i]*2+1, ans);

    cout<<ans<<endl;

}

