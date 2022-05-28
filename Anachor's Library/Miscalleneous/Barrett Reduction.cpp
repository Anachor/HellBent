///Source: Folklore
#include <bits/stdc++.h>
using namespace std;

struct FastMod {
    typedef unsigned long long ull;
	ull M, m;
	FastMod(ull M) : M(M), m(-1ULL / M) {}
	ull reduce(ull a) { // a % M + (0 or M)
		ull ans = a - (ull)((__uint128_t(m) * a) >> 64) * M;
		if (ans >= M)   ans -= M;
		return ans;
	}
} F(2);


int main() {
    cin >> mod;
    F = FastMod(mod);
}
