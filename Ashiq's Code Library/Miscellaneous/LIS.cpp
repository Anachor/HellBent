/// Longest Increasing Subsequence
#include <bits/stdc++.h>
using namespace std ;
const int N = 1e6;
int a[N] , LIS[N] ; /// to find decreasing Sub , simply multiply the elements by -1

int main () {
    int n ;
    for (int i = 1 ; i <= n ; i++) {
        scanf ("%d" , &a[i]) ;
    }
    vector <int> v ;
    for (int i = 1 ; i <= n ; i++) {
        int x = a[i] ;
        vector<int>::iterator it = upper_bound(v.begin(), v.end(), x) ; /// change it to lower_bound for strictly increasing subsequence
        if (it == v.end()) v.push_back(x);
        else *it = x;
        LIS[i] = upper_bound(v.begin(), v.end(), x) - v.begin() ; /// change it to lower_bound for strictly increasing subsequence
    }
}
