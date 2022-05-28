/**
    Implementation of Aho Corasick Algorithm
    Source: E-maxx (modified)

    Overall Complexity: O(alphabet size * number of characters in Trie)
**/

#include<bits/stdc++.h>
using namespace std;

namespace Aho {
    const int N = 1e6+7;        ///Number of characters in dictionary
    const int K = 26;           ///Alphabet size

    int nxt[N][K];              ///Children
    int go[N][K];               ///automaton

    int link[N];                ///Suffix link
    bool leaf[N];               ///isLeaf
    int par[N];                 ///Parent
    char ch[N];                 ///character of incoming edge
    int ex[N];                  ///exit link
    int sz;

    void init() {
        memset(nxt, -1, sizeof nxt);
        memset(go, -1, sizeof go);
        memset(link, -1, sizeof link);
        memset(leaf, 0, sizeof leaf);
        memset(ex, -1, sizeof ex);
        sz = 0;
    }

    void addString(const string &s) {
        int cur = 0;
        for (char c: s) {
            int cc = c-'a';
            if (nxt[cur][cc] == -1) {
                nxt[cur][cc] = ++sz;
                ch[sz] = c;
                par[sz] = cur;
            }
            cur = nxt[cur][cc];
        }
        leaf[cur] = 1;
    }

    int Go(int v, char ch);

    ///Amortized O(1)
    int getlink(int v) {
        if (link[v] != -1)  return link[v];
        if (v==0 || par[v] == 0)    return link[v] = 0;
        else return link[v] = Go(getlink(par[v]), ch[v]);
    }

    ///Amortized O(1)
    int Go (int v, char c) {
        int cc = c- 'a';
        if (go[v][cc] != -1)     return go[v][cc];
        if (nxt[v][cc] != -1)    return go[v][cc] = nxt[v][cc];
        else return go[v][cc] = (v ? Go(getlink(v), c) : 0);
    }

    ///Amortized O(1)
    int exitlink(int v) {
        if (ex[v] != -1)             return ex[v];
        int nxt = getlink(v);
        if (nxt==0 || leaf[nxt])     return ex[v] = nxt;
        return ex[v] = exitlink(nxt);
    }


    ///returns number of matches (including multiple matches)
    ///O(no of matches + length of s)
    int match(string s) {
        int cur = 0;
        int ans = 0;
        for (auto c: s) {
            cur = Go(cur, c);
            int e = (leaf[cur] ? cur : exitlink(cur));
            while (e)
                ans++,
                e = exitlink(e);
        }
        return ans;
    }
}

int main() {
    Aho::init();
    Aho::addString("banana");
    Aho::addString("ban");
    Aho::addString("nana");
    Aho::addString("anachor");
    Aho::addString("ana");

    cout<<Aho::match("ban")<<endl;           ///1
    cout<<Aho::match("banana")<<endl;        ///5
    cout<<Aho::match("bananachor")<<endl;    ///6
    cout<<Aho::match("ananana")<<endl;       ///5
    cout<<Aho::match("ba")<<endl;            ///0
    cout<<Aho::match("anachor")<<endl;       ///2
}
