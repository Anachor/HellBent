for (int i=0; i<(1<<K); i++)   dp[i] = a[i];
for (int i=0; i<K; i++)
  for (int mask = 0; mask < (1<<K); mask++) {
    if ((mask & (1<<i)))  /// == 0 for supermasks
      a[mask] += a[mask^(1<<i)];
