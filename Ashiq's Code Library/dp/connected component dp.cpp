/// Problem: Given an array A, find all permutations of A such that,
/// |A1-A2| + |A2-A3| + ... <= L , n <= 100, L <= 1000, Ai <= 1000
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 2147483647;

int arr[1010];
int n, l;

int mem[110][1010][2][110][2];
int mod = 1000000007;

ll dp(int at, int curl, int kl, int k, int kr) {

    // kl = 1 if there is a segment connected to the left border, 0 otherwise
    // kr = 1 if there is a segment connected to the right border, 0 otherwise
    // k is the number of segments in the middle

    int nxtl = curl;
    if (at > 0) {
        // add the penalty from the last element:
        nxtl += (kl+kr+2*k)*abs(arr[at]-arr[at-1]);
    }

    if (nxtl > l) return 0;
    if (k < 0) return 0;

    if (at == n-1) {
        return k == 0 ? 1 : 0;
    }
    if (mem[at][curl][kl][k][kr] != -1)
        return mem[at][curl][kl][k][kr];

    ll res = 0;

    res += dp(at+1, nxtl, 1, k, kr); // connect to left segment
    res += dp(at+1, nxtl, 1, k-1, kr)*k; // connect to left segment, and join to some middle segment

    res += dp(at+1, nxtl, kl, k, 1); // connect to right segment
    res += dp(at+1, nxtl, kl, k-1, 1)*k; // connect to right segment, and join to some middle segment

    res += dp(at+1, nxtl, kl, k+1, kr); // new segment
    res += dp(at+1, nxtl, kl, k, kr)*k*2; // connect to some middle segment
    res += dp(at+1, nxtl, kl, k-1, kr)*k*(k-1); // join two middle segments

    return mem[at][curl][kl][k][kr] = res % mod;
}

int main() {
    memset(mem,-1,sizeof(mem));
    cin >> n >> l;
    for(int i = 0; i < n; i++) cin >> arr[i];
    sort(arr,arr+n);
    cout << dp(0, 0, 0, 0, 0) << endl;
    return 0;
}
