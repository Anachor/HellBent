LL gcd(LL u, LL v) {
    if (u == 0) return v; if (v == 0) return u;
    int shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) swap(u, v);
        v = v - u;
    } while (v);
    return u << shift;
}
LL lcm(LL a, LL b) {return (a/gcd(a, b))*b;}
LL power(LL a, LL b, LL m) {
  a = (a%m+m)%m; LL ans = 1;
  while (b) {
    if (b & 1) ans = (ans*a)%m;
    a = (a*a)%m;
    b >>= 1;
  }
  return ans;
}
///returns g = gcd(a, b); finds x, y st d = ax+ by
LL egcd(LL a, LL b, LL &x, LL &y) {
  LL xx = y = 0; LL yy = x = 1;
  while (b) {
    LL q = a/b;
    LL t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}
///Solves ax=b(mod m)
vector<LL>SolveCongruence(LL a,LL b,LL m){
  LL x, y, g = egcd(a, m, x, y); vector<LL> ans;
  if (b%g == 0) {
    x = (x*(b/g))%m; if (x<0)    x+=m;
    for (LL i=0;i<g;i++) {
      ans.push_back(x); x=(x+m/g)%m;
    }
  }
  return ans;
}
LL inverse(LL a, LL m) {
  LL x, y, g = egcd(a, m, x, y);
  if (g > 1) return -1;
  return (x%m+m)%m;
}
//find z st z%m1=r1,z%m2=r2. Here, z is unique mod
//M=lcm(m1,m2), on failure, M =-1,
PLL CRT(LL m1, LL r1, LL m2, LL r2) {
  LL s, t, g = egcd(m1, m2, s, t);
  if (r1%g != r2%g) return PLL(0, -1);
  LL M = m1*m2;
  LL ss = ((s*r2)%m2)*m1, tt = ((t*r1)%m1)*m2;
  LL ans = ((ss+tt)%M+M)%M;
  return PLL(ans/g, M/g);
}
PLL CRT(const vector<LL> &m, const vector<LL>&r) {
  PLL ans = PLL(r[0], m[0]);
  for (LL i = 1; i < m.size(); i++) {
    ans = CRT(ans.second, ans.first, m[i], r[i]);
    if (ans.second == -1) break;
  }
  return ans;
}
///computes x and y such that ax + by = c
bool LinearDiophantine(LL a,LL b,LL c,LL &x,LL &y){
  if (!a && !b)  {x=y=0; return !c;}
  if (!a)  {x=0;y=c/b; return !(c%b);}
  if (!b)  {x=c/a;y=0; return !(c%a);}
  LL g = gcd(a, b);
  x=c/g*inverse(a/g, b/g); y=(c-a*x)/b;
  return !(c%g);
}
/// Min sol to a^x = b (mod M),use unmap for speed
int DiscreteLog(int a, int b, int M) {
  map<int, int> id; LL cur=1, RT=sqrt(M)+5;
  for (int i=0;i<RT;i++)  id[cur]=i,cur=(cur*a)%M;
  int pp = power(cur, M-2, M);
  cur = b;
  for (int i=0; i*RT<M; i++) {
    auto it = id.find(cur);
    if (it != id.end())   return i*RT+it->second;
    cur = (cur*pp)%M;
  }
  return -1;
}
