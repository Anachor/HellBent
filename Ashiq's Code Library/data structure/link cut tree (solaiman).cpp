/*
 Petar 'PetarV' Velickovic
 Data Structure: Link/cut Tree
 Source: https://github.com/PetarV-/Algorithms/blob/master/Data%20Structures/Link-cut%20Tree.cpp
*/

#include <bits/stdc++.h>
using namespace std;

/*
 The link/cut tree data structure enables us to efficiently handle a dynamic forest of trees.
 It does so by storing a decomposition of the forest into "preferred paths", where a path is
 preferred to another when it has been more recently accessed.
 Each preferred path is stored in a splay tree which is keyed by depth.
 The tree supports the following operations:
     - make_tree(v): create a singleton tree containing the node v
     - find_root(v): find the root of the tree containing v
     - link(v, w):   connect v to w
                     (precondition: v is root of its own tree,
                     and v and w are not in the same tree!)
     - cut(v):       cut v off from its parent
     - path(v):      access the path from the root of v's tree to v
                     (in order to e.g. perform an aggregate query on that path)
 More complex operations and queries are possible that require the data structure
 to be augmented with additional data. Here I will demonstrate the LCA(p, q)
 (lowest common ancestor of p and q) operation.
 Complexity:    O(1) for make_tree
                O(log n) amortized for all other operations
*/



const int MAXN = 100007;

struct LinkCutTree {
    struct Node {
        int L, R, P, lazyFlip;
        int PP;
    };

    Node LCT[MAXN];

    void normalize(int u) {
        assert(u != -1);
        if (LCT[u].L != -1) LCT[LCT[u].L].P = u;
        if (LCT[u].R != -1) LCT[LCT[u].R].P = u;
        // (+ update sum of subtree elements etc. if wanted
    }

    // set v as p's left child
    void setLeftChild(int p, int v) {
        LCT[p].L = v;
        normalize(p);
    }
    // set v as p's right child
    void setRightChild(int p, int v) {
        LCT[p].R = v;
        normalize(p);
    }

    void pushLazy(int u) {
        if (!LCT[u].lazyFlip) return;
        swap(LCT[u].L, LCT[u].R);
        LCT[u].lazyFlip = 0;
        if (LCT[u].L != -1) LCT[LCT[u].L].lazyFlip ^= 1;
        if (LCT[u].R != -1) LCT[LCT[u].R].lazyFlip ^= 1;
    }

    void make_tree(int v) {
        LCT[v].L = LCT[v].R = LCT[v].P = LCT[v].PP = -1;
        LCT[v].lazyFlip = 0;
    }

    void rotate(int v) {
        if (LCT[v].P == -1) return;
        int p = LCT[v].P;
        int g = LCT[p].P;
        if (LCT[p].L == v) {
            setLeftChild(p, LCT[v].R);
//            LCT[p].L = LCT[v].R;
//            if (LCT[v].R != -1) {
//                LCT[LCT[v].R].P = p;
//            }
            setRightChild(v, p);
//            LCT[v].R = p;
//            LCT[p].P = v;
        } else {
            setRightChild(p, LCT[v].L);
//            LCT[p].R = LCT[v].L;
//            if (LCT[v].L != -1) {
//                LCT[LCT[v].L].P = p;
//            }
            setLeftChild(v, p);
//            LCT[v].L = p;
//            LCT[p].P = v;
        }

        LCT[v].P = g;
        if (g != -1) {
            if (LCT[g].L == p) {
                setLeftChild(g, v);
//                LCT[g].L = v;
            } else {
                setRightChild(g, v);
//                LCT[g].R = v;
            }
        }

        // must preserve path-pointer!
        // (this only has an effect when g is -1)
        LCT[v].PP = LCT[p].PP;
        LCT[p].PP = -1;
    }

    void pushEmAll(int v) {
        if (LCT[v].P != -1) pushEmAll(LCT[v].P);
        pushLazy(v);
    }

    void splay(int v) {
//        cout << "splay " << v << endl;
        pushEmAll(v);
        while (LCT[v].P != -1) {
            int p = LCT[v].P;
            int g = LCT[p].P;
            if (g == -1) { // zig
                rotate(v);
            } else if ((LCT[p].L == v) == (LCT[g].L == p)) { // zig-zig
                rotate(p);
                rotate(v);
            } else { // zig-zag
                rotate(v);
                rotate(v);
            }
        }
    }

    /// returns v if v is in the root auxiliary tree
    /// otherwise returns the topmost unpreferred edge's parent
    int access(int v) {
        splay(v); // now v is root of its aux. tree
        if (LCT[v].R != -1) {
            LCT[LCT[v].R].PP = v;
            LCT[LCT[v].R].P = -1;
            setRightChild(v, -1);
//            LCT[v].R = -1;
        }

        int ret = v;
        while (LCT[v].PP != -1) {
            int w = LCT[v].PP;
            splay(w);
            if (LCT[w].PP == -1) ret = w;
            if (LCT[w].R != -1) {
                LCT[LCT[w].R].PP = w;
                LCT[LCT[w].R].P = -1;
            }
            LCT[v].PP = -1; /// ** missed ** Do we really need this?
            setRightChild(w, v);
//            LCT[w].R = v;
//            LCT[v].P = w;
            splay(v);
        }
        return ret;
    }

    int find_root(int v) {
        access(v);
        int ret = v;
        while (LCT[ret].L != -1) {
            ret = LCT[ret].L;
            pushLazy(ret);
        }
        access(ret);
        return ret;
    }

    /// make w, parent of v where v is a root
    void link(int v, int w) {// attach v's root to w
        access(w);
        // the root can only have right children in
        // its splay tree, so no need to check
        setLeftChild(v, w);
//        LCT[v].L = w;
//        LCT[w].P = v;
        LCT[w].PP = -1;
    }

    void cut(int v) {
        access(v);
        if (LCT[v].L != -1) {
            LCT[LCT[v].L].P = -1;
            LCT[LCT[v].L].PP = -1;
            setLeftChild(v, -1);
//            LCT[v].L = -1;
        }
    }

    void make_root(int v) {
        access(v);
        int l = LCT[v].L;
        if (l != -1) {
            setLeftChild(v, -1);
            LCT[l].P = -1;
            LCT[l].PP = v;
            LCT[l].lazyFlip ^= 1;
        }
    }

    bool isConnected(int p, int q) {
        return find_root(p)==find_root(q);
    }

    /// assuming p and q is in the same tree
    int LCA(int p, int q) {
        access(p);
        return access(q);
    }
};


int main()
{
    // This is the code I used for the problem Dynamic LCA (DYNALCA)
    // on Sphere Online Judge (SPOJ)

    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    LinkCutTree lct;
    for (int i = 1; i <= n; i++) lct.make_tree(i);

    while (m--) {
        string cmd;
        cin >> cmd;
        if (cmd == "link") {
            int p, q;
            cin >> p >> q;
            lct.link(p, q);
        } else if (cmd == "cut") {
            int p;
            cin >> p;
            lct.cut(p);
        } else if (cmd == "lca") {
            int p, q;
            cin >> p >> q;
            cout << lct.LCA(p, q) << "\n";
        }
    }

    return 0;
}
