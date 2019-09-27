#include <bits/stdtr1c++.h>

#define MAX 100010

using namespace std;

/// 1 based index for arrays and trees
vector <int> adj[MAX];
int r, S[MAX], E[MAX]; /// S[i] = starting index of subtree rooted at i, E[i] = ending index of the subtree rooted at i

void dfs(int i, int p){
    if (n == 1){
        S[i] = E[i] = ++r;
        return;
    }
    int j, x, len = adj[i].size();

    S[i] = ++r;
    for (j = 0; j < len; j++){
        if (adj[i][j] != p) dfs(adj[i][j], i);
    }
    E[i] = r;
}

int main(){
    r = 0;
    dfs(1, 0); /// 1 is root
}
