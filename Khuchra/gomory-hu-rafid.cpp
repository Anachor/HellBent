#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define INF 2000000000
const int MAX_E=60003;
const int MAX_V=5003;
int ver[MAX_E],cap[MAX_E],nx[MAX_E],last[MAX_V],ds[MAX_V],st[MAX_V],now[MAX_V],edge_count,S,T;

inline void reset()
{
	memset(nx,-1,sizeof(nx));
	memset(last,-1,sizeof(last));
	edge_count=0;
}
inline void addedge(const int v,const int w,const int capacity,const int reverse_capacity)
{
	ver[edge_count]=w; cap[edge_count]=capacity; nx[edge_count]=last[v]; last[v]=edge_count++;
	ver[edge_count]=v; cap[edge_count]=reverse_capacity; nx[edge_count]=last[w]; last[w]=edge_count++;
}
inline bool bfs()
{
	memset(ds,-1,sizeof(ds));
	int a,b;
	a=b=0;
	st[0]=T;
	ds[T]=0;
	while (a<=b)
	{
		int v=st[a++];
		for (int w=last[v];w>=0;w=nx[w])
		{
			if (cap[w^1]>0 && ds[ver[w]]==-1)
			{
				st[++b]=ver[w];
				ds[ver[w]]=ds[v]+1;
			}
		}
	}
	return ds[S]>=0;
}
int dfs(int v,int cur)
{
	if (v==T) return cur;
	for (int &w=now[v];w>=0;w=nx[w])
	{
		if (cap[w]>0 && ds[ver[w]]==ds[v]-1)
		{
			int d=dfs(ver[w],min(cur,cap[w]));
			if (d)
			{
				cap[w]-=d;
				cap[w^1]+=d;
				return d;
			}
		}
	}
	return 0;
}
inline long long flow()
{
	long long res=0;
	while (bfs())
	{
		for (int i=0;i<MAX_V;i++) now[i]=last[i];
		while (1)
		{
			int tf=dfs(S,INF);
			res+=tf;
			if (!tf) break;
		}
	}
	return res;
}

typedef struct { int u, v, w; } edge;

// returns edges of gomory hu tree
// nodes are labeled 1..n here and also in dinic
vector<edge> gomory_hu(int n, vector<edge> &e) {
	vector<edge> edg;
	vector<int> par(n+1, 1);

	for(int i=2; i<=n; ++i) {
		reset();
		for(auto &qq : e) addedge(qq.u, qq.v, qq.w, qq.w);
		S = par[i], T = i;
		edg.push_back( { par[i], i, (int) flow() } );

		for(int j=i+1; j<=n; ++j) {
			if(ds[j] >= 0 and par[j] == par[i]) {
				par[j] = i;
			}
		}
	}
	return edg;
}

// ------------------ BEGIN CUT ------------------
// The following solves CF 343E. Pumping Stations

const int N = 207;
int par[N];
vector<int> seq[N];	// node sequences

inline int Find(int r) {
	return par[r] == r ? r : par[r] = Find(par[r]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector< edge > e;
	while(m--) {
		int u, v, c;
		cin >> u >> v >> c;
		e.push_back( { u, v, c } );
	}

	auto edg = gomory_hu(n, e);
	// for(auto &qq : edg) {
	// 	cerr << qq.u << " - " << qq.v << ": " << qq.w << "\n";
	// }
	sort(edg.begin(), edg.end(), [](edge &p, edge &q) { return p.w > q.w; });
	for(int i=1; i<=n; ++i) {
		par[i] = i;
		seq[i].push_back(i);
	}

	int res = 0;
	for(auto &qq : edg) {
		int pu = Find(qq.u), pv = Find(qq.v);
		if(pu != pv) {
			par[pv] = pu;
			seq[pu].insert(seq[pu].end(), seq[pv].begin(), seq[pv].end());
		}
		res += qq.w;
	}

	cout << res << "\n";
	int root = Find(1);
	for(auto &qq : seq[root]) {
		cout << qq << " ";
	} cout << "\n";

	return 0;
}
