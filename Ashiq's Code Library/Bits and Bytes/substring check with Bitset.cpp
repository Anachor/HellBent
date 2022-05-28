/// How many times a string occur in another one using Bitset
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
char s[N], t[N];
bitset <N> bs[26], cur;

int main () {
    //freopen ("in.txt", "r" , stdin) ;
    scanf ("%s" , s+1);
    int n = strlen(s+1);
    for (int i = 1; i <= n; i++) bs[s[i]-'a'][i] = 1;
    int q;
    cin >> q;
    while (q--) {
        int type;
        scanf ("%d", &type);
        if (type == 1) {
            int idx;
            scanf ("%d", &idx);
            scanf("%s",t);
            bs[s[idx]-'a'][idx] = 0;
            s[idx] = t[0];
            bs[s[idx]-'a'][idx] = 1;
        }
        else {
            int l, r;
            scanf ("%d %d %s" , &l, &r, t+1);
            int m = strlen(t+1);
            if (r-l+1 < m) {
                printf("0\n");
                continue;
            }
            cur.reset();
            cur = ~cur;
            for (int i = 1 ; i <= m ; i++) {
                cur &= (bs[t[i]-'a']>>(i-1)) ;
            }
            cur >>= l;
            int ans = cur.count();
            cur >>= (r-l-m+2);
            ans -= cur.count();
            printf ("%d\n",ans);
        }
    }
}
