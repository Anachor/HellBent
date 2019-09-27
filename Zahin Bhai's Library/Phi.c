#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 4000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int phi[MAX];

void Totient(){
    clr(phi);
    int i, j, x;

    for (i = 1; i < MAX; i++){
        phi[i] += i;
        for (j = (i << 1); j < MAX; j += i){
            phi[j] -= phi[i];
        }
    }
}

int main(){
    Totient();
}
