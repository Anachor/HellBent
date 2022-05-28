/// Cut Polygon (not tested)
void ints(vector<Point> &V,Point a,Point b,Line l){
  Point p = l[0], q = l[1];
  LD na = (a-p).cross(q-p), nb = (b-p).cross(q-p);
  if (na*nb < 0.0)
    V.push_back(a + (b-a)*(na/(na-nb)));
}
vector<Point> cut(vector<Point> polygon,Line l,
                                        int sign){
  vector<Point> np; int sz = polygon.size();
  for(int i = 0 ; i < sz ; i++) {
    Point p = polygon[i], q = polygon[(i+1)%sz];
    if(dcmp(l.Dir().cross(p))*sign>=0) np.pb(p);
    ints(np, p, q, l);
  }
  return np;
}
///diameter of a convex polygon p (not tested)
LD rotating_calipers(vector<Point> p) {
  int q = 1, n = p.size(); LD ans = 0;
  for( int i = 0; i < n; i++) {
    while(p[i].cross(p[(i+1)%n],p[(q+1)%n]) >
        p[i].cross(p[(i+1)%n],p[q])) q = (q+1)%n;
   LD t1=(p[i]-p[q]).Norm();
   LD t2=(p[(i+1)%n]-p[q]).Norm();
   ans = max(ans, max(t1, t2));
  }
  return ans;
}
///minimum area rect for convex polygon(!tested)
LD rec_rotating_calipers(vector<Point> p) {
  int n=p.size(),l=0,r=0,q=1;
  LD ans1=1e15, ans2=1e15;
  for( int i = 0; i < n; i++) {
    while(dcmp(p[i].cross(p[(i+1)%n],p[(q+1)%n])
      -p[i].cross(p[(i+1)%n],p[q])) > 0) q=(q+1)%n;
    while(dcmp((p[(i+1)%n]-p[i]).dot
               (p[(r+1)%n]-p[r]))>0) r=(r+1)%n;
    if (!i) l = q;
    while(dcmp((p[(i+1)%n]-p[i]).dot
               (p[(l+1)%n]-p[l]))<0) l=(l+1)%n;
    LD d = (p[(i+1)%n]-p[i]).Norm();
    LD h = p[i].cross(p[(i+1)%n],p[q])/d;
    LD w =(((p[(i+1)%n]-p[i]).dot(p[r]-p[i]))
           -((p[(i+1)%n]-p[i]).dot(p[l]-p[i])))/d;
    ans1 = min(ans1,2*(h+w)),ans2 = min(ans2,h*w);
  }
  return ans2;
}
struct Polygon {
  vector<Point> pts;
  Polygon(vector<Point> pts_) : pts(pts_) {}
  Polygon() : Polygon(vector<Point>()) {}
  void Add(Point p) { pts.push_back(p);}
  // positive for counterclockwise
  LD Area() {
    LD area = 0;
    for(int i = 0; i < SZ(pts); i++)
      area += pts[i].cross(pts[(i + 1) % SZ(pts)]);
    area /= 2; return area;
  }
  void OrientCounterclockwise() {
    if (Area()<0) reverse(pts.begin(), pts.end());
  }
  int next(int a) {
    if (a + 1 < SZ(pts)) return a + 1;
    return 0;
  }
  pair<int, int> FurthestPair() {
    MakeConvexHull(); OrientCounterclockwise();
    int furth = 1;
    pair<int, int> best_pair = make_pair(0, 0);
    LD best_dis = 0;
    for (int i = 0; i < SZ(pts); i++) {
      Point side = pts[next(i)] - pts[i];
      while(side.cross(pts[furth] - pts[i])
          < side.cross(pts[next(furth)]-pts[i])){
        furth = next(furth);
      }
      vector<int> vec{i, next(i)};
      for (auto ind : vec) {
        if (pts[ind].Dist(pts[furth]) > best_dis){
          best_pair = make_pair(ind, furth);
          best_dis = pts[ind].Dist(pts[furth]);
        }
      }
    }
    return best_pair;
  }
  void MakeConvexHull() {
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
        while(SZ(H)>=2&&dir*(pts[i]-H[SZ(H)-2]).
              cross(H.back()-H[SZ(H)-2]) > -EPS){
          H.pop_back();
        }
        H.push_back(pts[i]);
      }
    }
    pts.clear();
    for(auto p:one_way_hull[1])pts.push_back(p);
    for(int i = SZ(one_way_hull[0])-2; i >= 1; i--)
      pts.push_back(one_way_hull[0][i]);
  }
  // without sides
  vector<vector<bool>> InsideDiagonalsMatrix() {
    int n = pts.size();
    vector<vector<bool>> res(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        Line diag(pts[i], pts[j]);
        if(i==j || abs(i-j)==1 || abs(i-j)==n-1)
          continue;
        res[i][j] = 1;
        for (int k = 0; k < n; k++) {
          int kk = next(k);
          Line side(pts[k], pts[kk]);
          if(k==i || k==j || kk==i || kk==j)
            continue;
          vector<Point>inter =
                  Utils::InterSegs(diag,side);
          if (SZ(inter)) res[i][j] = 0;
        }
        int act = next(i), passed_j = 0;
        LD areas[2] = {0, 0};
        while (act != i) {
          passed_j |= (act == j);
          LD t =
            pts[i].cross(pts[act],pts[next(act)]);
          areas[passed_j] += t; act = next(act);
        }
        if (areas[0] * areas[1] < EPS)
          res[i][j] = 0;
      }
    }
    return res;
  }
};
// CLIP START
bool InUpper(Point a) {
  if (abs(a.y) > EPS) return a.y > 0;
  return a.x > 0;
}
bool angle_cmp(const Point a, const Point b) {
  bool u = InUpper(a), v = InUpper(b);
  return u!=v ? u : a.cross(b)>0;
}
LD cross(Point a, Point b, Point c, Point d) {
  return (d-c).cross(a-c) / (d - c).cross(a - b);
}
struct ClipLine { // valid side is on left
  ClipLine(Point A, Point B) {
    al = A, bl = B, a = A, b = B;
  }
  Point al,bl; // original line points
  mutable Point a,b; // actual intersection points
  Point dir() const { return bl - al; }
  bool operator<(const ClipLine& l) const {
    return angle_cmp(dir(),l.dir());
  }
  Point cross(const ClipLine& l) {
    return al+(bl-al)*::cross(al,bl,l.al,l.bl);
  }
  bool left(Point p){return(bl-al).cross(p-al)>0;}
};
struct Clip {
  Clip(LD r) : area(4*r*r) {
    Point a{-r,-r}, b{r,-r}, c{r,r}, d{-r,r};
    lines = {ClipLine(a,b), ClipLine(b,c),
                    ClipLine(c,d), ClipLine(d,a)};
  }
  void insert(Line l){insert(ClipLine(l[0],l[1]));}
  void insert(ClipLine l) {
    assert(abs(l.dir().SqNorm()) > EPS); find(l);
    while(size()&&!l.left(it->a)&&!l.left(it->b))
      erase();
    if(size())
      while(prev(),size() && !l.left(it->a) &&
            !l.left(it->b)) erase();
    if(size()&&(!l.left(it->a) || !l.left(it->b))){
      l.a = l.cross(*it);
      area -= l.a.cross(it->b)*.5;
      it->b = l.a; next();
      l.b = l.cross(*it);
      if ((l.a-l.b).SqNorm() < EPS) l.b = l.a;
      area -= it->a.cross(l.b) * .5;
      it->a = l.b;
      if (!(l.a - l.b).IsZero()) {
        area += l.a.cross(l.b)*.5;
        lines.insert(l);
      }
    }
  }
  void find(const ClipLine &l) {
    it = lines.lower_bound(l);
    if(it == lines.end()) { it = lines.begin(); }
  }
  void recalculate() {
    area = 0;
    for(const ClipLine &l : lines)
      area+=l.a.cross(l.b);
    area *= .5;
  }
  int size() { return lines.size(); }
  void next(){if(++it==lines.end())
    it = lines.begin();}
  void prev(){
    if(it==lines.begin()) it=lines.end();--it;
  }
  void erase() {
      assert(it!=lines.end());
      area -= it->a.cross(it->b)*.5;
      it = lines.erase(it);
      if(it==lines.end()) it = lines.begin();
  }
  typename set<ClipLine>::iterator it;
  set<ClipLine> lines;
  LD area;
};