#include <bits/stdtr1c++.h>

#define MAXROW 630
#define MAXCOL 630
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/***

Gauss-Jordan Elimination in Galois Field, GF(2)

n = number of linear equations
m = number of variables
ar[i][m] = right-hand side value of constants

For instance, the system of linear equations (note not in GF(2)) becomes:

2x + y -z = 8      ----->  (i)
-3x -y + 2z = -11  ----->  (ii)
-2x + y + 2z = -3  ----->  (iii)

n = 3 (x, y, z), m = 3 (i, ii, iii)
ar[0] = {2, 1, -1, 8}    ----->  (i)
ar[1] = {-3, -1, 2, -11} ----->  (ii)
ar[2] = {-2, 1, 2, -3}   ----->  (iii)


Returns -1 when there is no solution
Otherwise returns the number of independent variables (0 for an unique solution)
Contains a solution in the bit vector res on successful completion
Note that the array is modified in the process

***/

int gauss(int n, int m, bitset <MAXCOL> ar[MAXROW], bitset <MAXCOL>& res){ /// hash = 169721
    res.reset();
    vector <int> pos(m, -1);
    int i, j, k, l, v, p, free_var = 0;

    for (j = 0, i = 0; j < m && i < n; j++){
        for (k = i, p = i; k < n; k++){
            if (ar[k][j]){
                p = k;
                break;
            }
        }

        if (ar[p][j]){
            pos[j] = i;
            swap(ar[p], ar[i]);

            for (k = 0; k < n; k++){
                if (k != i && ar[k][j]) ar[k] ^= ar[i];
            }
            i++;
        }
    }

    for (i = 0; i < m; i++){
        if (pos[i] == -1) free_var++;
        else res[i] = ar[pos[i]][m];
    }

    for (i = 0; i < n; i++) {
        for (j = 0, v = 0; j < m; j++) v ^= (res[j] & ar[i][j]);
        if (v != ar[i][m]) return -1;
    }
    return free_var;
}

int main(){

}
