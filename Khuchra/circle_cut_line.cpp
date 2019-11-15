#include <bits/stdc++.h>
using namespace std ;

#define double long double

const double eps = 1e-9 ;

int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0.0) return -1;
    return 1;
}

struct Point {
    double x , y ;
    Point() {}
    Point(double x_,double y_) {x=x_,y=y_;}
    Point operator + (const Point &p) {
        return {x+p.x,y+p.y} ;
    }
    Point operator - (const Point &p) {
        return {x-p.x,y-p.y} ;
    }
    Point operator * (const double &t) {
        return {x*t,y*t} ;
    }
    double operator * (const Point &p) {
        return x*p.x + y*p.y ;
    }
    double operator ^ (const Point &p) {
        return x*p.y - y*p.x ;
    }
};


struct Line {
    double a , b , c ; // ax + by + c = 0
    Point p , d ; // p + dt
    Line() {}
    Line(double a_,double b_,double c_) {
        a = a_ , b = b_ , c = c_ ;
        d = Point(-b,a) ;
        if (dcmp(a) == 0) {
            p = Point(0,-c/b) ;
        }
        else {
            p = Point(-c/a,0) ;
        }
    }
    Line(Point p_,Point q_) {
        p = p_ , d = q_ - p_;
    }
    double val(Point p) {
        return a*p.x + b*p.y + c ;
    }
}line[4];

int n ;
double R ;

const int N = 50005 ;
const double pi = acos(-1.0) ;


void intersect(vector<Point> &V,Point a,Point b,Line l) {
    Point p = l.p , q = l.p + l.d ;
    double na = (a-p)^(q-p) , nb = (b-p)^(q-p) ;
   // double na = l.val(a) , nb = l.val(b) ;
//    if (dcmp(na*nb) >= 0) return ;
    if (na*nb < 0.0) {
        V.push_back(a + (b-a)*(na/(na-nb))) ;
    }
}

void cut(vector<Point> &polygon, Line l, int sign) {
    vector<Point> np ;
    int sz = polygon.size();
    for(int i = 0 ; i < sz ; i++) {
        Point p = polygon[i] , q = polygon[(i+1)%sz];
//        cout << "val: " << l.val(p) << endl ;
        if (dcmp(l.val(p))*sign >= 0) {
            np.push_back(p);
        }
        intersect(np,p,q,l);
    }
    polygon = np ;
}

vector <Point> Circle ;

double f(int mask) {
    vector <Point> circle = Circle ;
    for(int i = 0 ; i < n ; i++) {
        if ( (mask>>i)&1 ) {
            cut(circle,line[i],+1);
        }
        else {
            cut(circle,line[i],-1);
        }
    }
    if (circle.size() == 0.0) return 0.0 ;
    int sz = circle.size() ;
    double area = 0 ;
    for(int i = 0 ; i < sz ; i++) {
        area += (circle[i]^circle[(i+1)%sz]) ;
    }
    return area/2.0 ;
}


void init() {
    for(int i = 0 ; i < N ; i++) {
        double angle = 2.0*pi/N*i ;
        Circle.push_back(Point(R*cos(angle),R*sin(angle))) ;
    }
}


bool used[20] ;
vector < double > v ;
map < pair<double,double> , pair<double,double> > Map ;

void solve(double &t1,double &t2) {
    if (Map.find({t1,t2}) != Map.end()) {
        pair<double,double> t = Map[{t1,t2}] ;
        t1 = t.first , t2 = t.second ;
        return ;
    }
    int who = 2 ;
    if (t1 < t2 + eps) {
        who = 1 ;
    }
    double best1 = t1 , best2 = t2 ;
    if (who == 1) {
        for(int i = 0 ; i < v.size() ; i++) {
            if (!used[i]) {
                double cur = v[i] ;
                used[i] = true ;
                double tt1 = t1 + cur , tt2 = t2 ;
                solve(tt1,tt2) ;
                if (best1 < tt1) {
                    best1 = tt1 ;
                    best2 = tt2 ;
                }
                used[i] = false ;
            }
        }
    }
    else {
        for(int i = 0 ; i < v.size() ; i++) {
            if (!used[i]) {
                double cur = v[i] ;
                used[i] = true ;
                double tt1 = t1  , tt2 = t2 + cur ;
                solve(tt1,tt2) ;
                if (best2 < tt2) {
                    best1 = tt1 ;
                    best2 = tt2 ;
                }
                used[i] = false ;
            }
        }
    }
    Map[{t1,t2}] = {best1,best2} ;
    t1 = best1 , t2 = best2 ;
}


int main() {

    freopen("vs.in" , "r" , stdin) ;
    freopen("vs.out" , "w" , stdout) ;



    cout << setprecision(12) << fixed ;
    cin >> n >> R ;
    init() ;
    for(int i = 0 ; i < n ; i++) {
        double a,b,c ;
        cin >> a >> b >> c ;
        line[i] = {a,b,c} ;
    }
    for(int i = 0 ; i < (1<<n) ; i++) {
        double slice = f(i) ;
        if (slice > eps) {
            v.push_back(slice) ;
//            cout << "slice: " << slice << endl ;
        }
    }
    double best1 = 0 , best2 = 0 ;
    solve(best1,best2) ;
    cout << best1 << " " << best2 << endl ;

}
