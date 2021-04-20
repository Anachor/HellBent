///Visibility Polygon

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
struct PT {
  LL x, y;
  PT() {}
  PT(LL x, LL y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (LL c)     const { return PT(x*c,   y*c  ); }
  PT operator / (LL c)     const { return PT(x/c,   y/c  ); }
};

LL dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
LL dist2(PT p, PT q)   { return dot(p-q,p-q); }
LL cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
LL cross(PT a, PT b, PT c) { return cross(b-a, c-a);}

ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}

bool half(PT p) {
    assert(p.x || p.y);
    return p.y > 0 || (p.y == 0 && p.x > 0);
}

int compare(PT a, PT b) {
    auto l = make_tuple(half(b), 0);
    auto r = make_tuple(half(a), cross(a, b));
    return l==r ? 0 : ( l<r ? -1 : 1) ;
}

double distance(PT X, PT A, PT B) {
    B = B-A;
    assert(cross(X, B));
    return sqrt(dot(X, X))*cross(A, B)/cross(X, B);
}

bool compareDis(PT X, PT A, PT B, PT AA, PT BB) {
    B = B-A;
    BB = BB-AA;
    assert(cross(X, B) && cross(X, BB));
    return 1.0*cross(A, B)/cross(X, B) <  1.0*cross(AA, BB)/cross(X, BB);
}

pair<double, double> shoot(PT X, double len) {
    double rat = len/sqrt(dot(X, X));
    return make_pair(X.x*rat, X.y*rat);
}


vector<pair<double, double>> getVisibilityPolygon(PT Z, vector<PT> &p) {
    for (PT &X: p)  X = X-Z;
    int n = p.size();
    PT O(0, 0);

    auto comp = [](PT a, PT b) {return compare(a, b) < 0;};
    map<PT, vector<int>, decltype(comp) > events(comp);

    for (int i=1; i<=n; i++) {
        PT X = p[i-1], Y = p[i%n];
        if (cross(O, X, Y) < 0) swap(X, Y);
        if (compare(X, Y) == 0) continue;
        events[X].push_back(i);
        events[Y].push_back(-i);
    }

    PT dir, last = events.rbegin() -> first;
    auto comp2 = [&dir, &p, &n](int i, int j) {return compareDis(dir, p[i-1], p[i%n], p[j-1], p[j%n]); };
    multiset<int, decltype(comp2)> st(comp2);

    vector<bool> open(n+1);
    for (auto pr: events) {
        for (int v: pr.second)
            if (v > 0)  open[v] = 1;
        for (int v: pr.second)
            if (v < 0)  open[-v] = 0;
    }

    vector<int> pending;
    vector<pair<double, double>> poly;

    for (int i=1; i<=n; i++)
        if (open[i]) pending.push_back(i);

     for (auto pr: events) {
        PT nw = pr.first;
        dir = nw+last;

        for (int i: pending) st.insert(i);
        pending.clear();

        int i = *st.begin();
        poly.push_back(shoot(last, distance(last, p[i-1], p[i%n])));
        poly.push_back(shoot(nw, distance(nw, p[i-1], p[i%n])));

        for (int i: pr.second) {
            if (i < 0)  st.erase(-i);
            else        pending.push_back(i);
        }
        last = nw;
    }
    return poly;

}


///Solves Timus 1464. Light
const int PR = 100000;
PT inputPoint() {
    double x, y;
    cin>>x>>y;
    return PT( round(x*PR), round(y*PR) );
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    PT Z = inputPoint();

    int n;
    cin>>n;

    vector<PT> p;
    for (int i=1; i<=n; i++) {
        p.push_back(inputPoint());
    }

    double ans = 0;
    auto poly = getVisibilityPolygon(Z, p);

    for (int i=0; i<poly.size(); i++) {
        int n = (i+1)%poly.size();
        ans += poly[i].first*poly[n].second - poly[i].second*poly[n].first;
    }
    cout<<setprecision(5)<<fixed<<abs(ans/2.0/PR/PR)<<"\n";
}

