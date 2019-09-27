/**
You have to cut a wood stick into pieces. The most affordable company, The Analog Cutting Machinery,
Inc.  (ACM), charges money according to the length of the stick being cut.  Their procedure of work
requires that they only make one cut at a time.
It is easy to notice that different selections in the order of cutting can led to different prices. For
example, consider a stick of length 10 meters that has to be cut at 2, 4 and 7 meters from one end.
There are several choices. One can be cutting first at 2, then at 4, then at 7. This leads to a price of 10
+ 8 + 6 = 24 because the first stick was of 10 meters, the resulting of 8 and the last one of 6. Another
choice could be cutting at 4, then at 2, then at 7. This would lead to a price of 10 + 4 + 6 = 20, which
is a better price.
Your boss trusts your computer abilities to find out the minimum cost for cutting a given stick.
*//

#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N=1000+7;
LL a[N];
LL dp[N][N];
int opt[N][N];

const long long INF=1e15;


//solves ZOJ 2860

int main ()
{
    ios::sync_with_stdio(false);
    int l, n;

    while (cin>>l>>n)
    {
        a[0] = 0;
        a[++n] = l;

        for (int i=1; i<n; i++)
            cin>>a[i];

        for (int i=1; i<=n; i++)
            opt[i-1][i] = i-1;

        for (int len = 2; len<=n; len++)
            for (int l=0; l+len<=n; l++)
            {
                int r=l+len;
                int optl = opt[l][r-1];
                int optr = opt[l+1][r];
                dp[l][r] = INF;

                for (int i=optl; i<=optr; i++)
                {
                    LL cost = dp[l][i] + dp[i][r] + (a[r] - a[l]);
                    if (cost < dp[l][r])
                        dp[l][r] = cost,
                        opt[l][r] = i;
                }
            }

        cout<<dp[0][n]<<endl;
    }
}

