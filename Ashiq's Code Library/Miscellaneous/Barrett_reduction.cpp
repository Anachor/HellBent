// http://www.usaco.org/index.php?page=viewproblem2&cpid=1045

#include <bits/stdc++.h>
using namespace std;


typedef unsigned long long ull;

struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
}F(2);

int mod;

inline int mul(int x, int y) {
    int r = F.reduce(1ll*x*y);
    if(r >= mod) r -= mod;
    return r;
}


int main() {
    cin >> mod;
    F = FastMod(mod);
}
