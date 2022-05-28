LD areaCT(Point pa, Point pb, LD r) {
  if (pa.Norm() < pb.Norm()) swap(pa, pb);
  if (dcmp(pb.Norm()) == 0) return 0;
  LD a=pb.Norm(),b=pa.Norm(),c=(pb-pa).Norm();
  LD sinB = fabs(pb.cross(pb-pa)/a/c);
  LD cosB = pb.dot(pb-pa)/a/c;
  LD sinC = fabs(det(pa,pb)/a/b);
  LD cosC = pa.dot(pb)/a/b;
  LD B = atan2(sinB, cosB), C = atan2(sinC, cosC);
  LD S = 0.;
  if (a > r) {
    S = C / 2 * r * r;
    LD h = a * b * sinC / c;
    if(h < r && B < PI / 2) {
      S -= (Acos(h/r)*r*r - h*sqrt(r*r-h*h));
    }
  } else if (b > r) {
    LD theta = PI - B - Asin((sinB/r * a,-1,+1));
    S = a*r*sin(theta)/2 + (C-theta)/2*r*r;
  } else {
      S = sinC * a * b / 2;
  }
  return S;
}
LD poly_cross(vector<Point> P, Point cen, LD r) {
  int n = P.size(); LD ans = 0;
  for(int i = 0; i < n; i++) {
    LD cr=fabs(areaCT(P[i]-cen,P[(i+1)%n]-cen,r))*
            dcmp((P[i]-cen).cross(P[(i+1)%n]-cen));
    ans += cr;
  }
  return ans;
}
