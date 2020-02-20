int dcmp(int x) {
  if(x < 0) return -1;
  return x > 0;
}
struct Point {
  int x, y;
  Point() {}
  Point(int a, int b) : x(a), y(b) {}
  Point(const Point& a) : x(a.x), y(a.y) {}
  void operator=(const Point& a){x=a.x;y=a.y;}
  Point operator+(const Point& a) const {
    Point p(x + a.x, y + a.y); return p;
  }
  Point operator-(const Point& a) const {
    Point p(x - a.x, y - a.y); return p;
  }
  Point operator*(int a)const {
    return Point(x*a,y*a);
  }
  Point operator/(int a)const{
    return Point(x/a, y/a);
  }
  int cross(const Point& a)const {
    return x * a.y - y * a.x;
  }
  int cross(Point a, Point b) const {
    a = a - *this;b = b - *this;return a.cross(b);
  }
  int DotProd(const Point& a) const {
    return x * a.x + y * a.y;
  }
  Point Rotate90() { return Point(-y, x); }
  bool operator < (const Point &p) const{
    return make_pair(x, y) < make_pair(p.x, p.y);
  }
  bool operator > (const Point &p) const {
    return make_pair(x, y) > make_pair(p.x, p.y);
  }
  int SqNorm() { return x * x + y * y; }
};
bool OnSegment(Point p, Point a, Point b) {
  return (a-p).cross(b-p)==0&&(a-p).DotProd(b-p)<0;
}
int isPointInPolygon(Point p,vector<Point> &poly){
  int wn = 0, n = poly.size();
  for(int i = 0; i < n; i++) {
    if(OnSegment(p,poly[i],poly[(i+1)%n]))
      return -1;//on edge
    int k=(poly[(i+1)%n]-poly[i]).cross(p-poly[i]);
    int d1 = poly[i].y-p.y;
    int d2 = poly[(i+1)%n].y-p.y;
    if (k > 0 && d1 <= 0 && d2 > 0) wn++;
    if (k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  if (wn != 0) return 1; //inside
  return 0; //outside
}
// returns 1 if p is on or inside triangle(a,b,c)
bool PointInTriangle
            (Point a,Point b,Point c,Point p) {
  int d1 = dcmp((b-a).cross(p-b));
  int d2 = dcmp((c-b).cross(p-c));
  int d3 = dcmp((a-c).cross(p-a));
  return !(((d1 < 0) || (d2 < 0) || (d3 < 0)) &&
        ((d1 > 0) || (d2 > 0) || (d3 > 0)));
}
struct ConvexHull {
  vector<Point> hull, lr, ur; int n;
  /// builds convex hull of a set of points
  bool ccw(Point p, Point q, Point r) {
      return p.cross(q, r) > 0;
  }
  int cross(Point p, Point q, Point r) {
    return (q-p).cross(r-q);
  }
  Point LineLineIntersection
        (Point p1, Point p2, Point q1, Point q2) {
    int a1 = cross(q1,q2,p1),a2 = -cross(q1,q2,p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
  }
  void init(vector<Point> &poly) {
    hull.clear(), lr.clear(), ur.clear();
    sort(poly.begin(),poly.end());
    for(int i = 0; i < poly.size(); i++) {
      while(lr.size() >= 2 &&
        !ccw(lr[lr.size()-2],lr.back(),poly[i]))
          lr.pop_back();
      lr.push_back(poly[i]);
    }
    for(int i = (int)poly.size()-1; i >= 0; i--){
      while(ur.size() >= 2 &&
        !ccw(ur[ur.size()-2],ur.back(),poly[i]))
          ur.pop_back();
      ur.push_back(poly[i]);
    }
    hull = lr;
    for(int i = 1; i+1 < ur.size(); i++)
      hull.push_back(ur[i]);
    n = hull.size();
  }
  int sign(int x) {
    if (x < 0) return -1; return x > 0;
  }
  int crossOp(Point p, Point q, Point r) {
    int c = (q-p).cross(r-q);if (c < 0) return -1;
    return (c > 0);
  }
  //tests if p is inside or on the convex poly
  //if Pt p is on side a,b is the idx of two ends
  bool contain(Point p,int&a,int&b){
    if(p.x < lr[0].x || p.x>lr.back().x) return 0;
    int id = lower_bound(lr.begin(),
          lr.end(),Point(p.x,-INF)) - lr.begin();
    if(lr[id].x == p.x){
      if(lr[id].y > p.y) return 0;
    } else {
      if(crossOp(lr[id-1],lr[id],p) < 0) return 0;
      if(crossOp(lr[id-1],lr[id],p) == 0){
        a = id - 1; b = id;
        return 1;
      }
    }
    id = lower_bound(ur.begin(),ur.end(),Point
          (p.x,INF),greater<Point>()) - ur.begin();
    if(ur[id].x == p.x){
      if(ur[id].y < p.y) return 0;
    } else {
      if(crossOp(ur[id-1],ur[id],p) < 0) return 0;
      if(crossOp(ur[id-1],ur[id],p) == 0) {
        a = id - 1 + lr.size() - 1;
        b = id  + lr.size() - 1;
        return 1;
      }
    }
    return 1;
  }
  int find(vector<Point> &vec, Point dir) {
    int l = 0, r = vec.size();
    while(l+5<r){
      int L = (l*2+r)/3, R = (l+r*2)/3;
      if(vec[L].DotProd(dir)>vec[R].DotProd(dir))
        r=R;
      else
        l=L;
    }
    int ret = l;
    for(int k = l+1; k < r; k++)
      if(vec[k].DotProd(dir)>vec[ret].DotProd(dir))
        ret = k;
    return ret;
  }
  ///rays frm inf in dir, returns the furthest Pt
  int findFarest(Point dir){
    if(sign(dir.y) > 0 || sign(dir.y) == 0 &&
                                sign(dir.x) > 0){
      return ((int)lr.size()-1 + find(ur,dir))%n;
    } else {
      return find(lr,dir);
    }
  }
  Point get(int l, int r, Point p1, Point p2){
    int sl = crossOp(p1,p2,hull[l%n]);
    while(l+1<r){
      int m = (l+r)>>1;
      if(crossOp(p1,p2,hull[m%n]) == sl) l = m;
      else r = m;
    }
    return LineLineIntersection
                  (p1,p2,hull[l%n],hull[(l+1)%n]);
  }
//Ints between line and convex polygon. O(log(n))
//touching the hull does not count as intersection
  vector<Point>Line_Hull_Intersection
                            (Point p1, Point p2){
    int X = findFarest((p2-p1).Rotate90());
    int Y = findFarest((p1-p2).Rotate90());
    if(X > Y) swap(X,Y);
    if(crossOp(p1,p2,hull[X])*
                      crossOp(p1,p2,hull[Y]) < 0){
      return {get(X,Y,p1,p2),get(Y,X+n,p1,p2)};
    } else {
      return {};
    }
  }
  void update_tangent(Point p,int id,int&a,int&b){
    if(crossOp(p,hull[a],hull[id]) > 0) a = id;
    if(crossOp(p,hull[b],hull[id]) < 0) b = id;
  }
  void binary_search(int l,int r,Point p,
                                    int&a,int&b){
    if(l==r) return;
    update_tangent(p,l%n,a,b);
    int sl = crossOp(p,hull[l%n],hull[(l+1)%n]);
    while(l+1<r){
      int m = l+r>>1;
      if(crossOp(p,hull[m%n],hull[(m+1)%n]) == sl)
        l=m;
      else r=m;
    }
    update_tangent(p,r%n,a,b);
  }
  void get_tangent(Point p,int&a,int&b){
    if(contain(p,a,b)) return;
    a = b = 0;
    int id = lower_bound(lr.begin(), lr.end(),p)
                                    - lr.begin();
    binary_search(0,id,p,a,b);
    binary_search(id,lr.size(),p,a,b);
    id = lower_bound(ur.begin(), ur.end(),p,
                   greater<Point>()) - ur.begin();
    binary_search((int)lr.size() - 1,
                (int) lr.size() - 1 + id,p,a,b);
    binary_search((int) lr.size() - 1 + id,
          (int) lr.size() - 1 + ur.size(),p,a,b);
  }
};