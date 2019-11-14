/// maximum convex polygon and circle intersection area
/// given polygon and circle's radius
/// n*log^2(n)

#include <bits/stdc++.h>
using namespace std;

typedef double ld;
const ld eps = 1e-12, PI = acos(-1);

int dcmp(ld x) {
    if (fabs(x)<eps) return 0; return x < 0 ? -1 : 1;
}

int sign(ld x) {
    if(x < 0) return -1;
    return 1;
}

struct PT {
  ld x,y;
  PT() {}
  PT(ld x,ld y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y) {}
  ld len() {
    return sqrt(x*x+y*y);
  }
};
PT operator +(PT a,PT b) {
  return PT(a.x+b.x,a.y+b.y);
}
PT operator -(PT a,PT b) {
  return PT(a.x-b.x,a.y-b.y);
}
PT operator *(PT a,ld b) {
  return PT(a.x*b,a.y*b);
}
PT operator /(PT a,ld b){
  return PT(a.x/b,a.y/b);
}
ld operator *(PT a,PT b){ //dot
    return a.x*b.x+a.y*b.y;
}
ld operator ^(PT a,PT b){  //cross
    return a.x*b.y-a.y*b.x;
}

ld len(PT p) {
    return sqrt(p*p);
}

ld sqr(ld x) {
    return x*x;
}
ld det(PT a, PT b) {
    return a^b;
}
ld dot(PT a, PT b) {
    return a*b;
}

ld clamp(ld x, ld l, ld r) {
    if(x < l) return l;
    if(x > r) return r;
    return x;
}

double areaCT(PT pa, PT pb, double r) {
	if (pa.len() < pb.len()) swap(pa, pb);
	if (dcmp(pb.len()) == 0) return 0;
	double a = pb.len(), b = pa.len(), c = (pb - pa).len();
	double sinB = fabs(det(pb, pb - pa) / a / c),
		cosB = dot(pb, pb - pa) / a / c,
		sinC = fabs(det(pa, pb) / a / b),
		cosC = dot(pa, pb) / a / b;
	double B = atan2(sinB, cosB), C = atan2(sinC, cosC);
	double S = 0.;
	if (a > r) {
		S = C / 2 * r * r;
		double h = a * b * sinC / c;
		if (h < r && B < PI / 2) {
			S -= (acos(h / r) * r * r - h * sqrt(r * r - h * h));
		}
	} else if (b > r) {
		double theta = PI - B - asin(clamp(sinB / r * a,-1,+1));
		S = a * r * sin(theta) / 2 + (C - theta) / 2 * r * r;
	} else {
		S = sinC * a * b / 2;
	}
	return S;
}

ld poly_cross(vector<PT> P, PT cen, ld r) {
    int n = P.size();
    ld ans = 0;
    for(int i = 0; i < n; i++) {
        ld cur_area = fabs(areaCT(P[i]-cen, P[(i+1)%n]-cen, r))*sign(det(P[i]-cen,P[(i+1)%n]-cen));
        ans += cur_area;
    }
    return ans;
}


/// intersection of line ab and cd
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a;d=c-d;c=c-a;
  assert((b*b) > eps && (d*d) > eps);
  return a + b*(c^d)/(b^d);
}

const ld inf = 1e100;
int n;
ld Rad;

ld f(double X, vector<PT> P) {
    int n = P.size();
    double U = -1e100, D = 1e100;
    for(int i = 0; i < n; i++) {
        ld x1 = P[i].x, x2 = P[(i+1)%n].x;
        if(dcmp(x1-X) == 0 && dcmp(x1-x2) == 0) {
            U = max(U, P[i].y);
            U = max(U, P[(i+1)%n].y);
            D = min(D, P[i].y);
            D = min(D, P[(i+1)%n].y);
            continue;
        }
        if(x1 > x2) swap(x1, x2);
        if(X >= x1 && X <= x2) {
            PT ints = ComputeLineIntersection(P[i], P[(i+1)%n], PT(X,0), PT(X,1));
            U = max(U, ints.y);
            D = min(D, ints.y);
        }
    }

    ld lo = D, hi = 220;
    for(int itr = 1; itr <= 100; itr++) {
        ld mid = (lo+hi)/2.0;
        if(poly_cross(P, PT(X,mid),Rad) < eps) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    ld upper = lo;

    lo = -200, hi = U;
    for(int itr = 1; itr <= 100; itr++) {
        ld mid = (lo+hi)/2.0;
        if(poly_cross(P, PT(X,mid),Rad) < eps) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }
    ld lower = lo;
    ld ans = 0;
    for(int itr = 1; itr <= 100; itr++) {
        ld m1 = (lower+lower+upper)/3.0, m2 = (lower+upper+upper)/3.0;
        ld ar1 = poly_cross(P, PT(X,m1),Rad), ar2 = poly_cross(P, PT(X,m2), Rad);
        ans = max(ans, ar1);
        ans = max(ans, ar2);
        if(ar1 < ar2) lower = m1;
        else upper = m2;
    }
    return ans;
}




int main() {

    cout << setprecision(12) << fixed;
    cin >> n >> Rad;
    vector<PT> P(n);
    ld L = inf, R = -inf;
    for(int i = 0; i < n; i++) {
        cin >> P[i].x >> P[i].y;
        L = min(L, P[i].x);
        R = max(R, P[i].x);
    }
    double ans = 0;
    for(int itr = 1; itr <= 100; itr++) {
        ld m1 = (L+L+R)/3.0, m2 = (L+R+R)/3.0;
        ld ar1 = f(m1, P), ar2 = f(m2, P);
        ans = max(ans, ar1);
        ans = max(ans, ar2);
        if(ar1 < ar2) L = m1;
        else R = m2;
    }
    cout << ans << endl;
}