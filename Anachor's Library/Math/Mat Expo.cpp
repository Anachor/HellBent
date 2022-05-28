///Author: anachor
#include<bits/stdc++.h>
using namespace std;

const int M = 1e9+7;
typedef vector<int> row;
typedef vector<row> matrix;

matrix operator*(const matrix&a, const matrix &b) {
    int n = a.size();
    int p = b.size();
    int m = b[0].size();

    matrix ans(n, row(m));
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            for (int k=0; k<p; k++)
                ans[i][j] = (ans[i][j] + 1LL*a[i][k]*b[k][j])%M;
    return ans;
}

matrix unit(int n) {
    matrix ans(n, row(n));
    for (int i=0; i<n; i++)
        ans[i][i] = 1;
    return ans;
}

matrix power(const matrix &a, long long p) {
    if (p == 0)     return unit(a.size());
    matrix ans = power(a, p/2);
    ans = ans * ans;
    if (p%2)        ans = ans*a;
    return ans;
}


typedef vector<vector<long long>> VVL;
int gauss(VVL ar, int e, VVL &res){
    int n = ar.size(), m = ar[0].size()-1;
    vector<int> pos(m, -1);

    for (int j=0, i=0; j<m && i<n; j++) {
        int p = i;
        for (int k=i; k<n; k++){
            if (abs(ar[k][j]) > abs(ar[p][j])) p = k;
        }
        if (abs(ar[p][j]) > EPS){
            pos[j] = i;
            swap(ar[p], ar[i]);

            for (int k=0; k<n; k++){
                if (k == i) continue;
                double x = ar[k][j]/ar[i][j];
                for (int l=j; l<m+e; l++) ar[k][l] -= ar[i][l] * x;
            }
            i++;
        }
    }
    int free_var = 0;
    for (int i=0;i<m; i++) free_var += (pos[i] == -1);

    for (int k=0; k<e; k++) {
        res.emplace_back(vector<double>(m));
        for (int i=0; i<m; i++)
            res.back()[i] = ar[pos[i]][m+k]/ar[pos[i]][i];
//        for (int i = 0; i < n; i++) {
//            double val = 0;
//            for (int j=0; j<m; j++) val += res.back()[j]*ar[i][j];
//            if (abs(val-ar[i][m]) > EPS) res.back().clear();
//        }
    }
    return free_var;

}

///Finds kth Fibonacci number
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin>>n;

    matrix base(2, row(2));
    base[0][0] = 0, base[0][1] = 1;
    base[1][0] = 1, base[1][1] = 1;

    base = power(base, n);
    cout<<setprecision(10)<<fixed<<base[0][1]<<endl;

}
