
/*
    Heavy-Light Decomposition
    1.  flat[] (0-indexed) has the flattened array of the tree according
        to the decomposition into chains
    2.  flatIdx[] is the reverse map of flat[]
    3.  There will be O(logN) segments of chains between node u & v.
    4.  getChainSegments(u, v) calculates these in O(logN) time
    5.  dfs(u, p) & HLD(u, p) are essential. The rest of the functions
        are auxiliary

    Author: solaimanope
*/

#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>PII;
const int MAXN = 500007;
const int LOGN = 20;
vector<int>edg[MAXN];

int sbtr[MAXN], lvl[MAXN], pr[MAXN][LOGN];
int chainIdx[MAXN], chainHead[MAXN], flatIdx[MAXN], flat[MAXN];
int chainCnt, flatCnt;

void dfs(int u, int p)
{
    lvl[u] = lvl[p] + 1;
    pr[u][0] = p;
    for (int k = 1; k < LOGN; k++) {
        pr[u][k] = pr[pr[u][k-1]][k-1];
    }

    sbtr[u] = 1;
    for (int v : edg[u]) {
        if (v==p) continue;
        dfs(v, u);
        sbtr[u] += sbtr[v];
    }
}

/// auxiliary function
int getLCA(int u, int v)
{
    if (lvl[u] < lvl[v]) swap(u, v);
    for (int k = LOGN-1; k >= 0; k--) {
        if (lvl[u]-(1<<k) >= lvl[v]) {
            u = pr[u][k];
        }
    }
    if (u==v) return u;
    for (int k = LOGN-1; k >= 0; k--) {
        if (pr[u][k] != pr[v][k]) {
            u = pr[u][k];
            v = pr[v][k];
        }
    }
    return pr[u][0];
}

void HLD(int u, int p)
{
    chainIdx[u] = chainCnt;
    flatIdx[u] = flatCnt;
    flat[flatCnt] = u;
    flatCnt++;

    int biggie = -1, mx = 0;
    for (int v : edg[u]) {
        if (v==p) continue;
        if (mx < sbtr[v]) {
            mx = sbtr[v];
            biggie = v;
        }
    }
    if (biggie==-1) return;

    HLD(biggie, u);
    for (int v : edg[u]) {
        if (v==p||v==biggie) continue;
        chainCnt++;
        chainHead[chainCnt] = v;
        HLD(v, u);
    }
}

/// upSegments(l, u, vp) add segments for (l, u] to vp vector
/// provided l is an ancestor of u
void upSegments(int l, int u, vector<PII>&vp)
{
    while (chainIdx[l] != chainIdx[u]) {
        int uhead = chainHead[chainIdx[u]];
        vp.push_back(PII(flatIdx[uhead], flatIdx[u]));
        u = pr[uhead][0];
    }
    if (l!=u) {
        vp.push_back(PII(flatIdx[l]+1, flatIdx[u]));
    }
}

vector<PII>getChainSegments(int u, int v)
{
    int l = getLCA(u, v);
    vector<PII>rt;
    rt.push_back(PII(flatIdx[l], flatIdx[l]));
    if (u==v) return rt;
    upSegments(l, u, rt);
    upSegments(l, v, rt);
    return rt;
}

PII getSubtreeSegment(int u) {
    return PII(flatIdx[u], flatIdx[u]+sbtr[u]-1);
}

void performHLD(int root)
{
    dfs(root, 0);
    chainCnt = 0;
    flatCnt = 0;
    chainHead[0] = root;
    HLD(root, 0);
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edg[u].push_back(v);
        edg[v].push_back(u);
    }

    performHLD(1);

    for (int i = 0; i < n; i++) cout << flat[i] << ' ';


    return 0;
}
