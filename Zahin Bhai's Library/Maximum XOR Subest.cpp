#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define bitlen(x) ((x) == 0 ? (0) : (64 - __builtin_clzll(x)))
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

long long ar[MAX];

long long solve(int n, long long* ar){ /// hash = 220650
    vector <long long> v[64];
    for (int i = 0; i < n; i++) v[bitlen(ar[i])].push_back(ar[i]);

    long long m, x, res = 0;
    for (int i = 63; i > 0; i--){
        int l = v[i].size();
        if (l){
            m = v[i][0];
            res = max(res, res ^ m);

            for (int j = 1; j < l; j++){
                x = m ^ v[i][j];
                if (x) v[bitlen(x)].push_back(x);
            }
            v[i].clear();
        }
    }
    return res;
}

int main(){
    return 0;
}
