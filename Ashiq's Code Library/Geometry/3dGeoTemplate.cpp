#include <bits/stdc++.h>
using namespace std ;

typedef double ld ;

const ld eps = 1e-12 ;

struct Point {
    ld x , y , z ;
    Point() {}
    Point(ld x_,ld y_,ld z_) {
        x = x_ , y = y_ , z = z_ ;
    }
    Point operator + (Point const &P) {
        return Point(x+P.x,y+P.y,z+P.z) ;
    }
    Point operator - (Point const &P) {
        return Point(x-P.x,y-P.y,z-P.z) ;
    }
    ld operator * (Point const &P) {
        return (x*P.x+y*P.y+z*P.z) ;
    }
    Point operator ^ (Point const &P) {
        return Point(y*P.z-z*P.y,z*P.x-x*P.z,x*P.y-y*P.x) ;
    }
    Point operator / (ld d) {
        return Point(x/d,y/d,z/d) ;
    }
    Point operator * (ld d) {
        return Point(x*d,y*d,z*d) ;
    }
};

ld dist2 (Point A , Point B) {
    return (B-A)*(B-A) ;
}
ld dist(Point A , Point B) {
    return sqrt(dist2(A,B)) ;
}
ld length(Point A) {
    return sqrt(A*A) ;
}

ld tri_area(Point A , Point B , Point C) {
    return length( (B-A)^(C-A) ) /2.0 ;
}

// project point c onto line segment through a and b
Point ProjectPointSegment(Point a, Point b, Point c) {
    double r = (b-a)*(b-a);
    if (fabs(r) < eps) return a;
    r = ( (c-a)*(b-a) ) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(Point a, Point b, Point c) {
    return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// A , B , C are three points on the plane , calculates P's Projected Point on the plane
Point ProjectedPointOnAPlane (Point A , Point B , Point C , Point P) {
    Point AB = B-A , AC = C-A ;
    Point n = AB^AC ;
    Point P_ = P + n * ( (n*(A-P))/(n*n) ) ;
    return P_ ;
}

bool InsideATriangle (Point A , Point B , Point C , Point P) {
    if (abs(tri_area(A,B,P) + tri_area(A,C,P) + tri_area(B,C,P) - tri_area(A,B,C)) < eps) return 1 ;
    return 0 ;
}

// Minimum distance from Point P on a triangle with vertices A,B,C

ld PointDistanceOn3dTriangle(Point A,Point B,Point C,Point P) {
    Point P_ = ProjectedPointOnAPlane(A,B,C,P) ;
    ld ret = 1e19 ;
    if (InsideATriangle(A,B,C,P_)) {
        ret = min(ret,dist(P,P_)) ;
    }
    ret = min(ret,DistancePointSegment(A,B,P)) ;
    ret = min(ret,DistancePointSegment(B,C,P)) ;
    ret = min(ret,DistancePointSegment(A,C,P)) ;
    return ret ;
}

struct face {
    Point a , b , c ;
};

vector<face> Convex3dHull(vector<Point> &V) {
    vector <face> Faces ;
    for (int i = 0 ; i < V.size() ; i++) {
        for (int j = i+1 ; j < V.size() ; j++) {
            for (int k = j+1 ; k < V.size() ; k++) {
                if (tri_area(V[i],V[j],V[k]) < eps) {
                    continue ;
                }
                bool up = 0 , down = 0 ;
                Point AB = V[j]-V[i] , AC = V[k]-V[i] ;
                Point normal = AB^AC ;
                for (int l = 0 ; l < V.size() ; l++) {
                    if (l == i or l == j or l == k) {
                        continue ;
                    }
                    if (abs(normal*(V[l]-V[i])) < eps) {
                        if ( abs( (tri_area(V[i],V[j],V[l]) + tri_area(V[i],V[k],V[l]) + tri_area(V[j],V[k],V[l]) - tri_area(V[j],V[k],V[i]) ) ) < eps ) {
                            up = down = 1 ;
                            break ;
                        }
                    }
                    else if (normal*(V[l]-V[i]) < 0) {
                        down = 1 ;
                    }
                    else {
                        up = 1 ;
                    }
                }
                if (up == 0 or down == 0) {
                    face temp ;
                    temp.a = V[i] , temp.b = V[j] , temp.c = V[k] ;
                    Faces.push_back(temp) ;
                }
            }
        }
    }
    return Faces ;
}

// takes spherical co-ordinate (r,phi,theta) , phi is the radian angle in XY plane (longitude)

Point Spherical2Cartesian (Point A) {
    return Point(A.x*cos(A.y)*cos(A.z) , A.x*sin(A.y)*cos(A.z) , A.x*sin(A.z)) ;
}

double GeoDistance(Point A , Point B) {
    double R = A.x ;
    A = Spherical2Cartesian(A) ;
    B = Spherical2Cartesian(B) ;
    double d = dist(A,B) ;
    double angleInCenter = 2.0*asin(d/(2.0*R)) ;
    return R*angleInCenter ;
}


int main () {
    //freopen ("in.txt" , "r" , stdin) ;
    int tc ; scanf("%d" , &tc) ;
    while (tc--) {
        int n ; scanf("%d" , &n) ;
        vector <Point> S1 , S2 ;
        for (int i = 1 ; i <= n ; i++) {
            Point P ;
            scanf("%lf %lf %lf" , &P.x , &P.y , &P.z) ;
            S1.push_back(P) ;
        }
        ld surf = 0 ;
        vector <face> Faces1 = Convex3dHull(S1) ;
        for(int i = 0 ; i < Faces1.size() ; i++) {
            surf += tri_area(Faces1[i].a,Faces1[i].b,Faces1[i].c) ;
        }
        int m ; scanf("%d",&m) ;
        for (int i = 1 ; i <= m ; i++) {
            Point P ;
            scanf("%lf %lf %lf" , &P.x , &P.y , &P.z) ;
            S2.push_back(P) ;
        }
        vector <face> Faces2 = Convex3dHull(S2) ;
        for(int i = 0 ; i < Faces2.size() ; i++) {
            surf += tri_area(Faces2[i].a,Faces2[i].b,Faces2[i].c) ;
        }
        ld di = 1e19 ;
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < Faces2.size() ; j++) {
                di = min(di,PointDistanceOn3dTriangle(Faces2[j].a,Faces2[j].b,Faces2[j].c,S1[i])) ;
            }
        }
        for (int i = 0 ; i < m ; i++) {
            for (int j = 0 ; j < Faces1.size() ; j++) {
                di = min(di,PointDistanceOn3dTriangle(Faces1[j].a,Faces1[j].b,Faces1[j].c,S2[i])) ;
            }
        }
        surf += di ;
        printf ("%.12f\n" , surf) ;
    }
    return 0 ;
}
