//p[0][i] = maxlen of hlf palin arnd half idx i
//p[1][i] = maxlen of hlf palin arnd idx i,0 based
VI p[2];
void manacher(const string s) {
  int n = s.size(); p[0] = VI(n+1); p[1] = VI(n);
  for (int z=0; z<2; z++)
    for (int i=0, l=0, r=0; i<n; i++) {
      int t = r - i + !z;
      if (i<r) p[z][i] = min(t, p[z][l+t]);
      int L = i-p[z][i], R = i+p[z][i] - !z;
      while (L>=1 && R+1<n && s[L-1] == s[R+1])
        p[z][i]++, L--, R++;
      if (R>r) l=L, r=R;
    }
}
bool ispalin(int l, int r) {
  int mid = (l+r+1)/2, sz = r-l+1;
  return 2*p[sz%2][mid] + sz%2 >=sz;
}
