/// 2D Partial SUM
/// x1,y1,x2,y2 >= 1 : this must be true

#include <bits/stdc++.h>
using namespace std;
int a[1001][101];

int main () {
    while (true) {
        int x1 , y1 , x2 , y2 , x ;
        cin >> x1 >> y1 >> x2 >> y2 >> x;
        if (x1 == 0) break;
        a[x1][y1] += x;
        a[x1][y2+1] -= x;
        a[x2+1][y1] -= x;
        a[x2+1][y2+1] += x;
    }
    for(int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            a[i][j] += a[i][j-1] + a[i-1][j] - a[i-1][j-1] ;
            cout << a[i][j] << " " ;
        }
        cout << endl ;
    }
    return 0;
}
