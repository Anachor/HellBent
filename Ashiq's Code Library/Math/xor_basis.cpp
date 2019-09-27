#include <bits/stdc++.h>
using namespace std;

/// not tested yet

typedef long long ll;

const int N = 1e6 + 100;
const int lg = 18;

vector<int> xor_basis(vector <int> a) {
    int n = a.size();
    int row = 0;
    vector<int> basis;
    vector<bool> colm(lg, 0);
    for(int k = lg-1; k >= 0; k--) {
        for(int i = row; i < n; i++) {
            if((a[i]>>k)&1) {
                swap(a[i], a[row]);
                break;
            }
        }
        if(row < n && (a[row]>>k)&1) {
            basis.push_back(a[row]);
            colm[k] = 1;
            for(int i = row + 1; i < n; i++) {
                if((a[i]>>k)&1) a[i] ^= a[row];
            }
            row++;
        }
    }
    return basis;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    xor_basis(a);
    return 0;
}
