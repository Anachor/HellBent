#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
    ll x, y;
    bool operator < (const point &P) {
        return make_pair(x, y) < make_pair(P.x, P.y);
    }
    bool operator != (const point &P) {
        return make_pair(x, y) != make_pair(P.x, P.y);
    }
};

bool CCW (point a , point b , point c) {
    long long area = ( a.x - b.x ) * ( b.y - c.y ) - ( b.x - c.x ) * ( a.y - b.y );
    if (area > 0) return 1; /// change to  >= 0 if redundant points are also required
    return 0;
}

void monotone_chain (vector <point> &p, vector <point> &hull) {
    hull.clear();
    sort (p.begin() , p.end());
    vector <point> L, U;
    for(int i = 0 ; i < p.size() ; i++) {
        while(L.size() >= 2 and !CCW(L[L.size()-2] , L.back() , p[i])) {
            L.pop_back();
        }
        L.push_back(p[i]);
    }
    for(int i = (int)p.size()-1 ; i >= 0 ; i--) {
        while(U.size() >= 2 and !CCW(U[U.size()-2] , U.back() , p[i])) {
            U.pop_back();
        }
        U.push_back(p[i]);
    }
    for(int i = 0; i < L.size(); i++) hull.push_back(L[i]);
    if (L.back() != U[0]) hull.push_back(U[0]);
    for(int i = 1; i + 1 < U.size(); i++) hull.push_back(U[i]);
    if (U.back()!=L[0]) hull.push_back(U.back());
}

int main () {
    int n;
    cin >> n;
    vector <point> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
    }
    vector <point> hull;
    monotone_chain(v, hull);
    for(int i = 0; i < hull.size(); i++) {
        cout << hull[i].x << " " << hull[i].y << endl;
    }
    return 0 ;
}
