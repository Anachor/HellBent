#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 2010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n, ar[MAX];

/*** Largest area in a histogram ***/
/*** Be careful, long long might be required ***/

int histogram(int n, int* ar){
    int i = 0, j, a, x, top = 0, res = 0;

    stack[0] = -1;
    while (i < n){
        if (!top || (ar[stack[top]] <= ar[i]) ) stack[++top] = i++;
        else{
            x = stack[top--];
            a = ar[x] * (i - stack[top] - 1);
            if (a > res) res = a;
        }
    }

    while (top){
        x = stack[top--];
        a = ar[x] * (i - stack[top] - 1);
        if (a > res) res = a;
    }

    return res;
}

int main(){

}
