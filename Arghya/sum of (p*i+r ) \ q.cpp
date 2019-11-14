/*
i64 res = 0 ;
for(int i=0 ; i<n ; i++) res += ( p*i+r )/q ;
return res ;
*/
//this function does the above thing in logarithmic time
i64 findSum(i64 n, i64 p, i64 r, i64 q) {
  if (p == 0) {
    return (r / q) * n;
  }
  if (p >= q || r >= q) {
    return ((p / q) * (n - 1) + 2 * (r / q)) * n / 2 + findSum(n, p % q, r % q, q);
  }
  return findSum((p * n + r) / q, q, (p * n + r) % q, p);
}