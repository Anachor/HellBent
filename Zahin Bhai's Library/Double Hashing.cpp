#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct simplehash{
    int len;
    long long base, mod;
    vector <int> P, H, R;

    simplehash(){}
    simplehash(const char* str, long long b, long long m){
        base = b, mod = m, len = strlen(str);
        P.resize(len + 3, 1), H.resize(len + 3, 0), R.resize(len + 3, 0);

        for (int i = 1; i <= len; i++) P[i] = (P[i - 1] * base) % mod;
        for (int i = 1; i <= len; i++) H[i] = (H[i - 1] * base + str[i - 1] + 1007) % mod;
        for (int i = len; i >= 1; i--) R[i] = (R[i + 1] * base + str[i - 1] + 1007) % mod;
    }

    inline int range_hash(int l, int r){
        int hashval = H[r + 1] - ((long long)P[r - l + 1] * H[l] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }

    inline int reverse_hash(int l, int r){;
        int hashval = R[l + 1] - ((long long)P[r - l + 1] * R[r + 2] % mod);
        return (hashval < 0 ? hashval + mod : hashval);
    }
};

struct stringhash{
    simplehash sh1, sh2;
    stringhash(){}
    stringhash(const char* str){
        sh1 = simplehash(str, 1949313259, 2091573227);
        sh2 = simplehash(str, 1997293877, 2117566807);
    }

    inline long long range_hash(int l, int r){
        return ((long long)sh1.range_hash(l, r) << 32) ^ sh2.range_hash(l, r);
    }

    inline long long reverse_hash(int l, int r){
        return ((long long)sh1.reverse_hash(l, r) << 32) ^ sh2.reverse_hash(l, r);
    }
};

int main(){

}
