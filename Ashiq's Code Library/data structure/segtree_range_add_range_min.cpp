#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 100;


/**
    1) Add X in a range
    2) query for min in a range

**/

long long inf = 1e18;
long long tr[4*N], lz[4*N];

void propagate(int u, int st, int en) {
    if (!lz[u]) return;
    tr[u] += lz[u];
    if (st!=en) {
        lz[2*u] += lz[u];
        lz[2*u+1] += lz[u];
    }
    lz[u] = 0;
}

void update(int u, int st, int en, int l, int r, long long x) {
    propagate(u, st, en);
    if (r<st || en<l)  return;
    else if (l<=st && en<=r) {
        lz[u] += x;
        propagate(u, st, en);
    }
    else {
        int mid = (st+en)/2;
        update(2*u, st, mid, l, r, x);
        update(2*u+1, mid+1, en, l, r, x);
        tr[u] = min(tr[2*u], tr[2*u+1]);
    }
}

long long query(int u, int st, int en, int l, int r) {
    propagate(u, st, en);
    if (r<st || en<l)  return inf;
    else if (l<=st && en<=r) return tr[u];
    else {
        int mid = (st+en)/2;
        return min(query(2*u, st, mid, l, r), query(2*u+1, mid+1, en, l, r));
    }
}

int main() {

}
