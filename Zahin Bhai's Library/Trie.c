#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LET 26
#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int r, idx, counter[MAX], trie[MAX][LET];

void initialize(){
    int i;
    r = 0, idx = 1, counter[r] = 0;
    for (i = 0; i < LET; i++) trie[r][i] = 0;
}

void insert(int x){ /// Set r = 0 before inserting first character
    int i, j;
    if (!trie[r][x]){
        trie[r][x] = idx;
        r = idx++;
        for (i = 0, counter[r] = 1; i < LET; i++) trie[r][i] = 0;
    }
    else r = trie[r][x], counter[r]++;
}

int main(){
    int i, j, x;
    initialize();
    char str[1010];

    while (scanf("%s", str) != EOF){
        r = 0; /// r = root = 0
        for (j = 0; str[j] != 0; j++){
            x = str[j] - 'a';
            insert(x);
        }
    }
    return 0;
}
