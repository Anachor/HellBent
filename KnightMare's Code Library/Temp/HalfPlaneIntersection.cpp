#include<bits/stdc++.h>
using namespace std;
double EPS = 1e-12;

struct PT {
  double x, y;
  PT() {}
  PT(double x, double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (double c)     const { return PT(x*c,   y*c  ); }
  PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double len(PT p)           { return sqrt(dot(p, p));}
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}

PT RotateCCW90(PT p)    { return PT(-p.y,p.x); }
PT RotateCW90(PT p)     { return PT(p.y,-p.x); }

bool LinesParallel(PT a, PT b, PT c, PT d) {
  return fabs(cross(b-a, c-d)) < EPS;
}

PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  return a + b*cross(c, d)/cross(b, d);
}

/// Set of points C such that A,B,C are ccw.
struct HalfPlane {
    PT A, B;

    bool onHalfPlane (PT p) {
        return cross(A-B, B-p) >= -EPS;
    }
};

///Get Halfplane for ax+by+c >= 0
HalfPlane getHalfPlane(double a, double b, double c) {
    PT A, B, C;
    if (abs(a) < EPS) {
        A = PT(0, -c/b);
        B = PT(1, -c/b);
    }
    else {
        A = PT(-c/a, 0);
        B = PT(-(b+c)/a, 1);
    }
    C = A + RotateCCW90(B-A);
    if (a*C.x+b*C.y+c < 0)  swap(A, B);
    return {A, B};
}

double INF = 1e100;

bool halfPlaneIntersection(vector<HalfPlane> planes) {
    int n = planes.size();
    shuffle(planes.begin(), planes.end(), mt19937(time(NULL)));

    PT best(INF, INF);
    for (int i=0; i<n; i++) {
        HalfPlane &hp = planes[i];
        if (hp.onHalfPlane(best))   continue;

        PT dir = hp.B - hp.A;
        dir = dir/len(dir);
        PT X = hp.A+dir*INF, Y = hp.A-dir*INF;

        for (int j=0; j<i; j++) {
            HalfPlane &cp = planes[j];
            if (LinesParallel(hp.A, hp.B, cp.A, cp.B)) {
                if (!cp.onHalfPlane(hp.A))  return false;
            }
            else {
                PT O = ComputeLineIntersection(hp.A, hp.B, cp.A, cp.B);
                bool bX = cp.onHalfPlane(X);
                bool bY = cp.onHalfPlane(Y);

                if (bX && bY)   continue;
                else if (bX)       Y = O;
                else if (bY)       X = O;
                else return false;
            }
        }

        if (X.x+X.y < Y.x + Y.y)    best = Y;
        else                        best = X;
    }
    return true;
}

///Solves DMOJ - Arrow (https://dmoj.ca/problem/ccoprep3p3)
///Set EPS to 1e-20 and use long double

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    vector<HalfPlane> planes;
    planes.push_back(getHalfPlane(-1, 0, 0));
    planes.push_back(getHalfPlane(0, 1, 0));
    for (int i=0; i<n; i++) {
        double x, y1, y2;
        cin>>x>>y1>>y2;
        planes.push_back(getHalfPlane(x*x, x, -y1));
        planes.push_back(getHalfPlane(-x*x, -x, y2));
    }

    int lo = 0, hi = n;
    while (lo < hi) {
        int m = (lo + hi+1)/2;
        vector<HalfPlane> cur(planes.begin(), planes.begin() + 2*m+2);
        if (halfPlaneIntersection(cur)) lo = m;
        else                            hi = m-1;
    }
    cout<<lo<<endl;
}
