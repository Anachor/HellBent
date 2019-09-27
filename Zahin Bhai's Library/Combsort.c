#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n, ar[MAX];

void combsort(int n, int* ar){
    if (n <= 1) return;
    int i, j, x, g = n, flag = 0;
    while ((g != 1) || flag){
        flag = 0;
        if (g != 1) g *= 0.77425;

        for (i = 0; (i + g) < n; i++){
            if (ar[i] > ar[i + g]){
                flag = 1;
                x = ar[i], ar[i] = ar[i + g], ar[i + g] = x;
            }
        }
    }
}

int main(){
    int i, j;
    n = MAX - 10;
    for (i = 0; i < n; i++) ar[i] = (rand() << 15 ^ rand()) % MAX;

    combsort(n, ar);
    for (i = 0; (i + 1) < n; i++){
        if (ar[i] > ar[i + 1]) puts("fail");
    }
    return 0;
}
