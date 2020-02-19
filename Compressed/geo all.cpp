#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
#define pb push_back
#define SZ(x) ((int)(x).size())
const LD EPS = 1e-9;
const LD PI = acos(-1);
LD Sq(LD x)     {return x * x;}
LD Acos(LD x)   {return acos(min(1.0L,max(-1.0L, x)));}
LD Sqrt(LD x)   {return sqrt(max(0.0L, x));}
int dcmp(LD x) {
  if(fabs(x) < EPS) return 0;
  return (x > 0.0 ? +1 : -1);
}


struct Point {
  LD x, y;
  Point() {}
  Point(LD a, LD b) : x(a), y(b) {}
  Point(const Point& a) : x(a.x), y(a.y) {}
  void operator=(const Point& a) { x = a.x; y = a.y; }
  Point operator+(const Point& a) const { Point p(x + a.x, y + a.y); return p; }
  Point operator-(const Point& a) const { Point p(x - a.x, y - a.y); return p; }
  Point operator*(LD a) const { Point p(x * a, y * a); return p; }
  Point operator/(LD a) const { assert(a > EPS); Point p(x / a, y / a); return p; }

  bool IsZero() const {
    return abs(x) < EPS && abs(y) < EPS;
  }
  bool operator==(const Point& a) const {
    return (*this - a).IsZero();
  }
  LD CrossProd(const Point& a) const {
    return x * a.y - y * a.x;
  }
  LD CrossProd(Point a, Point b) const {
    a = a - *this;
    b = b - *this;
    return a.CrossProd(b);
  }
  LD DotProd(const Point& a) const {
    return x * a.x + y * a.y;
  }
  LD Norm() const {
    return Sqrt(Sq(x) + Sq(y));
  }
  void NormalizeSelf() {
    *this = *this / Norm();
  }
  Point Normalize() {
    Point res(*this);
    res.NormalizeSelf();
    return res;
  }
  LD Dist(const Point& a) const {
    return (*this - a).Norm();
  }
  LD Angle() const {
    return atan2(y, x);
  }
  void RotateSelf(LD angle) {
    LD c = cos(angle);
    LD s = sin(angle);
    LD nx = x * c - y * s;
    LD ny = y * c + x * s;
    y = ny;
    x = nx;
  }
  Point Rotate(LD angle) const {
    Point res(*this);
    res.RotateSelf(angle);
    return res;
  }
  static bool LexCmp(const Point& a, const Point& b) {
    if (abs(a.x - b.x) > EPS) {
      return a.x < b.x;
    }
    return a.y < b.y;
  }
  LD SqNorm() {
    return x * x + y * y;
  }
};

ostream& operator<<(ostream& out, Point p) {
  return out << "(" << p.x << ", " << p.y << ")";
}

struct Circle {
  Point center;
  LD r;
  Circle(LD x, LD y, LD rad) {
    center = Point(x, y);
    r = rad;
  }
  Circle(const Point& a, LD rad) : center(a), r(rad) {}
  Point RotateRightMost(LD ang) const {
    return center + Point{r * cos(ang), r * sin(ang)};
  }
  bool operator==(const Circle& c) const {
    return center == c.center && abs(r - c.r) < EPS;
  }
};

struct Line {
  Point p[2];
  bool is_seg;
  Line(Point a, Point b, bool is_seg_ = false) {
    p[0] = a;
    p[1] = b;
    is_seg = is_seg_;
  }
  Line() {
  }
  /// Ax + By + C = 0
  /// not tested
  Line(LD A, LD B, LD C, bool is_seg_ = false) {
    if(fabs(A) > EPS) {
        p[0] = Point(-C/A, 0.0);
        p[1] = Point(-(B+C)/A, 1.0);
    }
    else {
        p[0] = Point(0.0, -C/B);
        p[1] = Point(1.0, -(A+C)/B);
    }
    is_seg = is_seg_;
  }
  Point& operator[](int a) {
    return p[a];
  }
  Point Dir() {
    return p[1] - p[0];
  }
  Point NormalVector() {
    Point perp = p[1] - p[0];
    perp.RotateSelf(PI / 2);
    perp.NormalizeSelf();
    return perp;
  }
  /// not tested
  Line Translate(Point q) {
    return Line(p[0] + q, p[1] + q, is_seg);
  }
  // (A, B, C) such that A^2 + B^2 = 1, (A, B) > (0, 0)
  vector<LD> LineEqNormLD() { // seems ok
    LD A = p[1].y - p[0].y;
    LD B = p[0].x - p[1].x;
    LD C = -(A * p[0].x + B * p[0].y);
    assert(abs(A * p[1].x + B * p[1].y + C) < EPS);
    LD norm = Sqrt(Sq(A) + Sq(B));
    vector<LD> res{A, B, C};
    for (auto& x : res) { x /= norm; }
    if (A < -EPS || (abs(A) < EPS && B < -EPS)) {
      for (auto& x : res) { x *= -1; }
    }
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
    if (A < 0 || (A == 0 && B < 0)) {
      for (auto& x : res) { x *= -1; }
    }
    return res;
  }
};

namespace Utils {
  LD Angle(Point P, Point Q, Point R) { // angle PQR
    LD ang2 = (P - Q).Angle();
    LD ang1 = (R - Q).Angle();
    LD ans = ang1 - ang2;
    if (ans < EPS) {
      ans += 2 * PI;
    }
    return ans;
  }
  bool PtBelongToLine(Point p, Line l) {
    return abs(l[0].CrossProd(l[1], p)) < EPS;
  }
  bool PtBelongToSeg(Point p, Line l) { // seems ok
    return abs(p.Dist(l[0]) + p.Dist(l[1]) - l[0].Dist(l[1])) < EPS;
  }
  bool AreParallel(Line l1, Line l2) { // seems ok
    return abs(l1[0].CrossProd(l2[0], l1[1]) - l1[0].CrossProd(l2[1], l1[1])) < EPS;
  }
  bool AreCollinear(Line l1, Line l2) { /// not tested
    return AreParallel(l1, l2) && PtBelongToLine(l2[0], l1);
  }
  Point ProjPtToLine(Point p, Line l) { ///Tested
    Point diff = l[1] - l[0];
    return l[0] + diff * (diff.DotProd(p - l[0]) / diff.DotProd(diff));
  }
  Point ReflectPtWRTLine(Point p, Line l) {
    Point proj = ProjPtToLine(p, l);
    return proj * 2 - p;
  }
  /// project point c onto line segment AB
  /// not tested
  Point ProjPtToSegment(Point p, Line l) {
    LD base = (l[1]-l[0]).SqNorm();
    if (fabs(base) < EPS) return l[0];
    LD param = (p-l[0]).DotProd(l[1]-l[0])/base;
    if (param < 0) return l[0];
    if (param > 1) return l[1];
    return l[0] + (l[1]-l[0]) * param;
  }
  ///distance from point p to line AB
  /// not tested
  LD PtToLine(Point p, Line l) {
    Point v1 = l[1] - l[0], v2 = p - l[0];
    return fabs(v1.CrossProd(v2))/v1.Norm();
  }
  ///distance from point p to segment AB
  /// not tested
  LD PtToSegment(Point p, Line l) {
    if (l[0] == l[1]) return (p-l[0]).Norm();
    Point v1 = l[1] - l[0], v2 = p - l[0], v3 = p - l[1];
    if ((v1.DotProd(v2)) < -EPS) return v2.Norm();
    else if ((v1.DotProd(v3)) > EPS) return v3.Norm();
    else return fabs(v1.CrossProd(v2))/v1.Norm();
  }
  vector<Point> InterLineLine(Line& a, Line& b) { // working fine
    Point vec_a = a[1] - a[0];
    Point vec_b1 = b[1] - a[0];
    Point vec_b0 = b[0] - a[0];
    LD tr_area = vec_b1.CrossProd(vec_b0);
    LD quad_area = vec_b1.CrossProd(vec_a) + vec_a.CrossProd(vec_b0);
    if (abs(quad_area) < EPS) { // parallel or coinciding
      if (PtBelongToLine(a[0], b)) {
        return {a[0], a[1]};
      } else {
        return {};
      }
    }
    return {a[0] + vec_a * (tr_area / quad_area)};
  }
  // returns a vector of points such that their convex hull is intersection of those segments
  // SZ(res) == 0 => empty intersection, SZ(res) == 1 => intersection is a point, SZ(res) == 2 => intersection is a segment
  vector<Point> InterSegs(Line l1, Line l2) { // seems ok
    if (!Point::LexCmp(l1[0], l1[1])) { swap(l1[0], l1[1]); }
    if (!Point::LexCmp(l2[0], l2[1])) { swap(l2[0], l2[1]); }
    if (AreParallel(l1, l2)) {
      if (!PtBelongToLine(l2[0], l1)) { return vector<Point>(); }
      vector<Point> ends(2);
      for (int tr = 0; tr < 2; tr++) {
        if (Point::LexCmp(l1[tr], l2[tr]) ^ tr) {
          ends[tr] = l2[tr];
        } else {
          ends[tr] = l1[tr];
        }
      }
      if ((ends[1] - ends[0]).IsZero()) {
        ends.pop_back();
      }
      if (SZ(ends) == 2 && Point::LexCmp(ends[1], ends[0])) { return vector<Point>(); }
      return ends;
    } else {
      vector<Point> p = InterLineLine(l1, l2);
      if (PtBelongToSeg(p[0], l1) && PtBelongToSeg(p[0], l2)) { return p; }
      return vector<Point>();
    }
  }
  /// not tested
  LD SegmentToSegmentDistance(Line l1, Line l2) {
    vector<Point> inter = InterSegs(l1, l2);
    if(inter.size() > 0) return 0.0;
    LD ans = min(PtToSegment(l1[0], l2), PtToSegment(l1[1], l2));
    ans = min(ans, PtToSegment(l2[0], l1));
    ans = min(ans, PtToSegment(l2[1], l1));
    return ans;
  }

  // 0, 1, 2 or 3 pts. In case of 3 pts it means they are equal
  vector<Point> InterCircleCircle(Circle a, Circle b) {
    if (a.r + EPS < b.r) {
      swap(a, b);
    }
    if (a == b) {
      return vector<Point>{a.RotateRightMost(0), a.RotateRightMost(2 * PI / 3),
          a.RotateRightMost(4 * PI / 3)};
    }
    Point diff = b.center - a.center;
    LD dis = diff.Norm();
    LD ang = diff.Angle();
    LD longest = max(max(a.r, b.r), dis);
    LD per = a.r + b.r + dis;
    if (2 * longest > per + EPS) {
      return vector<Point>();
    }
    if (abs(2 * longest - per) < 2 * EPS) {
      return vector<Point>{a.RotateRightMost(ang)};
    }
    LD ang_dev = Acos((Sq(a.r) + Sq(dis) - Sq(b.r)) / (2 * a.r * dis));
    return vector<Point>{a.RotateRightMost(ang - ang_dev), a.RotateRightMost(ang + ang_dev)};
  }

  vector<Point> InterCircleLine(Circle c, Line l) { /// Tested here: http://codeforces.com/gym/100554/submission/10197624
    Point proj = ProjPtToLine(c.center, l);
    LD dis_proj = c.center.Dist(proj);
    if (dis_proj > c.r + EPS) { return vector<Point>(); }
    LD a = Sqrt(Sq(c.r) - Sq(dis_proj));
    Point dir = l[1] - l[0];
    LD dir_norm = dir.Norm();
    vector<Point> cands{proj + dir * (a / dir_norm), proj - dir * (a / dir_norm)};
    if (cands[0].Dist(cands[1]) < EPS) { return vector<Point>{proj}; }
    return cands;
  }
  vector<Point> InterCircleSeg(Circle c, Line l) { //seems ok
    vector<Point> from_line = InterCircleLine(c, l);
    vector<Point> res;
    for (auto p : from_line) {
      if (PtBelongToSeg(p, l)) { res.pb(p); }
    }
    return res;
  }
  vector<Point> TangencyPtsToCircle(Circle c, Point p) { // seems ok
    LD d = c.center.Dist(p);
    if (d < c.r - EPS) { return {}; }
    if (d < c.r + EPS) { return {p}; }
    LD from_cent = (p - c.center).Angle();
    LD ang_dev = Acos(c.r / d);
    return {c.RotateRightMost(from_cent - ang_dev), c.RotateRightMost(from_cent + ang_dev)};
  }
  // outer and inner tangents tested only locally (however I believe that rigorously)
  vector<Line> OuterTangents(Circle c1, Circle c2) {
    if (c1 == c2) { return {}; } // is it surely best choice?
    if (c1.r < c2.r) { swap(c1, c2); }
    if (c2.r + c1.center.Dist(c2.center) < c1.r - EPS) { return {}; }
    if (abs(c1.r - c2.r) < EPS) {
      Point diff = c2.center - c1.center;
      Point R = diff.Rotate(PI / 2) * (c1.r / diff.Norm());
      return {{c1.center + R, c2.center + R}, {c1.center - R, c2.center - R}};
    }
    Point I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r - c2.r));
    if (c2.r + c1.center.Dist(c2.center) < c1.r + EPS) {
      return {{I, I + (c2.center - c1.center).Rotate(PI / 2)}};
    }
    vector<Point> to1 = TangencyPtsToCircle(c1, I);
    vector<Point> to2 = TangencyPtsToCircle(c2, I);
    vector<Line> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(Utils::PtBelongToLine(I, res[0]));
    assert(Utils::PtBelongToLine(I, res[1]));
    return res;
  }
  // unfortunately big part of code is same as in previous function
  // can be joined when putting appropriate signs in few places
  // however those ifs differ a bit hence it may not be good idea
  // to necessarily join them
  vector<Line> InnerTangents(Circle c1, Circle c2) {
    if (c1 == c2) { return {}; } // this time surely best choice
    if (c1.r < c2.r) { swap(c1, c2); }
    LD d = c1.center.Dist(c2.center);
    if (d < c1.r + c2.r - EPS) { return {}; }
    Point I = c1.center + (c2.center - c1.center) * (c1.r / (c1.r + c2.r));
    if (d < c1.r + c2.r + EPS) {
      return {{I, I + (c2.center - c1.center).Rotate(PI / 2)}};
    }
    vector<Point> to1 = TangencyPtsToCircle(c1, I);
    vector<Point> to2 = TangencyPtsToCircle(c2, I);
    vector<Line> res{{to1[0], to2[0]}, {to1[1], to2[1]}};
    assert(Utils::PtBelongToLine(I, res[0]));
    assert(Utils::PtBelongToLine(I, res[1]));
    return res;
  }

  // tested here: http://codeforces.com/contest/600/submission/14961583
  // DON'T change anything as this will lead to precision errors
  // don't know why, but this is the only version which works precisely even for very mean cases
  // tested here: http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=006254 problem I

  LD DiskInterArea(Circle c1, Circle c2) {
    if (c1.r < c2.r) {
      swap(c1, c2);
    }
    LD d = c1.center.Dist(c2.center);
    if (c1.r + c2.r < d + EPS) {
      return 0;
    }
    if (c1.r - c2.r > d - EPS) {
      return PI * Sq(c2.r);
    }
    LD alfa = Acos((Sq(d) + Sq(c1.r) - Sq(c2.r)) / (2 * d * c1.r));
    LD beta = Acos((Sq(d) + Sq(c2.r) - Sq(c1.r)) / (2 * d * c2.r));
    return alfa * Sq(c1.r) + beta * Sq(c2.r) - sin(2 * alfa) * Sq(c1.r) / 2 - sin(2 * beta) * Sq(c2.r) / 2;
  }
  Line RadicalAxis(Circle c1, Circle c2) {
    LD d = c1.center.Dist(c2.center);
    LD a = (Sq(c1.r) - Sq(c2.r) + Sq(d)) / (2 * d);
    Point Q = c1.center + (c2.center - c1.center) * (a / d);
    Point R = Q + (c2.center - c1.center).Rotate(PI / 2);
    return Line(Q, R);
  }

  /// sol contains the center of these circles
  /// not tested
  vector<Point> CircleThroughAPointAndTangentToALineWithRadius(Point p, Line l, LD r) {
    vector<Point> sol;
    Point normal = l.NormalVector();
    Line l1 = l.Translate(normal * r), l2 = l.Translate(normal * (-r));
    sol = InterCircleLine(Circle(p, r), l1);
    vector<Point> t = InterCircleLine(Circle(p, r), l2);
    for(auto pp : t) sol.push_back(pp);
    return sol;
  }
  /// sol contains the center of these circles
  /// not tested
  vector<Point> CircleTangentToTwoLinesWithRadius(Line l1,Line l2, LD r) {
    vector<Point> sol;
    Point e1 = l1.NormalVector(), e2 = l2.NormalVector();
    Line L1[2]={l1.Translate(e1 * r),l1.Translate(e1 * (-r))},
    L2[2]={l2.Translate(e2 * r),l2.Translate(e2 * (-r))};
    for(int i = 0; i < 2; i++) {
      for(int j = 0; j < 2; j++) {
        vector<Point> t = InterLineLine(L1[i],L2[j]);
        for(auto pp : t) sol.push_back(pp);
      }
    }
    return sol;
  }
  /// sol contains the center of these circles
  /// not tested
  vector<Point> CircleTangentToTwoDisjointCirclesWithRadius(Circle c1, Circle c2, LD r) {
    c1.r += r; c2.r += r;
    return InterCircleCircle(c1, c2);
  }
}


// CENTERS BEGIN
Point Bary(Point A, Point B, Point C, LD a, LD b, LD c) {
    return (A * a + B * b + C * c) / (a + b + c);
}

Point Centroid(Point A, Point B, Point C) {
    return Bary(A, B, C, 1, 1, 1);
}

Point Circumcenter(Point A, Point B, Point C) {
    LD a = (B - C).SqNorm(), b = (C - A).SqNorm(), c = (A - B).SqNorm();
    return Bary(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}

Point Incenter(Point A, Point B, Point C) {
    return Bary(A, B, C, (B - C).Norm(), (A - C).Norm(), (A - B).Norm());
}

Point Orthocenter(Point A, Point B, Point C) {
    LD a = (B - C).SqNorm(), b = (C - A).SqNorm(), c = (A - B).SqNorm();
    return Bary(A, B, C, (a+b-c)*(c+a-b), (b+c-a)*(a+b-c), (c+a-b)*(b+c-a));
}

Point Excenter(Point A, Point B, Point C) { // opposite to A
    LD a = (B - C).Norm(), b = (A - C).Norm(), c = (A - B).Norm();
    return Bary(A, B, C, -a, b, c);
}

/// Cut Polygon (not tested)

void intersect(vector<Point> &V, Point a, Point b, Line l) {
    Point p = l[0], q = l[1];
    LD na = (a-p).CrossProd(q-p), nb = (b-p).CrossProd(q-p);
    if (na*nb < 0.0) {
        V.push_back(a + (b-a)*(na/(na-nb))) ;
    }
}
vector<Point> cut(vector<Point> &polygon, Line l, int sign) {
    vector<Point> np;
    int sz = polygon.size();
    for(int i = 0 ; i < sz ; i++) {
        Point p = polygon[i], q = polygon[(i+1)%sz];
        if(dcmp(l.Dir().CrossProd(p)) * sign >= 0) {
            np.push_back(p);
        }
        intersect(np, p, q, l);
    }
    return np;
}


///diameter of a convex polygon p
/// not tested
LD rotating_calipers(vector<Point> p) {
  int q = 1, n = p.size();
  LD ans = 0;
  for( int i = 0; i < n; i++) {
    while(p[i].CrossProd(p[(i+1)%n],p[(q+1)%n]) > p[i].CrossProd(p[(i+1)%n],p[q]))
      q = (q+1)%n;
    ans = max(ans, (LD)max((p[i]- p[q]).Norm(), (p[(i+1)%n] -p[q]).Norm()));
  }
  return ans;
}
///minimum area rectangle for convex polygon
/// not tested
LD rec_rotating_calipers(vector<Point> p) {
  int n = p.size();
  int q = 1;
  LD ans1 = 1e15, ans2 = 1e15;
  int l = 0, r = 0;
  for( int i = 0; i < n; i++ ) {
    while(dcmp(p[i].CrossProd(p[(i+1)%n],p[(q+1)%n])-p[i].CrossProd(p[(i+1)%n],p[q])) > 0)
      q=(q+1)%n;
    while (dcmp((p[(i+1)%n]-p[i]).DotProd(p[(r+1)%n]-p[r])) > 0)
      r=(r+1)%n;
    if (!i) l = q;
    while (dcmp((p[(i+1)%n]-p[i]).DotProd(p[(l+1)%n]-p[l])) < 0)
      l=(l+1)%n;
    LD d = (p[(i+1)%n]-p[i]).Norm();
    LD h = p[i].CrossProd(p[(i+1)%n],p[q])/d;
    LD w =(((p[(i+1)%n]-p[i]).DotProd(p[r]-p[i]))-((p[(i+1)%n]-p[i]).DotProd(p[l]-p[i])))/d;
    ans1 = min(ans1, 2*(h+w)), ans2 = min(ans2,h*w);
  }
  return ans2;
}

struct Polygon {
  vector<Point> pts;
  Polygon(vector<Point> pts_) : pts(pts_) {}
  Polygon() : Polygon(vector<Point>()) {}
  void Add(Point p) {
    pts.push_back(p);
  }
  // positive for counterclockwise
  LD Area() {
    LD area = 0;
    for(int i = 0; i < SZ(pts); i++) {
      area += pts[i].CrossProd(pts[(i + 1) % SZ(pts)]);
    }
    area /= 2;
    return area;
  }
  void OrientCounterclockwise() {
    if (Area() < 0) {
      reverse(pts.begin(), pts.end());
    }
  }
  int next(int a) {
    if (a + 1 < SZ(pts)) {
      return a + 1;
    }
    return 0;
  }
  pair<int, int> FurthestPair() { // tested here: http://codeforces.com/contest/333/submission/11058065
    MakeConvexHull();
    OrientCounterclockwise();
    int furth = 1;
    pair<int, int> best_pair = make_pair(0, 0);
    double best_dis = 0;
    for (int i = 0; i < SZ(pts); i++) {
      Point side = pts[next(i)] - pts[i];
      while (side.CrossProd(pts[furth] - pts[i]) < side.CrossProd(pts[next(furth)] - pts[i])) {
        furth = next(furth);
      }
      vector<int> vec{i, next(i)};
      for (auto ind : vec) {
        if (pts[ind].Dist(pts[furth]) > best_dis) {
          best_pair = make_pair(ind, furth);
          best_dis = pts[ind].Dist(pts[furth]);
        }
      }
      cerr<<"Furthest from: "<<pts[i]<<"-"<<pts[next(i)]<<" is "<<pts[furth]<<endl;
    }
    return best_pair;
  }
  void MakeConvexHull() { // tested everywhere http://codeforces.com/contest/333/submission/11058065
    vector<Point> one_way_hull[2];
    sort(pts.begin(), pts.end(), Point::LexCmp);
    for (int dir = -1; dir <= 1; dir += 2) {
      int hull_num = (dir + 1) / 2;
      auto& H = one_way_hull[hull_num];
      one_way_hull[hull_num].push_back(pts[0]);
      if (SZ(pts) > 1) {
        H.push_back(pts[1]);
      }
      for(int i = 2; i < SZ(pts); i++) {
        while (SZ(H) >= 2 &&
            dir * (pts[i] - H[SZ(H) - 2]).CrossProd(H.back() - H[SZ(H) - 2]) > -EPS) {
          H.pop_back();
        }
        H.push_back(pts[i]);
      }
    }
    pts.clear();
    for (auto p : one_way_hull[1]) {
      pts.push_back(p);
    }
    for (int i = SZ(one_way_hull[0]) - 2; i >= 1; i--) {
      pts.push_back(one_way_hull[0][i]);
    }
  }
  // without sides
  vector<vector<bool>> InsideDiagonalsMatrix() { // tested here: http://codeforces.com/contest/438/submission/11063385
    int n = pts.size();
    vector<vector<bool>> res(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Line diag(pts[i], pts[j]);
        if (i == j || abs(i - j) == 1 || abs(i - j) == n - 1) { continue; }
        res[i][j] = 1;
        for (int k = 0; k < n; k++) {
          int kk = next(k);
          Line side(pts[k], pts[kk]);
          if (k == i || k == j || kk == i || kk == j) { continue; }
          vector<Point> inter = Utils::InterSegs(diag, side);
          if (SZ(inter)) { res[i][j] = 0; }
        }
        int act = next(i);
        LD areas[2] = {0, 0};
        int passed_j = 0;
        while (act != i) {
          passed_j |= (act == j);
          areas[passed_j] += pts[i].CrossProd(pts[act], pts[next(act)]);
          act = next(act);
        }
        if (areas[0] * areas[1] < EPS) {
          res[i][j] = 0;
        }
      }
    }
    return res;
  }
};

// CLIP START
bool InUpper(Point a) {
  if (abs(a.y) > EPS) {
    return a.y > 0;
  }
  return a.x > 0;
}

bool angle_cmp(const Point a, const Point b) {
  bool u = InUpper(a);
  bool v = InUpper(b);
  return u!=v ? u : a.CrossProd(b)>0;
}

/**
  * @brief a+(b-a)*f \in c+lin(d-c)
  * @returns f
  */
LD cross(Point a, Point b, Point c, Point d) {
  return (d - c).CrossProd(a - c) / (d - c).CrossProd(a - b);
}

struct ClipLine { // valid side is on left
  ClipLine(Point A, Point B) : al(A), bl(B), a(A), b(B) {};
  Point al,bl; // original line points
  mutable Point a,b; // actual intersection points
  Point dir() const { return bl - al; }
  bool operator<(const ClipLine& l) const { return angle_cmp(dir(),l.dir()); }
  Point cross(const ClipLine& l) {
    return al + (bl - al) * ::cross(al, bl, l.al, l.bl);
  }
  bool left(Point p) {
    return (bl - al).CrossProd(p - al) > 0;
  }
};

struct Clip {
  Clip(LD r) : area(4*r*r) {
    Point a{-r,-r}, b{r,-r}, c{r,r}, d{-r,r};
    lines = {ClipLine(a,b), ClipLine(b,c), ClipLine(c,d), ClipLine(d,a)};
  }

  void insert(Line l) { insert(ClipLine(l[0], l[1])); }

  void insert(ClipLine l) {
    assert(abs(l.dir().SqNorm()) > EPS);
    find(l);
    while (size() && !l.left(it->a) && !l.left(it->b)) { erase(); }
    if (size()) {
      while (prev(), size() && !l.left(it->a) && !l.left(it->b)) { erase(); }
    }
    if (size() && (!l.left(it->a) || !l.left(it->b))) {
      l.a = l.cross(*it);
      area -= l.a.CrossProd(it->b)*.5; it->b = l.a; next();
      l.b = l.cross(*it);
      if ((l.a-l.b).SqNorm() < EPS) {
        l.b = l.a;
      }
      area -= it->a.CrossProd(l.b) * .5;
      it->a = l.b;
      if (!(l.a - l.b).IsZero()) {
        area += l.a.CrossProd(l.b)*.5;
        lines.insert(l);
      }
    }
    //assert(l.dir().SqNorm()>1e-13);
  }

  void find(const ClipLine &l) {
    it = lines.lower_bound(l);
    if (it == lines.end()) { it = lines.begin(); }
  }

  void recalculate() {
    area = 0; for (const ClipLine &l : lines) area += l.a.CrossProd(l.b);
    area *= .5;
  }

  int size() { return lines.size(); }
  void next() { if(++it==lines.end()) it = lines.begin(); }
  void prev() { if(it==lines.begin()) it = lines.end(); --it; }
  void erase() {
      assert(it!=lines.end());
      area -= it->a.CrossProd(it->b)*.5;
      it = lines.erase(it);
      if(it==lines.end()) it = lines.begin();
  }
  typename set<ClipLine>::iterator it;
  set<ClipLine> lines;
  LD area;
};
// CLIP ENDS

struct Point3 {
  LD x, y, z;
  Point3() {}
  Point3(LD a, LD b, LD c) : x(a), y(b), z(c){}
  void operator=(const Point3& a) { x = a.x; y = a.y; z = a.z; }
  Point3 operator+(Point3 a) { Point3 p{x + a.x, y + a.y, z + a.z}; return p; }
  Point3 operator-(Point3 a) { Point3 p{x - a.x, y - a.y, z - a.z}; return p; }
  Point3 operator*(LD a) { Point3 p{x * a, y * a, z * a}; return p; }
  Point3 operator/(LD a) { assert(a > EPS); Point3 p{x / a, y / a, z / a}; return p; }
  LD& operator[](int a) {
    if (a == 0) { return x; }
    if (a == 1) { return y; }
    if (a == 2) { return z; }
    assert(false);
  }
  bool IsZero() {
    return abs(x) < EPS && abs(y) < EPS && abs(z) < EPS;
  }
  bool operator==(Point3 a) {
    return (*this - a).IsZero();
  }
  LD DotProd(Point3 a) {
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
    Point3 res(*this);
    res.NormalizeSelf();
    return res;
  }
  LD Dis(Point3 a) {
    return (*this - a).Norm();
  }
  pair<LD, LD> SphericalAngles() {
    return {atan2(z, Sqrt(x * x + y * y)), atan2(y, x)};
  }
  LD Area(Point3 p) {
    return Norm() * p.Norm() * sin(Angle(p)) / 2;
  }
//  LD Angle(Point3 p) {
//    LD a = Norm();
//    LD b = p.Norm();
//    LD c = Dis(p);
//    return Acos((a * a + b * b - c * c) / (2 * a * b));
//  }
  /// not tested
  LD Angle(Point3 b) {
    Point3 a(*this);
    return Acos(min(abs(a.DotProd(b))/a.Norm()/b.Norm(), 1.0l));
  }
  LD Angle(Point3 p, Point3 q) {
    return p.Angle(q);
  }
  Point3 CrossProd(Point3 p) {
    Point3 q(*this);
    return {q[1] * p[2] - q[2] * p[1], q[2] * p[0] - q[0] * p[2], q[0] * p[1] - q[1] * p[0]};
  }
  bool LexCmp(Point3& a, const Point3& b) {
    if (abs(a.x - b.x) > EPS) { return a.x < b.x; }
    if (abs(a.y - b.y) > EPS) { return a.y < b.y; }
    return a.z < b.z;
  }
};

struct Line3 {
  Point3 p[2];
  Line3() {}
  Line3(Point3 a, Point3 b) {
    p[0] = a, p[1] = b;
  }
  Point3& operator[](int a) { return p[a]; }
};

struct Plane {
  Point3 p[3];
  Point3& operator[](int a) { return p[a]; }
  Plane(Point3 p0, Point3 p1, Point3 p2) {
    p[0] = p0; p[1] = p1; p[2] = p2;
  }
  Plane(Point3 normal, LD D) {
    /// to do, update p[0], p[1], p[2]
  }
  Point3 GetNormal() {
    Point3 cross = (p[1] - p[0]).CrossProd(p[2] - p[0]);
    return cross.Normalize();
  }
  void GetPlaneEq(LD& A, LD& B, LD& C, LD& D) {
    Point3 normal = GetNormal();
    A = normal[0];
    B = normal[1];
    C = normal[2];

    D = normal.DotProd(p[0]);
    assert(abs(D - normal.DotProd(p[1])) < EPS);
    assert(abs(D - normal.DotProd(p[2])) < EPS);
  }
  vector<Point3> GetOrtonormalBase() {
    Point3 normal = GetNormal();
    Point3 cand = {-normal.y, normal.x, 0};
    if (abs(cand.x) < EPS && abs(cand.y) < EPS) {
      cand = {0, -normal.z, normal.y};
    }
    cand.NormalizeSelf();
    Point3 third = Plane{Point3{0, 0, 0}, normal, cand}.GetNormal();
    assert(abs(normal.DotProd(cand)) < EPS && abs(normal.DotProd(third)) < EPS && abs(cand.DotProd(third)) < EPS);
    return {normal, cand, third};
  }
};

struct Circle3 {
  Plane pl;
  Point3 cent;
  LD r;
};

struct Sphere {
  Point3 cent;
  LD r;
};

namespace Utils3 {
  //angle PQR
  LD Angle(Point3 P, Point3 Q, Point3 R) {
    return (P - Q).Angle(R - Q);
  }
  LD Area(Point3 p, Point3 q, Point3 r) { // ok
    q = q-p;
    r = r-p;
    return q.Area(r);
  }
  /// not tested
  LD DistPtLine(Point3 p, Line3 l){
    return ((l[1]-l[0]).CrossProd((p-l[0]))).Norm()/(l[1]-l[0]).Norm();
  }
  Point3 ProjPtToLine3(Point3 p, Line3 l) { // ok
    Point3 diff = l[1] - l[0];
    diff.NormalizeSelf();
    return l[0] + diff * (p - l[0]).DotProd(diff);
  }
  /// proj pt c onto line seg through a and b
  /// not tested
  Point3 ProjPtSeg3(Point3 p, Line3 l) {
    LD r = (l[1]-l[0]).DotProd(l[1]-l[0]);
    if(abs(r) < EPS) return l[0];
    r = (p-l[0]).DotProd(l[1]-l[0])/r;
    if(r < 0) return l[0];
    if (r > 1) return l[1];
    return l[0] + (l[1]-l[0]) * r;
  }
  ///compute distance from c to segment between a and b
  LD DistPtSeg3(Point3 p, Line3 l) {
    Point3 q = ProjPtSeg3(p, l);
    return p.Dis(q);
  }
  LD DisPtLine3(Point3 p, Line3 l) { // ok
    LD dis2 = p.Dis(ProjPtToLine3(p, l));
    return dis2;
  }
  bool PtBelongToLine3(Point3 p, Line3 l) {
    return DisPtLine3(p, l) < EPS;
  }
  bool Lines3Equal(Line3 p, Line3 l) {
    return PtBelongToLine3(p[0], l) && PtBelongToLine3(p[1], l);
  }
  /// not tested
  bool OrientPointPlane(Point3 t, Plane p){
    LD dot = p.GetNormal().DotProd(t - p[0]);
    return dcmp(dot);
  }
  Point3 ProjPtToPlane(Point3 p, Plane pl) {
    Point3 normal = pl.GetNormal();
    return p - normal * normal.DotProd(p - pl[0]);
  }
  LD DisPtPlane(Point3 p, Plane pl) {
    Point3 normal = pl.GetNormal();
    return abs(normal.DotProd(p - pl[0]));
  }
  bool PtBelongToPlane(Point3 p, Plane pl) {
    return DisPtPlane(p, pl) < EPS;
  }
  bool Line3BelongToPlane(Line3 l, Plane pl) {
    return PtBelongToPlane(l[0], pl) && PtBelongToPlane(l[1], pl);
  }
  ///shift plane up(dist>0)/down(dist<0) to distance dist
  /// not tested
  Plane ShiftUpDown(Plane p, LD dist) {
    Point3 n = p.GetNormal();
    LD d = p.GetNormal().DotProd(p[0]);
    return Plane(n, d + dist * n.Norm());
  }
  Plane ParallelPlane(Plane pl, Point3 A) { // plane parallel to pl going through A
    Point3 diff = A - ProjPtToPlane(A, pl);
    return Plane{pl[0] + diff, pl[1] + diff, pl[2] + diff};
  }
  ///undefined if line and plane is parallel ie( p.b*l.d = 0 )
  /// not tested
  Point3 InterLinePlane(Line3 l, Plane p) {
    Point3 normal = p.GetNormal();
    LD D = normal.DotProd(p[0]);
    LD k = (D - (normal.DotProd(l[0])))/(normal.DotProd(l[1]-l[0]));
    return l[0] + (l[1]-l[0])*k;
  }
  /// not tested, assumes planes are not parallel
  Line3 InterPlanePlane(Plane p1, Plane p2) {
    Point3 n1 = p1.GetNormal(), n2 = p2.GetNormal();
    LD d1 = n1.DotProd(p1[0]), d2 = n2.DotProd(p2[0]);
    Point3 dir = n1.CrossProd(n2);
    assert(!dir.IsZero()); /// parallel plane
    Point3 u = (n2 * d1 - n1 * d2).CrossProd(dir)/dir.DotProd(dir);
    return Line3(u, u + dir);
  }
  Point PlanePtTo2D(Plane pl, Point3 p) { // ok
    assert(PtBelongToPlane(p, pl));
    vector<Point3> base = pl.GetOrtonormalBase();
    Point3 control{0, 0, 0};
    for (int tr = 0; tr < 3; tr++)  {
      control = control + base[tr] * p.DotProd(base[tr]);
    }
    assert(PtBelongToPlane(pl[0] + base[1], pl));
    assert(PtBelongToPlane(pl[0] + base[2], pl));
    assert((p - control).IsZero());
    return {p.DotProd(base[1]), p.DotProd(base[2])};
  }
  Line PlaneLineTo2D(Plane pl, Line3 l) {
    return {PlanePtTo2D(pl, l[0]), PlanePtTo2D(pl, l[1])};
  }
  Point3 PlanePtTo3D(Plane pl, Point p) { // ok
    vector<Point3> base = pl.GetOrtonormalBase();
    return base[0] * base[0].DotProd(pl[0]) + base[1] * p.x + base[2] * p.y;
  }
  Line3 PlaneLineTo3D(Plane pl, Line l) {
    return Line3{PlanePtTo3D(pl, l[0]), PlanePtTo3D(pl, l[1])};
  }
  Line3 ProjLineToPlane(Line3 l, Plane pl) { // ok
    return Line3{ProjPtToPlane(l[0], pl), ProjPtToPlane(l[1], pl)};
  }
  /// not tested
  Point3 ClosestPtOnL1FromL2(Line3 l1, Line3 l2){
    Point3 n = (l1[1]-l1[0]).CrossProd(l2[1]-l2[0]), n3 = (l2[1]-l2[0]).CrossProd(n);
    ///p is the plane including line l2 and n
    Plane p = Plane(n3, n3.DotProd(l2[0]));
    return InterLinePlane(l1, p);
  }
  vector<Point3> InterLineLine(Line3 k, Line3 l) {
    if (Lines3Equal(k, l)) { return {k[0], k[1]}; }
    if (PtBelongToLine3(l[0], k)) { return {l[0]}; }
    Plane pl{l[0], k[0], k[1]};
    if (!PtBelongToPlane(l[1], pl)) { return {}; }
    Line k2 = PlaneLineTo2D(pl, k);
    Line l2 = PlaneLineTo2D(pl, l);
    vector<Point> inter = Utils::InterLineLine(k2, l2);
    vector<Point3> res;
    for (auto P : inter) { res.pb(PlanePtTo3D(pl, P)); }
    return res;
  }
  /// not tested
  LD DisLineLine (Line3 l1, Line3 l2){
    Point3 dir = (l1[1]-l1[0]).CrossProd(l2[1]-l2[0]);
    if(dcmp(dir.Norm()) == 0) return DistPtLine(l2[0], l1);
    return abs((l2[0]-l1[0]).DotProd(dir))/dir.Norm();
  }
//  LD DisLineLine(Line3 l, Line3 k) { // ok
//    Plane together {l[0], l[1], l[0] + k[1] - k[0]}; // parallel FIXME
//    Line3 proj = ProjLineToPlane(k, together);
//    Point3 inter = (Utils3::InterLineLine(l, proj))[0];
//    Point3 on_k_inter = k[0] + inter - proj[0];
//    return inter.Dis(on_k_inter);
//  }
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

  Point3 PtFromSphericalAng(LD alpha, LD beta) { // ok
    return {cos(alpha) * cos(beta), cos(alpha) * sin(beta), sin(alpha)};
  }

  // image of B in rotation wrt line passing through origin s.t. A1->A2
  // implemented in more general case with similarity instead of rotation
  Point3 RotateAccordingly(Point3 A1, Point3 A2, Point3 B1) { // ok
    Plane pl{A1, A2, {0, 0, 0}};
    Point A12 = PlanePtTo2D(pl, A1);
    Point A22 = PlanePtTo2D(pl, A2);
    complex<LD> rat = complex<LD>(A22.x, A22.y) / complex<LD>(A12.x, A12.y);
    Plane plb = ParallelPlane(pl, B1);
    Point B2 = PlanePtTo2D(plb, B1);
    complex<LD> Brot = rat * complex<LD>(B2.x, B2.y);
    return PlanePtTo3D(plb, {Brot.real(), Brot.imag()});
  }
  /// not tested
  vector<Point3> InterLineSphere(Line3 l, Sphere s){
    vector<Point3> ints;
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
  vector<Circle3> InterPlaneSphere(Plane pl, Sphere s) { // ok
    Point3 proj = ProjPtToPlane(s.cent, pl);
    LD dis = s.cent.Dis(proj);
    if (dis > s.r + EPS) {
      //return {{{}, {}, {}}, {}, -1};
      return {};
    }
    if (dis > s.r - EPS) {
      //return {{{}, {}, {}}, proj, 0};
      return {{pl, proj, 0}}; // is it best choice?
    }
    return {{pl, proj, Sqrt(s.r * s.r - dis * dis)}};
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


/// not tested
bool InsideATriangle(Point3 a, Point3 b, Point3 c, Point3 p) {
  Plane abc = Plane(a, b, c);
  if(!Utils3::PtBelongToPlane(p, abc)) return false;
  Point3 n = abc.GetNormal();
  vector<int> sign(3);
  for(int i = 0; i < 3; i++) {
    LD t = n.DotProd((abc[(i+1)%3] - abc[i]).CrossProd(p - abc[i]));
    sign[i] = dcmp(t);
  }
  if(sign[0] >= 0 && sign[1] >= 0 && sign[2] >= 0) return 1;
  if(sign[0] <= 0 && sign[1] <= 0 && sign[2] <= 0) return 1;
  return 0;
}
LD PtDistOn3dTriangle(Point3 a, Point3 b, Point3 c, Point3 p){
  Plane abc = Plane(a,b,c);
  Point3 p_ = Utils3::ProjPtToPlane(p, abc);
  LD ret = 1e19;
  if(InsideATriangle(a,b,c,p_))
    ret = min(ret, p.Dis(p_));
  ret = min(ret, Utils3::DistPtSeg3(p, Line3(a,b)));
  ret = min(ret, Utils3::DistPtSeg3(p, Line3(b,c)));
  ret = min(ret, Utils3::DistPtSeg3(p, Line3(a,c)));
  return ret;
}


struct Face{
  Point3 a, b, c;
  Face(){}
  Face(Point3 a, Point3 b, Point3 c) : a(a), b(b), c(c) {}
  Face(const Face &f) : a(f.a), b(f.b), c(f.c) {}
};
/// not tested
LD ployhedronVolume(vector<Face> &vec) {
  if(vec.size() == 0) return 0;
  Point3 reff = vec[0].a;
  LD vol = 0;
  for(int i = 1; i < vec.size(); i++) {
    Point3 ar = (vec[i].b-vec[i].a).CrossProd(vec[i].c - vec[i].a);
    vol += abs(ar.DotProd(reff-vec[i].a));
  }
  return vol/6.0;
}
/// not tested, O(n^4) 3d convex hull
vector<Face> Convex3dHull(vector<Point3> &V) {
  vector <Face> Faces;
  for(int i = 0; i < V.size(); i++) {
    for(int j = i+1; j < V.size(); j++) {
      for (int k = j+1; k < V.size(); k++) {
        if (((V[j]-V[i]).CrossProd(V[k]-V[i])).Norm() < EPS)
          continue;
        bool up = 0, down = 0;
        Plane P(V[i], V[j], V[k]);
        Point3 normal = P.GetNormal();
        for (int l = 0; l < V.size(); l++) {
          if (l == i or l == j or l == k)
            continue;
          if(InsideATriangle(V[i], V[j], V[k], V[l])) {
            up = down = 1;
            break;
          }
          else if(normal.DotProd(V[l]-V[i]) < 0)
            down = 1;
          else
            up = 1;
        }
        if (up == 0 or down == 0) {
          Face temp;
          temp.a = V[i], temp.b = V[j] , temp.c = V[k] ;
          Faces.push_back(temp) ;
        }
      }
    }
  }
  return Faces;
}

struct PointS {
  LD lat, lon;
  PointS(LD latt, LD lonn) { lat = latt; lon = lonn; }
  Point3 toEucl() {
    return Point3{cos(lat) * cos(lon), cos(lat) * sin(lon), sin(lat)};
  }
  PointS(Point3 p) {
    p.NormalizeSelf();
    lat = asin(p.z);
    lon = Acos(p.y / cos(lat));
  }
};

LD DistS(Point3 a, Point3 b) {
	return atan2l(b.CrossProd(a).Norm(), a.DotProd(b));
}

struct CircleS {
	Point3 o; // center of circle on sphere
	LD r; // arc len
	LD area() const { return 2 * PI * (1 - cos(r)); }
};

CircleS From3(Point3 a, Point3 b, Point3 c) { // any three different points
	int tmp = 1;
	if ((a - b).Norm() > (c - b).Norm()) { swap(a, c); tmp = -tmp; }
	if ((b - c).Norm() > (a - c).Norm()) { swap(a, b); tmp = -tmp; }
	Point3 v = (c - b).CrossProd(b - a); v = v * (tmp / v.Norm());
	return CircleS{v, DistS(a,v)};
}

CircleS From2(Point3 a, Point3 b) { // neither the same nor the opposite
	Point3 mid = (a + b) / 2;
	mid = mid / mid.Norm();
	return From3(a, mid, b);
}

LD Angle(Point3 A, Point3 B, Point3 C) { //angle at A, no two points opposite
	LD a = B.DotProd(C);
	LD b = C.DotProd(A);
	LD c = A.DotProd(A);
	return Acos((b - a * c) / Sqrt((1 - Sq(a)) * (1 - Sq(c))));
}

LD TriangleArea(Point3 A, Point3 B, Point3 C) { // no two poins opposite
	LD a = Angle(C, A, B);
	LD b = Angle(A, B, C);
	LD c = Angle(B, C, A);
	return a + b + c - PI;
}

vector<Point3> IntersectionS(CircleS c1, CircleS c2) { // what about c1==c2 case?
	Point3 n = c2.o.CrossProd(c1.o), w = c2.o * cos(c1.r) - c1.o * cos(c2.r);
	LD d = n.SqNorm();
  if (d < EPS) {
    cerr<<"parallel circles?\n";
    return {};
  }
  LD a = w.SqNorm() / d;
	vector<Point3> res;
	if (a >= 1 + EPS) { return res; }
	Point3 u = n.CrossProd(w) / d;
	if (a > 1 - EPS) {
    res.pb(u);
	  return res;
	}
	LD h = Sqrt((1 - a) / d);
	res.pb(u + n * h);
	res.pb(u - n * h);
	return res;
}


int main() {

}
