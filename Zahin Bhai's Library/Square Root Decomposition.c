#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LIM 50
#define MAX 10010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

bool islucky[MAX], start[100010];
int n, m, d, q, len = 0, lucky[100], ar[100010], pos[100010], add[LIM], counter[LIM][MAX];

int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

void backtrack(int i){
    if (i >= MAX) return;
    if (i){
        islucky[i] = true;
        lucky[len++] = i;
    }
    backtrack((i * 10) + 4);
    backtrack((i * 10) + 7);
}

void Generate(){
    int i, j, k, l;
    m = sqrt(0.5 + (n * len * 1.5));

    clr(add), clr(counter);
    for (i = 0, d = 0; i < n; i += m){
        start[i] = true;
        for (j = 0, k = i; j < m && k < n; j++, k++){
            pos[k] = d;
            counter[d][ar[k]]++;
        }
        d++;
    }
}

void update(int l, int r, int v){
    int i = l;
    while (i <= r) {
        int k = pos[i];
        if (start[i] && (i + m - 1) <= r){
            add[k] += v;
            i += m;
        }
        else{
            counter[k][ar[i]]--;
            ar[i] += v;
            counter[k][ar[i]]++;
            i++;
        }
    }
}

int count(int l, int r){
    int i = l, j = 0, res = 0;
    while (i <= r) {
        int k = pos[i];
        if (start[i] && (i + m - 1) <= r){
            for (j = len - 1; j >= 0; j--){
                int x = lucky[j] - add[k];
                if (x < 0) break;
                res += counter[k][x];
            }
            i += m;
        }
        else res += islucky[ar[i++] + add[k]];
    }
    return res;
}

int main(){
    backtrack(0);
    qsort(lucky, len, sizeof(int), compare);

    char str[15];
    int i, j, k, l, r, d, v;
    while (scanf("%d %d", &n, &q) != EOF){
        for (i = 0; i < n; i++) scanf("%d", &ar[i]);
        Generate();

        while (q--){
            scanf("%s %d %d", str, &l, &r);
            if (str[0] == 'c') printf("%d\n", count(--l, --r));
            else{
                scanf("%d", &v);
                update(--l, --r, v);
            }
        }
    }
    return 0;
}
