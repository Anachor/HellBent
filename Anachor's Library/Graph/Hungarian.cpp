/**
    Hungarian algorithm for minimum weighted bipartite matching. (1-indexed)
    For max cost, negate cost matrix and negate output.
    Complexity: O(n^2 m). n must not be greater than m.

    Input: (n+1) x (m+1) cost matrix. (0th row and column are useless)
    Output: (ans, ml), where ml[i] = match for node i on the left.

    Source: upobir
*/
#include<bits/stdc++.h>
using namespace std;

template<typename T>
pair<T, vector<int>> Hungarian(const vector<vector<T>> &cost){
    const T INF = numeric_limits<T>::max();
    int n = cost.size()-1, m = cost[0].size()-1;
    vector<T> U(n+1), V(n+1);
    vector<int> mr(m+1), way(m+1), ml(n+1);

    for(int i = 1; i<=n; i++){
        mr[0] = i;
        int lastJ = 0;
        vector<T> minV(m+1, INF);
        vector<bool> used(m+1);
        do{
            used[lastJ] = true;
            int lastI = mr[lastJ], nextJ;
            T delta = INF;
            for(int j = 1; j<=m; j++){
                if(used[j]) continue;
                T diffCost = cost[lastI][j] - U[lastI] - V[j];
                if(diffCost < minV[j]) minV[j] = diffCost, way[j] = lastJ;
                if(minV[j] < delta) delta = minV[j], nextJ = j;
            }
            for(int j = 0; j<=m; j++){
                if(used[j]) U[mr[j]] += delta, V[j] -= delta;
                else        minV[j] -= delta;
            }
            lastJ = nextJ;
        } while(mr[lastJ] != 0);
        do{
            int prevJ = way[lastJ];
            mr[lastJ] = mr[prevJ];
            lastJ = prevJ;
        } while(lastJ != 0);
    }
    for (int i=1; i<=m; i++)    ml[mr[i]] = i;
    return {-V[0], ml} ;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    vector<vector<long long>> cost(n+1, vector<long long>(n+1));
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)    cin>>cost[i][j];

    auto [ans, match] = Hungarian(cost);
    cout<<ans<<endl;
    for (int i=1; i<=n; i++)    cout<<match[i]-1<<" ";
}
