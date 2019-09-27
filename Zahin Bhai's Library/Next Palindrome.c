#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char str[MAX];

void next_palindrome(char* str){
    int i, j, k, l, x, n = strlen(str), carry = 1;
    for (i = 0, j = n - 1; j >= 0; i++, j--){
        if (carry){
            if (str[j] == 57) carry = 1, str[j] = 48;
            else carry = 0, str[j]++;
        }

        if (i > j) str[i] = str[j];
        else{
            if (str[i] < str[j]) carry = 1;
            str[j] = str[i];
        }
    }

    if (carry){
        str[n - 1] = 49;
        for (i = n - 1; i >= 0; i--) str[i + 1] = str[i];
        str[0] = 49, str[n + 1] = 0;
    }
}

int main(){
    int T = 0, t, i, j, k;

    scanf("%d", &t);
    while (t--){
        scanf("%s", str);
        next_palindrome(str);
        printf("Case %d: %s\n", ++T, str);
    }
    return 0;
}
