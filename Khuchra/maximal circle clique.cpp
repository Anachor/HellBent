/*
You are given a disk of radius R with its center at the origin and N integer points outside that disk. Let us consider a graph on these points as vertices, where points A and B are connected by an edge if and only if the line AB does not intersect the disk.

Find the maximal clique in this graph
*/
#include <bits/stdc++.h>
using namespace std ;

const int N = 5005 ;
const double pi = acos(-1.0) ;

struct Data {
    double a , b ;
    int id ;
    bool operator < (const Data &p) {
        return a < p.a ;
    }
}P[N];

bool comp(Data p, Data q) {
    p.a < q.a ;
}

int main() {
    int n , r ;
    cin >> n >> r ;
    for(int i = 1 ; i <= n ; i++) {
        int x , y ;
        cin >> x >> y ;
        double u = atan2((double)y,(double)x) ;
        double range = acos(r/sqrt(x*x+y*y)) ;
        double a = u-range , b = u+range ;
        if (a <= -pi) {
            a += 2.0*pi ;
        }
        if (b > pi) {
            b -= 2.0*pi ;
        }
        if (a > b) swap(a,b);
        P[i] = {a,b,i} ;
    }
    sort(P+1,P+n+1) ;
    int ans = 0 ;
    vector <int> res ;
    for(int i = 1; i <= n; i++) {
        vector<int> par(n+1,-1) ;
        vector < pair<double,int> > cur ;
        cur.push_back({P[i].b,i}) ;
        for(int j = i+1 ; j <= n ; j++) {
            if (P[j].a > P[i].b) break ;
            if (P[j].b < P[i].b) continue ;
            int sz = upper_bound(cur.begin(),cur.end(),make_pair(P[j].b,j))-cur.begin() ;
            if (sz == cur.size()) {
                par[j] = cur.back().second ;
                cur.push_back({P[j].b,j}) ;
            }
            else {
                cur[sz] = make_pair(P[j].b,j) ;
                par[j] = cur[sz-1].second;
            }
        }
        int cur_ans = cur.size() ;
        if (cur_ans > ans) {
            ans = cur_ans ;
            res.clear() ;
            int p = cur.back().second ;
            while(p!=-1) {
                res.push_back(P[p].id) ;
                p = par[p] ;
            }
        }
    }
    cout << ans << endl ;
    for(int x : res) {
        cout << x << " " ;
    }
}
