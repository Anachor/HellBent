/// Adjacency matrix implementation of Stoer-Wagner min cut algorithm.
/// Source: Stanford Notebook
/// Running time: O(n^3)
/// Input: Matrix c[i][j] = total weight between i and j. (0-indexed)
/// OUTPUT: (min cut value, nodes in half of min cut)

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
pair<LL,vector<int>> globalMinCut(vector<vector<LL>> c) {
    int N = c.size();
    LL best_w = -1;
    vector<int> used(N), cut, best_cut;

    for (int phase = N-1; phase >= 0; phase--) {
        vector<LL> w = c[0];
        vector<int> vis = used;
        int prev, last = 0;
        for (int i = 0; i < phase; i++) {
            prev = last;
            last = -1;
            for (int j = 1; j < N; j++)
                if (!vis[j] && (last==-1 || w[j] > w[last]))  last = j;
            if (i == phase-1) {
                for(int j=0; j<N; j++)  c[prev][j] += c[last][j];
                for(int j=0; j<N; j++)  c[j][prev]  = c[prev][j];
                used[last] = true;
                cut.push_back(last);
                if (best_w==-1 || w[last] < best_w) {
                    best_cut = cut;
                    best_w = w[last];
                }
            } else {
                for (int j=0; j<N; j++) w[j] += c[last][j];
                vis[last] = true;
            }
        }
    }
    return make_pair(best_w, best_cut);
}

/// Solves UVA problem #10989: Bomb, Divide and Conquer
int main() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int n, m;
    cin >> n >> m;
    vector<vector<LL>> weights(n, vector<LL>(n));
    for (int j = 0; j < m; j++) {
      int a, b, c;
      cin >> a >> b >> c;
      weights[a-1][b-1] = weights[b-1][a-1] = c;
    }
    auto res = globalMinCut(weights);
    cout << "Case #" << i+1 << ": " << res.first << endl;
  }
}
