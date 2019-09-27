#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// alpha = maximum score maximizing player (p = 0) is assured so far
/// beta = minimum score minimizing player (p = 1) is assured so far
int backtrack(struct node cur, int i, int p, int alpha, int beta){
    if (i == n){
        return evaluate(cur);
    }

    int j, k, x;
    vector <struct node> ar = transition(cur, deck[i], p);

    for (j = 0; j < ar.size(); j++){
        x = backtrack(ar[j], i + 1, p ^ 1, alpha, beta);
        if (p == 0 && x > alpha) alpha = x; /// First player will maximize his score
        if (p == 1 && x < beta) beta = x; /// Second player will minimize his score
        if (alpha >= beta) break;
    }

    if (p == 0) return alpha;
    return beta;
}

int main(){
    struct node start;
    backtrack(start, 0, 0, -INF, INF);
    return 0;
}
