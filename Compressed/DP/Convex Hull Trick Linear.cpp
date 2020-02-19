//Min:M inc, x dec, useless(s-1, s-2, s-3)
//    M dec, x inc, useless(s-3, s-2, s-1)
//Max:M inc, x inc, useless(s-3, s-2, s-1)
//    M dec, x dec, useless(s-1, s-2, s-3)
struct CHT {
  vector<LL> M; vector<LL> C; int ptr = 0;
  bool useless(int l1, int l2, int l3) {
    return (C[l3]-C[l1])*(M[l1]-M[l2])
        <= (C[l2]-C[l1])*(M[l1]-M[l3]);
  } ///Use double comp if M,C is LL range
  LL f(int id, LL x) {return M[id]*x+C[id];}
  void add(LL m, LL c) {
    M.push_back(m); C.push_back(c);
    int s = M.size();
    while (s >= 3 && useless(s-3, s-2, s-1)) {
      M.erase(M.end()-2); C.erase(C.end()-2); s--;
    }
  }
  LL query(LL x) {
    if (ptr >= M.size()) ptr = M.size()-1;
    while (ptr<M.size()-1 && f(ptr,x)>f(ptr+1,x))
      ptr++;
    return f(ptr, x);
  }
};
