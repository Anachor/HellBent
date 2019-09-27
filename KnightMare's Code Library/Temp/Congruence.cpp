/// This is a collection of useful code for solving problems that
/// involve modular linear equations. Note that all of the
/// algorithms described here work on NON-NEGATIVE INTEGERS.
/// Source: Stanford Notebook (modified)

#include <bits/stdc++.h>
#define LL long long
using namespace std;
typedef pair<LL, LL> PLL;


/// Computes gcd(a,b)
/// Range: LL
LL gcd(LL a, LL b) {
	while (b) { LL t = a%b; a = b; b = t; }
	return a;
}

/// computes lcm(a,b)
/// Range: int
LL lcm(LL a, LL b) {
	return (a/gcd(a, b))*b;
}

/// (a^b) mod m via successive squaring
/// Range: int
LL power(LL a, LL b, LL m) {
    a = (a%m+m)%m;
	LL ans = 1;
	while (b) {
		if (b & 1) ans = (ans*a)%m;
		a = (a*a)%m;
		b >>= 1;
	}
	return ans;
}

/// returns g = gcd(a, b); finds x, y such that d = ax + by
/// Range: int (tested on CF 982E :( )
LL egcd(LL a, LL b, LL &x, LL &y) {
	LL xx = y = 0;
	LL yy = x = 1;
	while (b) {
		LL q = a/b;
		LL t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

/// finds all solutions to ax = b (mod m)
/// Range: int (not tested)
vector<LL> SolveCongruence(LL a, LL b, LL m) {
	LL x, y;
	vector<LL> ans;
	LL g = egcd(a, m, x, y);
	if (b%g == 0) {
		x = (x*(b/g))%m;
		if (x<0)    x+=m;
		for (LL i=0; i<g; i++) {
			ans.push_back(x);
			x = (x+m/g)%m;
		}
	}
	return ans;
}

/// Computes b such that ab = 1 (mod m), returns -1 on failure
/// Range: int
LL inverse(LL a, LL m) {
	LL x, y;
	LL g = egcd(a, m, x, y);
	if (g > 1) return -1;
	return (x%m+m)%m;
}

/// Chinese remainder theorem (special case):
/// find z such that z % m1 = r1, z % m2 = r2.
/// Here, z is unique modulo M = lcm(m1, m2).
/// Return (z, M).  On failure, M = -1.
/// Range: int (tested on CF 982E :( )
PLL CRT(LL m1, LL r1, LL m2, LL r2) {
	LL s, t;
	LL g = egcd(m1, m2, s, t);
	if (r1%g != r2%g) return PLL(0, -1);
	LL M = m1*m2;
	LL ss = ((s*r2)%m2)*m1;
	LL tt = ((t*r1)%m1)*m2;
	LL ans = ((ss+tt)%M+M)%M;
	return PLL(ans/g, M/g);
}


/// Chinese remainder theorem:
/// find z such that z % m[i] = r[i] for all i.
/// The solution is unique modulo M = lcm(m[i]).
/// Return (z, M). On failure, M = -1.
/// Note that we do not require the mod values to be co-prime.
/// Range: int (if LCM fits in LL)
PLL CRT(const vector<LL> &m, const vector<LL> &r) {
	PLL ans = PLL(r[0], m[0]);
	for (LL i = 1; i < m.size(); i++) {
		ans = CRT(ans.second, ans.first, m[i], r[i]);
		if (ans.second == -1) break;
	}
	return ans;
}

/// computes x and y such that ax + by = c
/// returns whether the solution exists
/// Range: int
bool LinearDiophantine(LL a, LL b, LL c, LL &x, LL &y) {
	if (!a && !b) {
		if (c) return false;
		x = y = 0;
		return true;
	}
	if (!a) {
		if (c%b) return false;
		x = 0; y = c/b;
		return true;
	}
	if (!b) {
		if (c%a) return false;
		x = c/a; y = 0;
		return true;
	}
	LL g = gcd(a, b);
	if (c%g) return false;
	x = c/g * inverse(a/g, b/g);
	y = (c-a*x)/b;
	return true;
}

int main() {
	// expected: 2
	cout << gcd(14, 30) << endl;

	// expected: 2 -2 1
	LL x, y;
	LL g = egcd(14, 30, x, y);
	cout << g << " " << x << " " << y << endl;

	// expected: 95 45
    vector<long long> sols = SolveCongruence(14, 30, 100);
	for (LL i = 0; i < sols.size(); i++) cout << sols[i] << " ";
	cout << endl;

	// expected: 8
	cout << inverse(8, 9) << endl;

	// expected: 23 105
	//           11 12
	PLL ans = CRT({3,5,7}, {2,3,2});
	cout << ans.first << " " << ans.second << endl;
	ans = CRT({4,6}, {3,5});
	cout << ans.first << " " << ans.second << endl;

	// expected: 5 -15
	if (!LinearDiophantine(7, 2, 5, x, y)) cout << "ERROR" << endl;
	else cout << x << " " << y << endl;
	return 0;
}
