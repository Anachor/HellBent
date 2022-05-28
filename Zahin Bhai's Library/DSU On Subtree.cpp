/// Codeforces 601D
/// D[i] = number of distinct strings starting at vertex i and ending on some vertex down subtree i

#include <bits/stdtr1c++.h>

#define MAX 300010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

const long long HMOD[] = {2078526727, 2117566807};
const long long BASE[] = {1572872831, 1971536491};

char str[MAX];
vector <int> adj[MAX];
int n, C[MAX], D[MAX], T[MAX];
set <long long> S[MAX];

void dfs(int i, int p, long long h1, long long h2){ /// hash = 400687
    h1 = (h1 * BASE[0] + str[i - 1] + 10007) % HMOD[0];
    h2 = (h2 * BASE[1] + str[i - 1] + 10007) % HMOD[1];

    int j, k, x, idx = 0, res = 0, len = adj[i].size();
    for (j = 0; j < len; j++){
        x = adj[i][j];
        if (x != p){
            dfs(x, i, h1, h2);
            if (D[x] > res) res = D[x], idx = x; /// update
        }
    }

    if (idx) T[i] = T[idx]; /// If maximum subtree child found, set root to root of subtree
    for (j = 0; j < len; j++){
        x = adj[i][j];
        if (x != p && T[x] != T[i]){
            for (auto it: S[T[x]]) S[T[i]].insert(it); /// If not parent and not maximum subtree, insert
            S[T[x]].clear(); /// Finally clear the remaining items since not required anymore
        }
    }
    S[T[i]].insert((h1 << 31) ^ h2);
    D[i] = S[T[i]].size();
}

int main(){
    int i, j, k, l, a, b, c, x, res;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) T[i] = i;
    for (i = 1; i <= n; i++) scanf("%d", &C[i]); /// Set parent[i] = i

    scanf("%s", str);
    for (i = 1; i < n; i++){
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0, 0, 0);
    for (res = 0, c = 0, i = 1; i <= n; i++){
        x = C[i] + D[i];
        if (x > res) res = x, c = 1;
        else if (x == res) c++;
    }

    printf("%d\n%d\n", res, c);
    return 0;
}
