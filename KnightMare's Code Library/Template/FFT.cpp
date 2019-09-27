/**
Iterative Implementation of Discrete Fast Fourier Transform
Complexity: O(N log N)

Possible Optimizations:
1. Remove leading zeros (No, seriously!!!!)
2. Writing a custom complex class reduces runtime.
3. If there are multiple testcases of similar sizes, it
   might be faster to precalculate the roots of unity.
**/

#include<bits/stdc++.h>
using namespace std;

typedef complex<double> CD;
typedef long long LL;
const double PI = acos(-1);

struct FFT
{
    int N;
    vector<int> perm;

    void precalculate() {
        perm.resize(N);
        perm[0] = 0;

        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }
    }

    void fft(vector<CD> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N&(N-1)) == 0);
            precalculate();
        }

        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int len = 2; len <= N; len <<= 1) {
            double angle = 2 * PI / len;
            if (invert) angle = -angle;
            CD factor = polar(1.0, angle);

            for (int i=0; i<N; i+=len) {
                CD w(1);
                for (int j=0; j<len/2; j++) {
                    CD x = v[i+j], y = w * v[i+j+len/2];
                    v[i+j] = x+y;
                    v[i+j+len/2] = x-y;
                    w *= factor;
                }
            }
        }
        if (invert)
            for (CD &x : v) x/=N;
    }

    vector<LL> multiply(const vector<LL> &a, const vector<LL> &b) {
        vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());

        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        fa.resize(n);
        fb.resize(n);

        fft(fa);
        fft(fb);
        for (int i=0; i<n; i++) fa[i] *= fb[i];
        fft(fa, true);

        vector<LL> ans(n);
        for (int i=0; i<n; i++)
            ans[i] = round(fa[i].real());
        return ans;
    }
};

///Solves SPOJ POLYMUL
///Given two polynomials, find their product

int main()
{
    int t;
    cin>>t;
    FFT fft;

    while (t--)
    {
        int n;
        cin>>n;

        vector<LL> a(n+1), b(n+1), ans;
        for (int i=0; i<=n; i++)    cin>>a[n-i];
        for (int i=0; i<=n; i++)    cin>>b[n-i];

        ans = fft.multiply(a, b);

        for (int i=2*n; i>=0; i--)
            cout<<ans[i]<<" ";
        cout<<endl;
    }
}
