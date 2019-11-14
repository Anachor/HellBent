#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Lattice{
    ll x , y ;
    Lattice(ll x_,ll y_) {x=x_,y=y_;}
    Lattice() {}

    Lattice operator + (const Lattice &p) {
        return {x+p.x,y+p.y} ;
    }
    Lattice operator - (const Lattice &p) {
        return {x-p.x,y-p.y} ;
    }
    ll operator * (const Lattice &p) {
        return x*p.x+y*p.y ;
    }
    Lattice operator * (const ll t) {
        return Lattice(t*x,t*y);
    }
    Lattice operator / (const ll t) {
        return Lattice(x/t,y/t);
    }
    ll operator ^ (const Lattice &p) {
        return x*p.y-y*p.x ;
    }
    bool operator < (const Lattice &p) const {
        return make_pair(x,y) < make_pair(p.x,p.y) ;
    }
    bool operator > (const Lattice &p) const {
        return make_pair(x,y) > make_pair(p.x,p.y) ;
    }
    Lattice rot90() {
        return Lattice(-y,x) ;
    }
};

bool onSegment(Lattice p,Lattice q,Lattice a) {
    return ( (p-q)^(q-a) ) == 0 and ((p-a)*(q-a)) <= 0 ;
}

int sign (ll x) {
    if (x < 0) return -1;
    return x > 0;
}

bool intersect(Lattice a,Lattice b,Lattice p,Lattice q) {
    if ( (sign( ((b-a)^(p-a)) ) * sign( ((b-a)^(q-a)) )) == -1 and (sign( ((q-p)^(a-p)) ) * sign( ((q-p)^(b-p)))) == -1) {
        return 1;
    }
    if (onSegment(a,b,p)) return 1;
    if (onSegment(a,b,q)) return 1;
    if (onSegment(p,q,a)) return 1;
    if (onSegment(p,q,b)) return 1;
    return 0;
}

bool intersect(vector<Lattice> &A,vector<Lattice> &B,Lattice dir) {
    int n = A.size() , m = B.size();
    for(int i = 0; i < n; i++) {
        Lattice p = A[i];
        Lattice q = p + dir*100000 ;
        for(int j = 0; j < m; j++) {
            Lattice a = B[j] , b = B[(j+1)%m];
            if (intersect(a,b,p,q)) {
                return 1;
            }
        }
    }
    return 0;
}


const double eps = 1e-9;


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

bool ccw (Lattice p,Lattice q,Lattice r) {
    return ( (q-p)^(r-p) ) > 0;
}

void ConvexHull(vector<Lattice> &poly) {
    sort(poly.begin(),poly.end()) ;
    vector<Lattice> hull,lower,upper ;
    for(int i = 0 ; i < poly.size() ; i++) {
        while(lower.size() >= 2 and !ccw(lower[lower.size()-2],lower.back(),poly[i])) {
            lower.pop_back() ;
        }
        lower.push_back(poly[i]) ;
    }
    for(int i = poly.size()-1 ; i >= 0 ; i--) {
        while(upper.size() >= 2 and !ccw(upper[upper.size()-2],upper.back(),poly[i])) {
            upper.pop_back() ;
        }
        upper.push_back(poly[i]) ;
    }
    hull = lower ;
    for(int i = 1 ; i + 1 < upper.size() ; i++) hull.push_back(upper[i]) ;
    poly = hull ;
}

double Abs(Point p) {
    return sqrt(p*p);
}

const double magic = 100000.0;

bool onSegment(Point p,Point q,Point a) {
    return dcmp((p-q)^(q-a)) == 0 and dcmp( ((p-a)*(q-a)) ) <= 0 ;
}

void intersect(Point a,Point b,Point p,Point q,vector<double> &res) {
    Point dir = (b-a)*(1.0/magic) ;
    if ( (dcmp( ((b-a)^(p-a)) ) * dcmp( ((b-a)^(q-a)) )) == -1 and (dcmp( ((q-p)^(a-p)) ) * dcmp( ((q-p)^(b-p)))) == -1) {
        double na = (q-p)^(a-p) , nb = (q-p)^(b-p);
        double t = magic*na/(na-nb) ;
        if (t > 0.0) res.push_back(t);
    }
    else {
        vector<Point> ends;
        if (onSegment(a,b,p)) ends.push_back(p);
        if (onSegment(a,b,q)) ends.push_back(q);
        if (onSegment(p,q,a)) ends.push_back(a);
        if (onSegment(p,q,b)) ends.push_back(b);

        for(int i = 0 ; i < ends.size() ; i++) {
            Point tp = ends[i];
            if (dcmp(dir.x) != 0) {
                double t = (tp.x-a.x)/dir.x ;
                if (t > 0.0) res.push_back(t);
            }
            else {
                double t = (tp.y-a.y)/dir.y ;
                if (t > 0.0)res.push_back(t);
            }
        }
    }
}

void solve(vector<double> &events,vector<Point> &A,vector<Point> &B,Point dir) {
    int n = A.size() , m = B.size() ;
    double vel = Abs(dir);
    for(int i = 0 ; i < n ; i++) {
        Point a = A[i] , b = a + dir*magic ;
        for(int j = 0 ; j < m ; j++) {
            Point p = B[j] , q = B[(j+1)%m];
            intersect(a,b,p,q,events);
        }
    }
}

void intersect(vector<Point> &V,Point a,Point b,Point p,Point q) {
    double na = (a-p)^(q-p) , nb = (b-p)^(q-p) ;
    if (na*nb < 0.0) {
        V.push_back(a + (b-a)*(na/(na-nb))) ;
    }
}


void cut(vector<Point> &polygon, Point a , Point b) {
    vector<Point> np ;
    int sz = polygon.size();
    for(int i = 0 ; i < sz ; i++) {
        Point p = polygon[i] , q = polygon[(i+1)%sz];
        if (dcmp((b-a)^(p-a)) >= 0) {
            np.push_back(p);
        }
        intersect(np,p,q,a,b);
    }
    polygon = np ;
}

double calc(vector <Point> &A,vector<Point> &B) {
    int m = B.size();
    for(int i = 0 ; i < m ; i++) {
        Point p = B[i] , q = B[(i+1)%m];
        cut(A,p,q);
    }
    if (A.size() == 0) return -1e9;
    if (A.size() < 3) return 0;
    double area = 0.0 ;
    int n = A.size() ;
    for(int i = 0 ; i < n; i++) {
        area += (A[i]^A[(i+1)%n]);
    }
    return 0.5*area;
}


double area(vector<Point> A , vector<Point> &B,Point dir) {
    for(int i = 0 ; i < A.size() ; i++) A[i] = A[i] + dir ;
    return calc(A,B);
}

int main() {

    //freopen ("in.txt" , "r" , stdin);
    int n ;
    while(cin >> n) {
        vector<Lattice> A(n);
        for(int i = 0; i < n; i++) {
            cin >> A[i].x >> A[i].y;
        }
        Lattice da;
        cin >> da.x >> da.y;
        int m; cin >> m;
        vector<Lattice> B(m);
        for(int i = 0; i < m; i++) cin >> B[i].x >> B[i].y;
        Lattice db;
        cin >> db.x >> db.y;
        if (da.x == db.x and da.y == db.y) {
            cout << "never" << endl;
            continue ;
        }
        ConvexHull(A); n = A.size();
        ConvexHull(B); m = B.size();
        if( intersect(A,B,da-db) or intersect(B,A,db-da) ) {
            vector<Point> C(n), D(m);
            for(int i = 0 ; i < n ; i++) C[i].x = A[i].x , C[i].y = A[i].y ;
            for(int i = 0 ; i < m ; i++) D[i].x = B[i].x , D[i].y = B[i].y ;
            Point dirA = Point(da.x,da.y);
            Point dirB = Point(db.x,db.y);
            vector <double> events;
            solve(events,C,D,(dirA-dirB));
            solve(events,D,C,(dirB-dirA));
            events.push_back(0.0) ;
            events.push_back(magic) ;
            sort(events.begin(),events.end()) ;
            Point dir = dirA-dirB;
            double ans = -1e8 , Time = 0.0 ;
            for(int i = 1 ; i < events.size() ; i++) {
                double lo = events[i-1] , hi = events[i] ;
                for(int it = 1 ; it <= 50 ; it++) {
                    double m1 = (2.0*lo + hi)/3.0 , m2 = (lo + 2.0*hi)/3.0;
                    double a1 = area(C,D,dir*m1) , a2 = area(C,D,dir*m2) ;
                    if (dcmp(a1-a2) == 0) {
                        hi = m2 ;
                    }
                    else if (a1 > a2) {
                        hi = m2 ;
                    }
                    else {
                        lo = m1 ;
                    }
                }
                double cur = area(C,D,dir*lo) ;
                if (dcmp(cur-ans) == 1) {
                    ans = cur;
                    Time = lo;
                }
            }
            cout << setprecision(12) << Time << endl ;
        }
        else {
            cout << "never" << endl;
        }
    }
    return 0;
}
