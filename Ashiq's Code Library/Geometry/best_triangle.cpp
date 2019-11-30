// https://codeforces.com/problemset/problem/682/E
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;
typedef long long ll;

struct PT {
    ll x, y;
    PT(ll x_, ll y_) {
        x = x_, y = y_;
    }
    PT() {}
    PT operator + (const PT &p) {
        return PT(x+p.x, y+p.y);
    }
    PT operator - (const PT &p) {
        return PT(x-p.x, y-p.y);
    }
    ll operator * (const PT &p) {
        return x*p.x + y*p.y;
    }
    ll operator ^ (const PT &p) {
        return x*p.y - y*p.x;
    }
    bool operator < (const PT &p) {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
};

bool ccw(PT p, PT q, PT r) {
    long long cross = (q-p)^(r-q);
    return cross > 0;
}

void init(vector<PT> &poly) {
    vector<PT> hull, lower, upper;
    sort(poly.begin(),poly.end()) ;
    for(int i = 0 ; i < poly.size() ; i++) {
      while(lower.size() >= 2 and !ccw(lower[lower.size()-2],lower.back(),poly[i])) {
          lower.pop_back() ;
      }
      lower.push_back(poly[i]) ;
    }
    for(int i = (int)poly.size()-1 ; i >= 0 ; i--) {
      while(upper.size() >= 2 and !ccw(upper[upper.size()-2],upper.back(),poly[i])) {
        upper.pop_back() ;
      }
      upper.push_back(poly[i]) ;
    }
    hull = lower;
    for(int i = 1 ; i + 1 < upper.size() ; i++) hull.push_back(upper[i]);
    poly = hull;
}

ll Area(PT p, PT q, PT r) {
    return (q-p)^(r-q);
}

int main() {
    // freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    long long S;
    cin >> n >> S;
    vector<PT> P(n);
    for(int i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
    }
    init(P);
    n = P.size();
    ll best = 0;
    int a, b, c;
    for(int i = 0; i < n; i++) {
        int k = (i+1)%n;
        for(int j = (i+1)%n; j != i; j = (j+1)%n) {
            while(Area(P[i], P[j], P[(k+1)%n]) > Area(P[i], P[j], P[k])) {
                k = (k+1)%n;
            }
            if(Area(P[i], P[j], P[k]) > best) {
                best = Area(P[i], P[j], P[k]);
                a = i, b = j, c = k;
            }
        }
    }
    ll x1 = P[a].x + P[b].x - P[c].x, x2 = P[a].x + P[c].x - P[b].x, x3 = P[b].x + P[c].x - P[a].x;
    ll y1 = P[a].y + P[b].y - P[c].y, y2 = P[a].y + P[c].y - P[b].y, y3 = P[b].y + P[c].y - P[a].y;
    cout << x1 << " " << y1 << endl;
    cout << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << endl;
    return 0;
}

