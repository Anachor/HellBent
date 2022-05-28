#include <bits/stdc++.h>
using namespace std;
/// 1D BIT

struct BIT {
    int n;
    vector<int> tree;
    void init(int n_) {
        n = n_;
        tree.assign(n+1,0);
    }
    void upd (int idx, int val) {
        while (idx <= n) {
            tree[idx] += val ;
            idx += idx & (-idx) ;
        }
    }
    int query (int idx) {
        int sum = 0 ;
        while (idx > 0) {
            sum += tree[idx] ;
            idx -= idx & (-idx) ;
        }
        return sum ;
    }
    int Sum(int i, int j) {
        return query(j)-query(i-1);
    }
};

int main() {

}
