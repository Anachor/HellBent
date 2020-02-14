LL gcd(LL u, LL v) {
    if (!u) return v;  if (!v) return u;
    int shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctzll(v);
        if (u > v) swap(u, v);
        v = v - u;
    } while (v);
    return u << shift;
}
LL lcm(LL a,LL b){return (a/gcd(a,b))*b;}
LL power(LL a,LL b,LL m) {
  a = (a%m+m)%m; LL ans = 1;
  while (b) {
    if (b & 1) ans = (ans*a)%m;
    a = (a*a)%m;  b >>= 1;
  }
  return ans;
}
///returns gcd(a,b); finds x,y st d=ax+by
LL egcd(LL a, LL b, LL &x, LL &y) {
  LL xx = y = 0, yy = x = 1, q;
  while (b) {
    q = a/b; t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}
/// finds all solutions to ax = b (mod m)
vector<LL> Congruence(LL a, LL b, LL m) {
  LL x, y; vector<LL> ans;
  LL g = egcd(a, m, x, y);
  if (b%g == 0) {
    x = (x*(b/g))%m; if (x<0) x+=m;
    for (LL i=0; i<g; i++)
      ans.push_back(x), x = (x+m/g)%m;
  }
  return ans;
}
LL inverse(LL a, LL m) { /// a^-1 (mod m)
  LL x, y, g = egcd(a, m, x, y);
  return g > 1 ? -1 : (x%m+m)%m;
}
///Return (z, M) st. z%m1=r1, z%m2=r2.
///M = lcm(m1, m2) On failure, M = -1.
PLL CRT(LL m1, LL r1, LL m2, LL r2) {
  LL s, t, g=egcd(m1,m2,s,t), M = m1*m2;
  if (r1%g != r2%g) return PLL(0, -1);
  LL ss=((s*r2)%m2)*m1,tt=((t*r1)%m1)*m2;
  LL ans = ((ss+tt)%M+M)%M;
  return PLL(ans/g, M/g);
}
///computes x and y such that ax + by = c
bool Solve(LL a,LL b,LL c,LL &x,LL &y) {
  if (!a && !b)  {x=y=0; return !c;}
  if (!a)  {x=0;y=c/b; return !(c%b);}
  if (!b)  {x=c/a;y=0; return !(c%a);}
  LL g = gcd(a, b);
  x=c/g*inverse(a/g, b/g); y=(c-a*x)/b;
  return !(c%g);
}