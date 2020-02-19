/** Find primitive root of p assuming p is prime.
if not, we must add calculation of phi(p)
Complexity : O(Ans * log (phi(n)) * log n  +sqrt(p))
Returns -1 if not found
*/
int primitive_root(int p) {
  vector<int> factor; int phi = p-1,  n = phi;
  for (int i=2; i*i<=n; ++i)
    if (n%i == 0) {
      factor.push_back (i);
      while (n%i==0)  n/=i;
    }
  if (n>1)  factor.push_back(n);
  for (int res=2; res<=p; ++res) {
    bool ok = true;
    for (int i=0; i<factor.size() && ok; ++i)
      ok &= power(res, phi/factor[i], p) != 1;
    if (ok)  return res;
  }
  return -1;
}
int nttdata(int mod,int &root,int &inv, int &pw) {
  int c = 0, n = mod-1; while (n%2==0) c++, n/=2;
  pw = (mod-1)/n; int g = primitive_root(mod);
  root = power(g, n, mod);
  inv = power(root, mod-2, mod);
  return c;
}
