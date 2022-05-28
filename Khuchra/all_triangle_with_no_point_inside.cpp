#include <bits/stdc++.h>
using namespace std ;

struct Point {
    int x, y ;
    Point() {}
    Point(int x_,int y_) {x=x_,y=y_;}
    Point operator + (const Point &p) {
        return Point(x+p.x,y+p.y);
    }
    Point operator - (const Point &p) {
        return Point(x-p.x,y-p.y);
    }
    Point operator * (int t) {
        return Point(x*t,y*t);
    }
    int operator * (const Point &p) {
        return x*p.x + y*p.y;
    }
    int operator ^ (const Point &p) {
        return x*p.y - y*p.x;
    }
    bool operator < (const Point &p) const {
        return make_pair(y,x) < make_pair(p.y,p.x);
    }
};

bool comp(Point p, Point q) {
    return ( (p^q) > 0 );
}


int main() {
    freopen("farmer.in","r",stdin);
    freopen("farmer.out","w",stdout);
    int n ; cin >> n ;
    vector <Point> P(n) ;
    for(int i = 0 ; i < n ; i++) {
        cin >> P[i].x >> P[i].y;
    }
    sort(P.begin(),P.end());

    int ans = 0;
    for(int i = 0 ; i < n ; i++) {
        Point p = P[i];
        vector<Point> upper;
        for(int j = i+1 ; j < n ; j++) {
            upper.push_back(P[j]-p) ;
        }
        sort(upper.begin(),upper.end(),comp);
        for(int j = 0 ; j + 1 < upper.size() ; j++) {
            Point p = upper[j];
            Point q = upper[j+1];
            for(int k = j + 1 ; k < upper.size() ; k++) {
                Point r = upper[k];
                if ( ((q-p)^(r-p)) >= 0 ) {
                    q = r;
                    ans++;
                }
            }
        }
    }
    printf ("%d\n" , ans);
}
