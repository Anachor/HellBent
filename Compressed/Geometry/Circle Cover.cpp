///Check if the all of the area of circ(O, R) in
///Circ(OO, RR) is covered by some other circle
bool CoverCircle(PT O, double R, vector<PT> &cen,
      vector<double> &rad, PT OO, double RR) {
  int n = cen.size();
  vector<pair<double, double>> arcs;
  for (int i=0; i<n; i++) {
    PT P = cen[i]; double r = rad[i];
    if (i!=0 && R + sqrt(dist2(O, P))<r) return 1;
    if (i==0 && r + sqrt(dist2(O, P))<R) return 1;
    vector<PT> inter =
             CircleCircleIntersection(O, P, R, r);
    if (inter.size() <= 1)  continue;
    PT X = inter[0], Y = inter[1];
    if (cross(O, X, Y) < 0) swap(X, Y);
    if (!(cross(O, X, P) >= 0 &&
          cross(O, Y, P) <= 0))  swap(X, Y);
    if (i==0)     swap(X, Y);
    X = X-O; Y=Y-O;
    double ll = atan2(X.y, X.x);
    double rr = atan2(Y.y, Y.x);
    if (rr < ll)  rr += 2*PI;
    arcs.emplace_back(ll, rr);
  }
  if (arcs.empty())   return false;
  sort(arcs.begin(), arcs.end());
  double st = arcs[0].ff, en = arcs[0].ss,ans = 0;
  for (int i=1; i<arcs.size(); i++) {
    if (arcs[i].first <= en + EPS)
      en = max(en, arcs[i].second);
    else st = arcs[i].first, en = arcs[i].second;
    ans = max(ans, en-st);
  }
  return ans >= 2*PI;
}
