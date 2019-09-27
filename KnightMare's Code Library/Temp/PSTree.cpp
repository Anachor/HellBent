/*
    Persistent Segment Tree Basic Code
    Memory: O(N+QlogN)
    Point Update, Range Query

    solves SPOJ MKTHNUM
    given a query (i,j,k)
    find the kth element in the sorted subarray [i,j]
*/

#include<bits/stdc++.h>
using namespace std;
const int MAXX = 100000;

struct Node {
    int cnt;
    Node *bam, *dan;
    Node(int c = 0, Node *b = NULL, Node *d = NULL) :  cnt(c), bam(b), dan(d) {}

    void build(int l, int r) {
        if (l==r) return;
        int mid = (l+r)/2;
        bam = new Node();
        dan = new Node();
        bam->build(l, mid);
        dan->build(mid+1, r);
    }

    Node* update(int l, int r, int idx, int v) {
        if (idx < l || r < idx) return this;
        if (l==r) {
            Node *ret = new Node(cnt);
            ret->cnt += v;
            return ret;
        }

        Node* ret = new Node();
        int mid = (l+r)/2;
        ret->bam = bam->update(l, mid, idx, v);
        ret->dan = dan->update(mid+1, r, idx, v);
        ret->cnt = ret->bam->cnt + ret->dan->cnt;
        return ret;
    }
}* root[MAXX+7];

int getKth(Node* R, Node* L, int l, int r, int k) {
    assert(R->cnt+L->cnt >= k);
    if (l==r) {
        return l;
    }
    int bk = R->bam->cnt-L->bam->cnt;
    int mid = (l+r)/2;
    if (k <= bk) return getKth(R->bam, L->bam, l, mid, k);
    else return getKth(R->dan, L->dan, mid+1, r, k-bk);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int>v(n), s(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s[i] = v[i];
    }

    sort(s.begin(), s.end());
    map<int, int>mp;
    for (int i = 0; i < n; i++) mp[s[i]] = i;

    root[0] = new Node();
    root[0]->build(0, MAXX-1);

    for (int i = 1; i <= n; i++) {
        root[i] = root[i-1]->update(0, MAXX-1, mp[v[i-1]], 1);
    }

    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        assert(1 <= k && k <= j-i+1);
        int x = getKth(root[j], root[i-1], 0, MAXX-1, k);
        cout << s[x] << '\n';
    }


    return 0;
}
