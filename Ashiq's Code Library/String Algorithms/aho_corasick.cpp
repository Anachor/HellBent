/// lightoj Aho Corasick Solution :
/// Given n distinct patterns and 1 main string (str) , calculates the number
/// times each pattern occurs in the main string

#include <bits/stdc++.h>
using namespace std;

const int N = 250000 + 1000, ALPHA = 26;

struct AC {
    struct state {
        int to[ALPHA], depth, suffLink, par, parLet, cnt, nxt[ALPHA];
    }states[N];
    vector<int> suffix_tree[N];
    int tot_nodes;
    void init() {
        for(int i = 0; i < N; i++) suffix_tree[i].clear();
        memset(states, 0, sizeof states); /// be careful if it gets tle for too much memset
        tot_nodes = 1;
    }
    int add_string(string &str) {
        int cur = 1;
        for(int i = 0; i < str.size(); i++) {
            int c = str[i]-'a';
            if(!states[cur].to[c]) {
                states[cur].to[c] = ++tot_nodes;
                states[tot_nodes].par = cur;
                states[tot_nodes].depth = states[cur].depth + 1;
                states[tot_nodes].parLet = c;
            }
            cur = states[cur].to[c];
        }
        return cur;
    }
    void push_links() {
        queue <int> que;
        que.push(1);
        while (!que.empty()) {
            int node = que.front();
            que.pop();
            if (states[node].depth <= 1) states[node].suffLink = 1;
            else {
                int cur = states[states[node].par].suffLink;
                int parLet = states[node].parLet;
                while (cur > 1 and !states[cur].to[parLet]) {
                    cur = states[cur].suffLink;
                }
                if (states[cur].to[parLet]) {
                    cur = states[cur].to[parLet];
                }
                states[node].suffLink = cur;
            }
            if (node != 1) suffix_tree[states[node].suffLink].push_back(node); /// creates suffix link tree
            for (int i = 0 ; i < ALPHA; i++) {
                if (states[node].to[i]) {
                    que.push(states[node].to[i]);
                }
            }
        }
    }
    int next_state(int from, int c) {
        if(states[from].nxt[c]) return states[from].nxt[c];
        int cur = from;
        while(cur > 1 and !states[cur].to[c]) cur = states[cur].suffLink;
        if(states[cur].to[c]) cur = states[cur].to[c];
        return states[from].nxt[c] = cur;
    }
    void dfs(int u) {
        for(int v : suffix_tree[u]) {
            dfs(v);
            states[u].cnt += states[v].cnt;
        }
    }
}aho;


int main () {
    //freopen ("in.txt" , "r" , stdin);

    int tc, caseno = 1;
    cin >> tc;
    while(tc--) {
        aho.init();
        int n;
        cin >> n;
        string T;
        cin >> T;
        vector<int> node_id(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            string s;
            cin >> s;
            node_id[i] = aho.add_string(s);
        }
        aho.push_links();
        int cur = 1;
        for(int i = 0; i < T.size(); i++) {
            cur = aho.next_state(cur, T[i]-'a');
            aho.states[cur].cnt++;
        }
        aho.dfs(1);
        cout << "Case " << caseno++ << ":\n";
        for(int i = 1; i <= n; i++) {
            cout << aho.states[node_id[i]].cnt << "\n";
        }
    }
}
