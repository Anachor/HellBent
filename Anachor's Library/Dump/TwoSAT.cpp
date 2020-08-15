/**
    2 SAT
    Complexity: Linear
    Source: Repon da
**/

#include <bits/stdc++.h>
using namespace std;
const int N = 101;
// 1 based Indexing.
// call init(n) -> n is number of variable
struct TwoSAT{
    int n,nn;
    vector<int> G[2*N] , R[2*N], top; //G - original graph,R -Reverse graph,top-topological
    int col[2*N],vis[2*N],ok[2*N];   // col- sccNo, ok -> value assignment.
    void init(int n)
    {
        this->n=n;
        this->nn = n+n;
        for(int i=  0; i <= nn; i ++) G[i].clear(), R[i].clear(), col[i] = 0, vis[i] = 0, ok[i] = 0;
        top.clear();
    }

    int inv(int no) { return (no <= n) ? no + n: no - n; }
    void add(int u,int v)
    {
        G[u].push_back(v);
        R[v].push_back(u);
    }
    void OR(int u,int v){
        add(inv(u), v);
        add(inv(v), u);
    }
    void AND(int u,int v){
        add(u,v);
        add(v,u);
    }
    void XOR(int u,int v){
        add(inv(v), u);
        add(u, inv(v));
        add(inv(u), v);
        add(v, inv(u));
    }
    void XNOR(int u,int v){
        add(u,v);
        add(v,u);
        add(inv(u), inv(v));
        add(inv(v), inv(u));
    }
    void force_true(int x) {
        add(inv(x),x);
    }
    void force_false(int x) {
        add(x,inv(x));
    }
    void dfs(int u)
    {
        vis[u] = 1;
        for(int i = 0; i < G[u].size(); i ++ ) {
            int v = G[u][i];
            if(vis[v] == 0 ) dfs(v);
        }
        top.push_back(u);
    }

    void dfs1(int u,int color)
    {
        col[u] = color;
        if(u <= n) ok[u] = 1;
        else ok[u - n] = 0;
        for(int i = 0 ;i < R[u].size(); i ++ ) {
            if(col[R[u][i]] == 0 )dfs1(R[u][i], color);
        }
    }
    void FindScc()
    {

        for(int i = 1; i <= nn ; i ++ ) {
            if(vis[i] == 0 ) dfs(i);
        }

        int color = 0;
        reverse(top.begin(), top.end());
        for(auto u: top) {
            if(col[u] == 0) dfs1(u , ++ color);
        }


    }
    void solve()
    {
        FindScc();
        for(int i=1;i<=n;i++){
            if(col[i] == col[n + i]) {
                printf("Impossible\n");
                return;
            }
        }
        vector<int> v;
        for(int i = 1; i <= n; i ++ ) {
            if(ok[i]) v.push_back(i); // All 1'
        }
        cout << v.size() << endl;
        for(auto x: v) printf("%d ",x); puts("");

    }
};

int main()
{

    return 0;
}
