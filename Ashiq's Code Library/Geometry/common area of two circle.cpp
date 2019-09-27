#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


typedef double ld;

ld eps = 1e-9;


int dcmp(ld x){
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    return 1;
}

struct PT {
  double x,y;
  PT() {}
  PT(double x,double y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y) {}
  bool operator == (const PT &p) const {
    return dcmp(x-p.x)==0 && dcmp(y-p.y)==0;
  }
};
PT operator +(PT a,PT b) {
  return PT(a.x+b.x,a.y+b.y);
}
PT operator -(PT a,PT b) {
  return PT(a.x-b.x,a.y-b.y);
}
PT operator *(PT a,double b) {
  return PT(a.x*b,a.y*b);
}
PT operator /(PT a,double b){
  return PT(a.x/b,a.y/b);
}
double operator *(PT a,PT b){ //dot
    return a.x*b.x+a.y*b.y;
}
double operator ^(PT a,PT b){  //cross
    return a.x*b.y-a.y*b.x;
}

const double pi = acos(-1.0);

double len(PT p) {
    return sqrt(p*p);
}

double angleRad( PT a, PT b ){
  return acos( max(-1.0, min(1.0, (a*b)/(len(a)*len(b)))) );
}
ld angle(PT v) {
  return atan2(v.y,v.x);
}
int getCircleCircleIntersection(PT C1,double r1, PT C2, double r2, vector<PT>& sol) {
  ld d = len(C1-C2);
  if (dcmp(d)==0){
    if (dcmp(r1 - r2)==0) return -1; //same circle
    return 0; //concentric circle
  }
  if (dcmp(r1+r2-d)<0) return 0; //no intersection, outside
  if (dcmp(fabs(r1-r2)-d)>0) return 0; //no intersection, inside
  ld a = angle(C2-C1);
  ld da = acos((r1*r1+d*d - r2*r2)/ (2*r1*d));
  PT p1 = PT(C1.x+cos(a-da)*r1,C1.y+sin(a-da)*r1);
  PT p2 = PT(C1.x+cos(a+da)*r1,C1.y+sin(a+da)*r1);
  sol.push_back(p1);if (p1==p2) return 1;
  sol.push_back(p2);
  return 2;
}

double circle_portion(PT c, double r, PT ints, PT c2) {
    double ang = angleRad(c2-c,ints-c);
    if(ang <= pi/2.0) {
        return r*r*(ang-sin(ang)*cos(ang));
    }
    return r*r*(ang + sin(pi-ang)*cos(pi-ang));
}

double common_area_between_two_circle(PT c1, double r1, PT c2, double r2) {
    if(r1 < r2) swap(c1,c2), swap(r1,r2);
    double distance_between_centers = sqrt(((c1-c2)*(c1-c2)));
    if(distance_between_centers >= r1+r2) return 0.0;
    if(distance_between_centers <= abs(r1-r2)) return pi*r2*r2;
    vector<PT> ints;
    getCircleCircleIntersection(c1,r1,c2,r2,ints);
    assert(ints.size() == 2);
    return circle_portion(c1,r1,ints[0],c2) +
            circle_portion(c2,r2,ints[0],c1);
}




int main() {

    // freopen("in.txt", "r", stdin);

    cout << setprecision(12) << fixed;
    int tc, caseno = 1;
    cin >> tc;
    while(tc--) {
        PT c1, c2;
        double r1, r2;
        cin >> c1.x >> c1.y >> r1;
        cin >> c2.x >> c2.y >> r2;
        double ans = max(0.0,common_area_between_two_circle(c1,r1,c2,r2));
        cout << "Case " << caseno++ << ": " << ans << endl;
    }

    return 0;
}

