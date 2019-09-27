/*
    Persistent Segment Tree with Lazy Propagation

    The following code solves the problem:
        1. Add a, a+b, a+2b, ... to [l, r]
        2. Find the sum of [l, r]
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Node{
    LL sum; LL lazyA = 0, lazyB = 0; bool hasLazy = false;
    Node* bam, *dan;
    Node(LL s = 0, Node *b = NULL, Node *d = NULL) : sum(s), bam(b), dan(d) { }
    void init(int l, int r) {
        if (l==r) return;
        int mid = (l+r)/2;
        bam = new Node();
        dan = new Node();
        bam->init(l, mid);
        dan->init(mid+1, r);
    }
    void propagate(int l, int r) {
        if (!hasLazy) return;           ///important
        LL n = r-l+1;
        sum += n * lazyA;
        sum += ((n*(n-1))/2) * lazyB;
        if (l!=r) {
            bam = new Node(*bam);
            dan = new Node(*dan);
            int mid = (l+r)/2;
            bam->lazyA += lazyA;
            bam->lazyB += lazyB;
            dan->lazyA += lazyA+lazyB*(mid-l+1);
            dan->lazyB += lazyB;
            bam->hasLazy = true;
            dan->hasLazy = true;
        }
        lazyA = 0;
        lazyB = 0;
        hasLazy = false;
    }

    Node* update(int l, int r, int x, int y, LL a, LL b) {
        propagate(l, r);
        if (r < x || y < l) return this;
        if (x <= l && r <= y) {
            Node* rt = new Node(*this);
            rt->lazyA += a+(l-x)*b;
            rt->lazyB += b;
            rt->hasLazy = true;
            rt->propagate(l, r);
            return rt;
        }
        int mid = (l+r)/2;
        Node* rt = new Node();
        rt->bam = bam->update(l, mid, x, y, a, b);
        rt->dan = dan->update(mid+1, r, x, y, a, b);
        rt->sum = rt->bam->sum + rt->dan->sum;
        return rt;
    }
    LL query(int l, int r, int x, int y) {
        propagate(l, r);
        if (x <= l && r <= y) return sum;
        LL ans = 0;
        int mid = (l+r)/2;
        if (x <= mid) ans += bam->query(l, mid, x, y);
        if (mid < y) ans += dan->query(mid+1, r, x, y);
        return ans;
    }
};

int main()
{


    return 0;
}
