#include <bits/stdc++.h>
#define VD  vector<double>
#define VVD vector<VD>
using namespace std;

/**
Gauss-Jordan Elimination for solving multi-variable
Linear Equations. If there are multiple solutions,
outputs a arbitrary valid solution. If some of the
variable are unsolvable, they are assigned nan.

INPUT:  2D vector representing the Augmented Matrix form
OUTPUT: 1D vector containing the solutions
Complexity: O(n^3)

Note: There must be as exactly as many equations as
variables, if there are less equations, add all zero rows
to make n nows. If there are more than n equations, keep
n (preferably unique) equations and check the others using
that solution.

*/

void print(VVD mat)
{
    int n=mat.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cout<<mat[i][j]<<" ";
        cout<<" | "<<mat[i][n]<<endl;
    }
}

const double EPS = 1e-9;
VD Gauss(VVD a)
{
    int n=a.size();

    for (int i=0; i<n; i++) {
        int id=i;
        for (int j=i; j<n; j++)
            if (abs(a[j][i]) > abs(a[id][i]))
                id = j;
        swap(a[i], a[id]);

        if (abs(a[i][i]) < EPS)   continue;

        for (int j=i+1; j<n; j++)
            for (int k=n; k>=i; k--)
                a[j][k] -= a[i][k] * (a[j][i] / a[i][i]);
    }

    for (int i=0; i<n; i++) {
        if (abs(a[i][i]) < EPS)   continue;
        for (int j=0; j<i; j++)
            for (int k=n; k>=i; k--)
                a[j][k] -= a[i][k] * (a[j][i] / a[i][i]);
    }

    VD sol(n);
    vector<bool> bad(n);

    for (int i=n-1; i>=0; i--)
    {
        if (abs(a[i][i]) < EPS && abs(a[i][n]) > EPS)   bad[i]=1;
        else if (abs(a[i][i]) < EPS)      sol[i]=0;
        else    sol[i] = a[i][n]/a[i][i];

        for(int j=i; j<n; j++)
            if( abs(a[i][j]) > EPS && bad[j])
                bad[i]=1;
    }

    for (int i=0; i<n; i++)
        if (bad[i])     sol[i]=NAN;

    return sol;
}

int main()
{
    int n;
    cin>>n;
    VVD mat (n, VD (n+1));
    for (int i=0; i<n; i++)
        for (int j=0; j<=n; j++)
            cin>>mat[i][j];

    VD sol = Gauss(mat);

    for (int i=0; i<n; i++)
        cout<<sol[i]<<endl;
}
