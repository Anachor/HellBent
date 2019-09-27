#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char str[MAX], pattern[MAX];
int fail[MAX], pos[MAX], T[MAX][26]; /*** T[i]['a'-'z'] = Length of matched pattern[0:i - 1] + char j ***/

void fail_function(char* str){
    int i, k;
    k = fail[0] = -1;

    for (i = 1; str[i]; i++){
        while (k >= 0 && (str[k + 1] != str[i])) k = fail[k];
        if (str[i] == str[k + 1]) k++;
        fail[i] = k;
    }
}

int count(char* str, char* pattern, int* pos){
    int i, k = 0, len = 0;
    fail_function(pattern);

    for (i = 0; str[i]; i++){
        while (k > 0 && str[i] != pattern[k]) k = fail[k - 1] + 1;
        if (pattern[k] == str[i]) k++;
        if (!pattern[k]){
            pos[len++] = (i - k + 1);
            k = fail[k - 1] + 1;
        }
    }

    return len;
}

void Generate(char* str){
    int i, j, k;
    fail_function(str);

    for (i = 0; str[i]; i++){
        for (j = 0; j < 26; j++){
            char ch = j + 'a';

            k = i;
            while (k > 0 && str[k] != ch) k = fail[k - 1] + 1;
            if (str[k] == ch) k++;
            T[i][j] = k;
        }
    }
}

int main(){
}
