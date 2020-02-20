vector<int> pr; int lp[N+1]; //lowest prime factor
void sieve() {
  for (int i=2; i<N; ++i) {
    if (lp[i] == 0) {lp[i] = i; pr.push_back(i);}
    for (int j=0; j<pr.size() && pr[j]<=lp[i]
                              && i*pr[j]<N; ++j)
      lp[i * pr[j]] = pr[j];
  }
}
