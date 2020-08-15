/**
  Solves SPOJ HORRIBLE - Horrible Queries
  Range Increment Update, Range Sum Query
**/

#include <bits/stdc++.h>
#define LL long long
using namespace std;

const int N = 1e5+7;
int a[N];
LL tr[4*N];
LL lz[4*N];

///1. Merge left and right
LL combine (LL left, LL right) {
    return left + right;
}

///2. Push lazy down and merge lazy
void propagate(int u, int st, int en) {
    tr[u] += (en-st+1)*lz[u];
    if (st!=en) {
        lz[2*u] += lz[u];
        lz[2*u+1] += lz[u];
    }
    lz[u] = 0;
}


void build(int u, int st, int en) {
    if (st==en) {
        tr[u] = a[st];          ///3. Initialize
        lz[u] = 0;
    }
    else {
        int mid = (st+en)/2;
        build(2*u, st, mid);
        build(2*u+1, mid+1, en);
        tr[u] = combine(tr[2*u], tr[2*u+1]);
        lz[u] = 0;              ///3. Initialize
    }
}

void update(int u, int st, int en, int l, int r, int x) {
    propagate(u, st, en);
    if (r<st || en<l)  return;
    else if (l<=st && en<=r) {
        lz[u] += x;             ///4. Merge lazy
        propagate(u, st, en);
    }
    else {
        int mid = (st+en)/2;
        update(2*u, st, mid, l, r, x);
        update(2*u+1, mid+1, en, l, r, x);
        tr[u] = combine(tr[2*u], tr[2*u+1]);
    }
}

LL query(int u, int st, int en, int l, int r) {
    propagate(u, st, en);
    if (r<st || en<l)  return 0;        /// 5. Proper null value
    else if (l<=st && en<=r)    return tr[u];
    else {
        int mid = (st+en)/2;
        return combine(query(2*u, st, mid, l, r), query(2*u+1, mid+1, en, l, r));
    }
}

void debug(int u, int st, int en) {
    cout<<"--->"<<u<<" "<<st<<" "<<en<<" "<<tr[u]<<" "<<lz[u]<<endl;
    if (st==en) return;
    int mid = (st+en)/2;
    debug(2*u, st, mid);
    debug(2*u+1, mid+1, en);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    while (t--) {
        int n, q;
        cin>>n>>q;
        build(1,1,n);

        while (q--) {
            int c, l, r;
            cin>>c>>l>>r;

            if (c==1)   cout<<query(1, 1, n, l, r)<<"\n";
            else {
                int x;
                cin>>x;
                update(1, 1, n, l, r, x);
            }
//            debug(1, 1, n);
        }
    }
}

