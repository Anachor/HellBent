#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define clr(ar) (memset(ar, 0, sizeof(ar)))
#define read() freopen("lol.txt", "r", stdin)

bool visited[MAX];
int t, line, n, m, ar[MAX][MAX], adj[MAX][MAX], left[MAX], right[MAX], len[MAX];

bool bipartite_matching(int u){
    int v = 0, j = 0;
    for (j = 0; j < len[u]; j++){
        v = adj[u][j];
        if (visited[v]) continue;
        visited[v] = true;

        if (right[v] == -1 || bipartite_matching(right[v])){
            left[u] = v;
            right[v] = u;
            return true;
        }
    }
    return false;
}

int max_matching(){
    memset(left, -1, sizeof(left));
    memset(right, -1, sizeof(right));

    int i, counter = 0;
    for (i = 0; i < n; i++){
        clr(visited);
        if (bipartite_matching(i)) counter++;
    }
    return counter;
}

int main(){
    int a, b;
    while (scanf("%d %d", &n, &m) != EOF){
        clr(len);
        while (m--){
            scanf("%d %d", &a, &b);
            adj[a][len[a]++] = b;
        }
    }
    return 0;
}
