#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;

struct PT {
  double x, y, z;
  PT() {}
  PT(double x, double y, double z) : x(x), y(y), z(z) {}
  PT(const PT &p) : x(p.x), y(p.y), z(p.z)    {}
};
PT operator +(PT a,PT b){
  return PT(a.x+b.x,a.y+b.y, a.z+b.z);
}
PT operator -(PT a,PT b){
  return PT(a.x-b.x,a.y-b.y, a.z-b.z);
}
PT operator *(PT a,double b){
  return PT(a.x*b,a.y*b, a.z*b);
}
PT operator /(PT a,double b){
  return PT(a.x/b,a.y/b, a.z/b);
}
double operator *(PT a,PT b) {
  return a.x*b.x+a.y*b.y+a.z*b.z;
}
PT operator ^(PT a,PT b){
  return PT(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
int dcmp(double x){
  if (abs(x)<eps) return 0;
  return x<0 ? -1 : 1;
}
bool operator <(const PT &a,const PT &b){
  return make_pair(make_pair(a.x,a.y), a.z) <
         make_pair(make_pair(b.x,b.y), b.z);
}
bool operator==(const PT &a,const PT &b){
return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0&&dcmp(a.z-b.z)==0;
}
double len(PT a){
  return sqrt(a*a);
}
double dist(PT a, PT b){
  return sqrt((a-b)*(a-b));
}
double dist2(PT a, PT b){
  return ((a-b)*(a-b));
}
PT reversePT(PT a){
  return a*(-1);
}
///Angle between two vector
double angleRad( PT a, PT b ){
  return acos( max(-1.0, min(1.0, (a*b)/(len(a)*len(b)))) );
}
///small angle between two vector
double smallAngle( PT a, PT b ){
   return acos( min(abs(a*b)/len(a)/len(b), 1.0) );
}
///u + dt
struct Line{
  PT d, u;
  Line(PT d,PT u):d(d),u(u){}
  PT point(double t){
    return u + d*t;
  }
};
///ax + by + cz = d
struct Plane{
    double a,b,c,d;PT n;
    Plane(){}
    Plane(PT p, PT q, PT r ) :
      Plane( (q-p)^(r-p), ((q-p)^(r-p))*(p) ) {}
    ///normal in direction of p,q,r
    Plane(double a, double b, double c, double d) :
      a(a), b(b), c(c), d(d), n(PT(a,b,c)){}
    Plane(PT n, double d) :
      n(n), a(n.x), b(n.y), c(n.z), d(d) {}
    Plane(const Plane &p) :
      n(p.n), d(p.d), a(p.a), b(p.b), c(p.c) {}
};
///returns 0 if t is on plane p
///returns 1/-1 if t is on positive/negative side of normal
int side( Plane &p, PT a ){
  return dcmp(p.a*a.x + p.b*a.y + p.c*a.z - p.d);
}



///translate all point on a plane with respect to t
Plane Translate( Plane &p, PT t ){
  return Plane( p.n, p.d + p.n*t );
}
///rotate d to the left with respect to normal in plane p
PT rotateCCW90(Plane p, PT d){
  return (p.n^d);
}
PT unitVector( PT v ){
  return v/len(v);
}
///rotate d to the right with respect to normal in plane p
PT rotateCW90(Plane p, PT d){
  return (d^p.n);
}
///shift plane up(dist>0)/down(dist<0) to distance dist
Plane ShiftUpDown( Plane &p, double dist ){
  return Plane( p.n, p.d + dist*len(p.n) );
}
///returns 0 if t is on plane of a,b,c
///returns 1/-1 if t is on positive/negative side of a,b,c
int orientPointPlane( PT a, PT b, PT c, PT t ){
  double v = ( (b-a)^(c^a) )*(t-a);
  return dcmp(v);
}
///projection of point q on plane p
PT projectPointPlane( Plane &p, PT q ){
  return PT( q + p.n*((p.d- p.n*q)/(p.n*p.n)) );
}
///reflection of point q on plane p
PT reflectPointPlane( Plane &p, PT q ){
  return PT( q + p.n*(2.0*((p.d- p.n*q)/(p.n*p.n))) );
}
///assuming a is the center, ab is new x axis
vector<PT> convert3Dto2D( PT a, PT b, PT c, vector<PT>pt ){
  PT n = (b-a)^(c-a),dx = unitVector(b-a),
    dy = unitVector(n^(b-a));
  vector<PT>newpt;
  for( int i = 0; i < pt.size(); i++ )
    newpt.push_back( PT( dx*(pt[i]-a), dy*(pt[i]-a), 0 ) );
  return newpt;
}
double distancePointLine( Line l, PT p ){
  return len(l.d^( p-l.u ))/len(l.d);
}
PT projectPointLine( Line l, PT p ){
  return PT( l.u + l.d*(( (p-l.u)*(l.d) )/(l.d*l.d)) );
}
PT reflectPointLine( Line l, PT p ){
  return PT( projectPointLine(l,p)*2.0 - p );
}
///undefined if line and plane is parallel ie( p.b*l.d = 0 )
PT intersectionLinePlane( Line &l, Plane &p ){
  double k = (p.d - (p.n*l.u))/(p.n*l.d);
  return PT(l.u + l.d*k);
}
Line intersectioPlanePLane( Plane &p1, Plane &p2 ){
  PT d = p1.n^p2.n;
  return Line(d, ((p2.n*p1.d - p1.n*p2.d)^d)/(d*d));
}
double distanceLineLine( Line &l1, Line &l2 ){
  PT d = l1.d^l2.d;
  if( dcmp(len(d))==0 ) return distancePointLine(l1, l2.u);
  return abs( (l2.u-l1.u)*d )/len(d);
}
PT closestPointOnL1fromL2( Line &l1, Line &l2 ){
  PT n = l1.d^l2.d, n3 = l2.d^n;
  ///p is the plane including line l2 and n
  Plane p = Plane( n3, n3*l2.u );
  return intersectionLinePlane( l1, p );
}
///2 planes are parallel if crs product of their normal is 0
///2 planes are parallel if dot product of their normal is 0
///angle between two lines is angle between direction vector
double smallAngleBetweenTwoPlane( Plane p1, Plane p2 ){
  return smallAngle(p1.n, p2.n);
}
double angleBetweenTwoPlane( Plane p1, Plane p2 ){
  return angleRad(p1.n, p2.n);
}
double smallAngleBetweenPlaneLine( Plane &p1, Line &l1 ){
  return acos(-1.0) - smallAngle(p1.n, l1.d);
}

bool intersectionLineSegmentSphere(PT cen, double r, Line l){
  double h2 = r*r - distancePointLine(l, cen)*
                    distancePointLine(l, cen);
  if( dcmp(h2) < 0 ) return 0;
  if( dcmp(h2) == 0 ){
    return OnSegment(projectPointLine(l, cen), l.a, l.b);
  }
  PT v = projectPointLine(l, cen);
  PT h = l.d*sqrt(h2)/len(l.d);
  return OnSegment(v+h,l.a,l.b)&&OnSegment(v-h,l.a,l.b);
}

double angleRad( PT a, PT b ){
  return acos( max(-1.0, min(1.0, (a*b)/(len(a)*len(b)))) );
}
// returns 0 if on any end

bool OnSegment(PT p,PT a,PT b) {
  return dcmp(len((a-p)^(b-p))) == 0 && dcmp((a-p)*(b-p)) < 0;
}

double tri_area( PT a, PT b, PT c ){
  return 0.5*len((b-a)^(c-a));
}
struct Face{
  PT a, b, c;
  Face(){}
  Face(PT a, PT b, PT c) : a(a), b(b), c(c) {}
  Face( const Face &f ) : a(f.a), b(f.b), c(f.c) {}
};
///phi = longitude, lamda = lattitude
struct Sphere{
  PT cen; double r;
  Sphere(){}
  Sphere( const Sphere &s ) : cen(s.cen), r(s.r) {}
  Sphere( PT cen, double r ) : cen(cen), r(r) {}
  PT convert( double phi, double lamda ){
    return PT( r*cos(phi)*cos(lamda),r*cos(phi)*sin(lamda),
              r*sin(phi) );
  }
};
double surfaceArea( vector<Face> &vec){
  double s = 0;
  for( int i = 0; i < vec.size(); i++ )
    s = s + len((vec[i].b-vec[i].a)^(vec[i].c-vec[i].a));
  return s*0.5;
}
double ployhedronVolume( vector<Face> &vec ){
  if( vec.size() == 0 ) return 0;
  PT reff = vec[0].a; double vol = 0;
  for( int i = 1; i < vec.size(); i++ ) {
    PT ar = (vec[i].b-vec[i].a)^(vec[i].c - vec[i].a);
    vol += abs( ar*(reff-vec[i].a) );
  }
  return vol/6.0;
}
vector<PT> intersectionLineSphere(PT cen, double r, Line l){
  vector<PT>vec;
  double h2 = r*r - distancePointLine(l, cen)*
                    distancePointLine(l, cen);
  if( dcmp(h2) < 0 ) return vec;
  if( dcmp(h2) == 0 ){
    vec.push_back( projectPointLine(l, cen) );
    return vec;
  }
  PT v = projectPointLine(l, cen);
  PT h = l.d*sqrt(h2)/len(l.d);
  vec.push_back(v+h); vec.push_back(v-h);
  return vec;
}
/// let's consider the case of a spherical triangle ABC.
///It's area is given by r2(a + b + c - pi) where r is
///the radius of the sphere and a; b; c are the amplitudes
///of the three interior angles of ABC
bool InsideATriangle (PT A , PT B , PT C , PT P) {
  if (abs(tri_area(A,B,P) + tri_area(A,C,P) +
      tri_area(B,C,P) - tri_area(A,B,C)) < eps) return 1 ;
  return 0 ;
}
///project point c onto line segment through a and b
PT projectPointSegment(PT a, PT b, PT c){
  double r = (b-a)*(b-a);
  if(abs(r) < eps) return a;
  r = ( (c-a)*(b-a) ) / r;
  if (r < 0) return a; if (r > 1) return b;
  return a + (b-a)*r;
}
///compute distance from c to segment between a and b
double distancePointSegment(PT a, PT b, PT c){
  return dist(c, projectPointSegment(a, b, c));
}
///Minimum distance from Point P on a triangle with vertices A,B,C
double PointDistanceOn3dTriangle(PT A, PT B, PT C, PT P){
  Plane ABC = Plane(A,B,C); PT P_ = projectPointPlane(ABC,P);
  double ret = 1e19 ;
  if (InsideATriangle(A,B,C,P_))
      ret = min(ret, dist(P,P_)) ;
  ret = min(ret, distancePointSegment(A,B,P)) ;
  ret = min(ret, distancePointSegment(B,C,P)) ;
  ret = min(ret, distancePointSegment(A,C,P)) ;
  return ret ;
}
vector<Face> Convex3dHull(vector<PT> &V) {
  vector <Face> Faces ;
  for (int i = 0 ; i < V.size() ; i++) {
    for (int j = i+1 ; j < V.size() ; j++) {
      for (int k = j+1 ; k < V.size() ; k++) {
        if (tri_area(V[i],V[j],V[k]) < eps)
          continue ;
        bool up = 0 , down = 0 ;
        PT AB = V[j]-V[i] , AC = V[k]-V[i] ;
        PT normal = AB^AC ;
        for (int l = 0 ; l < V.size() ; l++) {
          if (l == i or l == j or l == k)
            continue ;
          if (abs(normal*(V[l]-V[i])) < eps) {
            if ( abs( ( tri_area(V[i],V[j],V[l]) +
                        tri_area(V[i],V[k],V[l]) +
                        tri_area(V[j],V[k],V[l]) -
                        tri_area(V[j],V[k],V[i]) ) ) < eps ){
              up = down = 1 ;
              break ;
            }
          }
          else if (normal*(V[l]-V[i]) < 0)
            down = 1 ;
          else
            up = 1 ;
        }
        if (up == 0 or down == 0) {
          Face temp;
          temp.a = V[i], temp.b = V[j] , temp.c = V[k] ;
          Faces.push_back(temp) ;
        }
      }
    }
  }
  return Faces ;
}

double greatCirclePointDistance( Sphere s, double phi1,
                double lamda1, double phi2, double lamda2){
  PT p1 = s.convert( phi1, lamda1 );
  PT p2 = s.convert( phi2, lamda2 );
  //always takes into account smallest distance
  return angleRad( p1-s.cen, p2-s.cen )*s.r;
}

double greatCircleArea( Sphere s, double phi1, double lamda1,
    double phi2, double lamda2, double phi3, double lamda3 )
{
  PT p1 = s.convert( phi1, lamda1 ),
  p2 = s.convert( phi2, lamda2 ),p3 = s.convert(phi3,lamda3);
  double a = angleBetweenTwoPlane( Plane(s.cen, p1, p2),
                                  Plane(s.cen, p1, p3) );
  double b = angleBetweenTwoPlane( Plane(s.cen, p2, p3),
                                  Plane(s.cen, p2, p1) );
  double c = angleBetweenTwoPlane( Plane(s.cen, p3, p1),
                                  Plane(s.cen, p3, p2) );
  return s.r*s.r*( a+b+c-acos(-1.0) );
}
