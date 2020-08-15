/*
Solves CF 863D
Given an array
2 types of updates
    1. Reverse a segment
    2. Cyclically shift a segment to the right
*/

#include<bits/stdc++.h>
using namespace std;

typedef struct item * pitem;
struct item {
    int prior, value, cnt;
    bool rev;

    item(int value):prior(rand()), value(value) {
        cnt = 0;
        rev = 0;
        l = r = nullptr;
    }

    pitem l, r;
};

namespace Treap {

    int cnt (pitem it) {
        return it != nullptr? it->cnt : 0;
    }

    void upd_cnt (pitem it) {
        if (it!=nullptr)
            it->cnt = cnt(it->l) + cnt(it->r) + 1;
    }

    void push (pitem it) {
        if (it != nullptr && it->rev == true) {
            it->rev = false;
            swap (it->l, it->r);
            if (it->l)  it->l->rev ^= true;
            if (it->r)  it->r->rev ^= true;
        }
    }

    void merge (pitem & t, pitem l, pitem r) {
        push (l);
        push (r);
        if (l==nullptr || r==nullptr)
            t = (l!=nullptr) ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
        upd_cnt (t);
    }

    void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
        if (t==nullptr) {
            l = r = nullptr;
            return;
        }
        push (t);
        int cur_key = add + cnt(t->l);

        if (key <= cur_key)
            split (t->l, l, t->l, key, add),  r = t;
        else
            split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
        upd_cnt (t);
    }

    void reverse (pitem &t, int l, int r) {
        pitem t1, t2, t3;
        split (t, t1, t2, l);
        split (t2, t2, t3, r-l+1);
        t2->rev ^= true;
        merge (t, t1, t2);
        merge (t, t, t3);
    }


    void insert (pitem & t, int key, int value) {

        pitem x = new item(value);

        pitem L, R;
        split(t, L, R, key);
        merge(L, L, x);
        merge(t, L, R);

        upd_cnt(t);
    }

    void erase (pitem & t, int key) {
        assert(cnt(t) > key);

        pitem L, MID, R;
        split(t, L, MID, key);
        split(MID, MID, R, 1);
        merge(t, L, R);

        delete MID;

        upd_cnt(t);
    }


    void cyclicShift(pitem &t, int l, int r)
    {
        assert(0 <= l && r < cnt(t));

        pitem L, MID, R;
        split(t, L, MID, r);
        split(MID, MID, R, 1);
        merge(t, L, R);

        assert(MID!=nullptr);
        insert(t, l, MID->value);
        delete MID;
        upd_cnt(t);
    }

    void output (pitem t, vector< int >&v) {
        if (t==nullptr)  return;
        push (t);
        output (t->l, v);
        v.push_back(t->value);
        output (t->r, v);
    }

    void output2 (pitem t) {
        if (t==nullptr)  return;
        push (t);
        cout << "(";
        output2 (t->l);
        cout << (t->value);
        output2 (t->r);
        cout << ")";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    srand(time(0));

    pitem tr = nullptr;

    int n, q, m;
    cin >> n >> q >> m;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Treap::insert(tr, i, x);
    }


    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (l==r) continue;
        if (t==1) Treap::cyclicShift(tr, l, r);
        else Treap::reverse(tr, l, r);
    }


    vector< int >b;
    Treap::output(tr, b);

    while (m--) {
        int x;
        cin >> x; x--;
        cout << b[x] << " ";
    }


    return 0;
}

