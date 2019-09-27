#include <stdio.h>

int n, lim, counter;

void backtrack(int i, int c, int l, int r){
    if (!i){
        counter++;
        return;
    }

    int bitmask, x;
    --i, bitmask = lim & ~(l | r | c);

    while (bitmask){
        x = (-bitmask & bitmask);
        if (!x) return;
        bitmask ^= x;
        backtrack(i, c | x, (l | x) << 1, (r | x) >> 1);
    }
}

int main(){
    while (scanf("%d", &n)){
        counter = 0, lim = (1 << n) - 1;
        backtrack(n, 0, 0, 0);
        printf("%d solutions for a %d x %d chessboard\n", counter, n, n);
    }
    return 0;
}
