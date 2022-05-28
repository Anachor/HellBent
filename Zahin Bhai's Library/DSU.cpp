#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace dsu{
    int n, parent[MAX], counter[MAX];

    inline void init(int nodes){
        n = nodes;
        for (int i = 0; i <= n; i++){
            parent[i] = i;
            counter[i] = 1;
        }
    }

    inline int find_root(int i){
        while (i != parent[i]){
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return parent[i];
    }

    inline void merge(int a, int b){
        int c = find_root(a), d = find_root(b);
        if (c != d){
            parent[c] = d;
            counter[d] += counter[c], counter[c] = 0;
        }
    }

    inline bool connected(int a, int b){
        int c = find_root(a), d = find_root(b);
        return (c == d);
    }

    inline int component_size(int i){
        int p = find_root(i);
        return counter[p];
    }
}

int main(){

}
