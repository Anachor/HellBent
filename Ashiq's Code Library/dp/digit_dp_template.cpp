#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


int totNodes = 1;

struct state {
    int to[20] ;
    int depth ;
    int suffLink ;
    int par ;
    int parLet ;
    int cnt ;
    int nxt[20] ;
}states[205];

int add (string &str, int val) {

    int cur = 1 ; // root with a empty string
    int len = str.size();
    for (int i = 0 ; i < len ; i++) {
        char c = str[i] ;
        if (!states[cur].to[c-'a']) {
            states[cur].to[c-'a'] = ++totNodes ;
            states[totNodes].par = cur ;
            states[totNodes].depth = states[cur].depth + 1 ;
            states[totNodes].parLet = c-'a' ;
        }
        cur = states[cur].to[c-'a'] ;
    }
    states[cur].cnt += val;
    return cur ;
}

vector<int> g[205];

void dfs(int u) {
    for(int v : g[u]) {
        states[v].cnt += states[u].cnt;
        dfs(v);
    }
}

void pushLinks() {
    queue <int> Q ; Q.push(1) ;
    while (!Q.empty()) {
        int node = Q.front() ;
        Q.pop() ;
        if (states[node].depth <= 1) {
            states[node].suffLink = 1 ;
        }
        else {
            int cur = states[states[node].par].suffLink ;
            int parLet = states[node].parLet ;
            while (cur > 1 and !states[cur].to[parLet]) {
                cur = states[cur].suffLink ;
            }
            if (states[cur].to[parLet]) {
                cur = states[cur].to[parLet] ;
            }
            states[node].suffLink = cur;
        }
        for (int i = 0 ; i < 26 ; i++) {
            if (states[node].to[i]) {
                Q.push(states[node].to[i]) ;
            }
        }
    }
    for(int i = 2; i <= totNodes; i++) g[states[i].suffLink].push_back(i);
    dfs(1);
}



int Next (int from , char ch) {
    if (states[from].nxt[ch-'a']) return states[from].nxt[ch-'a'] ;
    int cur = from ;
    int c = ch - 'a' ;
    while (cur > 1 and !states[cur].to[c]) {
        cur = states[cur].suffLink ;
    }
    if (states[cur].to[c]) {
        cur = states[cur].to[c] ;
    }
    return states[from].nxt[ch-'a'] = cur ;
}

string input_string(bool flag) {
    int k;
    cin >> k;
    string ret;
    if(flag) ret.assign(200-k, 'a');
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        ret.push_back('a' + x);
    }
    return ret;
}

int n, base, limit;
int mod = 1e9 + 7;
int dp[201][201][501][2][2][2];
string R, L;


void add(int &x, int y) {
    x += y;
    if(x>=mod) x-=mod;
}

int call(int pos, int state, int sum, bool start, bool alreadyLarge, bool alreadySmall) {
    if(sum > limit) return 0;
    if(pos == 200) return 1;
    if(dp[pos][state][sum][start][alreadyLarge][alreadySmall] != -1) return dp[pos][state][sum][start][alreadyLarge][alreadySmall];
    int ret = 0;
    for(int i = 0; i < base; i++) {
        if(alreadyLarge == false && i < L[pos]-'a') continue;
        if(alreadySmall == false && i > R[pos]-'a') continue;
        int npos = pos + 1;
        bool nstart = start|(i>0);
        bool nalreadyLarge = alreadyLarge|(i>L[pos]-'a');
        bool nalreadySmall = alreadySmall|(i<R[pos]-'a');
        int nstate = state;
        if(nstart) nstate = Next(nstate, 'a' + i);
        int nsum = sum + states[nstate].cnt;
        add(ret, call(npos, nstate, nsum, nstart, nalreadyLarge, nalreadySmall));
    }
    dp[pos][state][sum][start][alreadyLarge][alreadySmall] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(states, 0, sizeof states);
    cin >> n >> base >> limit;
    L = input_string(1);
    R = input_string(1);
    memset(dp, -1, sizeof dp);
    for(int i = 1; i <= n; i++) {
        string s = input_string(0);
        int x;
        cin >> x;
        int state = add(s, x);
    }
    pushLinks();
    cout << call(0,1,0,0,0,0) << endl;
    return 0;
}

