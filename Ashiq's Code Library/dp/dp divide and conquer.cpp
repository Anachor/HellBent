#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5005 ;
int n , K;
int a[N];
int dp[N][N] ,cost[N][N] ;

void solve(int i , int l , int r , int ql , int qr){
    if(r < l){
        return;
    }
    int mid = (l + r)/2 ;
    int idx = -1;
    int val = 0 ;
    for(int j = ql ; j <= min(qr , mid) ; ++j){
        int tmp = dp[i - 1][j - 1] + cost[j][mid];
        if(tmp >= val){
            val = tmp;
            idx = j;
        }
    }
    dp[i][mid] = val;
    solve(i , l , mid - 1 , ql , idx);
    solve(i , mid + 1 , r , idx , qr);
}

int main(){
    int tc ; cin >> tc ;
    while (tc--) {
        scanf ("%lld %lld" , &n , &K);
        for (int i = 1 ; i <= n ; i++) {
            scanf ("%lld" , &a[i]) ;
            dp[1][i] = dp[1][i-1]|a[i] ;
        }
        for (int i = 1 ; i <= n ; i++) {
            for (int j = i ; j <= n ; j++) {
                cost[i][j] = cost[i][j-1]|a[j] ;
            }
        }
        for (int k = 2; k <= K ; k++) {
            solve(k,1,n,1,n) ;
        }
        printf ("%lld\n" , dp[K][n]) ;
    }
}
