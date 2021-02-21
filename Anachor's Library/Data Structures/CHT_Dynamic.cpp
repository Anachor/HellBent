#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

///convex hull for maximizing
///in case of minimization, just insert(-m,-c) and negate the result for query

bool Q;
struct Line {
	mutable ll m, c, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : m < o.m;
	}
};

struct LineContainer : multiset<Line> {
	const ll inf = LLONG_MAX;   ///for doubles, use inf = 1/.0, div(a,b) = a/b
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } /// floored division

	bool isect(iterator x, iterator y) {
		if (y == end())     { x->p = inf; return false; }
		if (x->m == y->m)   x->p = x->c > y->c ? inf : -inf;
		else                x->p = div(y->c - x->c, x->m - y->m);
		return x->p >= y->p;
	}
	void addLine(ll m, ll c) {
		auto z = insert({m, c, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y))   isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)  isect(x, erase(y));
	}
	ll query(ll x) {
		if (empty())        return -inf;
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.m * x + l.c;
	}
}ch;


/// Solves https://old.yosupo.jp/problem/line_add_get_min
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    for (int i=0; i<n; i++) {
        long long x, y;
        cin>>x>>y;
        ch.addLine(-x, -y);
    }

    for (int i=0; i<q; i++) {
        long long t, x, y;
        cin>>t;

        if (!t) {
            cin>>x>>y;
            ch.addLine(-x, -y);
        }
        else {
            cin>>x;
            cout<<-ch.query(x)<<"\n";
        }
    }
}
