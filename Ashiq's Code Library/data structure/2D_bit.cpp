/// 2D BIT
/// careful with if sum exceeds int limit
#include <bits/stdc++.h>
using namespace std ;

const int N = 1e3 + 5;
int BIT[N][N];

void upd (int idx, int idy, int n, int val) { /// n = maximum row and col
    int temp = idy;
    while (idx <= n) {
        idy = temp;
        while (idy <= n) {
            BIT[idx][idy] += val;
            idy += idy & (-idy);
        }
        idx += idx & (-idx);
    }
}
int query (int idx, int idy) {
    int sum = 0, temp = idy;
    while (idx > 0) {
        idy = temp;
        while (idy > 0) {
            sum += BIT[idx][idy];
            idy -= idy & (-idy);
        }
        idx -= idx & (-idx);
    }
    return sum;
}

int SUM (int x1, int y1, int x2, int y2) {
    return query(x2,y2)-query(x1-1,y2) - query(x2,y1-1)+query(x1-1,y1-1);
}

int main() {

    return 0;
}
