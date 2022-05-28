#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Find's the rank of permutation
/// Rank and permutation elements are 1 base indexed

long long find_rank(vector <int> permutation){
    long long res = 1;
    int i, j, n = permutation.size();
    vector <bool> visited(n + 1, false);
    vector <long long> factorial(n + 1, 1);
    for (i = 1; i <= n; i++) factorial[i] = factorial[i - 1] * i;

    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if (!visited[j]){
                if (permutation[i - 1] == j){
                    visited[j] = true;
                    break;
                }
                res += factorial[n - i];
            }
        }
    }
    return res;
}

/// Find's the k'th permutation of 1 to n
/// Rank and permutation elements are 1 base indexed

vector <int> find_rank(int n, long long k){
    int i, j;
    vector <int> res(n, 0);
    vector <bool> visited(n + 1, false);
    vector <long long> factorial(n + 1, 1);
    for (i = 1; i <= n; i++) factorial[i] = factorial[i - 1] * i;

    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if (!visited[j]){
                if (factorial[n - i] >= k){
                    visited[j] = true;
                    res[i - 1] = j;
                    break;
                }
                k -= factorial[n - i];
            }
        }
    }
    return res;
}

int main(){
    return 0;
}
