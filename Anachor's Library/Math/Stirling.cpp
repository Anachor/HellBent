vector<LL> getstirling(int n, LL m) {
    vector<LL> f(n+1), g(n+1), invfac(n+1), fac(n+1);

    fac[0] = 1;
    for (int i=1; i<=n; i++)    fac[i] = (fac[i-1]*i)%m;

    invfac[n] = power(fac[n], m-2, m);
    for (int i=n-1; i>=0; i--)  invfac[i] = (invfac[i+1]*(i+1))%m;

    f[0] = 1;
    for (int i=1; i<=n; i++)    f[i] = m-f[i-1];
    for (int i=1; i<=n; i++)    f[i] = (f[i] * invfac[i])%m;

    g[0] = 0;
    for (int i=1; i<=n; i++)    g[i] = power(i, n, m);
    for (int i=1; i<=n; i++)    g[i] = (g[i] * invfac[i])%m;

    vector<LL> ans = FFT::multiply(f, g, m);
    ans.resize(n+1);
    return ans;
}
