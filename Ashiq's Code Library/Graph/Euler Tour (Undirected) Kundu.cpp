#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    int other(int x) {return u^v^x;}
};

struct Eulerpath {
    int n;
    vector<Edge> edges;
    vector<bool> vis;
    vector<vector<int>> adj;

    Eulerpath(int nn) : n(nn), adj(nn) {}
    void addEdge(int u, int v) {
        edges.push_back({u, v});
        vis.push_back(0);
        int id = edges.size()-1;
        adj[u].push_back(id);
        adj[v].push_back(id);
    }

    bool getTour(vector<int> &path) {
        int u = 0, cnt=0;
        for (int i=0; i<n; i++)
            if(adj[i].size()%2) {
                u = i;
                ++cnt;
            }

        if (cnt !=0 && cnt != 2)    return false;

        stack<int> st;
        path.clear();

        while (true) {
            while (adj[u].size() && vis[adj[u].back()] == 1)    adj[u].pop_back();

            if (adj[u].empty()) {
                path.push_back(u);
                if (st.empty()) break;
                u = st.top();
                st.pop();
            }
            else {
                st.push(u);
                int id = adj[u].back();
                vis[id] = 1;
                u = edges[id].other(u);
            }
        }

        for (int i=0; i<edges.size(); i++)
            if (!vis[i])
                return false;
        return true;
    }
};


int main() {
    int n, m;
    cin>>n>>m;

    Eulerpath solver(n);
    while (m--) {
        int u, v;
        cin>>u>>v;
        solver.addEdge(u, v);
    }

    vector<int> v;
    bool b = solver.getTour(v);
    if (!b) cout<<"None"<<endl;
    else for (int x: v)  cout<<x<<" ";
}
