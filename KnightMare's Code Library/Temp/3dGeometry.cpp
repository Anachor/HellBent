/**
Almost everything is untested
Use at own risk :P - Anachor
*/

#include<bits/stdc++.h>
using namespace std;

double EPS = 1e-10;

struct PT {
    double x, y, z;
    PT() {}
    PT(double x, double y, double z) : x(x), y(y), z(z) {}
    PT(const PT &p) : x(p.x), y(p.y), z(p.z)    {}
    PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y, z+p.z); }
    PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y, z-p.z); }
    PT operator * (double c)     const { return PT(x*c,   y*c  , z*c  ); }
    PT operator / (double c)     const { return PT(x/c,   y/c  , z/c  ); }
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y+p.z*q.z; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
PT cross(PT p, PT q)       { return PT(p.y*q.z-p.z*q.y, p.z*q.x-p.x*q.z, p.x*q.y-p.y*q.x); }
double len2(PT p)          { return dot(p, p);}
double len(PT p)           { return sqrt(dot(p, p));}
double triple(PT a, PT b, PT c) {return dot(a, cross(b, c));}

bool isCoplanar(PT a, PT b, PT c, PT d) {
    return abs(triple(b-a, c-a, d-a)) < EPS;
}

ostream &operator<<(ostream &os, const PT &p) {
    return os << "(" << p.x << "," << p.y << "," << p.z << ")";
}

istream &operator>>(istream &is, PT &p) {
    return is >> p.x >> p.y >> p.z;
}

/// compute center of circle given three non collinear points
PT ComputeCircleCenter(PT a, PT b, PT c) {
    PT x = cross(b-a, c-a);
    assert(len2(x) > EPS);

    PT num1 = cross(x, b-a) * len2(c-a);
    PT num2 = cross(c-a, x) * len2(b-a);
    return a + (num1 + num2)/(len2(x)*2);
}

/// distance of Line ab from o
double PointLineDistance(PT a, PT b, PT o) {
    PT ab = b-a;
    PT oa = a-o;
    return len(cross(ab, oa))/len(ab);
}

/// distance from Line ab to Line cd
/// Unstable for nearly parallel lines
double LineLineDistance(PT a, PT b, PT c, PT d) {
    PT ab = b-a;
    PT cd = d-c;
    PT dir = cross(ab, cd);

    double sz = len2(dir);
    if (sz < EPS) {
        return PointLineDistance(a,b,c);
    }

    dir = dir/len(dir);
    return abs(dot(dir, a-c));
}

struct Plane {
    PT normal;
    double d;      ///Ax + By + Cz = D
    Plane(double a, double b, double c, double d) : normal(a, b, c), d(d) {}
    Plane(PT normal, double d) : normal(normal), d(d) {}
};

///Get plane given by three Non-Collinear Points
Plane getPlane(PT a, PT b, PT c) {
    PT normal = cross(b-a, c-a);
    assert(len2(normal) > EPS);
    double d = dot(normal, a);
    return Plane(normal, d);
}

ostream &operator<<(ostream &os, const Plane &p) {
    return os << p.normal.x << "x + " << p.normal.y << "y + " << p.normal.z << "z = "<<p.d;
}

/// distance from point a to plane p
double PointPlaneDistance(PT a, Plane p) {
    return abs(dot(p.normal, a) - p.d) / len(p.normal);
}


int main()
{
    PT a, b, c;
    cin>>a>>b>>c;

    Plane p = getPlane(a, b, c);
    cout<<p<<endl;
}
