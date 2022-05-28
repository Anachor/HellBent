#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define CHUNK 8
#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n;
unsigned int bucket[1 << CHUNK], ar[MAX + 10], temp[MAX + 10];

void radix_sort(unsigned int* ar, int n){
    int i, j, x;
    const int bitmask = (1 << CHUNK) - 1;

    for (i = 0; i < 32; i += CHUNK){
        clr(bucket);
        for (j = 0; j < n; j++) bucket[(ar[j] >> i) & bitmask]++;
        for (j = 1; j <= bitmask; j++){
            bucket[j] += bucket[j - 1];
        }

        for (j = n - 1; j >= 0; j--) temp[--bucket[(ar[j] >> i) & bitmask]] = ar[j];
        for (j = 0; j < n; j++) ar[j] = temp[j];
    }
}

int main(){
    n = MAX;
    srand(time(0));
    int i, j, k, x, y;

    for (i = 0; i < n; i++) ar[i] = (rand() * rand());
    clock_t start = clock();
    radix_sort(ar, n);
    for (i = 0; (i + 1) < n; i++){
        if (ar[i] > ar[i + 1]) puts("YO");
    }
    printf("%0.5f s\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
