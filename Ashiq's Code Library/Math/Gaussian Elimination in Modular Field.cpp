#include <bits/stdtr1c++.h>

#define MAXROW 1010
#define MAXCOL 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

int expo(int a, int b, int MOD){
    int res = 1;

    while (b){
        if (b & 1) res = (long long)res * a % MOD;
        a = (long long)a * a % MOD;
        b >>= 1;
    }
    return res;
}

/// Gaussian elimination in field MOD (MOD should be a prime)
int gauss(int n, int m, int MOD, int ar[MAXROW][MAXCOL], vector<int>& res){
    res.assign(m, 0);
    vector <int> pos(m, -1);
    int i, j, k, l, p, d, free_var = 0;
    const long long MODSQ = (long long)MOD * MOD;

    for (j = 0, i = 0; j < m && i < n; j++){
        for (k = i, p = i; k < n; k++){
            if (ar[k][j] > ar[p][j]) p = k;
        }

        if (ar[p][j]){
            pos[j] = i;
            for (l = j; l <= m; l++) swap(ar[p][l], ar[i][l]);

            d = expo(ar[i][j], MOD - 2, MOD);
            for (k = 0; k < n && d; k++){
                if (k != i && ar[k][j]){
                    int x = ((long long)ar[k][j] * d) % MOD;
                    for (l = j; l <= m && x; l++){
                        if (ar[i][l]) ar[k][l] = (MODSQ + ar[k][l] - ((long long)ar[i][l] * x)) % MOD;
                    }
                }
            }
            i++;
        }
    }

    for (i = 0; i < m; i++){
        if (pos[i] == -1) free_var++;
        else res[i] = ((long long)ar[pos[i]][m] * expo(ar[pos[i]][i], MOD - 2, MOD)) % MOD;
    }

    for (i = 0; i < n; i++) {
        long long val = 0;
        for (j = 0; j < m; j++) val = (val + ((long long)res[j] * ar[i][j])) % MOD;
        if (val != ar[i][m]) return -1;
    }
    return free_var;
}

int main(){

}
