///Finds sum of floor((p*i+r)/q) from i = 0 to n-1
LL findSum(LL n, LL p, LL r, LL q) {
  if (p == 0) return (r / q) * n;
  if (p>=q||r>=q) return findSum(n,p%q,r%q,q) +
                        ((p/q)*(n-1)+2*(r/q))*n/2;
  return findSum((p*n+r)/q, q, (p*n+r)%q,p);
}
