/// not tested yet
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4e5 + 10;

template<typename T>
ostream& operator<<(ostream& os, vector<T> v) {
  os << "[";
  for (T &i: v) os << i << ",";
  os << "]";
  return os;
}

template<class TH> void _dbg(const char *sdbg, TH h){ cout<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cout<<*sdbg++;
  cout<<'='<<h<<','; _dbg(sdbg+1, a...);
}

#ifdef __DJKIM613
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (__VA_ARGS__)
#endif

struct query{
    int node, time, type;
    query(){}
    query(int node, int time, int type) : node(node), time(time), type(type) {}
};

long long sqrt(long long x){
    return x * x;
}

struct LCT{
    int N;
    vector<int> P;
    vector<vector<int>> CH;
    vector<long long> val1, val2;
    vector<long long> rval1, rval2;

    LCT(){}
    LCT(int N) : N(N){
        P.resize(N);    CH.resize(N);
        for(int i = 0 ; i < N ; i++) CH[i].resize(2);
        val1.resize(N, 1);  val2.resize(N, 0); val1[0] = 0;
        rval1.resize(N, 0);    rval2.resize(N, 0);
    }

    void push_up(int x){
        val1[x] = val1[CH[x][0]] + val1[CH[x][1]] + rval1[x] + 1;
        val2[x] = sqrt(val1[CH[x][0]]) + sqrt(val1[CH[x][1]]) + rval2[x];
    }

    bool is_root(int x){
        return (CH[P[x]][0] != x && CH[P[x]][1] != x);
    }

    void rotate(int x){
        int y = P[x], z = P[y], w = (CH[y][1] == x);
        if(!is_root(y)) CH[z][CH[z][1] == y] = x;
        CH[y][w] = CH[x][w ^ 1]; P[CH[x][w ^ 1]] = y;
        CH[x][w ^ 1] = y;   P[y] = x;   P[x] = z;
        push_up(y); push_up(x);
    }

    void splay(int x){
        while(!is_root(x)){
            int y = P[x], z = P[y];
            if(!is_root(y)) ((CH[z][0] == y) == (CH[y][0] == x)) ? rotate(y) : rotate(x);
            rotate(x);
        }
    }

    void access(int x){
        for(int t = 0 ; x ; t = x, x = P[x]){
            splay(x);
            rval1[x] += val1[CH[x][1]]; rval2[x] += sqrt(val1[CH[x][1]]);
            CH[x][1] = t;
            rval1[x] -= val1[CH[x][1]]; rval2[x] -= sqrt(val1[CH[x][1]]);
            push_up(x);
        }
    }

    void link(int x, int p){
        access(p);  splay(p);   splay(x);
        CH[p][1] = x;   P[x] = p;
        push_up(p);
    }

    void cut(int x, int p){
        access(p);  splay(p);   splay(x);
        rval1[p] -= val1[x];   rval2[p] -= sqrt(val1[x]); P[x] = 0;
        push_up(p);
    }

    int find_root(int x){
        access(x);  splay(x);
        while(CH[x][0]) x = CH[x][0];
        return x;
    }
};

int N, M;
int C[MAXN];
vector<query> Q[MAXN];
vector<int> ADJ[MAXN];
int P[MAXN];
long long ans[MAXN];
void dfs(int here){
    for(int there : ADJ[here]) if(there != P[here]) P[there] = here, dfs(there);
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);    cout.tie(nullptr);

    cin >> N >> M;
    for(int i = 1 ; i <= N ; i++) cin >> C[i];

    for(int i = 1 ; i < N ; i++) {
        int x, y;
        cin >> x >> y;
        ADJ[x].push_back(y);     ADJ[y].push_back(x);
    }

    dfs(1); P[1] = N + 1;
    LCT lct = LCT(N + 2);
    for(int i = 1 ; i <= N ; i++) lct.link(i, P[i]);
    for(int i = 1 ; i <= N ; i++) Q[C[i]].push_back(query(i, 0, 0));
    for(int i = 1 ; i <= M ; i++){
        int x, c;
        cin >> x >> c;
        Q[C[x]].push_back(query(x, i, 1));
        Q[C[x] = c].push_back(query(x, i, 0));
    }

    for(int i = 1 ; i <= N ; i++) Q[C[i]].push_back(query(i, M + 1, 1));

    for(int i = 1 ; i <= N ; i++) {
        for(auto q : Q[i]){
            int node = q.node, t = q.time, ff = lct.find_root(P[node]);
            if(q.type){
                lct.splay(ff);  lct.splay(node);
                ans[t] += lct.val2[ff] + lct.val2[node];
                //debug("[+]", ff, t, lct.val2[ff] + lct.val2[node]);
                lct.link(node, P[node]);    lct.splay(ff);
                ans[t] -= lct.val2[ff];
                //debug("[++]", ff, lct.val2[ff]);

            }
            else{
                lct.splay(ff);  ans[t] += lct.val2[ff];
                //debug("[-]", ff, t, lct.val2[ff]);
                lct.cut(node, P[node]);
                lct.splay(ff);  lct.splay(node);    ans[t] -= lct.val2[ff] + lct.val2[node];
                //debug("[--]", lct.val2[ff] + lct.val2[node]);
            }
        }
        //cout << '\n';
    }

    for(int i = 1 ; i <= M ; i++) ans[i] += ans[i - 1];
    for(int i = 0 ; i <= M ; i++) cout << ans[i] << '\n';
    return 0;
}
