#include <bits/stdtr1c++.h>

#define MAXN 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Implicit treap for SPOJ Horrible, Range updates and range queries

struct node{
    node *l, *r;
    int subtree, priority;
    long long sum, val, lazy;

    inline node(){
        l = r = 0;
    }

    inline node(long long v, int p){
        l = r = 0;
        priority = p;
        subtree = 1, val = sum = v, lazy = 0;
    }

    inline node(long long v){
        node(v, (rand() << 16) ^ rand());
    }

    inline void update(){
        subtree = 1;
        if (l) subtree += l->subtree;
        if (r) subtree += r->subtree;
    }
} pool[MAXN]; /// Maximum number of nodes in treap

struct Treap{
    int idx;
    struct node* root;

    /// Lazy propagation
    inline void push(node* cur){
        if (!cur || !cur->lazy) return;

        cur->update();
        cur->val += cur->lazy, cur->sum += (cur->lazy * cur->subtree);
        if (cur->l) cur->l->lazy += cur->lazy;
        if (cur->r) cur->r->lazy += cur->lazy;
        cur->lazy = 0;
    }

    /// Update root node from left child, right child and itself!
    inline void join(node* cur){
        if (!cur) return;

        cur->update();
        cur->sum = cur->val;
        if (cur->l) push(cur->l), cur->sum += cur->l->sum;
        if (cur->r) push(cur->r), cur->sum += cur->r->sum;
    }

    /// Merges two treaps l and r
    inline void merge(node* &cur, node* l, node* r){
        push(l), push(r); /// Lazy propagation
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) join(cur); /// Update root node from left child, right child and itself!
    }

    /// Splits treap cur, counter is the implicit key on subtree size
    inline void split(node* cur, node* &l, node* &r, int key, int counter = 0){
        if (!cur){
            l = r = 0;
            return;
        }

        push(cur); /// Lazy propagation
        int cur_key = counter + (cur->l ? cur->l->subtree : 0);
        if (key <= cur_key) split(cur->l, l, cur->l, key, counter), r = cur;
        else split(cur->r, cur->r, r, key, cur_key + 1), l = cur;
        if (cur) join(cur); /// Update root node from left child, right child and itself!
    }

    /// Faster insert when appending to the end, appends node v to the end of the array
    inline void build(int i, int v){
        pool[idx] = node(v);
        merge(root, root, &pool[idx++]);
    }

    /// Builds an implicit treap from an array and returns pointer to the root in O(n)
    inline node* build(int i, int j, int* ar){
        int k = (i + j) >> 1;
        pool[idx] = node(ar[k], (j - i + 1));
        node *cur = &pool[idx++];
        if (i < k) cur->l = build(i, k - 1, ar);
        if (j > k) cur->r = build(k + 1, j, ar);
        join(cur);
        return cur;
    }

    /// Inserts a number in the i'th position with value v
    inline void insert(int i, long long v){
        node *l, *r;
        split(root, l, r, i);
        pool[idx] = node(v);
        merge(root, l, &pool[idx++]); /// New node created here
        merge(root, root, r);
    }

    /// Adds v to the segment [a:b]
    inline void update(int a, int b, long long v){
        node *l, *r, *m;
        split(root, l, r, a - 1);
        split(r, m, r, b - a + 1);
        m->lazy += v;
        merge(m, m, r);
        merge(root, l, m);
    }

    /// Returns the sum of the segment[a:b]
    inline long long query(int a, int b){
        node *l, *r, *m;
        split(root, l, r, a - 1);
        split(r, m, r, b - a + 1);

        long long res = m->sum;
        merge(m, m, r);
        merge(root, l, m);
        return res;
    }

    Treap(){
        srand(time(0));
        idx = 0, root = 0;
    }

    inline int size(){
        if (root) return root->subtree;
        return 0;
    }
};

int main(){
    int t, n, q, i, j, k, f, l, r, x, v;

    scanf("%d", &t);
    while (t--){
        Treap T = Treap();
        scanf("%d %d", &n, &q);
        for (i = 1; i <= n; i++) T.insert(i, 0);

        while (q--){
            scanf("%d %d %d", &f, &l, &r);
            if (!f){
                scanf("%d", &v);
                T.update(l, r, v);
            }
            else printf("%lld\n", T.query(l, r));
        }
    }
    return 0;
}
