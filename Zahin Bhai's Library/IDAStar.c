#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int ida(int g, int lim, int l, int last, int idx){ /// last = last taken move, don't go there!
    int h = heuristic(l);
    if (!h){ /// Goal reached
        sequence[idx] = 0;
        puts(sequence);
        return g;
    }

    int f = g + h;
    if (f > lim) return f;
    int i, j, res = inf;
    for (i = 0; i < 12; i++){
        if (dis[l][i] == 1 && i != last){
            sequence[idx] = str[i];
            swap(str[l], str[i]);
            int x = ida(g + 1, lim, i, l, idx + 1);
            if (x < res) res = x; /// Update next limit in iterative deepening
            swap(str[l], str[i]);
            if (res <= lim) return res; /// Since iterative deepening, return if solution found
        }
    }
    return res;
}

int Solve(int l){
    int lim = heuristic(l);
    for (; ;){
        int nlim = ida(0, lim, l, l, 0);
        if (nlim <= lim) return nlim;
        else lim = nlim;
    }
    return -1;
}
