#include <bits/stdtr1c++.h>

#define MAXN 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct node{
    node *l, *r;
    int val, counter, mask, subtree, priority;

    inline node(){
        l = r = 0;
    }

    inline node(int v, int c, int p){
        l = r = 0;
        priority = p;
        subtree = c, val = v, counter = c, mask = (1 << v);
    }

    inline node(int v, int c){
        node(v, c, (rand() << 16) ^ rand());
    }

    inline void update(){
        subtree = counter;
        if (l) subtree += l->subtree;
        if (r) subtree += r->subtree;
    }
} pool[MAXN]; /// Maximum number of nodes in treap

struct Treap{
    int idx;
    struct node* root;

    inline void join(node* cur){
        if (!cur) return;
        cur->update();
        cur->mask = 1 << cur->val;
        if (cur->l) cur->mask |= cur->l->mask;
        if (cur->r) cur->mask |= cur->r->mask;
    }

    inline void merge(node* &cur, node* l, node* r){
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) join(cur);
    }

    /// Smallest v such that l->subtree = v and v >= key
    inline void split(node* cur, node* &l, node* &r, int key, int counter = 0){
        if (!cur){
            l = r = 0;
            return;
        }

        int cur_key = counter + (cur->l ? cur->l->subtree : 0);
        if (key <= cur_key) split(cur->l, l, cur->l, key, counter), r = cur;
        else split(cur->r, cur->r, r, key, cur_key + cur->counter), l = cur;
        if (cur) join(cur);
    }

    inline void divide(node* &cur, int i){
        node *l, *r, *m, *t;
        split(cur, l, r, i);
        if (!(!l || l->subtree == i)){
            m = l;
            while (m->r) m = m->r;
            int v = m->val, c1 = i - (l->subtree - m->counter), c2 = m->counter - c1;

            split(l, l, t, l->subtree - m->counter);
            pool[idx] = node(v, c1);
            merge(l, l, &pool[idx++]); /// Assign to t or m if required
            pool[idx] = node(v, c2);
            merge(l, l, &pool[idx++]); /// Assign to t or m if required

        }
        merge(cur, l, r);
    }

    inline void insert(int i, int v, int c){ /// Inserts c copies of v after position i
        divide(root, i);
        node *l, *r, *m;
        split(root, l, r, i);
        pool[idx] = node(v, c);
        merge(l, l, &pool[idx++]);
        merge(root, l, r);
    }

    inline void erase(int a, int b){ /// Removes the segment [a:b]
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        merge(root, l, r);
    }

    inline int query(int a, int b){ /// Number of distinct characters(a-z) in the segment [a:b]
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        int res = m->mask;
        merge(l, l, m);
        merge(root, l, r);
        return __builtin_popcount(res);
    }

    Treap(){
        idx = 0, root = 0;
    }

    inline int size(){
        if (root) return root->subtree;
        return 0;
    }
};

int main(){

}
