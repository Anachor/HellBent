LD ccw(Point p, Point q, Point r) {
    return (q-p).cross(r-q);
}
// ax + by = c
struct Line{
  LD a, b, c;
  Point u, d;
  Line(LD a, LD b,LD c):a(a), b(b), c(c) {
    // careful that u, d is not updated here.
  }
  Line(Point u_, Point d_) {
    u = u_, d = d_;//anti-clock dir is the region
    a = d.y, b = -d.x, c = -u.y*d.x + u.x*d.y;
    // ax + by <= c
  }
  bool operator < (const Line &l)const{
    bool flag1 = mp(a, b) > mp(0.0L, 0.0L);
    bool flag2 = mp(l.a, l.b) > mp(0.0L, 0.0L);
    if(flag1 != flag2) return flag1 > flag2;
    LD t = ccw(Point(0.0L, 0.0L),
             Point(a, b), Point(l.a, l.b));
    return dcmp(t) == 0 ? c*hypot(l.a, l.b) <
                            l.c * hypot(a, b):t>0;
  }
  Point slope() { return Point(a, b);}
};
Point cross(Line a, Line b){
  LD det = a.a * b.b - b.a * a.b;
  return Point((a.c * b.b - a.b * b.c) / det,
            (a.a * b.c - a.c * b.a) / det);
}
bool bad(Line a, Line b, Line c){
  if(ccw(Point(0, 0), a.slope(), b.slope()) <= 0)
    return false;
  Point crs = cross(a, b);
  return crs.x * c.a + crs.y * c.b >= c.c;
}
// ax + by <= c;
bool hpi(vector<Line> v, vector<Point> &solution){
  sort(v.begin(), v.end());
  deque<Line> dq;
  for(auto &i : v) {
    if(!dq.empty()&&!dcmp(ccw(Point(0,0),
        dq.back().slope(), i.slope()))) continue;
    while(dq.size()>=2&&bad(dq[dq.size()-2],
                    dq.back(), i)) dq.pop_back();
    while(dq.size()>=2&&bad(i,dq[0],dq[1]))
      dq.pop_front();
    dq.pb(i);
  }
  while(dq.size()>2&&bad(dq[dq.size()-2],
                dq.back(),dq[0])) dq.pop_back();
  while(dq.size()>2&&bad(dq.back(),
                dq[0],dq[1])) dq.pop_front();
  vector<Point> tmp;
  for(int i=0; i< dq.size(); i++){
    Line cur = dq[i], nxt = dq[(i+1)%dq.size()];
    if(ccw(Point(0,0),cur.slope(),nxt.slope())
                            <= EPS) return false;
    tmp.pb(cross(cur, nxt));
  }
  solution = tmp; return true;
}
int main() {
  int n; cin >> n; vector<Point> P(n);
  for(int i=0;i<n;i++) cin >> P[i].x >> P[i].y;
  LD R = 1e9;
  vector<vector<Point>> voronoi_diagram;
  for(int i = 0; i < n; i++) {
      vector<Line> lines;
      lines.pb(Line(1,0,R)); // x <= R
      lines.pb(Line(-1,0,R));// x >= -R => -x <= R
      lines.pb(Line(0,1,R)); // y <= R
      lines.pb(Line(0,-1,R));// y >= -R => -y <= R
      for(int j = 0; j < n; j++) {
          if(P[i] == P[j]) continue;
          Point u=(P[i]+P[j])*0.5,dir = P[j]-P[i];
          Point dir_90 = dir.Rotate90();
          Point v = u + dir_90;
          LD a = dir_90.y, b = -dir_90.x;
          LD = c = -u.y*dir_90.x + u.x*dir_90.y;
          lines.pb(Line(a,b,c));
      }
      vector<Point> polygon;
      hpi(lines, polygon);
      voronoi_diagram.pb(polygon);
  }
}