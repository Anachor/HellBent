#include <bits/stdtr1c++.h>

#define MAXN 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct node{
    node *l, *r;
    int key, subtree, priority;

    inline node(){
        l = r = 0;
    }

    inline node(int val){
        l = r = 0;
        subtree = 1, key = val;
        priority = (rand() << 16) ^ rand();
    }

    inline void update(){
        subtree = 1;
        if (l) subtree += l->subtree;
        if (r) subtree += r->subtree;
    }
} pool[MAXN]; /// Maximum number of nodes in treap

struct Treap{
    int idx; /// Make global if multiple copy of treaps required as of some moment
    struct node* root;

    inline void merge(node* &cur, node* l, node* r){
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) cur->update();
    }

    /// Splits treap into 2 treaps l and r such that all values in l <= key and all values in r > key
    inline void split(node* cur, node* &l, node* &r, int key){
        if (!cur) l = r = 0;
        else if (key <= cur->key) split(cur->l, l, cur->l, key), r = cur;
        else split(cur->r, cur->r, r, key), l = cur;
        if (cur) cur->update();
    }

    inline void insert(node* &cur, node* it){
        if (!cur) cur = it;
        else if (it->priority > cur->priority) split(cur, it->l, it->r, it->key), cur = it;
        else insert((it->key < cur->key)? cur->l : cur->r, it);
        if (cur) cur->update();
    }

    inline void erase(node* &cur, int key){
        if (!cur) return;
        if (cur->key == key) merge(cur, cur->l, cur->r);
        else erase((cur->key > key) ? cur->l : cur->r, key);
        if (cur) cur->update();
    }

    Treap(){
        srand(time(0));
        idx = 0, root = 0; /// Remove idx = 0 and include in main to reset all
                          /// if multiple copy of treaps required as of some moment
    }

    inline void insert(int key){
        pool[idx] = node(key);
        insert(root, &pool[idx++]);
    }

    inline void erase(int key){
        erase(root, key);
    }

    inline int size(){
        if (root) return root->subtree;
        return 0;
    }

    /// Returns the k'th smallest element of the treap in 1-based index, -1 on failure
    inline int kth(int k){
        if ((k < 1) || (k > size())) return -1;

        node *l, *r, *cur = root;
        for (; ;){
            l = cur->l, r = cur->r;
            if (l){
                if (k <= l->subtree) cur = l;
                else if ((l->subtree + 1) == k) return cur->key;
                else cur = r, k -= (l->subtree + 1);
            }
            else{
                if (k == 1) return (cur->key);
                else cur = r, k--;
            }
        }
    }

    /// Returns the count of keys less than x in the treap
    inline int count(int key){
        int res = 0;
        node *l, *r, *cur = root;

        while (cur){
            l = cur->l, r = cur->r;
            if (cur->key < key) res++;
            if (key < cur->key) cur = l;
            else{
                cur = r;
                if (l) res += l->subtree;
            }
        }
        return res;
    }
};

int main(){

}
