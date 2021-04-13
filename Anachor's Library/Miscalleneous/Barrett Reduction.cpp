#include <bits/stdc++.h>
using namespace std;

struct FastMod {
    typedef unsigned long long ull;
	ull M, m;
	FastMod(ull M) : M(M), m(-1ULL / M) {}
	ull reduce(ull a) { // a % M + (0 or M)
		return a - (ull)((__uint128_t(m) * a) >> 64) * M;
	}
	ull mul(ull x, ull y) {
        ull r = F.reduce(1ll*x*y);
        if(r >= M) r -= M;
        return r;
    }
};


int main() {
    cin >> mod;
    F = FastMod(mod);
}
