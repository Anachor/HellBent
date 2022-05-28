#include <bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;

vector<vector<int>> multiply(vector<vector<int>> &a, vector<vector<int>> &b) {
    int dim = a.size();
    vector<vector<int>> c(dim, vector<int>(dim, 0));
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            for(int k = 0; k < dim; k++) {
                c[i][j] += 1ll*a[i][k]*b[k][j]%mod;
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

vector<vector<int>> bigmod(long long p, vector<vector<int>> &base) {
    if(p == 0) {
        int dim = (int)base.size();
        vector<vector<int>> unity(dim, vector<int>(dim, 0));
        for(int i = 0; i < dim; i++) unity[i][i] = 1;
        return unity;
    }
    if(p&1) {
        vector<vector<int>> ret = bigmod(p-1,base);
        return multiply(ret, base);
    }
    vector<vector<int>> ret = bigmod(p/2,base);
    return multiply(ret,ret);
}

int main() {

}
