#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
// Problem         : Mod Mod Mod (NAIPC 2019)
// Author          : Darcy Best
// Expected Result : AC
// Complexity      : O(log(p+q)) per test case

// I will instead compute:
//  (p + 2p + ... + np) - q * ([p/q] + [2p/q] + ... + [np/q])

#include <iostream>
using namespace std;

// Computes [p/q] + [2p/q] + ... + [np/q]
long long sum_of_floors(long long p,long long q,long long n){
  if(p == 0 || n == 0) return 0;

  if(n >= q)
    return p*(n/q)*(n+1) - (n/q)*((n/q)*p*q + p + q - 1)/2 + sum_of_floors(p,q,n%q);

  if(p >= q)
    return (p/q)*n*(n+1)/2 + sum_of_floors(p%q,q,n);

  return (n*p/q) * n - sum_of_floors(q,p,n*p/q);
}

long long gcd(long long a, long long b){
  return b == 0 ? a : gcd(b, a % b);
}

int main(){
  int C; cin >> C;

  while(C--){
    long long p,q,n; cin >> p >> q >> n;
    long long g = gcd(p,q);

    cout << (p * n * (n+1) / 2) - q * sum_of_floors(p/g, q/g, n) << endl;
  }
}
