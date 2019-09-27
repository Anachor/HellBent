#include <bits/stdc++.h>
using namespace std;

/**
0 is the root-(null string)
advance without memoization is applicable for
if you traverse through a
string (no tree) which is usually the case

Application:
# Number of Occ of each state:
    initialize each state(except the clones) with cnt[state] = 1
    loop in decreasing order of len[state], and update: cnt[link[state]] += cnt[state]
    Small to Large Approach might be used to actually know the positions rather than the count

# First Occ of each state:
    for new state: firstpos(cur) = len(cur)-1
    for cloned state: firstpos(clone) = firstpos(q)

# Longest Common Substring:
    Build Automata for one string, iterate over other's all suffix
**/


const int ALPHA = 26;

namespace SuffixAutomata {
    vector<vector<int>> to, next_state;
    vector<int> link, len;
    int n, sz, cur;

    void add(int c) {
        int p = cur;
        cur = ++sz;
        len[cur] = len[p] + 1;
        while (to[p][c] == 0) {
            to[p][c] = cur;
            p = link[p];
        }
        if (to[p][c] == cur) {
            link[cur] = 0;
            return;
        }
        int q = to[p][c];
        if (len[q] == len[p] + 1) {
            link[cur] = q;
            return;
        }
        int cl = ++sz;
        to[cl] = to[q];
        link[cl] = link[q];
        len[cl] = len[p] + 1;
        link[cur] = link[q] = cl;
        while (to[p][c] == q) {
            to[p][c] = cl;
            p = link[p];
        }
    }
    /** advance with memoization **/
    int advance(int state, int c) {
        if(next_state[state][c] != -1) return next_state[state][c];
        int nstate;
        if(to[state][c]) nstate = to[state][c];
        else if(state) nstate = advance(link[state], c);
        else nstate = state;
        return next_state[state][c] = nstate;
    }
    /** advance without memoization **/
    /**
    int advance(int state, int c) {
        while (state and !to[state][c]) state = link[state];
        if (to[state][c]) state = to[state][c];
        return state;
    }
    **/
    void build(string &s) {
        cur = sz = 0;
        n = s.size();
        to.assign(2*n+1, vector<int> (ALPHA, 0)); /// null state + 2*n
        next_state.assign(2*n+1, vector<int> (ALPHA, -1));
        link.assign(2*n+1, 0);
        len.assign(2*n+1, 0);
        for(int i = 0; i < n; i++) {
            add(s[i]-'a'); /// change if CAPITAL Letters are needed
        }
    }
}

int main () {
    string s;
    cin >> s;
    SuffixAutomata::build(s);
    return 0;
}
