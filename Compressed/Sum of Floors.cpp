//sum of (p*i+r)/q  for i = 0...n-1
LL f(LL n, LL p, LL r, LL q) {
  if (p == 0)   return (r / q) * n;
  if (p>=q||r>=q) return f(n,p%q,r%q,q) +
               ((p/q)*(n-1)+2*(r/q))*n/2;
  return f((p*n+r)/q, q, (p*n+r)%q, p);
}