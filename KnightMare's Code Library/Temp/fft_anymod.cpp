/**
Iterative Implementation of Discrete Fast Fourier Transform
Can Handle any mod that fits in int
Complexity: O(N log N)

Possible Optimizations:
1. Remove leading zeros (No, seriously!!!!)
2. Writing a custom complex class reduces runtime.
3. If there are multiple testcases of similar sizes, it
   might be faster to precalculate the roots of unity.
4. If mod is < 2^26 use RT = 13 and comment out long double
**/

#include<bits/stdc++.h>
#define double long double
using namespace std;

typedef complex<double> CD;
typedef long long LL;
const double PI = acos(-1);

const int RT = 16;
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
            CD factor = polar(1.0L, angle);

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

    vector<LL> multiply(const vector<LL> &a, const vector<LL> &b, int M) {
        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        vector<CD> al(n), ar(n), bl(n), br(n);

        for (int i=0; i<a.size(); i++) {
            LL k = a[i]%M;
            al[i] = k >> RT;
            ar[i] = k & ((1<<RT)-1);
        }

        for (int i=0; i<b.size(); i++) {
            LL k = b[i]%M;
            bl[i] = k >>RT;
            br[i] = k & ((1<<RT)-1);
        }

        fft(al); fft(ar);
        fft(bl); fft(br);

        for (int i=0; i<n; i++) {
            CD ll = (al[i] * bl[i]);
            CD lr = (al[i] * br[i]);
            CD rl = (ar[i] * bl[i]);
            CD rr = (ar[i] * br[i]);
            al[i] = ll; ar[i] = lr;
            bl[i] = rl; br[i] = rr;
        }

        fft(al, true); fft(ar, true);
        fft(bl, true); fft(br, true);

        vector<LL> ans(n);
        for (int i=0; i<n; i++) {
            LL right = round(br[i].real());
            right %= M;
            LL mid = round(round(bl[i].real()) + round(ar[i].real()));
            mid = ((mid%M)<<RT)%M;
            LL left = round(al[i].real());
            left = ((left%M)<<(2*RT))%M;
            ans[i] = (left+mid+right)%M;
        }
        return ans;
    }
};

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

        ans = fft.multiply(a, b, 1e9+7);

        for (int i=2*n; i>=0; i--)
            cout<<ans[i]<<" ";
        cout<<endl;
    }
}
