#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int base = 0, mp[256];
char digit[256], str[256], temp[256];

void Generate(){
    int i;
    for (i = 32; i < 127; i++){
        if (i == 32 || i == 34 || i == 39 || i == 44 || i == 92) continue;

        digit[base] = i;
        mp[i] = base;
        base++;
    }
    digit[base] = 0;
}

void encode(char* str, int v){
    int i, j, k = 0, l = 0;
    do{
        temp[k++] = digit[v % base];
        v /= base;
    } while (v);

    for (i = k - 1; i >= 0; i--) str[l++] = temp[i];
    str[l] = 0;
}

int decode(char* str){
    int i, v = 0;
    for (i = 0; str[i]; i++) v = (v * base) + mp[str[i]];
    return v;
}

int main(){
    read();
    Generate();
    encode(str, 12345);
    printf("%d\n", decode(str));
    return 0;
}
