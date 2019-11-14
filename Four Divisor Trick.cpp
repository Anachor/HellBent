/*
Let S(v,m) be the count of integers in the range 2..v that remain after sieving with all primes smaller
or equal than m. That is S(v,m) is the count of integers up to v that
are either prime or the product of primes larger than m.

S(v, p) is equal to S(v, p-1) if p is not prime or v is smaller than p2. Otherwise (p prime, p2<=v) S(v,p)
can be computed from S(v,p-1) by finding the count of integers that are removed while sieving with p.
An integer is removed in this step if it is the product of p with another integer that has no
divisor smaller than p. This can be expressed as

S(v,p)= S(v,p−1)− ( S(v/p, p−1)− S(p−1,p−1) ).

During computation of S(N,p) it is sufficient to compute S(v,p) for all positive integers v that
are representable as floor(N/k) for some integer k and all p ≤ v1/2.

NOTE: Pi(N) = S(N,N). When you call S(N,N) it will need to compute S(N/k,N/k) in its lower substate.
Hence you can have all required values of Pi(N/k).

In my code DSUM(N,P) do the job of calculating S(N,P).

I used two arrays H[] and L[] for storing the values of S(N/k,p) in H[k] for k<=N1/2 and
for k>=N^(1/2) I stored the values of S(N/k,p) in L[N/k].

For computation I started with p=2 and changed the values of all the state which is going to
be affected by this particular prime. Continue doing this for all prime till N1/2 and
at the end for k<=N1/2, H[k] will contain the values of Pi(N/k) and L[k] will contain the values of Pi(k).

PS: My complexity is O(N3/4).
*/
#include <bits/stdc++.h>

#define PI (acos(-1.0))
#define DBG printf("Hi\n")
#define loop(i,n) for(i =1 ; i<=n; i++)
#define mp make_pair
#define pb push_back
#define mod 998244353LL
#define INF 1000000000
#define xx first
#define yy second
#define sq(x) ((x)*(x))
#define eps 0.0000000001
#define i64 long long int
#define ui64 unsigned long long int

using namespace std ;

#define maxn 1000000

i64 Lo[maxn+5] , Hi[maxn+5] ;

void primeCount( i64 N )
{
    i64 i , j , k , l , m ;

    i64 s = sqrt(N+0.0) + 1 ;

    for(i=1 ; i<=s ; i++) Lo[i] = i-1 ;
    for(i=1 ; i<=s ; i++) Hi[i] = (N/i) - 1 ;

    for(i=2 ; i<=s ; i++)
    {
        if( Lo[i] == Lo[i-1] ) continue ;

        i64 isq = i*i , lim = N/isq ;

        // we need , ( N/j ) >= i*i
        //  => j <= ( N/(i*i) )

        for( j=1 ; j<=lim && j<=s ; j++ )
        {
            if( i*j > s ) Hi[j] = Hi[j] - ( Lo[N/(i*j)] - Lo[i-1] ) ;
            else Hi[j] = Hi[j] - ( Hi[i*j] - Lo[i-1] ) ;
        }


        // j >= i*i
        for( j=s ; j>=isq ; j-- )
        {
            Lo[j] = Lo[j] - ( Lo[j/i] - Lo[i-1] ) ;
        }
    }
    return ;
}


int main()
{
    i64 i , j , k , l , m , n ;

    scanf("%lld",&n) ;

    primeCount(n) ;

    i64 ans = 0LL ;

    for(i=2 ; (i*i*i)<=n ; i++)
    {
        if( Lo[i]!=Lo[i-1] ) ans++ ;
    }

    for(i=2 ; i*i <=n ; i++)
    {
        if( Lo[i]==Lo[i-1] ) continue ;
        ans += (Hi[i] - Lo[i] ) ;
    }

    printf("%lld\n",ans ) ;
    return 0 ;
}
