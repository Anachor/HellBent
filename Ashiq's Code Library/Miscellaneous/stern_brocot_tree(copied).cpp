#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second

/// finds a fraction x/y with minimum y, such that L <= (x/y) < R
/// https://codeforces.com/blog/entry/50244

pair<long long, long long> solve(long double const&L, long double const&R){
    pair<long long, long long> l(0, 1), r(1, 1);
    if(L==0.0) return l; // corner case
    for(;;){
        pair<int, int> m(l.x+r.x, l.y+r.y);
        if(m.x<L*m.y){// move to the right;
            long long kl=1, kr=1;
            while(l.x+kr*r.x <= L*(l.y+kr*r.y))kr*=2;// exponential search
            while(kl!=kr){
                long long km = (kl+kr)/2;
                if(l.x+km*r.x < L*(l.y+km*r.y)) kl=km+1;
                else kr=km;
            }
            l = make_pair(l.x+(kl-1)*r.x, l.y+(kl-1)*r.y);
        } else if(m.x>=R*m.y){//move to the left
            long long kl=1, kr=1;
            while(r.x+kr*l.x>=R*(r.y+kr*l.y))kr*=2;// exponential search
            while(kl!=kr){
                long long km = (kl+kr)/2;
                if(r.x+km*l.x>=R*(r.y+km*l.y)) kl = km+1;
                else kr = km;
            }
            r = make_pair(r.x+(kl-1)*l.x, r.y+(kl-1)*l.y);
        } else {
            return m;
        }
    }
}


int main() {
    double L = 0.1, R = 0.5;
    pair<long long,long long> res = solve(L,R);
    cout << res.x << " " << res.y << endl;
}
