#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const double A = 4.0 * acos(0.0);
const double B = log10(exp(1.0));

long long digfact(long long n){
    if (n == 0 || n == 1) return 1;
    double x = ((0.5 * log(A * n)) + (n * log(n)) - n) * B;
    return ceil(x);
}

int main(){
    int t;
    long long n;

    scanf("%d", &t);
    while (t--){
        scanf("%lld", &n);
        printf("%lld\n", digfact(n));
    }
    return 0;
}
