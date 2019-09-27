#include <bits/stdtr1c++.h>

#define MAXC 1010
#define MAXV 1010
#define EPS 1e-13

#define MINIMIZE -1
#define MAXIMIZE +1
#define LESSEQ -1
#define EQUAL 0
#define GREATEQ 1
#define INFEASIBLE -1
#define UNBOUNDED 666

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace lp{
    long double val[MAXV], ar[MAXC][MAXV];
    int m, n, solution_flag, minmax_flag, basis[MAXC], index[MAXV];

    inline void init(int nvars, long double f[], int flag){
        solution_flag = 0;
        ar[0][nvars] = 0.0;
        m = 0, n = nvars, minmax_flag = flag;
        for (int i = 0; i < n; i++){
            ar[0][i] = f[i] * minmax_flag;
        }
    }

    inline void add_constraint(long double C[], long double lim, int cmp){
        m++, cmp *= -1;
        if (cmp == 0){
            for (int i = 0; i < n; i++) ar[m][i] = C[i];
            ar[m++][n] = lim;
            for (int i = 0; i < n; i++) ar[m][i] = -C[i];
            ar[m][n] = -lim;
        }
        else{
            for (int i = 0; i < n; i++) ar[m][i] = C[i] * cmp;
            ar[m][n] = lim * cmp;
        }
    }

    inline void init(){
        for (int i = 0; i <= m; i++) basis[i] = -i;
        for (int j = 0; j <= n; j++){
            ar[0][j] = -ar[0][j], index[j] = j, val[j] = 0;
        }
    }

    inline void pivot(int m, int n, int a, int b){
        for (int i = 0; i <= m; i++){
            if (i != a){
                for (int j = 0; j <= n; j++){
                    if (j != b){
                        ar[i][j] -= (ar[i][b] * ar[a][j]) / ar[a][b];
                    }
                }
            }
        }

        for (int j = 0; j <= n; j++){
            if (j != b) ar[a][j] /= ar[a][b];
        }
        for (int i = 0; i <= m; i++){
            if (i != a) ar[i][b] = -ar[i][b] / ar[a][b];
        }

        ar[a][b] = 1.0 / ar[a][b];
        swap(basis[a], index[b]);
    }

    inline long double solve(){
        init();
        int i, j, k, l;
        for (; ;){
            for (i = 1, k = 1; i <= m; i++){
                if ((ar[i][n] < ar[k][n]) || (ar[i][n] == ar[k][n] && basis[i] < basis[k] && (rand() & 1))) k = i;
            }
            if (ar[k][n] >= -EPS) break;

            for (j = 0, l = 0; j < n; j++){
                if ((ar[k][j] < (ar[k][l] - EPS)) || (ar[k][j] < (ar[k][l] - EPS) && index[i] < index[j] && (rand() & 1))){
                    l = j;
                }
            }
            if (ar[k][l] >= -EPS){
                solution_flag = INFEASIBLE;
                return -1.0;
            }
            pivot(m, n, k, l);
        }

        for (; ;){
            for (j = 0, l = 0; j < n; j++){
                if ((ar[0][j] < ar[0][l]) || (ar[0][j] == ar[0][l] && index[j] < index[l] && (rand() & 1))) l = j;
            }
            if (ar[0][l] > -EPS) break;

            for (i = 1, k = 0; i <= m; i++){
                if (ar[i][l] > EPS && (!k || ar[i][n] / ar[i][l] < ar[k][n] / ar[k][l] - EPS || (ar[i][n] / ar[i][l] < ar[k][n] / ar[k][l] + EPS && basis[i] < basis[k]))){
                    k = i;
                }
            }
            if (ar[k][l] <= EPS){
                solution_flag = UNBOUNDED;
                return -666.0;
            }
            pivot(m, n, k, l);
        }

        for (i = 1; i <= m; i++){
            if (basis[i] >= 0) val[basis[i]] = ar[i][n];
        }
        solution_flag = 1;
        return (ar[0][n] * minmax_flag);
    }
}

int main(){
}
