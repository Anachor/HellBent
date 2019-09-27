/**
Min Cost Max Flow
Complexity: Jani na (Should be fast enough)
Source: Repon da
*/

#include<bits/stdc++.h>
using namespace std;

const int maxn = 105;
typedef long long T;
struct Edge {
    int  u , v ;
    T cap ,flow , cost;
};

struct MCMF {
    int n,m,s,t;      // Total Number of Node Including S,T
    vector<int> G[maxn];     //Graph
    vector<Edge> E;         // EdgeList
    T d[maxn];             // Distance Array of BeTmanFord
    bool inq[maxn];           // Is node in queue
    int p[maxn];
    T a[maxn];
    const T INF = 1e18+7;

    MCMF(int n) : n(n) {}

    void addEdge( int u , int v , T cap , T cost ){
        E.push_back({u, v , cap , 0 , cost});       // Positive Cost
        E.push_back({v,u , 0, 0 , -cost } );        // Negative Cost
        m = (int) E.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    bool BelmanFord(T &flow , T &cost ) {
        for(int i = 0; i < n ;i  ++) d[i] = INF ;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty() ) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;

            for( int i = 0 ; i < G[u].size() ; i ++ ) {
                Edge &e = E[G[u][i]];
                if( e.cap > e.flow && d[e.v] > d[u] + e.cost ) {
                    d[e.v] = d[u] + e.cost;
                    p[e.v] = G[u][i];
                    a[e.v] = min( a[u] , e.cap - e.flow );

                    if( inq[e.v ] == 0 ) {
                        Q.push(e.v);
                        inq[e.v] = 1;
                    }
                }
            }
        }

        if( d[t] == INF ) return false;     // No augmenting Path
        flow = a[t];
        cost = d[t] ;               // Unit cost
        int u = t ;
        while( u  != s ) {
            E[p[u]].flow += a[t];
            E[p[u]^1].flow -= a[t];
            u = E[p[u]].u;
        }
        return true;
    }

    pair<T,T> Mincost (int s, int t) {
        this->s=s,this->t=t;
        T Mcost = 0;
        T Flow = 0;
        T f = 0 ;    // For Each CaT , The flow
        T d = 0;      // Shortest Distance / Cost Per Flow

        while(BelmanFord(f,d)) {
            Flow += f;
            Mcost += f *d ;
        }
        return make_pair(Flow, Mcost);
    }
};


///Solves Uva Data flow :|
const int M = 5000+5;
int u[M], v[M], c[M];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    while (cin>>n>>m) {
        MCMF solver(n+1);
        for (int i=0; i<m; i++)
            cin>>u[i] >> v[i] >> c[i];

        int k, d;
        cin>>d>>k;

        for (int i=0; i<m; i++)
            solver.addEdge(u[i], v[i], k, c[i]),
            solver.addEdge(v[i], u[i], k, c[i]);

        solver.addEdge(0, 1, d, 0);
        pair<T, T> ans = solver.Mincost(0, n);
        if (ans.first != d) cout<<"Impossible.\n";
        else                cout<<ans.second<<"\n";
    }
}
