#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

struct Point{
    int idx, x, y, d;
    double theta;
};

int n;
struct Point ar[2010];
double centre_x, centre_y;

int compare(const void* a, const void* b){
    struct Point P1 = *(struct Point*)a;
    struct Point P2 = *(struct Point*)b;

    if (fabs(P1.theta - P2.theta) <= 1e-9){
        double d1 = ((centre_x - P1.x) * (centre_x - P1.x)) + ((centre_y - P1.y) + (centre_y - P1.y));
        double d2 = ((centre_x - P2.x) * (centre_x - P2.x)) + ((centre_y - P2.y) + (centre_y - P2.y));
        if (fabs(d1 - d2) <= 1e-9) return 0;
        else if (d1 < d2) return -1;
        else return +1;
    }
    else if (P1.theta < P2.theta) return +1;
    else return -1;
}

int main(){
    int t, line, i, j;

    scanf("%d", &t);
    for (line = 1; line <= t; line++){
        scanf("%d", &n);
        centre_x = 0.0, centre_y = 0.0;

        for (i = 0; i < n; i++){
            scanf("%d %d", &ar[i].x, &ar[i].y);
            ar[i].idx = i;
            centre_x += ar[i].x;
            centre_y += ar[i].y;
        }

        centre_x /= (1.0 * n), centre_y /= (1.0 * n);
        for (i = 0; i < n; i++) ar[i].theta = atan2((double)ar[i].y - centre_y, (double)ar[i].x - centre_x);
        qsort(ar, n, sizeof(struct Point), compare);

        for (i = 0; i < n; i++){
            if (i != 0) putchar(32);
            printf("%d", ar[i].idx);
        }
        puts("");
    }
    return 0;
}
