#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Calculate hash of certain codes. Useful in validating codes copied during onsite contest.
unsigned long long code_hash(int MOD = 1000003, int BASE = 1000000007){
    freopen("copy.txt", "r", stdin);

    char str[1010];
    unsigned long long h = 0;

    while (scanf("%s", str) != EOF){
        int l = strlen(str);
        for (int j = 0; str[j]; j++){
            h = ((h * BASE) + str[j]) % MOD;
            assert(! ((j + 1) < l && str[j] == '/' && str[j + 1] == '/') ); /// Checking whether comments are removed
            assert(! ((j + 1) < l && str[j] == '/' && str[j + 1] == '*') ); /// Checking whether comments are removed
        }
    }
    return h;
}

int main(){
    printf("/// hash = %llu\n", code_hash());
    return 0;
}
