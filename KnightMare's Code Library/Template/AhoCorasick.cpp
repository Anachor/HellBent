#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int sigma = 26;
struct Vertex {
    int next[sigma];    /// indices of child node

    bool leaf = false;  /// true if the char is a last char in a string
    int p = -1;         /// index of parent node
    char pch;           /// parent character

    int link = -1;      /// suffix link for a vertex p is a edge that
                        /// points to the longest proper suffix of the
                        /// string corresponding to the vertex p.

    int go[sigma];      /// save the values of go(int v, char ch) in the array

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(next, next+sigma, -1);
        fill(go, go+sigma, -1);
    }
};

vector<Vertex> t(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].leaf = true;
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

/// returns the node to go from node 'v' with edge 'ch'

int go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}

void bfs()
{
    queue< int >q;
    q.push(0);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        get_link(u);

        if (t[t[u].link].leaf) t[u].leaf = true;
        /// ^^leaf variable is TRUE if it is the end char in the string
        /// OR if any of the nodes connected through the suffix links is TRUE

        /// Alternative is to keep a frequency of the end nodes (leaf==TRUE)
        /// connected up through the suffix links

        for (int v = 0; v < sigma; v++) {
            if (t[u].next[v]==-1) continue;
            q.push(t[u].next[v]);
        }
    }
}

int main()
{

    return 0;
}
