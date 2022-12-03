///Author: anachor, Stanford Notebook, YouKnowWho
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> PLL;

inline LL modit(LL x, LL m) {
	LL z = x%m; return z<0 ? z+m : z;
}

LL gcd(LL u, LL v) {
    if (u == 0) return v;
    if (v == 0) return u;
    int shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) swap(u, v);
        v = v-u;
    } while (v);
    return u << shift;
}

/// (a^b) mod m via successive squaring
LL power(LL a, LL b, LL m) {
    a = modit(a, m);
	LL ans = 1;
	while (b) {
		if (b & 1) ans = (ans*a)%m;
		a = (a*a)%m;
		b >>= 1;
	}
	return ans;
}

/// returns g = gcd(a, b); finds x, y such that d = ax+by
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
/// Computes b such that ab = 1 (mod m), returns -1 on failure
LL inverse(LL a, LL m) {
	LL x, y;
	LL g = egcd(a, m, x, y);
	if (g > 1) return -1;
	return modit(x, m);
}

/// Chinese remainder theorem (special case): find z st z%m1 = r1, z%m2 = r2.
/// z is unique modulo M = lcm(m1, m2). Returns (z, M). On failure, M = -1.
PLL CRT(LL m1, LL r1, LL m2, LL r2) {
	LL s, t;
	LL g = egcd(m1, m2, s, t);
	if (r1%g != r2%g) return PLL(0, -1);
	LL M = m1*m2;
	LL ss = ((s*r2)%m2)*m1;
	LL tt = ((t*r1)%m1)*m2;
	LL ans = modit(ss+tt, M);
	return PLL(ans/g, M/g);
}

/// returns (c, d) where x = c (mod d) equiv ax = b (mod m)
///  if no solution, returns (-1, -1)
pair<LL, LL> SolveCongruence(LL a, LL b, LL m) {
	LL x, y;
	LL g = egcd(a, m, x, y);
	if (b%g == 0) {
        LL d = m/g;
		x = modit(x*(b/g), d);
		return {x, d};
	}
	return {-1, -1};
}


///computes x and y such that ax+by = c, returns whether the solution exists
bool LinearDiophantine(LL a, LL b, LL c, LL &x, LL &y) {
	if (!a && !b) {
		if (c)          return false;
		x = y = 0;      return true;
	}
	if (!a) {
		if (c%b)        return false;
		x = 0; y = c/b; return true;
	}
	if (!b) {
		if (c%a)        return false;
		x = c/a; y = 0; return true;
	}
	LL g = gcd(a, b);
	if (c%g) return false;
	x = c/g*inverse(a/g, b/g);
	y = (c-a*x)/b;
	return true;
}


/// Find smallest primitive root of p assuming p is prime.
/// if not, change phi to phi(p);
/// Possible optimization, generate primes and factorize using only primes
LL primitive_root(LL p) {
    if (p == 2) return 1;
    LL phi = p-1, n = phi;

    vector<LL> factor;
    for (int i=2; i*i<=n; ++i)
        if (n%i == 0) {
            factor.push_back (i);
            while (n%i==0)  n/=i;
        }

    if (n>1)  factor.push_back(n);
    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (int i=0; i<factor.size() && ok; ++i)
            ok &= power(res, phi/factor[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

/// Tested in https://old.yosupo.jp/problem/discrete_logarithm_mod
/// Returns minimum non-negative  st a^x = b (mod m), -1 on failure
int discreteLog(int a, int b, int M) {
    a %= M, b %= M;
    int k = 1, add = 0, g;
    while ((g = gcd(a, M)) > 1) {
        if (b == k)     return add;
        if (b%g)      return -1;
        b/=g, M/=g, ++add;
        k = (1LL*k*a/g)%M;
    }

    int RT = sqrt(M)+1, aRT = 1;
    for (int i=0; i<RT; i++) aRT = (aRT*1LL*a)%M;

    ///Change to gp_hash_table or other hashtable for speed
    unordered_map<int, int> vals;
    for (int i=0, cur=b; i<=RT; i++) {
        vals[cur] = i;
        cur = (cur*1LL*a)%M;
    }

    for (int i=1, cur=k; i<=M/RT+1; i++) {
        cur = (cur*1LL*aRT)%M;
        if (vals.find(cur) != vals.end())    return RT*i-vals[cur]+add;
    }
    return -1;
}

/// Tested in https://old.yosupo.jp/problem/kth_root_mod
/// Returns x0 st x^a = b (mod P), -1 on failure, P must be prime
int discreteRoot(int a, int b, int P) {
    if (b%P == 0)     return    a == 0 ? -1 : 0;
    int g = primitive_root(P);
    int y = discreteLog(power(g, a, P), b, P);
    return y == -1 ? -1 : power(g, y, P);
}


// Tonnelli Shanks: finds x st x^2 = a (mod p)
// p must be prime. returns -1 if none. 
// complexity: O(log^2 p) worst case, O(log p) on average

int SQRT(int a, int p) {
	a = modit(a, p);
	if (a == 0) return 0;
	if (power(a, (p-1)/2, p) != 1)  return -1; 	
	if (p%4==3) 					return power(a, (p+1)/4, p);
	int s = p-1, n = 2;
	int r = 0, m;
	while (s%2 == 0) ++r, s/=2;
	// find a non-square mod p
	while (power(n, (p-1)/2, p) != p-1) ++n;
	int x = power(a, (s+1)/2, p);
	int b = power(a, s, p), g = power(n, s, p);
	for (;; r = m) {
		int t = b;
		for (m = 0; m<r && t!=1; ++m) t = 1LL*t*t%p;
		if (m == 0) return x;
		int gs = power(g, 1LL << (r-m-1), p);
		g = 1LL*gs*gs%p;
		x = 1LL*x*gs%p;
		b = 1LL*b*g%p;
	}
}

int main() {
	// expected: 2
	cout << gcd(14, 30) << endl;

	// expected: 2 -2 1
	LL x, y;
	LL g = egcd(14, 30, x, y);
	cout << g << " " << x << " " << y << endl;

	// expected: 45 50
    auto sols = SolveCongruence(14, 30, 100);
	cout << sols.first<<" "<<sols.second << endl;

	// expected: 8
	cout << inverse(8, 9) << endl;

	// expected: 43 45
	auto ans = CRT(9, 7, 15, 13);
	cout << ans.first << " " << ans.second << endl;

	// expected: 5 -15
	if (!LinearDiophantine(7, 2, 5, x, y)) cout << "ERROR" << endl;
	else cout << x << " " << y << endl;

	// expected: 2 4 -1
	cout<<SQRT(4, 7)<<" "<<SQRT(9, 7)<<" "<<SQRT(6, 11)<<endl;

	return 0;
}
