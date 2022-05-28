const LD EPS = 1e-9;
const LD PI = acos(-1);
LD Sq(LD x)     {return x * x;}
LD Acos(LD x){return acos(min(1.0L,max(-1.0L,x)));}
LD Asin(LD x){return asin(min(1.0L,max(-1.0L,x)));}
LD Sqrt(LD x) {return sqrt(max(0.0L, x));}
int dcmp(LD x) {
  if(fabs(x) < EPS) return 0;
  return (x > 0.0 ? +1 : -1);
}
struct Point {
  LD x, y;
  Point() {}
  Point(LD a, LD b) : x(a), y(b) {}
  Point(const Point& a) : x(a.x), y(a.y) {}
  void operator=(const Point& a) { x=a.x; y=a.y;}
  Point operator+(const Point& a) const
        { Point p(x + a.x, y + a.y); return p; }
  Point operator-(const Point& a)  const
        { Point p(x - a.x, y - a.y); return p; }
  Point operator*(LD a)const
        { Point p(x*a,y*a); return p; }
  Point operator/(LD a) const
  { assert(a > EPS); Point p(x/a,y/a); return p; }
  bool IsZero() const {
    return abs(x) < EPS && abs(y) < EPS;
  }
  bool operator==(const Point& a) const {
    return (*this - a).IsZero();
  }
  LD cross(const Point& a) const {
    return x * a.y - y * a.x;
  }
  LD cross(Point a, Point b) const {
    a = a-*this; b = b-*this; return a.cross(b);
  }
  LD dot(const Point& a) const {
    return x * a.x + y * a.y;
  }
  LD Norm() const { return Sqrt(Sq(x) + Sq(y));}
  void NormalizeSelf() { *this = *this / Norm();}
  Point Normalize() {
    Point res(*this);res.NormalizeSelf();
    return res;
  }
  LD Dist(const Point& a)const
        {return (*this-a).Norm();}
  LD Angle() const { return atan2(y, x);}
  void RotateSelf(LD angle) {
    LD c = cos(angle), s = sin(angle);
    LD nx = x*c-y*s, ny = y*c+x*s; y = ny, x = nx;
  }
  Point Rotate(LD angle) const {
    Point res(*this); res.RotateSelf(angle);
    return res;
  }
  static bool LexCmp(const Point&a,const Point&b){
    if(abs(a.x - b.x) > EPS) return a.x < b.x;
    return a.y < b.y;
  }
  LD SqNorm() { return x * x + y * y;}
};
struct Circle {
  Point center; LD r;
  Circle(LD x, LD y, LD rad) {
    center = Point(x, y); r = rad;
  }
  Circle(const Point& a,LD rad):center(a),r(rad){}
  Point PointAtAngle(LD ang) const {
    return center+Point{r*cos(ang),r*sin(ang)};
  }
  bool operator==(const Circle& c) const {
    return center == c.center && abs(r-c.r) < EPS;
  }
};
struct Line {
  Point p[2]; bool is_seg;
  Line(Point a, Point b, bool is_seg_ = false) {
    p[0] = a; p[1] = b; is_seg = is_seg_;
  }
  Line() {}
  // Ax + By + C = 0, not tested
  Line(LD A, LD B, LD C, bool is_seg_ = false) {
    if(fabs(A) > EPS)
      p[0]=Point(-C/A,0.),p[1]=Point(-(B+C)/A,1.);
    else
      p[0]=Point(0.,-C/B),p[1]=Point(1.,-(A+C)/B);
    is_seg = is_seg_;
  }
  Point& operator[](int a) { return p[a];}
  Point Dir() { return p[1] - p[0];}
  Point NormalVector() {
    Point perp = p[1]-p[0];perp.RotateSelf(PI/2);
    perp.NormalizeSelf(); return perp;
  }
  Line shift(Point q) { // not tested
    return Line(p[0] + q, p[1] + q, is_seg);
  }
  //(A,B,C) such that A^2+B^2=1, (A,B) >(0,0)
  vector<LD> LineEqNormLD() { // seems ok
    LD A = p[1].y - p[0].y, B = p[0].x - p[1].x;
    LD C = -(A * p[0].x + B * p[0].y);
    assert(abs(A*p[1].x + B*p[1].y + C) < EPS);
    LD norm = Sqrt(Sq(A) + Sq(B));
    vector<LD> res{A, B, C};
    for (auto& x : res)  x /= norm;
    if (A < -EPS || (abs(A) < EPS && B < -EPS))
      for (auto& x : res) { x *= -1; }
    return res;
  }
  // assumes that coordinates are integers!
  vector<int> LineEqNormInt() { // seems ok
    int A = round(p[1].y - p[0].y);
    int B = round(p[0].x - p[1].x);
    int C = -(A * p[0].x + B * p[0].y);
    int gcd = abs(__gcd(A, __gcd(B, C)));
    vector<int> res{A, B, C};
    for (auto& x : res) { x /= gcd; }
    if (A < 0 || (A == 0 && B < 0))
      for (auto& x : res) { x *= -1; }
    return res;
  }
};

namespace Utils {

LD Angle(Point P, Point Q, Point R) {// angle PQR
  LD ang2 = (P - Q).Angle(), ang1 = (R-Q).Angle();
  LD ans = ang1 - ang2;
  if (ans < EPS) ans += 2 * PI;
  return ans;
}
bool PtBelongToLine(Point p, Line l) {
  return abs(l[0].cross(l[1], p)) < EPS;
}
bool PtBelongToSeg(Point p, Line l) { // seems ok
  return abs(p.Dist(l[0])+p.Dist(l[1])
             -l[0].Dist(l[1])) < EPS;
}
bool AreParallel(Line l1, Line l2) { // seems ok
  LD t=l1[0].cross(l2[0],l1[1])
            -l1[0].cross(l2[1],l1[1]);
  return abs(t) < EPS;
}
bool AreCollinear(Line l1, Line l2) {// not tested
  return AreParallel(l1,l2) &&
                  PtBelongToLine(l2[0],l1);
}
Point ProjPtToLine(Point p, Line l) { //Tested
  Point dir = l[1]-l[0];
  return l[0]+dir*(dir.dot(p-l[0])/dir.dot(dir));
}
Point ReflectPtWRTLine(Point p, Line l) {
  Point proj = ProjPtToLine(p, l);return proj*2-p;
}
Point ProjPtToSegment(Point p, Line l){//!tested
  LD base = (l[1]-l[0]).SqNorm();
  if (fabs(base) < EPS) return l[0];
  LD param = (p-l[0]).dot(l[1]-l[0])/base;
  if (param < 0) return l[0];
  if (param > 1) return l[1];
  return l[0] + (l[1]-l[0]) * param;
}
LD PtToLine(Point p, Line l) { // not tested
  Point v1 = l[1] - l[0], v2 = p - l[0];
  return fabs(v1.cross(v2))/v1.Norm();
}
LD PtToSegment(Point p, Line l) {
  if (l[0] == l[1]) return (p-l[0]).Norm();
  Point v1 = l[1]-l[0], v2 = p-l[0], v3 = p-l[1];
  if ((v1.dot(v2)) < -EPS) return v2.Norm();
  else if ((v1.dot(v3)) > EPS) return v3.Norm();
  else return fabs(v1.cross(v2))/v1.Norm();
}
vector<Point> InterLineLine(Line& a, Line& b){//ok
  Point vec_a = a[1] - a[0];
  Point vec_b1 = b[1] - a[0];
  Point vec_b0 = b[0] - a[0];
  LD tr_area = vec_b1.cross(vec_b0);
  LD quad_area = vec_b1.cross(vec_a)
                            + vec_a.cross(vec_b0);
  if (abs(quad_area) < EPS){ //parallel/coinciding
    if (PtBelongToLine(a[0], b)) {
      return {a[0], a[1]};
    } else {
      return {};
    }
  }
  return {a[0] + vec_a * (tr_area / quad_area)};
}
//SZ(res)==0:empty,SZ(res)=1:=> intersection is
//a pt,SZ(res) == 2 => intersection is a segment
vector<Point> InterSegs(Line l1, Line l2) { // ok
  if(!Point::LexCmp(l1[0],l1[1]))
    swap(l1[0], l1[1]);
  if(!Point::LexCmp(l2[0],l2[1]))
    swap(l2[0], l2[1]);
  if(AreParallel(l1, l2)) {
    if(!PtBelongToLine(l2[0],l1))
      return vector<Point>();
    vector<Point> ends(2);
    for (int tr = 0; tr < 2; tr++)
      if (Point::LexCmp(l1[tr], l2[tr]) ^ tr)
        ends[tr] = l2[tr];
      else ends[tr] = l1[tr];
    if ((ends[1] - ends[0]).IsZero())
      ends.pop_back();
    if(SZ(ends)==2&&Point::LexCmp(ends[1],ends[0]))
      return vector<Point>();
    return ends;
  }
  else {
    vector<Point> p = InterLineLine(l1, l2);
    if(PtBelongToSeg(p[0],l1) &&
                          PtBelongToSeg(p[0],l2))
      return p;
    return vector<Point>();
  }
}
LD SegmentToSegmentDistance(Line l1,Line l2){//nt
  vector<Point> inter = InterSegs(l1, l2);
  if(inter.size() > 0) return 0.0;
  LD an=min(PtToSegment(l1[0],l2),
                          PtToSegment(l1[1],l2));
  an = min(an, PtToSegment(l2[0], l1));
  an = min(an, PtToSegment(l2[1], l1));
  return an;
}
//0,1,2,3 pts.If 3 pts it means they are equal
vector<Point>InterCircleCircle(Circle a,Circle b){
  if (a.r + EPS < b.r) swap(a, b);
  if (a == b) {
    return vector<Point>{a.PointAtAngle(0),
            a.PointAtAngle(2 * PI / 3),
                a.PointAtAngle(4 * PI / 3)};
  }
  Point diff=b.center-a.center;LD dis=diff.Norm();
  LD ang = diff.Angle();
  LD longest=max(max(a.r,b.r),dis),per=a.r+b.r+dis;
  if (2 * longest > per + EPS)
    return vector<Point>();
  if (abs(2 * longest - per) < 2 * EPS)
    return vector<Point>{a.PointAtAngle(ang)};
  LD d=Acos((Sq(a.r)+Sq(dis)-Sq(b.r))/(2*a.r*dis));
  return vector<Point>{a.PointAtAngle(ang - d),
                          a.PointAtAngle(ang+d)};
}
vector<Point>InterCircleLine(Circle c,Line l){//ok
  Point proj = ProjPtToLine(c.center, l);
  LD dis_proj = c.center.Dist(proj);
  if (dis_proj > c.r + EPS) return vector<Point>();
  LD a = Sqrt(Sq(c.r) - Sq(dis_proj));
  Point dir = l[1] - l[0];
  LD dir_norm = dir.Norm();
  vector<Point> cands{proj + dir * (a / dir_norm),
                    proj - dir * (a / dir_norm)};
  if (cands[0].Dist(cands[1])<EPS)
    return vector<Point>{proj};
  return cands;
}
vector<Point>InterCircleSeg(Circle c, Line l){//ok
  vector<Point> from_line = InterCircleLine(c, l);
  vector<Point> res;
  for(auto p:from_line)
    if(PtBelongToSeg(p,l)) res.pb(p);
  return res;
}
vector<Point>TangencyPtsToCircle(Circle c,Point p){
  LD d = c.center.Dist(p);//ok
  if (d < c.r - EPS) return {};
  if (d < c.r + EPS) return {p};
  LD from_cent = (p - c.center).Angle();
  LD ang_dev = Acos(c.r / d);
  return {c.PointAtAngle(from_cent - ang_dev),
            c.PointAtAngle(from_cent + ang_dev)};
}
vector<Line> OuterTangents(Circle c1, Circle c2) {
  if(c1 == c2) { return {}; }//is it best choice?
  if(c1.r < c2.r) { swap(c1, c2); }
  if(c2.r + c1.center.Dist(c2.center) < c1.r-EPS)
    return {};
  if (abs(c1.r - c2.r) < EPS) {
    Point diff = c2.center - c1.center;
    Point R = diff.Rotate(PI/2)*(c1.r/diff.Norm());
    return {{c1.center + R, c2.center + R},
                  {c1.center - R, c2.center - R}};
  }
  Point I = c1.center +
        (c2.center-c1.center)*(c1.r/(c1.r-c2.r));
  if (c2.r+c1.center.Dist(c2.center)<c1.r+EPS) {
    return
       {{I,I+(c2.center-c1.center).Rotate(PI/2)}};
  }
  vector<Point> to1 = TangencyPtsToCircle(c1, I);
  vector<Point> to2 = TangencyPtsToCircle(c2, I);
  vector<Line>res{{to1[0],to2[0]},{to1[1],to2[1]}};
  assert(Utils::PtBelongToLine(I, res[0]));
  assert(Utils::PtBelongToLine(I, res[1]));
  return res;
}
vector<Line> InnerTangents(Circle c1, Circle c2) {
  if (c1 == c2) return {};//surely best choice
  if (c1.r < c2.r) { swap(c1, c2); }
  LD d = c1.center.Dist(c2.center);
  if (d < c1.r + c2.r - EPS) { return {}; }
  Point I = c1.center +
    (c2.center-c1.center)*(c1.r/(c1.r+c2.r));
  if(d < c1.r + c2.r + EPS)  return {{I,I+
            (c2.center-c1.center).Rotate(PI/2)}};
  vector<Point> to1 = TangencyPtsToCircle(c1, I);
  vector<Point> to2 = TangencyPtsToCircle(c2, I);
  vector<Line>res{{to1[0],to2[0]},{to1[1],to2[1]}};
  assert(Utils::PtBelongToLine(I, res[0]));
  assert(Utils::PtBelongToLine(I, res[1]));
  return res;
}
LD DiskInterArea(Circle c1, Circle c2) {
  if (c1.r < c2.r) swap(c1, c2);
  LD d = c1.center.Dist(c2.center);
  if (c1.r + c2.r < d + EPS) return 0;
  if (c1.r - c2.r > d - EPS) return PI * Sq(c2.r);
  LD al=Acos((Sq(d)+Sq(c1.r)-Sq(c2.r))/(2*d*c1.r));
  LD be=Acos((Sq(d)+Sq(c2.r)-Sq(c1.r))/(2*d*c2.r));
  return al * Sq(c1.r) + be * Sq(c2.r) -
        sin(2*al)*Sq(c1.r)/2-sin(2*be)*Sq(c2.r)/2;
}
Line RadicalAxis(Circle c1, Circle c2) {
  LD d = c1.center.Dist(c2.center);
  LD a = (Sq(c1.r) - Sq(c2.r) + Sq(d)) / (2 * d);
  Point Q = c1.center+(c2.center-c1.center)*(a/d);
  Point R = Q+(c2.center-c1.center).Rotate(PI/2);
  return Line(Q, R);
}
vector<Point> CirThroughAPtAndTngntToALineWithRad
            (Point p, Line l, LD r) {//not tested
  vector<Point> sol;
  Point norm = l.NormalVector();
  Line l1=l.shift(norm*r);
  Line l2=l.shift(norm*(-r));
  sol = InterCircleLine(Circle(p, r), l1);
  vector<Point> t=InterCircleLine(Circle(p, r),l2);
  for(auto pp : t) sol.push_back(pp);
  return sol;
}
vector<Point>CirTngntToTwoLinesWithRad
            (Line l1,Line l2,LD r) { // not tested
  vector<Point> sol;
  Point e1 = l1.NormalVector();
  Point e2 = l2.NormalVector();
  Line L1[2]={l1.shift(e1*r),l1.shift(e1*(-r))},
  L2[2]={l2.shift(e2 * r),l2.shift(e2 * (-r))};
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      vector<Point> t = InterLineLine(L1[i],L2[j]);
      for(auto pp : t) sol.push_back(pp);
    }
  }
  return sol;
}
vector<Point> CirTanToTwoDisjointCirclesWithRadius
      (Circle c1, Circle c2, LD r) { // not tested
  c1.r += r; c2.r += r;
  return InterCircleCircle(c1, c2);
}
}

// CENTERS BEGIN
Point Bary(Point A,Point B,Point C,LD a,LD b,LD c){
  return (A * a + B * b + C * c) / (a + b + c);
}
Point Centroid(Point A, Point B, Point C) {
  return Bary(A, B, C, 1, 1, 1);
}
Point Circumcenter(Point A, Point B, Point C) {
  LD a = (B - C).SqNorm(), b = (C - A).SqNorm();
  LD c = (A - B).SqNorm();
  return Bary(A,B,C,a*(b+c-a),b*(c+a-b),c*(a+b-c));
}
Point Incenter(Point A, Point B, Point C) {
  return Bary(A,B,C,(B-C).Norm(),
              (A-C).Norm(),(A-B).Norm());
}
Point Orthocenter(Point A, Point B, Point C) {
  LD a=(B-C).SqNorm(),b=(C-A).SqNorm();
  LD c=(A-B).SqNorm();
  return Bary(A,B,C,(a+b-c)*(c+a-b),
              (b+c-a)*(a+b-c),(c+a-b)*(b+c-a));
}
Point Excenter(Point A,Point B,Point C){//opp to A
  LD a=(B-C).Norm(),b=(A-C).Norm(),c=(A-B).Norm();
  return Bary(A, B, C, -a, b, c);
}