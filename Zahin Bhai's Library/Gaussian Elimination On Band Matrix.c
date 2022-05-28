/// Gaussian Elimination on Sparse Band Matrix (Non-zero values confined to diagonal bands)
/// Complexity: O(n * m^3), n = number of rows, m = number of columns

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXM 22
#define MAXN 10002
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define cell_num(i, j) (m * (n - (i)) - (j) - 1)
#define valid(i, j) ((i) >= 0 && (i) < n && (j) >= 0 && (j) < m)

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int n, m;
double band[MAXN * MAXM][2 * MAXM + 1]; /// sparse band matrix, used to compactly represent non-zero entries of the gauss matrix
double rhs[MAXN * MAXM], aux[MAXN * MAXM]; /// rhs[] contains right-hand side constants before gauss, and solutions for the system after gauss

void init(int n, int m){
    int i, j, q = n * m, d = 2 * m + 1;

    clr(rhs);
    for (i = 0; i < q; i++){
        for (j = 0; j < d; j++){
            band[i][j] = 0.0;
        }
        band[i][m] = 1.0;
    }
}

/// adding p to gauss_matrix[r][c] (implicit) where r = cell_num[i][j] and c = cell_num[k][l]
/// gauss_matrix[][] does not exist, the co-ordinates are converted to band matrix representation
void add(int i, int j, int k, int l, double p){
    int u = cell_num(i, j), v = cell_num(k, l) - u + m;
    band[u][v] += p;
}

void gauss(int n, int m){
    double x, y;
    int i, j, k, l, d, u, v, q = n * m, r = 2 * m + 1;

    /// Forward Elimination
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            d = i * m + j;
            x = band[d][m], rhs[d] /= x;
            for (k = 0; k <= m && (d + k) < q; k++) band[d][m + k] /= x;

            for (l = 1; l <= m && (d + l) < q; l++){
                x = band[d + l][m - l], rhs[d + l] -= (x * rhs[d]);
                for (k = 0; k <= m && (d + k) < q; k++){
                    band[d + l][m - l + k] -= (x * band[d][m + k]);
                }
            }
        }
    }

    /// Backward substitution
    for (i = 0; i < q; i++) aux[i] = rhs[i], rhs[i] = 0.0;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            x = 0.0, u = cell_num(i, j);
            for (v = 0; v < r; v++) x += (band[u][v] * rhs[v + u - m]);
            rhs[u] = aux[u] - x;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    init(n, m);
    return 0;
}
