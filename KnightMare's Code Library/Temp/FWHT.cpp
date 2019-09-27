/**
Iterative implementation of Fast Walsh–Hadamard transform
Complexity: O(N log N)

XOR convolution:
    Given two arrays A, B; Find C where
    C[k] = sum(a[i]*b[j]); i^j=k
AND convolution:
    Given two arrays A, B; Find C where
    C[k] = sum(a[i]*b[j]); i&j=k
OR convolution:
    Given two arrays A, B; Find C where
    C[k] = sum(a[i]*b[j]); i|j=k
**/


#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define bitwiseXOR 1
///#define bitwiseAND 2
///#define bitwiseOR 3

void FWHT(vector< LL >&p, bool inverse)
{
    int n = p.size();
    assert((n&(n-1))==0);

    for (int len = 1; 2*len <= n; len <<= 1) {
        for (int i = 0; i < n; i += len+len) {
            for (int j = 0; j < len; j++) {
                LL u = p[i+j];
                LL v = p[i+len+j];

                #ifdef bitwiseXOR
                p[i+j] = u+v;
                p[i+len+j] = u-v;
                #endif // bitwiseXOR

                #ifdef bitwiseAND
                if (!inverse) {
                    p[i+j] = v;
                    p[i+len+j] = u+v;
                } else {
                    p[i+j] = -u+v;
                    p[i+len+j] = u;
                }
                #endif // bitwiseAND

                #ifdef bitwiseOR
                if (!inverse) {
                    p[i+j] = u+v;
                    p[i+len+j] = u;
                } else {
                    p[i+j] = v;
                    p[i+len+j] = u-v;
                }
                #endif // bitwiseOR
            }
        }
    }

    #ifdef bitwiseXOR
    if (inverse) {
        for (int i = 0; i < n; i++) {
            assert(p[i]%n==0);
            p[i] /= n;
        }
    }
    #endif // bitwiseXOR
}


int main()
{
    vector< LL >p(4);
    p[0] = 2;   p[1] = 4;   p[2] = 6;   p[3] = 8;
    vector< LL >q(4);
    q[0] = 3;   q[1] = 5;   q[2] = 7;  q[3] = 9;

    FWHT(p, false);
    FWHT(q, false);

    vector< LL >r(4);
    for (int i = 0; i < 4; i++) r[i] = p[i]*q[i];

    FWHT(r, true);
    for (int i = 0; i < 4; i++) {
        cout << "r[" << bitset<2>(i) << "] = " << r[i] << endl;
    }

    return 0;
}
