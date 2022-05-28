/**
Push-relabel using the highest label selection rule and the gap heuristic.
Complexity: O(V^2 sqrt(E))
Source: KACTL
To recover flow, look at positive values only

*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct PushRelabel {
	struct Edge {
		int to, be; LL flow, cap;
	};
	vector<vector<Edge>> adj;
	vector<LL> ec;
	vector<Edge*> cur;
	vector<vector<int>> hs;
	vector<int> H;
	PushRelabel(int n) : adj(n), ec(n), cur(n), hs(2*n), H(n) {}

	void addEdge(int s, int t, LL cap, LL rcap=0) {
		if (s == t) return;
		adj[s].push_back({t, adj[t].size(), 0, cap});
		adj[t].push_back({s, adj[s].size()-1, 0, rcap});
	}

	void addFlow(Edge& e, LL flow) {
		Edge &be = adj[e.to][e.be];
		if (!ec[e.to] && flow) hs[H[e.to]].push_back(e.to);
		e.flow += flow; e.cap -= flow; ec[e.to] += flow;
		be.flow -= flow; be.cap += flow; ec[be.to] -= flow;
	}
	LL maxFlow(int s, int t) {
		int v = adj.size();
		H[s] = v; ec[t] = 1;

		vector<int> co(2*v); co[0] = v-1;
		for (int i=0; i<v; i++) cur[i] = adj[i].data();
		for (Edge& e : adj[s]) addFlow(e, e.cap);

		for (int hi = 0;;) {
			while (hs[hi].empty())
                if (!hi--) return -ec[s];
			int u = hs[hi].back();
			hs[hi].pop_back();

			while (ec[u] > 0)  // discharge u
				if (cur[u] == adj[u].data() + adj[u].size()) {
					H[u] = 1e9;
					for (Edge& e : adj[u])
                        if (e.cap && H[u] > H[e.to]+1)
                            H[u] = H[e.to]+1, cur[u] = &e;

					if (++co[H[u]], !--co[hi] && hi < v)
						for (int i=0; i<v; i++)
                            if (hi < H[i] && H[i] < v)
                                --co[H[i]], H[i] = v + 1;
					hi = H[u];
				}
				else if (cur[u]->cap && H[u] == H[cur[u]->to]+1)
					addFlow(*cur[u], min(ec[u], cur[u]->cap));
				else cur[u]++;
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= adj.size(); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    int s = 1, t = n;
    cin>>s>>t;

    PushRelabel solver(n+1);
    while (m--) {
        int a, b, cap;
        cin>>a>>b>>cap;
        solver.addEdge(a, b, cap);
    }
    cout<<solver.maxFlow(s, t)<<endl;
}
