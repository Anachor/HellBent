//expo(a,b,m) returns (a^b)%m
//prime contains all primes upto 47000, Pt = number of prime
intl prime[10000], Pt = 0;
const intl LIM = LLONG_MAX, mod = 1000000007;
intl mul( intl a, intl b, intl mod) {
    intl x, res;
    if (a < b) swap(a, b);
    if (!b) return 0;
    if (a < (LIM / b)) return ((a * b) % mod);
    res = 0, x = (a % mod), b %= mod;
    while (b) {
        if (b & 1) {
            res = res + x;
            if (res >= mod) res -= mod;
        }
        b >>= 1; x <<= 1;
        if (x >= mod) x -= mod;
    }
    return res%mod;
}
int isPrime( intl n ) {
    if( n == 2 ) return 1;
    if( n % 2 == 0 ) return 0;
    intl d = n-1;
    while(d%2==0) d >>= 1;
    int test[] = {2,3,5,7,11,13,17,19,23};
    for( int i = 0; i < 9; i++ ) {
        intl x = test[i]%(n-2), temp = d;
        if(x < 2) x += 2;
        intl a = expo(x,d,n);
        while( temp != n-1 && a != 1 && a != n-1 ) {
            a = mul(a,a,n);
            temp <<= 1;
        }
        if( a != n-1 && (temp&1) ==0 ) return 0;
    }
    return 1;
}
intl pollard_rho(intl n, intl c) {
    intl x = 2, y = 2, i = 1, k = 2, d;
    while (true) {
        x = ( mul(x, x, n) + c);
        if (x >= n)	x -= n;
        d = gcd( abs(x - y), n);
        if (d > 1) return d;
        if (++i == k) {
            y = x; k <<= 1;
        }
    }
    return n;
}
void llfactorize(intl n, vector<intl> &f) {
    if (n == 1) return ;
    if (n < 1e9) {
        for (int i = 0; prime[i]*prime[i] <= n; i++) {
            while (n%prime[i] == 0) {
                f.push_back(prime[i]);
                n /= prime[i];
            }
        }
        if (n != 1)	f.push_back(n); return ;
    }
    if (isPrime(n)) {
        f.push_back(n); return ;
    }
    intl d = n;
    for (int i = 2; d == n; i++) d = pollard_rho(n, i);
    llfactorize(d, f);
    llfactorize(n/d, f);
}
void factorize( intl n, vector< pair<intl,intl> > &ans ) {
    vector<intl> v;
    llfactorize(n, v);
    sort( v.begin(), v.end() );
    intl a = v[0], b = 1;
    for( int i = 1; i < (int)v.size(); i++ ) {
        if( v[i] == v[i-1] ) b++;
        else {
            ans.pb( make_pair(a,b) );
            a = v[i]; b = 1;
        }
    }
    ans.pb( make_pair(a,b) );
}
int main(){
    vector< pair<intl, intl> >ans;
    factorize( n, ans );
    return 0;
}
