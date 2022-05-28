/// union volume of cones
/// https://codeforces.com/gym/102055/problem/F

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double eps = 1e-9, pi = acos(-1), PI = pi;

struct PT {
    double x, y;
    PT() {}
    PT(double x_, double y_) {
        x = x_, y = y_;
    }
    PT operator + (const PT &p) const {
        return PT(x+p.x, y+p.y);
    }
    PT operator * (const double t) const {
        return PT(x*t, y*t);
    }
    PT operator / (const double t) const {
        assert(fabs(t) > eps);
        return PT(x/t, y/t);
    }
    double operator * (const PT &p) const {
        return p.x*x + p.y*y;
    }
    PT operator - (const PT &p) const {
        return PT(x-p.x, y-p.y);
    }
    double operator ^ (const PT &p) {
        return x*p.y-y*p.x;
    }
    bool operator < (const PT &p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
    PT rot90() {
        return PT(-y, x);
    }
    bool operator == (const PT &p) const {
        return fabs(x-p.x) < eps && fabs(y-p.y) < eps;
    }
    double len() {
        return sqrt(x*x+y*y);
    }
};

int sign(double x) {
    if(x < 0) return -1;
    return 1;
}

double sqr(double x) {
    return x*x;
}
double det(PT a, PT b) {
    return a^b;
}
double dot(PT a, PT b) {
    return a*b;
}
double len(PT p) {
    return sqrt(p*p);
}

int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    if(x < 0.0) return -1;
    return 1;
}

double ccw(PT p, PT q, PT r) {
    return (q-p)^(r-q);
}

double clamp(double x, double l, double r) {
    if(x < l) return l;
    if(x > r) return r;
    return x;
}

double a, b, c, sinB, cosB, sinC, cosC, B, C, h;

double Func1(double r) {
    double I1 = C*r*r*r/6.0;
    double t = sqrt(abs(r*r-h*h));
    double lg = log(r+t);
    double I2 = (1.0/3.0)*r*r*r*acos(clamp(h/r,-1,1)) - (1.0/6.0)*h*(r*t+h*h*lg);
    I1 -= I2;
    double I3 = h*0.5*(r*t-h*h*lg);
    I1 += I3;
    return I1;
}

double Func2(double x) {
    double t = sqrt(abs(2.0*a*a*cos(2*B)/x/x - 2.0*a*a/x/x + 4.0));
    double I1 = 0.25*(x*x*sinB*t-2*a*a*sinB*sinB*sinB*log(x*(t+2))+2*a*x*sin(2*B));
    I1 *= a*0.5;
    double I2 = (B+C-PI)*x*x*x/6.0;
    I2 += (1.0/24.0)*(a*x*x*sinB*t+2*a*a*a*sinB*sinB*sinB*log(x*(t+2))+4.0*x*x*x*asin(clamp(a*sinB/x,-1,1)));
    return I1+I2;
}
double Func3(double x) {
    return sinC*a*b*0.5*x;
}

double volCT(PT pa, PT pb) {
    if (pa.len() < pb.len()) swap(pa, pb);
	if (dcmp(pb.len()) == 0) return 0;
	a = pb.len(), b = pa.len(), c = (pb - pa).len();
	sinB = fabs(det(pb, pb - pa) / a / c),
		cosB = dot(pb, pb - pa) / a / c,
		sinC = fabs(det(pa, pb) / a / b),
		cosC = dot(pa, pb) / a / b;
	B = atan2(sinB, cosB), C = atan2(sinC, cosC);
	h = a * b * sinC / c;
	if(dcmp(h) == 0 or dcmp(a) == 0 or dcmp(b) == 0) return 0;
	double S = 0.;
    if(h < a && B < PI/2) {
        if(h >= 1.0) S += C/6.0;
        else {
            S += C*h*h*h/6;
            double t1 = Func1(min(a, 1.0)) - Func1(h);
            S += t1;
        }
    }
    else {
        if(a >= 1.0) S += C/6.0;
        else S += C*a*a*a/6.0;
    }
    if(a >= 1.0) return S;
    S += Func2(min(b,1.0)) - Func2(a);
    if(b >= 1.0) return S;
    S += Func3(1.0)-Func3(b);
    return S;
}

double vol_poly(vector<PT> P, PT cen) {
    int n = P.size();
    double ans = 0;
    for(int i = 0; i < n; i++) {
        double cur_vol = fabs(volCT(P[i]-cen, P[(i+1)%n]-cen))*sign(det(P[i]-cen,P[(i+1)%n]-cen));
        ans += cur_vol;
    }
    return ans;
}

// ax + by = c

struct line{
	double a, b, c;
	PT u, d;
	line(double a, double b,double c):a(a), b(b), c(c) {
        // careful that u, d is not updated here.
	}
    line(PT u_, PT d_) {
        u = u_, d = d_; // counter clockwise direction is the region
        a = d.y, b = -d.x, c = -u.y*d.x + u.x*d.y; // ax + by <= c
    }
	bool operator < (const line &l)const{
		bool flag1 = make_pair(a, b) > make_pair(0.0, 0.0);
		bool flag2 = make_pair(l.a, l.b) > make_pair(0.0, 0.0);
		if(flag1 != flag2) return flag1 > flag2;
		long double t = ccw(PT(0, 0), PT(a, b), PT(l.a, l.b));
		return dcmp(t) == 0 ? c*hypot(l.a, l.b) < l.c * hypot(a, b):t>0;
	}
	PT slope() {
        return PT(a, b);
    }
};

PT cross(line a, line b){
	double det = a.a * b.b - b.a * a.b;
	return PT((a.c * b.b - a.b * b.c) / det,
            (a.a * b.c - a.c * b.a) / det);
}

bool bad(line a, line b, line c){
	if(ccw(PT(0, 0), a.slope(), b.slope()) <= 0) return false;
	PT crs = cross(a, b);
	return crs.x * c.a + crs.y * c.b >= c.c;
}

// ax + by <= c;

bool hpi(vector<line> v, vector<PT> &solution){
	sort(v.begin(), v.end());
	deque<line> dq;
	for(auto &i : v) {
        if(!dq.empty() && !dcmp(ccw(PT(0, 0), dq.back().slope(), i.slope()))) continue;
        while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
		while(dq.size() >= 2 && bad(i,dq[0],dq[1])) dq.pop_front();
		dq.push_back(i);
	}
	while(dq.size() > 2 && bad(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
	while(dq.size() > 2 && bad(dq.back(),dq[0],dq[1])) dq.pop_front();
	vector<PT> tmp;
	for(int i=0; i< dq.size(); i++){
		line cur = dq[i], nxt = dq[(i+1)%dq.size()];
		if(ccw(PT(0, 0), cur.slope(), nxt.slope()) <= eps) return false;
		tmp.push_back(cross(cur, nxt));
	}
	solution = tmp;
	return true;
}

int main() {

//     freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << setprecision(12) << fixed;

    int tc, caseno = 1;
    cin >> tc;
    while(tc--) {

        int n;
        cin >> n;
        vector<PT> P(n);
        for(int i = 0; i < n; i++) {
            cin >> P[i].x >> P[i].y;
        }
        double R = 22.0;
        double ans = 0;
        for(int i = 0; i < n; i++) {
            vector<line> lines;
            lines.push_back(line(1,0,R)); // x <= R
            lines.push_back(line(-1,0,R)); // x >= -R => -x <= R
            lines.push_back(line(0,1,R)); // y <= R
            lines.push_back(line(0,-1,R)); // y >= -R => -y <= R
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                PT u = (P[i]+P[j])*0.5;
                PT dir = P[j]-P[i];
                PT dir_90 = dir.rot90();
                PT v = u + dir_90;
                double a = dir_90.y, b = -dir_90.x, c = -u.y*dir_90.x + u.x*dir_90.y;
                lines.push_back(line(a,b,c));
            }
            vector<PT> polygon;
            hpi(lines, polygon);
            ans += vol_poly(polygon, P[i]);
        }
        cout << "Case " << caseno++ << ": ";
        cout << ans << endl;
    }
    return 0;
}

