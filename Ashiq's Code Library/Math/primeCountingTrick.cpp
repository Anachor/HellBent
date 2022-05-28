#define maxn 1000000
i64 Lo[maxn+5] , Hi[maxn+5] ;
void primeCount( i64 N )
{
  i64 i , j , k , l , m ; i64 s = sqrt(N+0.0) + 1 ;
  for(i=1 ; i<=s ; i++) Lo[i] = i-1 ;
  for(i=1 ; i<=s ; i++) Hi[i] = (N/i) - 1 ;
  for(i=2 ; i<=s ; i++) {
    if( Lo[i] == Lo[i-1] ) continue ;
    i64 isq = i*i , lim = N/isq ;
    // we need , ( N/j ) >= i*i  =>   j <= ( N/(i*i) )
    for( j=1 ; j<=lim && j<=s ; j++ ) {
      if(i*j>s) Hi[j] = Hi[j] - ( Lo[N/(i*j)] - Lo[i-1] ) ;
      else Hi[j] = Hi[j] - ( Hi[i*j] - Lo[i-1] ) ;
    }
    for( j=s ; j>=isq ; j-- ){ // j >= i*i
      Lo[j] = Lo[j] - ( Lo[j/i] - Lo[i-1] ) ;
    }
  }
    return ;
}
