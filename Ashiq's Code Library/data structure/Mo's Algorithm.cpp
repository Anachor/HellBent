/// Mo's Algorithm Template
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 3e5 + 100, BLOCK = 600;

struct Query {
    int l , r , id;
    bool operator <(const Query &p) const{
		int a = l/BLOCK, b = p.l/BLOCK;
		return a == b ? r < p.r : a < b;
	}
}Q[N];

void add (int idx) {}
void del (int idx) {}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q; cin >> q;
    for (int i = 1 ; i <= q ; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].id = i;
    }
    sort (Q+1,Q+1+q);
    int l = 1, r = 0;
    for (int i = 1 ; i <= q ; i++) {
        int ql = Q[i].l, qr = Q[i].r, id = Q[i].id;
        while (l < ql) del(l++);
        while (l > ql) add(--l);
        while (r > qr) del(r--);
        while (r < qr) add(++r);
    }
    return 0;
}
