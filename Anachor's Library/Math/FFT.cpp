#include<bits/stdc++.h>
using namespace std;

struct CD {
    double x, y;
    CD(double x=0, double y=0) :x(x), y(y) {}
    CD operator+(const CD& o) { return {x+o.x, y+o.y};}
    CD operator-(const CD& o) { return {x-o.x, y-o.y};}
    CD operator*(const CD& o) { return {x*o.x-y*o.y, x*o.y+o.x*y};}
    CD operator/(double d)    { return {x/d, y/d};}
};

typedef long long LL;
const double PI = acos(-1);

namespace FFT {
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
            CD factor = {cos(angle), sin(angle)};

            for (int i=0; i<N; i+=len) {
                CD w(1);
                for (int j=0; j<len/2; j++) {
                    CD x = v[i+j], y = w * v[i+j+len/2];
                    v[i+j] = x+y;
                    v[i+j+len/2] = x-y;
                    w = w*factor;
                }
            }
        }
        if (invert)
            for (CD &x : v) x=x/N;
    }

    vector<LL> multiply(const vector<LL> &a, const vector<LL> &b) {
        vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());

        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        fa.resize(n);
        fb.resize(n);

        fft(fa);
        fft(fb);
        for (int i=0; i<n; i++) fa[i] = fa[i] * fb[i];
        fft(fa, true);

        vector<LL> ans(n);
        for (int i=0; i<n; i++)
            ans[i] = round(fa[i].x);
        return ans;
    }
}

const int N = 1e6+7;
int ans[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, x, y;
    cin>>n>>x>>y;

    vector<LL> a(x+1), b(x+1);
    for (int i=0; i<=n; i++) {
        int z;
        cin>>z;
        a[z] = b[x-z] = 1;
    }

    a = FFT::multiply(a, b);
    for (int i=x+1; i<=2*x; i++) {
        if (a[i] == 0)  continue;
        int z = i-x+y;
        for (int k=z; k<N; k+=z)    ans[k] = z;
    }

    int q;
    cin>>q;

    while (q--) {
        int x;
        cin>>x;
        int res = ans[x/2]*2;
        if (res == 0)   res--;
        cout<<res<<"\n";
    }
}
