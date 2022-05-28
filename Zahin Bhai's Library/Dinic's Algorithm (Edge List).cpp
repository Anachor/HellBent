#include <bits/stdtr1c++.h>

#define MAXN 50010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Dinic's algorithm for directed graphs (0 based index for graphs)
/// For undirected graphs, just add two directed edges

const long long INF = (~0ULL) >> 1;

namespace flow{
    struct Edge{
        int u, v;
        long long cap, flow;

        Edge(){}
        Edge(int a, int b, long long c, long long f){
            u = a, v = b, cap = c, flow = f;
        }
    };

    vector <int> adj[MAXN];
    vector <struct Edge> E;
    int n, s, t, ptr[MAXN], len[MAXN], dis[MAXN], Q[MAXN];

    inline void init(int nodes, int source, int sink){
        clr(len);
        E.clear();
        n = nodes, s = source, t = sink;
        for (int i = 0; i < MAXN; i++) adj[i].clear();
    }

    /// Adds a directed edge with capacity c
    inline void addEdge(int a, int b, long long c){
        adj[a].push_back(E.size());
        E.push_back(Edge(a, b, c, 0));
        len[a]++;
        adj[b].push_back(E.size());
        E.push_back(Edge(b, a, 0, 0));
        len[b]++;
    }

    inline bool bfs(){
        int i, j, k, id, f = 0, l = 0;
        memset(dis, -1, sizeof(dis[0]) * n);

        dis[s] = 0, Q[l++] = s;
        while (f < l && dis[t] == -1){
            i = Q[f++];
            for (k = 0; k < len[i]; k++){
                id = adj[i][k];
                if (dis[E[id].v] == -1 && E[id].flow < E[id].cap){
                    Q[l++] = E[id].v;
                    dis[E[id].v] = dis[i] + 1;
                }
            }
        }
        return (dis[t] != -1);
    }

    long long dfs(int i, long long f){
        if (i == t || !f) return f;
        while (ptr[i] < len[i]){
            int id = adj[i][ptr[i]];
            if (dis[E[id].v] == dis[i] + 1){
                long long x = dfs(E[id].v, min(f, E[id].cap - E[id].flow));
                if (x){
                    E[id].flow += x, E[id ^ 1].flow -= x;
                    return x;
                }
            }
            ptr[i]++;
        }
        return 0;
    }

    long long dinic(){
        long long res = 0;

        while (bfs()){
            memset(ptr, 0, n * sizeof(ptr[0]));
            while (long long f = dfs(s, INF)) {
                res += f;
            }
        }
        return res;
    }
}

namespace nodeflow{
    void init(int n, int s, int t, vector <long long> capacity){
        flow::init(n * 2, s * 2, t * 2 + 1);

        for (int i = 0; i < n; i++){
            flow::addEdge(i * 2, i * 2 + 1, capacity[i]);
        }
    }

    void addEdge(int a, int b, long long c){
        flow::addEdge(a * 2 + 1, b * 2, c);
    }

    long long dinic(){
        return flow::dinic();
    }
}

int main(){

    int n , b , q ;
    cin >> n >> b >> q ;
    vector < pair<int,int> > v ;
    v.push_back({b,n}) ;
    v.push_back({0,0}) ;
    for (int i = 1 ; i <= q ; i++) {
        int x , k ;
        cin >> x >> k ;
        v.push_back({x,k}) ;
    }
    sort(v.begin(), v.end()) ;
    v.erase(unique(v.begin(),v.end()),v.end()) ;
    int source = 0 , nodes = 1 + 5 + v.size() , sink = nodes-1 ;
    flow :: init(nodes,source,sink) ;
    for (int i = 1 ; i <= 5 ; i++) {
        flow :: addEdge(source,i,n/5) ;
    }
    for (int i = 1 ; i < v.size() ; i++) {
        int cnt = v[i].second - v[i-1].second ;
        if (cnt < 0) {
            printf ("unfair") ;
            return 0 ;
        }
        flow :: addEdge(i+5,sink,+cnt) ;
        int l = v[i-1].first+1 , r = v[i].first ;
        if (l > r) {
            printf ("unfair") ;
            return 0 ;
        }
        int count_[5] ;
        memset (count_ , 0 , sizeof count_) ;
        for (int x = l ; x <= r ; x++) {
            count_[x%5]++ ;
        }
        for (int j = 1 ; j <= 5 ; j++) {
            flow::addEdge(j,i+5,count_[j-1]) ;
        }
    }
    if (flow::dinic() == n) {
        printf ("fair") ;
    }
    else {
        printf ("unfair") ;
    }
    return 0;
}
