#include<bits/stdc++.h>
#define LL long long
using namespace std;

LL modit(LL x, LL mod) {
	if(x>=mod) x-=mod;
	return x;
}

/// Use __int128 if available
LL mult(LL x, LL y, LL mod) {
	LL s=0, m=x%mod;
	while(y) {
		if(y&1) s = modit(s+m, mod);
		y>>=1;
		m = modit(m+m, mod);
	}
	return s;
}

LL power(LL x, LL p, LL mod){
	LL s=1, m=x;
	while(p) {
		if(p&1) s = mult(s, m, mod);
		p>>=1;
		m = mult(m, m, mod);
	}
	return s;
}

bool witness(LL a, LL n, LL u, int t){
	LL x = power(a,u,n);
	for(int i=0; i<t; i++) {
		LL nx = mult(x, x, n);
		if (nx==1 && x!=1 && x!=n-1) return 1;
		x = nx;
	}
	return x!=1;
}

/**
    return 1 if prime, 0 otherwise
    Range : 10^18

    Magic bases:
    n < 4,759,123,141        3 :  2, 7, 61
    n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
    n < 3,474,749,660,383    6 :  2, 3, 5, 7, 11, 13
    n < 2^64                 7 : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
    Handles 40000 18 digit primes in 1 second on Toph
*/

vector<LL> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool miller_rabin(LL n) {
	if (n < 2)    return 0;
	if (n%2==0)   return n==2;

	LL u = n-1;
	int t = 0;
	while(u%2==0)   u/=2, t++;  // n-1 = u*2^t

	for (LL v: bases) {
		LL a = v%(n-1) + 1;
		if(witness(a, n, u, t)) return 0;
	}
	return 1;
}


LL f(LL x, LL mod) {
	return modit(mult(x, x, mod) + 1, mod);
}

mt19937_64 rng;
LL randll(LL lo, LL hi) {
    return uniform_int_distribution<LL>(lo, hi)(rng);
}

/// If n is prime, returns n
/// Otherwise returns a proper divisor of n
/// Able to factorize ~40 18 digit semiprimes in 1 second on Toph
/// Range : 10^18
LL pollard_rho(LL n) {
    if (n==1)               return 1;
    if (n%2==0)             return 2;
	if (miller_rabin(n))    return n;

    while (true) {
        LL x = randll(1, n);
        LL y = 2, res = 1;

        for (int sz=2; res == 1; sz*=2) {
            for (int i=0; i<sz && res<=1; i++) {
                x = f(x, n);
                res = __gcd(abs(x-y), n);
            }
            y = x;
        }
        cout<<x<<" "<<res<<endl;
        if (res!=0 && res!=n) return res;
    }
}

int main()
{
    ///IMPORTANT!!!!!!!
    rng = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
    int t;
    cin>>t;

    while (t--) {
        LL x;
        cin>>x;
        LL factor = pollard_rho(x);
        cout<<x<<" = "<<factor<<" * "<<x/factor<<endl;
    }
}
