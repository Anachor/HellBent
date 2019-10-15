struct PT {
  ld x,y;
  PT() {}
  PT(ld x,ld y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y) {}
};
PT operator +(PT a,PT b) {
  return PT(a.x+b.x,a.y+b.y);
}
PT operator -(PT a,PT b) {
  return PT(a.x-b.x,a.y-b.y);
}
PT operator *(PT a,ld b) {
  return PT(a.x*b,a.y*b);
}
PT operator /(PT a,ld b){
  return PT(a.x/b,a.y/b);
}
ld operator *(PT a,PT b){ //dot
    return a.x*b.x+a.y*b.y;
}
ld operator ^(PT a,PT b){  //cross
    return a.x*b.y-a.y*b.x;
}

struct Line {
  PT p, v;ld ang;Line() {}
  ld a,b,c; // ax+by+c=0
  Line(PT p,PT v):p(p),v(v){
    ang=atan2(v.y,v.x);
    PT q = p+v;
    if( dcmp(q.x-p.x) == 0 ) {
      a = 1; b = 0; c = -p.x;
    }
    else{
      ld m = (q.y-p.y)/(q.x-p.x);
      a = m; b = -1, c = p.y - m*p.x;
    }
  }
  Line(ld a_,ld b_,ld c_){
    a = a_,b = b_,c = c_;
    v = Point(-b,a) ;
    if (dcmp(a) == 0) p = PT(0,-c/b);
    else p = PT(-c/a,0);
  }
  double val(PT q) { return a*q.x + b*q.y + c} ;
  bool operator < (const Line & L) const {return ang<L.ang;}
  PT point(ld t) { return p+v*t;}
};
int dcmp(ld x) {
    if (fabs(x)<eps) return 0; return x<0 ? -1 : 1;
}

/// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
  return fabs((b-a)^(c-d)) < eps;
}
bool LinesCollinear(PT a, PT b, PT c, PT d) {
  return LinesParallel(a, b, c, d) &&
  fabs((a-b)^(a-c)) < eps && fabs((c-d)^(c-a)) < eps;
}
/// intersection of line ab and cd
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a;d=c-d;c=c-a;
  assert((b*b) > EPS && (d*d) > EPS);
  return a + b*(c^d)/(b^d);
}
/// projection of point p on line AB
PT GetLineProjection(PT p,PT A,PT B) {
  PT v=B-A;
  return A+v*(v*(p-A))/(v*v);
}
///distance from point p to line AB
ld DistanceToLine(PT p,PT A,PT B) {
  PT v1 = B-A, v2 = p-A;
  return fabs(v1^v2)/len(v1);
}
///checks whether segment AB and segment CD intersects
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
  if (LinesCollinear(a, b, c, d)) {
    if (dist2(a, c) < eps || dist2(a, d) < eps ||
        dist2(b, c) < eps || dist2(b, d) < eps) return true;
    if ((c-a)*(c-b) > 0 && (d-a)*(d-b) > 0 && (c-b)*(d-b) > 0)
      return false;
    return true;
  }
  if (((d-a)^(b-a))*((c-a)^(b-a)) > 0) return false;
  if (((a-c)^(d-c))*((b-c)^(d-c)) > 0) return false;
  return true;
}
/// project point c onto line segment AB
PT ProjectPointSegment(PT a, PT b, PT c) {

  ld r = (b-a)*(b-a);
  if (fabs(r) < EPS) return a;
  r = (c-a)*(b-a)/r;
  if (r < 0) return a;
  if (r > 1) return b;
  return a + (b-a)*r;
}
///determine if p is on segment ab
//bool OnSegment(PT p,PT a,PT b) {
//  return dcmp((a-p)^(b-p)) == 0 && dcmp((a-p)*(b-p)) < 0;
//}
///distance from point p to segment AB
ld DistanceToSegment(PT p,PT A,PT B) {
  if (A==B) return len(p-A);
  PT v1 = B-A, v2 = p-A, v3 = p - B;
  if (dcmp(v1*v2)<0) return len(v2);
  else if (dcmp(v1*v3)>0 ) return len(v3);
  else return fabs(v1^v2) / len(v1);
}
double segment_segment_distance(PT a, PT b, PT p, PT q) {
    double d1 = dist(a, ProjectPointSegment(p, q, a)), d2 = dist(b, ProjectPointSegment(p, q, b)), d3 = dist(p, ProjectPointSegment(a, b, p)), d4 = dist(q, ProjectPointSegment(a ,b, q));
    return min(min(d1,d2),min(d3,d4));
}

/// Circle structure
struct CR {
  PT c; ld r,x,y;
  CR(PT c,ld r):c(c),r(r),x(c.x),y(c.y) {}
  PT point(ld rad) {
    return PT(c.x+cos(rad)*r,c.y+sin(rad)*r);
  }
};
int getLineCircleIntersection(Line L, CR cir, vector<PT> &sol) {
  if ( dcmp(DistanceToLine(cir.c,L.p,L.p+L.v)-cir.r)==0) {
    PT A=GetLineProjection(cir.c,L.p,L.p+L.v);
    sol.push_back(A);
    return 1;
  }
  ld a = L.v.x, b = L.p.x - cir.c.x, c = L.v.y, d= L.p.y - cir.c.y;
  ld e = a*a+c*c, f = 2*(a*b + c*d), g = b*b+d*d-cir.r*cir.r;
  ld delta = f*f - 4*e*g,t1,t2;
  if (dcmp(delta)<0) return 0;
  else if (dcmp(delta)==0) {
    t1 = t2 = -f / (2*e);
    sol.push_back(L.point(t1));
    return 1;
  }
  t1 = (-f - sqrt(delta)) / (2*e);
  sol.push_back(L.point(t1));
  t2 = (-f + sqrt(delta)) / (2*e);
  sol.push_back(L.point(t2));
  return 2;
}
ld angle(PT v) {
  return atan2(v.y,v.x);
}
int getCircleCircleIntersection(CR C1,CR C2, vector<PT>& sol) {
  ld d = len(C1.c-C2.c);
  if (dcmp(d)==0){
    if (dcmp(C1.r - C2.r)==0) return -1; //same circle
    return 0; //concentric circle
  }
  if (dcmp(C1.r+C2.r-d)<0) return 0; //no intersection, outside
  if (dcmp(fabs(C1.r-C2.r)-d)>0) return 0; //no intersection, inside
  ld a = angle(C2.c-C1.c);
  ld da = acos((C1.r*C1.r+d*d - C2.r*C2.r)/ (2*C1.r*d));
  PT p1 = C1.point(a-da), p2 = C1.point(a+da);
  sol.push_back(p1);if (p1==p2) return 1;
  sol.push_back(p2);
  return 2;
}
//tangent from p to circle c,returns dir vec from p to c
int getTangents(PT p,CR c, vector<PT> &sol){
  PT u= c.c-p;
  ld dist = len(u);
  if (dist<c.r) return 0;
  else if (dcmp(dist-c.r)==0){
    sol.push_back(RotateCCW(u,PI/2));
    return 1;
  }
  else{
    ld ang = asin(c.r / dist);
    sol.push_back(RotateCCW(u,-ang));
    sol.push_back(RotateCCW(u,ang));
    return 2;
  }
}
//tangent from p to circle c
//returns points on circle that touches the tangent
int getTangentsPoint(PT p,CR c, vector<PT> &point){
  PT u= c.c-p;ld dist = len(u);
  if (dist<c.r) return 0;
  else if (dcmp(dist-c.r)==0) {
    point.push_back(p);return 1;
  }
  else {
    PT v;ld ang = asin(c.r / dist);v = RotateCCW(u,-ang);
    point.push_back(GetLineProjection(c.c,p,p+v));
    v = RotateCCW(u, ang);
    point.push_back(GetLineProjection(c.c,p,p+v));return 2;
  }
}
//common tangent of two circle A and B; return the point on
//circles the tangent touchesai-bi is a common tangent
int getTangents(CR A,CR B, vector<PT> &a, vector<PT> &b) {
  int cnt = 0;
  if (A.r<B.r) {
    swap(A,B),swap(a,b);
  }
  ld d2=(A.c.x-B.c.x)*(A.c.x-B.c.x)+(A.c.y-B.c.y)*(A.c.y-B.c.y);
  ld rdiff = A.r-B.r; ld rsum = A.r+B.r;
  if (d2 < rdiff*rdiff) return 0;
  ld base = atan2(B.y-A.y,B.x-A.x);
  if (d2 == 0 && A.r == B.r) return -1;
  if (dcmp(d2-rdiff*rdiff)==0) {
    a.push_back(A.point(base)); b.push_back(B.point(base));
    return 1;
  }
  ld ang = acos((A.r-B.r)/sqrt(d2));
  a.push_back(A.point(base+ang));
  b.push_back(B.point(base+ang));
  a.push_back(A.point(base-ang));
  b.push_back(B.point(base-ang));
  if (dcmp(d2-rsum*rsum)) {
    a.push_back(A.point(base));
    b.push_back(B.point(base+PI));
  }
  else if (dcmp(d2-rsum*rsum)==1) {
    ld ang = acos((A.r+B.r)/sqrt(d2));
    a.push_back(A.point(base+ang));
    b.push_back(B.point(PI+base+ang));
    a.push_back(A.point(base-ang));
    b.push_back(B.point(PI+base-ang));
  }
  return (int)a.size();
}
/// pori_britto
CR CircumscribedCircle(PT p1,PT p2,PT p3){
  ld Bx = p2.x-p1.x, By= p2.y-p1.y;
  ld Cx = p3.x-p1.x, Cy= p3.y-p1.y,D = 2*(Bx*Cy-By*Cx);
  ld cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D + p1.x;
  ld cy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D + p1.y;
  PT p = PT(cx,cy); return CR(p,len(p1-p));
}
/// ontor_britto
CR InscribedCircle(PT p1,PT p2,PT p3) {
  ld a = len(p2-p3),b = len(p3-p1),c = len(p1-p2);
  PT p = (p1*a+p2*b+p3*c)/(a+b+c);
  return CR(p,DistanceToLine(p,p1,p2));
}
ld radToPositive(ld rad){
  if (dcmp(rad)<0) rad=ceil(-rad/PI)*PI+rad;
  if (dcmp(rad-PI)>=0) rad-=floor(rad/PI)*PI;
  return rad;
}
PT normalUnit(PT A){
  ld L = len(A);return PT(-A.y/L, A.x/L);
}
Line LineTranslation(Line l, PT v){
  l.p = l.p+v;return l;
}
/// sol contains the center of these circles
void CircleThroughAPointAndTangentToALineWithRadius(PT p,Line l,ld r,vector<PT>& sol) {
  PT e = normalUnit(l.v);
  Line l1=LineTranslation(l,e*r),l2=LineTranslation(l,-e*r);
  getLineCircleIntersection(l1,CR(p,r), sol);
  getLineCircleIntersection(l2,CR(p,r), sol);
}
/// sol contains the center of these circles
void CircleTangentToTwoLinesWithRadius(Line l1,Line l2, ld r, vector<PT>& sol) {
  PT e1 = normalUnit(l1.v), e2 = normalUnit(l2.v);
  Line L1[2]={LineTranslation(l1,e1*r),LineTranslation(l1,e1*(-r))},
  L2[2]={LineTranslation(l2,e2*r),LineTranslation(l2,-e2*r)};
  for( int i = 0; i < 2; i++ ) {
    for( int j = 0; j < 2; j++ ) {
      sol.push_back(ComputeLineIntersection(L1[i].p,L1[i].v,L2[j].p,L2[j].v));
    }
  }
}
/// sol contains the center of these circles
void CircleTangentToTwoDisjointCirclesWithRadius(CR c1,CR c2,
    ld r, vector<PT>& sol) {
  c1.r+=r;c2.r+=r;getCircleCircleIntersection(c1,c2,sol);
}

int isPointInPolygon(PT p, vector<PT> &poly)
{
    int wn=0;
    int n=poly.size();
    for(int i = 0; i < n; i++)
    {
        if (OnSegment(p,poly[i],poly[(i+1)%n])) return -1; //on edge
        int k=dcmp((poly[(i+1)%n]-poly[i])^(p-poly[i]));
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[(i+1)%n].y-p.y);
        if ( k > 0 && d1 <= 0 && d2 > 0 ) wn++;
        if ( k < 0 && d2 <= 0 && d1 > 0 ) wn--;
    }
    if (wn!=0) return 1; //inside
    return 0; //outside
}
/// Point in simple polygon,1:on/inside;0:strictly out
bool isPointOnPolygon(PT q,vector<PT> &p) {
  int n = p.size() , fl = 0;
  for(int i = 0 ; i < n ; i++) {
    if (fabs((q-p[i])^(p[i+1]-p[i])) < eps and (p[i]-q)*(p[i+1]-q) < eps ) {
      return true;
    }
  }
  for(int i = 0 ; i < n ; i++) {
    PT a = p[i] , b = p[i+1] ;
    if (fabs(a.x-b.x) < eps) continue ;
    if (a.x > b.x) swap(a,b);
    if (q.x < a.x-eps or q.x > b.x-eps) continue ;
    if (( (q-a)^(b-a) ) > 0.0) fl ^= 1 ;
  }
  return fl;
}
/// returns 1 if CCW or collinear , returns 0 if CW
bool CCW(PT a, PT b, PT c) {
  ld area=a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y;
  return (dcmp(area) >= 0);
}
/// returns 1 if p is on or inside triangle(a,b,c)
bool PointsInTriangle (PT a, PT b, PT c, PT p) {
  int d1 = dcmp((b-a)^(p-b)), d2 = dcmp((c-b)^(p-c)),
      d3 = dcmp((a-c)^(p-a));
  return !(((d1 < 0) || (d2 < 0) || (d3 < 0)) &&
        ((d1 > 0) || (d2 > 0) || (d3 > 0)));
}
/// cut a convex polygon by a line
vector<PT> cut(vector<PT> &polygon, Line l, int sign) {
    vector<PT> np ;
    int sz = polygon.size();
    for(int i = 0 ; i < sz ; i++) {
        PT p = polygon[i] , q = polygon[(i+1)%sz];
        if (dcmp(l.val(p))*sign >= 0) {
            np.push_back(p);
        }
        ld na = l.val(p), nb = l.val(q);
        if (na*nb < 0.0) {
          np.push_back(a + (b-a)*(na/(na-nb))) ;
        }
    }
    return np ;
}
///diameter of a convex polygon p
ld rotating_calipers(vector<PT> p)
{
  int q = 1, n = p.size();ld ans = 0;
  for( int i = 0; i < n; i++) {
    while(triArea2(p[i],p[(i+1)%n],p[(q+1)%n]) > triArea2(p[i],p[(i+1)%n],p[q] ))
      q=(q+1)%n;
    ans = max( ans, (ld)max(len(p[i]- p[q]), len(p[(i+1)%n] -p[q] ) ) );
  }
  return ans;
}
///minimum area rectangle for convex polygon
ld rec_rotating_calipers(PT *p,int n)
{
  int q=1;ld ans1=1e15,ans2=1e15;int l=0,r=0;
  for( int i = 0; i < n; i++ ) {
    while(dcmp(triArea2(p[i],p[(i+1)%n],p[(q+1)%n])-triArea2(p[i],p[(i+1)%n],p[q] )) >0)
      q=(q+1)%n;
    while (dcmp((p[(i+1)%n]-p[i])*(p[(r+1)%n]-p[r]))>0 )
      r=(r+1)%n;
    if (!i) l = q;
    while (dcmp((p[(i+1)%n]-p[i])*(p[(l+1)%n]-p[l]))<0 )
      l=(l+1)%n;
    ld d = len(p[(i+1)%n]-p[i]);
    ld h = triArea2(p[i],p[(i+1)%n],p[q] )/d;
    ld w =(((p[(i+1)%n]-p[i])*(p[r]-p[i]))-((p[(i+1)%n]-p[i])*(p[l]-p[i])))/d;
    ans1 = min(ans1, 2*(h+w)), ans2 = min(ans2,h*w);
  }
}

/*tangent lines to a convex polygon from a point outside*/
#define CW 	-1
#define ACW	 1
int direction(pii st, pii ed, pii q) {
  LL xp = (LL) (ed.xx - st.xx) * (q.yy - ed.yy) - (LL) (ed.yy - st.yy) * (q.xx - ed.xx);
  if(!xp) return 0; if(xp > 0) return ACW;
  return CW;
}
bool isGood(pii u, pii v, pii Q, int dir) {
  return (direction(Q, u, v) != -dir);
}
pii better(pii u, pii v, pii Q, int dir) {
  if(direction(Q, u, v) == dir) return u;
  return v;
}
pii tangents(vector<pii> &hull, pii Q, int dir, int lo, int hi) {
  int mid;
  while(hi - lo + 1 > 2) {
    mid = (lo + hi)/2;
    bool pvs = isGood(hull[mid], hull[mid - 1], Q, dir);
    bool nxt = isGood(hull[mid], hull[mid + 1], Q, dir);
    if(pvs && nxt) return hull[mid];
    if(!(pvs || nxt)) {
      pii p1 = tangents(hull, Q, dir, mid+1, hi);
      pii p2 = tangents(hull, Q, dir, lo, mid - 1);
      return better(p1, p2, Q, dir);
    }
    if(!pvs) {
      if(direction(Q, hull[mid], hull[lo]) == dir)  hi = mid - 1;
      else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
      else lo = mid + 1;
    }
    if(!nxt) {
      if(direction(Q, hull[mid], hull[lo]) == dir)  lo = mid + 1;
      else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
      else lo = mid + 1;
    }
  }
  pii ret = hull[lo];
  for(int i = lo + 1; i <= hi; i++) ret = better(ret, hull[i], Q, dir);
  return ret;
}
/// returns two point of convex polygon that is tangent
pair< pii, pii> get_tangents(vector<pii> &polygon, pii Q) {
  pii acw_tan = tangents(polygon, Q, ACW, 0, (int) polygon.size() - 1);
  pii cw_tan = tangents(polygon, Q, CW, 0, (int) polygon.size() - 1);
  return make_pair(acw_tan, cw_tan);
}
