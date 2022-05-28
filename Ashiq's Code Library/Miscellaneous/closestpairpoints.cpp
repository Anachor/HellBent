/// Closest Pair Point
#include <bits/stdc++.h>
using namespace std ;

typedef pair<long long,long long> point ;

const int N = 1e5 + 5 ;
int a[N] ;

struct ClosestPairPoints {
    vector < point > points ;
    const long long INF = 1e18 ;

    void init() {
        points.clear() ;
    }
    void addPoint(point P) {
        points.push_back(P) ;
    }
    long long Dist (int i , int j) {
        long long dx = points[i].first - points[j].first ;
        long long dy = points[i].second - points[j].second ;
        return dx*dx + dy*dy ;
    }
    long long DivideAndConq(int l , int r) {
        if (r - l + 1 <= 3) {
            long long ans = INF;
            for (int i = l ; i <= r ; i++) {
                for (int j = i+1 ; j <= r ; j++) {
                    ans = min(ans , Dist(i,j)) ;
                }
            }
            return ans ;
        }
        int mid = (l + r) / 2 ;
        long long ans = min(DivideAndConq(l,mid),DivideAndConq(mid+1,r)) ;
        vector < pair<long long,long long> > between ;
        for (int i = l ; i <= r ; i++) {
            long long dx = points[mid].first - points[i].first ;
            if (dx*dx < ans) {
                between.push_back({points[i].second,points[i].first}) ;
            }
        }
        sort(between.begin(),between.end()) ;
        for (int i = 0 ; i < between.size() ; i++) {
            for (int j = i + 1 ; j < between.size() ; j++) {
                long long dy = between[i].first - between[j].first ;
                if (dy*dy >= ans) {
                    break ;
                }
                long long dx = between[i].second - between[j].second ;
                ans = min(ans , dx*dx + dy*dy) ;
            }
        }
        return ans ;
    }

    long long ClosestPair() {
        sort(points.begin(),points.end()) ;
        return DivideAndConq(0,(int)points.size()-1) ;
    }
};


int main() {
    int n ;
    cin >> n ;
    ClosestPairPoints T ;
    T.init() ;
    for (int i = 1 ; i <= n ; i++) {
        point P ;
        cin >> P.first >> P.second ;
        T.addPoint(P) ;
    }
    printf ("%lld\n",T.ClosestPair()) ;
}
