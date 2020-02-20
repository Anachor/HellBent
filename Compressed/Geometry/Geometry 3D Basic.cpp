struct Point3 {
  LD x, y, z;
  Point3() {}
  Point3(LD a, LD b, LD c) : x(a), y(b), z(c){}
  void operator=(const Point3& a) {
    x=a.x,y=a.y,z=a.z;
  }
  Point3 operator+(Point3 a) {
    Point3 p{x + a.x, y + a.y, z + a.z}; return p;
  }
  Point3 operator-(Point3 a) {
    Point3 p{x - a.x, y - a.y, z - a.z}; return p;
  }
  Point3 operator*(LD a) {
    return Point3(x*a,y*a,z*a);
  }
  Point3 operator/(LD a) {
    assert(a > EPS); Point3 p{x/a, y/a, z/a};
    return p;
  }
  LD& operator[](int a) {
    if (a == 0) return x;
    if (a == 1) return y;
    if (a == 2) return z;
    assert(false);
  }
  bool IsZero() {
    return abs(x)<EPS&& abs(y)<EPS && abs(z) < EPS;
  }
  bool operator==(Point3 a) {
    return (*this - a).IsZero();
  }
  LD dot(Point3 a) {
    return x * a.x + y * a.y + z * a.z;
  }
  LD Norm() {
    return Sqrt(x * x + y * y + z * z);
  }
  LD SqNorm() {
    return x * x + y * y + z * z;
  }
  void NormalizeSelf() {
    *this = *this/Norm();
  }
  Point3 Normalize() {
    Point3 res(*this); res.NormalizeSelf();
    return res;
  }
  LD Dis(Point3 a) {
    return (*this - a).Norm();
  }
  pair<LD, LD> SphericalAngles() {
    return {atan2(z,Sqrt(x*x+y*y)),atan2(y,x)};
  }
  LD Area(Point3 p) {
    return Norm() * p.Norm() * sin(Angle(p)) / 2;
  }
//  LD Angle(Point3 p) {
//    LD a = Norm(), b = p.Norm(), c = Dis(p);
//    return Acos((a*a+b*b-c*c)/(2*a*b));
//  }
  LD Angle(Point3 b) { // not tested
    Point3 a(*this);
    return Acos(abs(a.dot(b))/a.Norm()/b.Norm());
  }
  LD Angle(Point3 p, Point3 q){return p.Angle(q);}
  Point3 cross(Point3 p) {
    Point3 q(*this);
    return {q[1]*p[2] - q[2]*p[1], q[2]*p[0] -
          q[0] * p[2], q[0] * p[1] - q[1] * p[0]};
  }
  bool LexCmp(Point3& a, const Point3& b) {
    if (abs(a.x - b.x) > EPS) { return a.x < b.x;}
    if (abs(a.y - b.y) > EPS) { return a.y < b.y;}
    return a.z < b.z;
  }
};
struct Line3 {
  Point3 p[2];
  Line3() {}
  Line3(Point3 a, Point3 b) { p[0] = a, p[1] = b;}
  Point3& operator[](int a) { return p[a]; }
};
struct Plane {
  Point3 p[3];
  Point3& operator[](int a) { return p[a]; }
  Plane(Point3 p0, Point3 p1, Point3 p2) {
    p[0] = p0; p[1] = p1; p[2] = p2;
  }
  // Ax + By + Cz = D
  Plane(Point3 normal, LD D) {
    /// to do, update p[0], p[1], p[2]
  }
  Point3 GetNormal() {
    Point3 cross = (p[1]-p[0]).cross(p[2]-p[0]);
    return cross.Normalize();
  }
  void GetPlaneEq(LD& A, LD& B, LD& C, LD& D) {
    Point3 normal = GetNormal();
    A = normal[0], B = normal[1], C = normal[2];
    D = normal.dot(p[0]);
    assert(abs(D - normal.dot(p[1])) < EPS);
    assert(abs(D - normal.dot(p[2])) < EPS);
  }
  vector<Point3> GetOrtonormalBase() {
    Point3 normal = GetNormal();
    Point3 cand = {-normal.y, normal.x, 0};
    if (abs(cand.x) < EPS && abs(cand.y) < EPS)
      cand = {0, -normal.z, normal.y};
    cand.NormalizeSelf();
    Point3 third = Plane{Point3{0, 0, 0},
                      normal, cand}.GetNormal();
    return {normal, cand, third};
  }
};
struct Circle3 {
  Plane pl; Point3 cent; LD r;
};
struct Sphere {
  Point3 cent; LD r;
};
namespace Utils3 {
  //angle PQR
  LD Angle(Point3 P, Point3 Q, Point3 R) {
    return (P - Q).Angle(R - Q);
  }
  LD Area(Point3 p, Point3 q, Point3 r) { // ok
    q = q-p; r = r-p; return q.Area(r);
  }
  LD DistPtLine(Point3 p, Line3 l){ // not tested
    return ((l[1]-l[0]).cross((p-l[0]))).Norm()/
                          (l[1]-l[0]).Norm();
  }
  Point3 ProjPtToLine3(Point3 p, Line3 l) { // ok
    Point3 diff = l[1]-l[0]; diff.NormalizeSelf();
    return l[0] + diff * (p - l[0]).dot(diff);
  }
  Point3 ProjPtSeg3(Point3 p, Line3 l) {//!tested
    LD r = (l[1]-l[0]).dot(l[1]-l[0]);
    if(abs(r) < EPS) return l[0];
    r = (p-l[0]).dot(l[1]-l[0])/r;
    if(r < 0) return l[0];
    if (r > 1) return l[1];
    return l[0] + (l[1]-l[0]) * r;
  }
  LD DistPtSeg3(Point3 p, Line3 l) {
    Point3 q = ProjPtSeg3(p, l); return p.Dis(q);
  }
  LD DisPtLine3(Point3 p, Line3 l) { // ok
    LD dis2 = p.Dis(ProjPtToLine3(p, l));
    return dis2;
  }
  bool PtBelongToLine3(Point3 p, Line3 l) {
    return DisPtLine3(p, l) < EPS;
  }
  bool Lines3Equal(Line3 p, Line3 l) {
    return PtBelongToLine3(p[0],l) &&
                          PtBelongToLine3(p[1],l);
  }
  bool OrientPointPlane(Point3 t,Plane p){//!tested
    LD dot = p.GetNormal().dot(t - p[0]);
    return dcmp(dot);
  }
  Point3 ProjPtToPlane(Point3 p, Plane pl) {
    Point3 normal = pl.GetNormal();
    return p - normal * normal.dot(p - pl[0]);
  }
  LD DisPtPlane(Point3 p, Plane pl) {
    Point3 normal = pl.GetNormal();
    return abs(normal.dot(p - pl[0]));
  }
  bool PtBelongToPlane(Point3 p, Plane pl) {
    return DisPtPlane(p, pl) < EPS;
  }
  bool Line3BelongToPlane(Line3 l, Plane pl) {
    return PtBelongToPlane(l[0], pl) &&
                      PtBelongToPlane(l[1], pl);
  }
  Plane ShiftUpDown(Plane p, LD dist) { //!tested
    Point3 n = p.GetNormal();
    LD d = p.GetNormal().dot(p[0]);
    return Plane(n, d + dist * n.Norm());
  }
  Plane ParallelPlane(Plane pl, Point3 A) {
    Point3 diff = A - ProjPtToPlane(A, pl);
    return Plane{pl[0]+diff,pl[1]+diff,pl[2]+diff};
  }
  //undefined for parallel line and plane(!tested)
  Point3 InterLinePlane(Line3 l, Plane p) {
    Point3 norm = p.GetNormal();
    LD D = norm.dot(p[0]);
    LD k =
      (D -(norm.dot(l[0])))/(norm.dot(l[1]-l[0]));
    return l[0] + (l[1]-l[0])*k;
  }
  // not tested, assumes planes are not parallel
  Line3 InterPlanePlane(Plane p1, Plane p2) {
    Point3 n1=p1.GetNormal(),n2 = p2.GetNormal();
    LD d1 = n1.dot(p1[0]), d2 = n2.dot(p2[0]);
    Point3 dir = n1.cross(n2);
    assert(!dir.IsZero()); /// parallel plane
    Point3 u =
          (n2*d1 - n1*d2).cross(dir)/dir.dot(dir);
    return Line3(u, u + dir);
  }
  Point PlanePtTo2D(Plane pl, Point3 p) { // ok
    assert(PtBelongToPlane(p, pl));
    vector<Point3> base = pl.GetOrtonormalBase();
    Point3 control{0, 0, 0};
    for (int tr = 0; tr < 3; tr++)  {
      control=control+base[tr] * p.dot(base[tr]);
    }
    assert(PtBelongToPlane(pl[0] + base[1], pl));
    assert(PtBelongToPlane(pl[0] + base[2], pl));
    assert((p - control).IsZero());
    return {p.dot(base[1]), p.dot(base[2])};
  }
  Line PlaneLineTo2D(Plane pl, Line3 l) {
    return
      {PlanePtTo2D(pl,l[0]),PlanePtTo2D(pl,l[1])};
  }
  Point3 PlanePtTo3D(Plane pl, Point p) { // ok
    vector<Point3> base = pl.GetOrtonormalBase();
    return base[0]*base[0].dot(pl[0]) +
                        base[1]*p.x+base[2]*p.y;
  }
  Line3 PlaneLineTo3D(Plane pl, Line l) {
    return Line3{PlanePtTo3D(pl,l[0]),
                        PlanePtTo3D(pl, l[1])};
  }
  Line3 ProjLineToPlane(Line3 l, Plane pl) { // ok
    return Line3{ProjPtToPlane(l[0], pl),
                        ProjPtToPlane(l[1], pl)};
  }
  Point3 ClosestPtOnL1FromL2(Line3 l1,Line3 l2){
    Point3 n = (l1[1]-l1[0]).cross(l2[1]-l2[0]);
    Point3 n3 = (l2[1]-l2[0]).cross(n);//!tested
    ///p is the plane including line l2 and n
    Plane p = Plane(n3, n3.dot(l2[0]));
    return InterLinePlane(l1, p);
  }
  vector<Point3> InterLineLine(Line3 k, Line3 l) {
    if (Lines3Equal(k, l)) { return {k[0], k[1]};}
    if (PtBelongToLine3(l[0], k)) {return {l[0]};}
    Plane pl{l[0], k[0], k[1]};
    if (!PtBelongToPlane(l[1], pl)) { return {}; }
    Line k2 = PlaneLineTo2D(pl, k);
    Line l2 = PlaneLineTo2D(pl, l);
    vector<Point>inter=Utils::InterLineLine(k2,l2);
    vector<Point3> res;
    for (auto P:inter) res.pb(PlanePtTo3D(pl, P));
    return res;
  }
  LD DisLineLine (Line3 l1, Line3 l2){ //!tested
    Point3 dir = (l1[1]-l1[0]).cross(l2[1]-l2[0]);
    if(dcmp(dir.Norm())==0)
      return DistPtLine(l2[0],l1);
    return abs((l2[0]-l1[0]).dot(dir))/dir.Norm();
  }
  /**
  LD DisLineLine(Line3 l, Line3 k) {//ok(para fix)
    Plane together{l[0],l[1],l[0]+k[1]-k[0]};
    Line3 proj = ProjLineToPlane(k, together);
    Point3 inter =
            (Utils3::InterLineLine(l,proj))[0];
    Point3 on_k_inter = k[0] + inter - proj[0];
    return inter.Dis(on_k_inter);
  } **/
  LD Det(Point3 a, Point3 b, Point3 d) { // ok
    Point3 pts[3] = {a, b, d};
    LD res = 0;
    for (int sign : {-1, 1}) {
      for (int st_col=0; st_col<3; st_col++) {
        int c = st_col;
        LD prod = 1;
        for (int r=0; r<3; r++){
          prod *= pts[r][c];
          c = (c + sign + 3) % 3;
        }
        res += sign * prod;
      }
    }
    return res;
  }
  Point3 PtFromSphericalAng(LD al, LD be) { // ok
   return{cos(al)*cos(be),cos(al)*sin(be),sin(al)};
  }
  //img of B in rot wrt line
  //passing thru orig s.t.A1->A2
  Point3 RotateAccordingly
          (Point3 A1,Point3 A2,Point3 B1) { // ok
    Plane pl{A1, A2, {0, 0, 0}};
    Point A12 = PlanePtTo2D(pl, A1);
    Point A22 = PlanePtTo2D(pl, A2);
    complex<LD> rat = complex<LD>(A22.x, A22.y) /
                        complex<LD>(A12.x, A12.y);
    Plane plb = ParallelPlane(pl, B1);
    Point B2 = PlanePtTo2D(plb, B1);
    complex<LD>Brot = rat*complex<LD>(B2.x, B2.y);
    return
      PlanePtTo3D(plb,{Brot.real(),Brot.imag()});
  }
  vector<Point3>InterLineSphere(Line3 l,Sphere s){
    vector<Point3> ints; // not tested
    LD h2 = Sq(s.r) - Sq(DisPtLine3(s.cent, l));
    if(dcmp(h2) < 0) return ints;
    if(dcmp(h2) == 0){
      ints.push_back(ProjPtToLine3(s.cent, l));
      return ints;
    }
    Point3 v = ProjPtToLine3(s.cent, l);
    Point3 dir = l[1] - l[0];
    Point3 h = dir * Sqrt(h2)/dir.Norm();
    ints.push_back(v+h); ints.push_back(v-h);
    return ints;
  }
  vector<Circle3>InterPlaneSphere
                          (Plane pl,Sphere s){//ok
    Point3 proj = ProjPtToPlane(s.cent, pl);
    LD dis = s.cent.Dis(proj);
    if (dis > s.r + EPS) {
      return {};
    }
    if (dis > s.r - EPS) {
      return {{pl, proj, 0}};// is it best choice?
    }
    return {{pl,proj,Sqrt(s.r*s.r-dis*dis)}};
  }
  bool PtBelongToSphere(Sphere s, Point3 p) {
    return abs(s.r - s.cent.Dis(p)) < EPS;
  }
  LD DisOnSphere(Sphere sph, Point3 A, Point3 B) {
    assert(PtBelongToSphere(sph, A));
    assert(PtBelongToSphere(sph, B));
    LD ang = Angle(A, sph.cent, B);
    return ang * sph.r;
  }
}
bool InsideATriangle
          (Point3 a,Point3 b,Point3 c,Point3 p){
  Plane abc = Plane(a, b, c);
  if(!Utils3::PtBelongToPlane(p, abc))return 0;
  Point3 n = abc.GetNormal();
  vector<int> sign(3);
  for(int i = 0; i < 3; i++) {
    LD t = n.dot((abc[(i+1)%3]-abc[i]).
                                cross(p-abc[i]));
    sign[i] = dcmp(t);
  }
  if(sign[0]>=0&&sign[1]>=0&&sign[2]>=0) return 1;
  if(sign[0]<=0&&sign[1]<=0&&sign[2]<=0) return 1;
  return 0;
}
LD PtDistOn3dTriangle
          (Point3 a,Point3 b,Point3 c,Point3 p){
  Plane abc = Plane(a,b,c);
  Point3 p_ = Utils3::ProjPtToPlane(p, abc);
  LD ret = 1e19;
  if(InsideATriangle(a,b,c,p_))
    ret = min(ret, p.Dis(p_));
  ret = min(ret,Utils3::DistPtSeg3(p, Line3(a,b)));
  ret = min(ret,Utils3::DistPtSeg3(p, Line3(b,c)));
  ret = min(ret,Utils3::DistPtSeg3(p, Line3(a,c)));
  return ret;
}
struct Face{
  Point3 a, b, c;
  Face(){}
  Face(Point3 a,Point3 b,Point3 c):a(a),b(b),c(c){}
  Face(const Face &f) : a(f.a), b(f.b), c(f.c) {}
};
LD ployhedronVolume(vector<Face> &vec) { //!tested
  if(vec.size() == 0) return 0;
  Point3 reff = vec[0].a; LD vol = 0;
  for(int i = 1; i < vec.size(); i++) {
    Point3 ar = (vec[i].b-vec[i].a).
                      cross(vec[i].c - vec[i].a);
    vol += abs(ar.dot(reff-vec[i].a));
  }
  return vol/6.0;
}
vector<Face>Convex3dHull(vector<Point3> &V){//nt
  vector <Face> Faces;
  for(int i = 0; i < V.size(); i++) {
    for(int j = i+1; j < V.size(); j++) {
      for(int k = j+1; k < V.size(); k++) {
        if(((V[j]-V[i]).cross(V[k]-V[i])).Norm()
            < EPS) continue;
        bool up = 0, down = 0;
        Plane P(V[i], V[j], V[k]);
        Point3 normal = P.GetNormal();
        for(int l = 0; l < V.size(); l++) {
          if (l == i or l == j or l == k)
            continue;
          if(InsideATriangle(V[i],V[j],V[k],V[l])){
            up = down = 1;
            break;
          }
          else if(normal.dot(V[l]-V[i])<0) down=1;
          else up = 1;
        }
        if(up == 0 or down == 0) {
          Face temp;
          temp.a=V[i],temp.b=V[j],temp.c=V[k];
          Faces.push_back(temp) ;
        }
      }
    }
  }
  return Faces;
}
struct PointS {
  LD lat, lon;
  PointS(LD latt, LD lonn) {lat=latt; lon=lonn;}
  Point3 toEucl() {
   return Point3{cos(lat)*cos(lon),
                    cos(lat)*sin(lon),sin(lat)};
  }
  PointS(Point3 p) {
    p.NormalizeSelf(); lat = Asin(p.z);
    lon = Acos(p.y / cos(lat));
  }
};
LD DistS(Point3 a, Point3 b) {
  return atan2l(b.cross(a).Norm(), a.dot(b));
}
struct CircleS {
  Point3 o; // center of circle on sphere
  LD r; // arc len
  LD area() const { return 2*PI*(1 - cos(r)); }
};
CircleS From3(Point3 a,Point3 b,Point3 c){
  int tmp = 1; //any 3 dif pts
  if((a-b).Norm()>(c-b).Norm()){
      swap(a,c);tmp = -tmp;
  }
  if((b-c).Norm()>(a-c).Norm()){
      swap(a,b);tmp = -tmp;
  }
  Point3 v=(c-b).cross(b-a);
  v = v * (tmp / v.Norm());
  return CircleS{v, DistS(a,v)};
}
CircleS From2(Point3 a,Point3 b){//nei same nor opp
  Point3 mid = (a + b) / 2;
  mid = mid / mid.Norm();
  return From3(a, mid, b);
}
//angle at A, no two points opposite
LD Angle(Point3 A, Point3 B, Point3 C) {
  LD a = B.dot(C), b = C.dot(A), c = A.dot(A);
  return Acos((b-a*c)/Sqrt((1-Sq(a))*(1-Sq(c))));
}
// no two poins opposite
LD TriangleArea(Point3 A, Point3 B, Point3 C) {
  LD a = Angle(C,A,B),b = Angle(A,B,C);
  LD c = Angle(B,C,A);
  return a + b + c - PI;
}
// what about c1==c2 case?
vector<Point3>IntersectionS
                        (CircleS c1, CircleS c2) {
  Point3 n = c2.o.cross(c1.o);
  Point3 w = c2.o * cos(c1.r) - c1.o * cos(c2.r);
  LD d = n.SqNorm();
  if (d < EPS) {
    cerr<<"parallel circles?\n";
    return {};
  }
  LD a = w.SqNorm() / d; vector<Point3> res;
  if (a >= 1 + EPS) return res;
  Point3 u = n.cross(w) / d;
  if (a > 1 - EPS) {
    res.pb(u); return res;
  }
  LD h = Sqrt((1 - a) / d);
  res.pb(u + n * h);
  res.pb(u - n * h);
  return res;
}
