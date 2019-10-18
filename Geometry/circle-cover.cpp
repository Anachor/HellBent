///Circle Cover

#include<bits/stdc++.h>
using namespace std;
double EPS = 1e-10;

int dcmp (double a, double b) {
    if (abs(a-b) < EPS)     return 0;
    return a>b ? 1 : -1;
}

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }

  bool operator < (const PT &p) const {
    if (dcmp(x, p.x) == 0)      return dcmp(y, p.y) < 0;
    return dcmp(x, p.x) < 0;
  }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
double cross(PT a, PT b, PT c) {return cross(b-a, c-a);}
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }

vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ret;
  double d = sqrt(dist2(a, b));
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d);
  double y = sqrt(r*r-x*x);
  PT v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}

const double PI = acos(-1);

bool CoverCircle(PT O, double R, vector<PT> &cen, vector<double> &rad, PT OO, double RR) {
    cen.insert(cen.begin(), OO);
    rad.insert(rad.begin(), RR);
    assert(cen.size() == rad.size());
    int n = cen.size();

    vector<pair<double, double>> arcs;

    for (int i=0; i<n; i++) {
        PT P = cen[i];
        double r = rad[i];

        if (i!=0 && R + sqrt(dist2(O, P)) < r)      return true;
        if (i==0 && r + sqrt(dist2(O, P)) < R)      return true;

        vector<PT> inter = CircleCircleIntersection(O, P, R, r);
        if (inter.size() <= 1)  continue;

        PT X = inter[0], Y = inter[1];
        if (cross(O, X, Y) < 0) swap(X, Y);
        if (!(cross(O, X, P) >= 0 && cross(O, Y, P) <= 0))  swap(X, Y);
        if (i==0)       swap(X, Y);

        X = X-O; Y=Y-O;
        double ll = atan2(X.y, X.x);
        double rr = atan2(Y.y, Y.x);
        if (rr < ll)  rr += 2*PI;
        arcs.emplace_back(ll, rr);
    }

    if (arcs.empty())   return false;
    sort(arcs.begin(), arcs.end());

    double st = arcs[0].first, en = arcs[0].second, ans = 0;
    for (int i=1; i<arcs.size(); i++) {
        if (arcs[i].first <= en + EPS)    en = max(en, arcs[i].second);
        else st = arcs[i].first, en = arcs[i].second;
        ans = max(ans, en-st);
    }
    return ans >= 2*PI;
}

bool check(PT O, double R, vector<PT> cen, double mid) {
    int n = cen.size();
    for (int i=0; i<n; i++) {
        vector<PT> cc = cen;
        vector<double> rr(n, mid);
        cc.erase(cc.begin()+i);
        rr.erase(rr.begin()+i);
        if (!CoverCircle(cen[i], mid, cc, rr, O, R)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, R;
    cin>>n>>R;

    PT O(0, 0);
    vector<pair<int, int>> v(n);
    for (int i=0; i<n; i++) cin>>v[i].first>>v[i].second;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    n = v.size();
    vector<PT> p;
    for (int i=0; i<n; i++)     p.emplace_back(v[i].first, v[i].second);

    double lo = 0, hi = 1e4;
    while (hi - lo > 5e-6){
        double mid = (lo + hi)/2;
        if (check(O, R, p, mid))              hi = mid;
        else                                lo = mid;
    }
    cout<<setprecision(7)<<fixed<<lo<<endl;
}
