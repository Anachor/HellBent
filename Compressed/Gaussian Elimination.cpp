///n = no of eqn, m = no of var, ar[i][m] = rhs
///returns -1 if no sol, else no of free variables
int gauss(int n,int m,double **ar,VD&res){
  res.assign(m, 0); vector<int> pos(m, -1);
  int i, j, k, l, p, free_var = 0;
  for (j = 0, i = 0; j < m && i < n; j++){
    for (k = i, p = i; k < n; k++){
      if (abs(ar[k][j]) > abs(ar[p][j])) p = k;
    }
    if (abs(ar[p][j]) > EPS){
      pos[j] = i;
      for (l = j; l <= m; l++)
        swap(ar[p][l], ar[i][l]);
      for (k = 0; k < n; k++){
        if (k != i){
          double x = ar[k][j] / ar[i][j];
          for (l=j; l<=m; l++)
            ar[k][l]-=(ar[i][l] * x);
        }
      }
      i++;
    }
  }
  for (i = 0; i < m; i++){
    if (pos[i] == -1) free_var++;
    else res[i] = ar[pos[i]][m] / ar[pos[i]][i];
  }
  for (i = 0; i < n; i++) {
    double val = 0.0;
    for (j = 0; j < m; j++)
      val += (res[j] * ar[i][j]);
    if (abs(val - ar[i][m]) > EPS) return -1;
  }
  return free_var;
}
int gauss(int n,int m, bitset<MAXCOL>ar[MAXROW],
                              bitset<MAXCOL>&res){
  res.reset(); vector<int>pos(m, -1);
  int i, j, k, l, v, p, free_var = 0;
  for (j = 0, i = 0; j < m && i < n; j++){
    for (k = i, p = i; k < n; k++){
      if (ar[k][j]) {p = k; break;}
    }
    if (ar[p][j]){
      pos[j] = i; swap(ar[p], ar[i]);
      for (k = 0; k < n; k++){
        if (k != i && ar[k][j]) ar[k] ^= ar[i];
      }
      i++;
    }
  }
  for (i = 0; i < m; i++){
    if (pos[i] == -1) free_var++;
    else res[i] = ar[pos[i]][m];
  }
  for (i = 0; i < n; i++) {
    for (j=0, v=0; j<m; j++) v^=(res[j]&ar[i][j]);
    if (v != ar[i][m]) return -1;
  }
  return free_var;
}
