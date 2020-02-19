typedef vector<Point3> face;
typedef vector<Point3> edge;
typedef vector<face> hull;
#define INSIDE (-1)
#define ON (0)
#define OUTSIDE (1)
int side(Point3 a, Point3 b, Point3 c, Point3 p){
  Point3 norm = (b-a).cross(c-a);
  Point3 me = p-a;
  return dcmp(me.dot(norm));
}
hull find_hull(vector<Point3> P) {
  random_shuffle(P.begin(), P.end());
  int n = P.size();
  for(int j = 2; j < n; j++) {
    Point3 n = (P[1]-P[0]).cross(P[j]-P[0]);
    if(n.Norm() > EPS) {swap(P[j], P[2]);break;}
  }
  for(int j = 3; j < n; j++) {
    if(side(P[0],P[1],P[2],P[j])) {
      swap(P[j], P[3]); break;
    }
  }
  if(side(P[0],P[1],P[2],P[3]) == OUTSIDE)
    swap(P[0], P[1]);
  hull H{ {P[0],P[1],P[2]}, {P[0],P[3],P[1]},
  {P[0],P[2],P[3]},{P[3],P[2],P[1]}};
  auto make_degrees = [&](const hull& H) {
    map<edge,int> ans;
    for(const auto & f : H) {
      for(int i = 0; i < 3; i++){
        Point3 a = f[i], b = f[(i+1)%3];
        ans[{a,b}]++;
      }
    }
    return ans;
  };
  for(int j = 4; j < n; j++) {
    hull H2; H2.reserve((int)H.size());
    vector<face> plane;
    for(const auto & f : H) {
      int s = side(f[0],f[1],f[2],P[j]);
      if (s == INSIDE || s == ON) H2.pb(f);
    }
    //For any edge that now only has 1 incident
    //face (it's other face deleted) add a new
    //face with this vertex and that edge.
    map<edge, int> D = make_degrees(H2);
    const auto tmp = H2;
    for (const auto & f : tmp) {
      for(int i = 0; i < 3; i++) {
        Point3 a = f[i], b = f[(i+1)%3];
        int d = D[{a,b}] + D[{b,a}];
        if (d==1) H2.pb({a, P[j], b});//a new face
      }
    }
    H = H2;
  }
  return H;
}
