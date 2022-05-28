bool is_colinear(Point a, Point b, Point c) {
  return fabs((b-a).cross(c-a)) < EPS;
}
bool on(Point a, Point b, Point x) {
  LD t = (x-a).Norm()+(x-b).Norm()-(a-b).Norm();
  return fabs(t) < EPS;
}
bool in_circle(const Point& v, const Circle& C) {
  return (v - C.center).Norm() <= C.r + EPS;
}
Circle better(Circle A, Circle B) {
  if (A.r < B.r) return A;
  return B;
}
Circle find_circle(Point a) {return Circle(a,0);}
Circle find_circle(Point a, Point b) {
  return Circle((a+b)/2,(a-b).Norm()/2);
}
Circle find_circle(Point a, Point b, Point c,
                          bool force_on = false) {
  if(is_colinear(a,b,c)) {
    if(on(a,b,c))
      return Circle((a+b)/2,(a-b).Norm()/2);
    if(on(a,c,b))
      return Circle((a+c)/2, (a-c).Norm() / 2);
    if(on(c,b,a))
      return Circle((c+b)/2, (c-b).Norm() / 2 );
  }
  Point u = (b-a), v = (c-a);
  Point uperp = u.Rotate90(),vperp = v.Rotate90();
  Point ab = (a+b)/2, ac = (a+c)/2;
  Point ans=InterLineLine(ab,ab+uperp,ac,ac+vperp);
  LD rad = ((ans-a).Norm()+
              (ans-b).Norm()+(ans-c).Norm())/3.0l;
  Circle C = Circle(ans,rad);
  if (force_on) return C;
  Circle C_ab = find_circle(a,b);
  Circle C_bc = find_circle(b,c);
  Circle C_ac = find_circle(a,c);
  if(in_circle(c, C_ab)) C = better(C, C_ab);
  if(in_circle(a, C_bc)) C = better(C, C_bc);
  if(in_circle(b, C_ac)) C = better(C, C_ac);
  return C;
}
Circle find_circle(vector<Point> P, int N, int K){
  if (K >= 3)
    return find_circle(P[N-1],P[N-2],P[N-3],true);
  if (N == 1) return find_circle(P[0]);
  if (N == 2) return find_circle(P[0],P[1]);
  int i = rand()%(N-K);
  swap(P[i], P[N-1-K]); swap(P[N-1-K], P[N-1]);
  auto C = find_circle(P, N-1, K);
  swap(P[N-1-K], P[N-1]); swap(P[i], P[N-1-K]);
  if (in_circle(P[i],C)) return C;
  swap(P[i], P[N-1-K]);
  C = find_circle(P, N, K+1);
  swap(P[i], P[N-1-K]);
  return C;
}
