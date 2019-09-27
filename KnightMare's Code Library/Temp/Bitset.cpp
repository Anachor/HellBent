/**
    Simple Bitset Class with ability to perform range bitwise operations.
    Written by - Anachor
**/


#include <bits/stdc++.h>
typedef unsigned long long ULL;
using namespace std;

struct Bitset {
    const static int B = 6, K = 64, X = 63;

    ///returns mask with bits l to r set, and others reset
    static inline ULL getmask(int l, int r) {
        if (r==X)  return -(1ULL<<l);
        return (1ULL<<(r+1)) - (1ULL<<l);
    }

    vector<ULL> bs;
    int N;

    Bitset(int n) {
        N = n/K+1;
        bs.resize(N);
    }

    void assign(ULL x) {
        fill(bs.begin()+1, bs.end(), 0);
        bs[0] = x;
    }

    bool get(int i) {
        return bs[i>>B] & (1ULL<<(i&X));
    }

    void set(int i) {
        bs[i>>B] |= (1ULL<<(i&X));
    }

    void reset(int i) {
        bs[i>>B] &= ~(1ULL<<(i&X));
    }

    void flip(int i) {
        bs[i>>B] ^= (1ULL<<(i&X));
    }

    void set(int l, int r) {
        int idl = l>>B;
        int idr = r>>B;
        int posl = l&X;
        int posr = r&X;

        if (idl == idr) {
            bs[idl] |= getmask(posl, posr);
            return;
        }

        bs[idl] |= getmask(posl, X);
        bs[idr] |= getmask(0, posr);

        for (int id = idl+1; id < idr; id++)
            bs[id] = -1;
    }

    void reset(int l, int r) {
        int idl = l>>B;
        int idr = r>>B;
        int posl = l&X;
        int posr = r&X;

        if (idl == idr) {
            bs[idl] &= ~getmask(posl, posr);
            return;
        }

        bs[idl] &= ~getmask(posl, X);
        bs[idr] &= ~getmask(0, posr);

        for (int id = idl+1; id < idr; id++)
            bs[id] = 0;
    }

    void flip(int l, int r) {
        int idl = l>>B;
        int idr = r>>B;
        int posl = l&X;
        int posr = r&X;

        if (idl == idr) {
            bs[idl] ^= getmask(posl, posr);
            return;
        }

        bs[idl] ^= getmask(posl, X);
        bs[idr] ^= getmask(0, posr);

        for (int id = idl+1; id < idr; id++)
            bs[id] = ~bs[id];
    }
};


///Solves CF 1146E - Hot is Cold
const int N = 1e5+7;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin>>n>>q;
    vector<int> a(n);
    for (int i=0; i<n; i++)    cin>>a[i];

    Bitset bs(2*N+1);
    bs.set(0+N, N+N);

    while (q--) {
        char c;
        int x;
        cin>>c>>x;

        if (c=='<') {
            if (x<=0)    bs.set(-N+N, x-1+N), bs.set(-x+1+N, N+N);
            else         bs.set(-N+N, -x+N), bs.flip(-x+1+N, x-1+N), bs.set(x+N, N+N);
        }
        else {
            if (x>=0)    bs.reset(-N+N, -x-1+N), bs.reset(x+1+N, N+N);
            else         bs.reset(-N+N, x+N), bs.flip(x+1+N, -x-1+N), bs.reset(-x+N, N+N);
        }
    }

    for (int i=0; i<n; i++) {
        bool b = bs.get(a[i]+N);
        if (b)  a[i] = abs(a[i]);
        else    a[i] = -abs(a[i]);
        cout<<a[i]<<" ";
    }
}
