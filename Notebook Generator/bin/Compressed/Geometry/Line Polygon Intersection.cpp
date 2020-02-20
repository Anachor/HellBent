///Dist from O to OX intersect AB, div by len(OX)
double distance(PT O, PT X, PT A, PT B) {
  B = B-A; A = A-O; X=X-O;
  return 1.0*cross(A, B)/cross(X, B);
}
int sign(LL a) { return a==0 ? 0 : (a>0 ?1:-1);}
//Special Pts are given by pair<double,int>(a,b)
//Let O be a special pt with OX,OY incident edges.
//Then a = AO/AB, b is an integer denoting type.
//CS: OX and OY are on the same side:   ignore
//CS: OX and OY are on the different side: b=0
//Cs: OX on line, OY on side, b=sign(cross(A,B,Y))
double LinePoly(PT A, PT B, const vector<PT> &p) {
  int n = p.size();
  vector<pair<double, int>> special;
  for (int i=0; i<n; i++) {
    PT X = p[i], Y = p[(i+1)%n], W = p[(i-1+n)%n];
    LL crx = cross(A, B, X), cry = cross(A, B, Y),
       crw = cross(A, B, W);
    if (crx == 0) {
      double f;
      if (B.x != A.x) f = 1.0*(X.x-A.x)/(B.x-A.x);
      else       f = 1.0*(X.y-A.y)/(B.y-A.y);
      if (sign(crw) && sign(cry))
        if (sign(crw) != sign(cry))
          special.pb({f, 0});
      else if(sign(cry)) special.pb({f,sign(cry)});
      else if(sign(crw)) special.pb({f,sign(crw)});
    }
    else if (sign(crx) == -sign(cry)) {
      double f = distance(A, B, X, Y);
      special.push_back({f, 0});
    }
  }
  sort(special.begin(), special.end());
  bool active = false;
  int sgn = 0; //lst side sign if curntly linear,
  double prv = 0, ans = 0;
  for (auto &pr: special) {
    double d = pr.first; int tp = pr.second;
    if (sgn) {
      assert(sgn && tp);
      if (sgn != tp)  active = !active;
      ans += d - prv; sgn = 0;
    }
    else {
      if (active)     ans += d - prv;
      if (tp == 0)    active = !active;
      else            sgn = tp;
    }
    prv = d;
  }
  return ans*sqrt(dot(B-A, B-A));
}
