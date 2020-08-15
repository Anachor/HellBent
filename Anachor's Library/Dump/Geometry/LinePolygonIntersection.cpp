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
LL cross(PT a, PT b, PT c)  { return cross(b-a, c-a);}
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}

///Distance from O to OX intersection AB, divided by length(OX)
double distance(PT O, PT X, PT A, PT B) {
    B = B-A; A = A-O; X=X-O;
    assert(cross(X, B));
    return 1.0*cross(A, B)/cross(X, B);
}

int sign(LL a) {
    return a==0 ? 0 : ( a>0 ? 1 : -1);
}

///Special Points are represented by pair<double, int> (a, b)
///Let O be a special point with OX and OY the incident edges.
///Then a = AO/AB, b is an integer denoting type.
///Cases: OX and OY are on the same side:   ignore
///Cases: OX and OY are on the different side:   b = 0
///Cases: OX collinear, OY on some side          b = sign(cross(A, B, Y))


double LinePolygonIntersection(PT A, PT B, const vector<PT> &p) {
    int n = p.size();
    vector<pair<double, int>> special;
    for (int i=0; i<n; i++) {
        PT X = p[i], Y = p[(i+1)%n], W = p[(i-1+n)%n];
        LL crx = cross(A, B, X), cry = cross(A, B, Y), crw = cross(A, B, W);

        if (crx == 0) {
            double f;
            if (B.x != A.x)  f = 1.0*(X.x-A.x)/(B.x-A.x);
            else             f = 1.0*(X.y-A.y)/(B.y-A.y);

            if (sign(crw) && sign(cry)) {
                if (sign(crw) != sign(cry))     special.push_back({f, 0});
            }
            else if (sign(cry))             special.push_back({f, sign(cry)});
            else if (sign(crw))             special.push_back({f, sign(crw)});
        }
        else if (sign(crx) == -sign(cry)) {
            double f = distance(A, B, X, Y);
            special.push_back({f, 0});
        }
    }

    sort(special.begin(), special.end());

    bool active = false;
    int sgn = 0;
    double prv = 0, ans = 0;

    for (auto &pr: special) {
        double d = pr.first;
        int tp = pr.second;

        if (sgn) {
            assert(sgn && tp);
            if (sgn != tp)  active = !active;
            ans += d - prv;
            sgn = 0;
        }
        else {
            if (active)         ans += d - prv;
            if (tp == 0)        active = !active;
            else                sgn = tp;
        }
        prv = d;
    }
    return ans*sqrt(dot(B-A, B-A));
}

///Solves CF 598F - Cut Length
const int PR = 100;
PT inputPoint() {
    double x, y;
    cin>>x>>y;
    return PT(round(PR*x), round(PR*y));
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    vector<PT> p(n);
    for (int i=0; i<n; i++) p[i] = inputPoint();

    while (m--) {
        PT A, B;
        A = inputPoint();
        B = inputPoint();
        cout<<setprecision(14)<<fixed<<LinePolygonIntersection(A, B, p)/PR<<endl;
    }
}
