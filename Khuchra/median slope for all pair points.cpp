#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree < pair<int,int> , null_type , less< pair<int,int> > ,rb_tree_tag,tree_order_statistics_node_update > ordered_set;

typedef long long db;

double dx, dy;

struct Point{
    db x, y;
    Point() {}
    Point(db x_,db y_) {x=x_,y=y_;}
    Point operator + (Point &p) {
        return Point(x+p.x,y+p.y);
    }
    Point operator - (Point &p) {
        return Point(x-p.x,y-p.y);
    }
    Point operator * (double t) {
        return Point(x*t,y*t);
    }
    db operator * (Point &p) {
        return x*p.x + y*p.y;
    }
    db operator ^ (Point &p) {
        return x*p.y - y*p.x;
    }
    bool operator < (const Point &p) const {
        return dx*y - dy*x < dx*p.y - dy*p.x;
    }
};

const double pi = acos(-1.0);
const int INF = 1e8;

double solve(vector<Point> &P,long long kth) {
    double lo = 0 , hi = pi;
    int n = P.size();
    for(int it = 1 ; it <= 35 ; it++) {
        double mid = (hi+lo)/2.0;
        long long cnt = 0;
        dx = cos(mid), dy = sin(mid);
        sort(P.begin(),P.end());
        ordered_set S ;
        for(int i = 0 ; i < n ; i++) {
            int c = S.order_of_key(make_pair(-P[i].y,INF));
            cnt += c;
            S.insert(make_pair(-P[i].y,i));
        }
        if(cnt >= kth) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}


int main() {

   // freopen ("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    vector<Point> P(n);
    for(int i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
    }
    double ans;
    long long m = (1ll*n*(n-1))/2;
    if(m&1) {
        ans = solve(P,m/2 + 1);
    }
    else {
        ans = 0.5*(solve(P,m/2)+solve(P,m/2+1));
    }
    cout << setprecision(12) << fixed << ans << endl;
}
