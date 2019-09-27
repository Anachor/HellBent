/// union of N <= 50 circle and their individual area
/// https://codeforces.com/gym/100941/attachments/download/4189/20082009-summer-petrozavodsk-camp-petrozavodsk-su-wx-contest-en.pdf
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); ++i)
#define forn(i, n) fore(i, 0, n)
#define fori(i, l, r) fore(i, l, int(r) + 1)

#define ifor(i, l, r) for(int i = int(r); i >= int(l); --i)
#define efor(i, l, r) ifor(i, l, int(r) - 1)
#define nfor(i, n) efor(i, 0, n)

#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define x first
#define y second

template<typename T> inline T abs(T a){ return ((a < 0) ? -a : a); }
template<typename T> inline T sqr(T a){ return a * a; }

template <typename T1, typename T2>
ostream& operator <<(ostream& out, const pair<T1, T2>& p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

typedef long long li;
typedef long double ld;

#ifdef KUVIMAN
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

bool solve(int);

ld getTime() {
	return clock() / ld(CLOCKS_PER_SEC);
}

int main() {
#ifdef KUVIMAN
	assert(freopen("input.txt", "r", stdin));
#else
	assert(freopen("runes.in", "r", stdin));
	assert(freopen("runes.out", "w", stdout));
#endif

	cout << fixed << setprecision(10);
	cerr << fixed << setprecision(3);

#ifdef KUVIMAN
	ld st = getTime();
#endif
	int test = 0;
	while (solve(test)) {
		++test;
#ifdef KUVIMAN
		ld ct = getTime();
		cerr << " == TIME : " << ct - st << " == " << endl;
		st = ct;
#endif
	}
	return 0;
}

// == TEMPLATE END ==

template <typename T1, typename T2>
auto max(const T1& a, const T2& b) -> decltype(true ? a : b) {
	return a > b ? a : b;
}
template <typename T1, typename T2>
auto min(const T1& a, const T2& b) -> decltype(true ? a : b) {
	return a < b ? a : b;
}

const ld EPS = 1e-8;
bool eqEps(ld a, ld b) {
	return abs(a - b) < EPS;
}

typedef pair<ld, ld> pt;
pt operator -(const pt& a, const pt& b) {
	return pt(a.x - b.x, a.y - b.y);
}
pt operator +(const pt& a, const pt& b) {
	return pt(a.x + b.x, a.y + b.y);
}
pt operator *(const pt& v, const ld& k) {
	return pt(v.x * k, v.y * k);
}
pt operator *(const ld& k, const pt& v) {
	return pt(k * v.x, k * v.y);
}
pt operator /(const pt& v, const ld& k) {
	return pt(v.x / k, v.y / k);
}
ld dot(const pt& a, const pt& b) {
	return a.x * b.x + a.y * b.y;
}
ld cross(const pt& a, const pt& b) {
	return a.x * b.y - a.y * b.x;
}
ld len2(const pt& v) {
	return dot(v, v);
}
ld len(const pt& v) {
	return sqrtl(len2(v));
}
pt rotate(const pt& v, const ld& sn, const ld& cs) {
	return pt(v.x * cs - v.y * sn, v.x * sn + v.y * cs);
}
pt norm(const pt& v) {
	return v / len(v);
}

vector<pt> intersect(const pair<pt,ld>& a, const pair<pt,ld>& b) {
	ld d = len(b.x - a.x);
	if (d < EPS)
		return vector<pt>();
	ld cs = (sqr(d) + sqr(a.y) - sqr(b.y)) / (2 * d * a.y);
	if (cs < -1 - EPS || cs > 1 + EPS)
		return vector<pt>();
	ld sn = sqrtl(max(0, 1 - sqr(cs)));
	vector<pt> res;
	pt v = norm(b.x - a.x) * a.y;
	res.pb(a.x + rotate(v, sn, cs));
	res.pb(a.x + rotate(v, -sn, cs));
	return res;
}

struct Event {
	ld y1, y2;
	bool down;
	pt c;
	ld r;
	Event(ld x1, ld x2, const pair<pt,ld>& c, bool down) {
		y1 = sqrtl(max(0, sqr(c.y) - sqr(x1 - c.x.x)));
		y2 = sqrtl(max(0, sqr(c.y) - sqr(x2 - c.x.x)));
		if (down) {
			y1 = -y1;
			y2 = -y2;
		}
		y1 += c.x.y;
		y2 += c.x.y;
		this->down = down;
		this->c = c.x;
		r = c.y;
	}
	Event(ld y) : y1(y), y2(y) {}
};

ld area(ld x1, ld x2, const Event& e) {
	ld res = (x2 - x1) * (e.y1 + e.y2) / 2;
	ld cs = dot(norm(pt(x1, e.y1) - e.c), norm(pt(x2, e.y2) - e.c));
	cs = max(-1, min(1, cs));
	ld sector = sqr(e.r) * acosl(cs) / 2 - abs(cross(pt(x1, e.y1) - e.c, pt(x2, e.y2) - e.c)) / 2;
	if (e.down)
		res -= sector;
	else
		res += sector;
	return res;
}

bool operator <(const Event& a, const Event& b) {
	if (abs(a.y1 - b.y1) > EPS)
		return a.y1 < b.y1;
	if (abs(a.y2 - b.y2) > EPS)
		return a.y2 < b.y2;
	if (a.down != b.down)
		return a.down;
	return (a.r > b.r) != a.down;
}
bool cmpY1(const Event& a, const Event& b) {
	return a.y1 < b.y1;
}
bool cmpY2(const Event& a, const Event& b) {
	return a.y2 < b.y2;
}

typedef pair<int,int> pti;
map<pti,pti> dsu;
pti root(pti v) {
	if (dsu.count(v) == 0)
		dsu[v] = v;
	if (dsu[v] == v) return v;
	return dsu[v] = root(dsu[v]);
}

bool solve(int) {
	int n;
	if (scanf("%d", &n) != 1)
		return false;
	vector<pair<pt,ld>> circles(n);
	forn(i, n) {
		int x, y, r;
		assert(scanf("%d%d%d", &x, &y, &r) == 3);
		circles[i] = mp(pt(x, y), r);
	}
	sort(all(circles));
	circles.erase(unique(all(circles)), circles.end());

	circles.pb(mp(pt(0, 0), 1e4));

	vector<ld> xs;
	for (auto c1 : circles) {
		xs.pb(c1.x.x - c1.y);
		xs.pb(c1.x.x + c1.y);
		for (auto c2 : circles) {
			auto inters = intersect(c1, c2);
			for (auto p : inters)
				xs.pb(p.x);
		}
	}
	sort(all(xs));
	xs.erase(unique(all(xs), eqEps), xs.end());

	vector<vector<Event>> evs(sz(xs) - 1);
	forn(i, sz(evs)) {
		ld x1 = xs[i], x2 = xs[i + 1];
		for (auto c : circles) {
			if (min(x1, x2) + EPS >= c.x.x - c.y && max(x1, x2) <= c.x.x + c.y + EPS) {
				evs[i].pb(Event(x1, x2, c, true));
				evs[i].pb(Event(x1, x2, c, false));
			}
		}
		sort(all(evs[i]));
	}

	dsu.clear();
	forn(i, sz(evs) - 1) {
		vector<ld> ys;
		for (auto e : evs[i])
			ys.pb(e.y2);
		for (auto e : evs[i + 1])
			ys.pb(e.y1);
		sort(all(ys));
		ys.erase(unique(all(ys), eqEps), ys.end());

		forn(j, sz(ys) - 1) {
			ld y = (ys[j] + ys[j + 1]) / 2;
			int id1 = int(upper_bound(all(evs[i]), Event(y), cmpY2) - evs[i].begin());
			int id2 = int(upper_bound(all(evs[i + 1]), Event(y), cmpY1) - evs[i + 1].begin());
			pti a = root(pti(i, id1));
			pti b = root(pti(i + 1, id2));
			if (a == b)
				continue;
			if (rand() & 1)
				swap(a, b);
			dsu[a] = b;
//			cerr << "MERGE " << a << ' ' << b << endl;
		}
	}

	map<pti,ld> ansq;
	forn(i, sz(evs)) {
		ld x1 = xs[i], x2 = xs[i + 1];
		ld prev = area(x1, x2, evs[i][0]);
		fore(j, 1, sz(evs[i])) {
			ld cur = area(x1, x2, evs[i][j]);
//			cerr << i << ' ' << j << " = " << cur - prev << endl;
			ansq[root(pti(i, j))] += cur - prev;
			prev = cur;
		}
	}

	vector<ld> ans;
	for (auto it : ansq) {
		if (it.x == root(pt(0, 1)))
			continue;
		if (it.y < 1e-4)
			continue;
		ans.pb(it.y);
	}

	sort(all(ans));

	printf("%d\n", sz(ans));
	forn(i, sz(ans)) {
		if (i) putchar(' ');
		printf("%.10f", double(ans[i]));
	}
	puts("");

	return true;
}
