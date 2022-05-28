PT dir;
bool half(PT p){
  return cross(dir, p) < 0 ||
        (cross(dir, p) == 0 && dot(dir, p) > 0);
}
bool polarComp(PT p, PT q) {
  return make_tuple(half(p), 0)
       < make_tuple(half(q), cross(p, q));
}
void process(vector<PT> &P) {
  int mnid = 0;
  for (int i=0; i<P.size(); i++)
    if (P[i] < P[mnid])
      mnid = i;
  rotate(P.begin(), P.begin()+mnid, P.end());
}
vector<PT> MinkowskiSum(vector<PT>A, vector<PT>B){
  process(A); process(B);
  int n = A.size(), m = B.size();
  vector<PT> P(n), Q(m);
  for(int i=0; i<n; i++) P[i] = A[(i+1)%n] - A[i];
  for(int i=0; i<m; i++) Q[i] = B[(i+1)%m] - B[i];
  dir = PT(0, -1);
  vector<PT> C(n+m+1);
  merge(P.begin(), P.end(), Q.begin(), Q.end(),
                          C.begin()+1, polarComp);
  C[0] = A[0] + B[0];
  for(int i=1; i<C.size(); i++) C[i]=C[i]+C[i-1];
  C.pop_back();
  return C;
}
