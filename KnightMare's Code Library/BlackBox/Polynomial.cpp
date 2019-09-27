#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 1000000007;

inline LL Power(LL b, LL p) {
    LL ret = 1;
    while(p--) {
        ret *= b;
        ret %= MOD;
    }
    return ret;
}

inline vector <int> getSequence(LL n, LL c, LL k) {
    vector <int> sequence;
    LL ans=0, fib[n*c+3];
    fib[0] = 0;
    fib[1] = 1;
    for(LL i=2; i<=n*c; i++) {
        fib[i] = fib[i-1] + fib[i-2];
        if(fib[i] >= MOD) fib[i] -= MOD;
    }
    for(LL i=0; i<=n; i++) {
        ans += Power(fib[i*c], k);
        if(ans >= MOD) ans -= MOD;
        sequence.push_back((int)ans);
    }
    return sequence;
}

#define MAX 65536
#define MOD 1000000007 /// MOD must be prime and greater than 2
#define MOD_THRESHOLD 18 /// MOD * MOD * MOD_THRESHOLD < 2^64
#define clr(ar) memset(ar, 0, sizeof(ar))

namespace pol{ /// Polynomial namespace
    unsigned long long temp[128];
    int ptr = 0, A[MAX * 2], B[MAX * 2], buffer[MAX * 6];

    /// Use faster multiplication techniques if required
    void karatsuba(int n, int *a, int *b, int *res){ /// hash = 829512
        int i, j, h;
        if (n < 17){
            for (i = 0; i < (n + n); i++) temp[i] = 0;
            for (i = 0; i < n; i++){
                if (a[i]){
                    for (j = 0; j < n; j++){
                        temp[i + j] += ((long long)a[i] * b[j]);
                    }
                }
            }
            for (i = 0; i < (n + n); i++) res[i] = temp[i] % MOD;
            return;
        }

        h = n >> 1;
        karatsuba(h, a, b, res);
        karatsuba(h, a + h, b + h, res + n);
        int *x = buffer + ptr, *y = buffer + ptr + h, *z = buffer + ptr + h + h;

        ptr += (h + h + n);
        for (i = 0; i < h; i++){
            x[i] = a[i] + a[i + h], y[i] = b[i] + b[i + h];
            if (x[i] >= MOD) x[i] -= MOD;
            if (y[i] >= MOD) y[i] -= MOD;
        }

        karatsuba(h, x, y, z);
        for (i = 0; i < n; i++) z[i] -= (res[i] + res[i + n]);
        for (i = 0; i < n; i++){
            res[i + h] = (res[i + h] + z[i]) % MOD;
            if (res[i + h] < 0) res[i + h] += MOD;
        }
        ptr -= (h + h + n);
    }

    int mul(int n, int *a, int m, int *b){ /// hash = 903808
        int i, r, c = (n < m ? n : m), d = (n > m ? n : m), *res = buffer + ptr;
        r = 1 << (32 - __builtin_clz(d) - (__builtin_popcount(d) == 1));
        for (i = d; i < r; i++) a[i] = b[i] = 0;
        for (i = c; i < d && n < m; i++) a[i] = 0;
        for (i = c; i < d && m < n; i++) b[i] = 0;

        ptr += (r << 1), karatsuba(r, a, b, res), ptr -= (r << 1);
        for (i = 0; i < (r << 1); i++) a[i] = res[i];
        return (n + m - 1);
    }

    inline void copy(int* to, const int* from, int n){
        memcpy(to, from, n * sizeof(int));
    }

    inline void add(int* res, const int* P, int pn, const int* Q, int qn){
        for (int i = 0; i < qn; i++){
            res[i] = P[i] + Q[i];
            if (res[i] >= MOD) res -= MOD;
        }
        copy(res + qn, P + qn, pn - qn);
    }

    inline void subtract(int* res, const int* P, int pn, const int* Q, int qn){
        for(int i = 0; i < qn; ++ i){
            res[i] = P[i] - Q[i];
            if (res[i] < 0) res[i] += MOD;
        }
        copy(res + qn, P + qn, pn - qn);
    }

    inline void shift(int* res, const int* P, int n, int k){
        for (int i = 0; i < n; i++) res[i] = ((long long)P[i] << k) % MOD;
    }

    inline void reverse_poly(int* res, const int* P, int n){
        if (&res[0] == &P[0]) reverse(res, res + n);
        else{
            for (int i = 0; i < n; i++) res[n - i - 1] = P[i];
        }
    }

    struct polynomial{
        vector <int> coefficient;

        polynomial(){}
        polynomial(int c0) : coefficient(1, c0){}
        polynomial(int c0, int c1) : coefficient(2) {coefficient[0] = c0, coefficient[1] = c1;}

        inline void resize(int n){
            coefficient.resize(n);
        }

        inline int* data(){
            return coefficient.empty() ? 0 : &coefficient[0];
        }

        inline const int* data() const{
            return coefficient.empty() ? 0 : &coefficient[0];
        }

        inline int size() const{
            return coefficient.size();
        }

        inline void set(int i, int x){
            if (size() <= i) resize(i + 1);
            coefficient[i] = x;
        }

        inline void normalize(){
            while (size() && coefficient.back() == 0) coefficient.pop_back();
        }

        static void multiply(polynomial &res, const polynomial& p, const polynomial& q){ /// hash = 569213
            if(&res == &p || &res == &q){
                polynomial temp;
                multiply(temp, p, q);
                res = temp;
                return;
            }

            res.coefficient.clear();
            if (p.size() != 0 && q.size() != 0){
                int i, j, l, n = 0, m = 0;
                for (i = 0; i < p.size(); i++) A[n++] = p.coefficient[i];
                for (i = 0; i < q.size(); i++) B[m++] = q.coefficient[i];

                l = mul(n, A, m, B);
                for (i = 0; i < l; i++) res.coefficient.push_back(A[i]);
            }
        }

        polynomial inverse(int n) const{
            polynomial res(n);
            res.resize(n);
            find_inverse(res.data(), n, data(), size());
            return res;
        }

        /// hash = 190805
        static void divide(polynomial &quot, polynomial &rem, const polynomial &p, const polynomial &q, const polynomial &inv) {
            int pn = p.size(), qn = q.size();
            quot.resize(max(0, pn - qn + 1)), rem.resize(qn - 1);
            divide_remainder_inverse(quot.data(), rem.data(), p.data(), pn, q.data(), qn, inv.data());
            quot.normalize(), rem.normalize();
        }

        polynomial remainder(const polynomial &q, const polynomial &inv) const{
            polynomial quot, rem;
            divide(quot, rem, *this, q, inv);
            return rem;
        }

        polynomial power(const polynomial &q, long long k) const{ /// hash = 556205
            int qn = q.size();
            if(qn == 1) return polynomial();
            if(k == 0) return polynomial(1);
            polynomial inv = q.inverse(max(size() - qn + 1, qn));
            polynomial p = this->remainder(q, inv);

            polynomial res = p;
            int l = 63 - __builtin_clzll(k);

            for(--l; l >= 0; --l){
                multiply(res, res, res);
                res = res.remainder(q, inv);
                if((k >> l) & 1){
                    multiply(res, res, p);
                    res = res.remainder(q, inv);
                }
            }
            return res;
        }

        static void multiply(int* res, const int* P, int pn, const int* Q, int qn);

        static void inverse_power_series(int* res, int res_n, const int* P, int pn);
        static void find_inverse(int* res, int res_n, const int* P, int pn);

        static void divide_inverse(int* res, int res_n, const int* revp, int pn, const int* inv);
        static void divide_remainder_inverse(int* quot, int* rem, const int* P, int pn, const int* Q, int qn, const int* inv);
    };

    void polynomial::multiply(int* res, const int* P, int pn, const int* Q, int qn){ /// hash = 25722
        polynomial P1, P2, P_res;
        for (int i = 0; i < pn; i++) P1.coefficient.push_back(P[i]);
        for (int i = 0; i < qn; i++) P2.coefficient.push_back(Q[i]);
        P_res.multiply(P_res, P1, P2);
        for (int i = 0; i < P_res.coefficient.size(); i++) res[i] = P_res.coefficient[i];
    }

    void polynomial::inverse_power_series(int* res, int res_n, const int* P, int pn){ /// hash = 553608
        if(res_n == 0) return;
        unique_ptr <int[]> ptr(new int[res_n * sizeof(int)]);
        int* u = ptr.get(), *v = u + res_n * 2, cur = 1, nxt = 1;

        clr(res);
        res[0] = P[0];
        while (cur < res_n){
            nxt = min(res_n, cur * 2);
            multiply(u, res, cur, res, cur);
            multiply(v, u, min(nxt, cur * 2 - 1), P, min(nxt, pn));
            shift(res, res, cur, 1);
            subtract(res, res, nxt, v, nxt);
            cur = nxt;
        }
    }

    void polynomial::find_inverse(int* res, int res_n, const int* P, int pn){
        unique_ptr <int[]> ptr(new int[pn]);
        int* tmp = ptr.get();
        reverse_poly(tmp, P, pn);
        inverse_power_series(res, res_n, tmp, pn);
    }

    void polynomial::divide_inverse(int* res, int res_n, const int* revp, int pn, const int* inv){
        unique_ptr <int[]> ptr(new int[pn + res_n]);
        int* tmp = ptr.get();
        multiply(tmp, revp, pn, inv, res_n);
        reverse_poly(res, tmp, res_n);
    }

    /// hash = 203864
    void polynomial::divide_remainder_inverse(int* quot, int* rem, const int* P, int pn, const int* Q, int qn, const int* inv){
        if(pn < qn){
            copy(rem, P, pn);
            for (int i = 0; i < qn - pn - 1; i++) rem[i + pn] = 0;
            return;
        }

        if(qn == 1) return;
        int quot_n = pn - qn + 1;
        int rn = qn - 1, tn = min(quot_n, rn), un = tn + rn;
        unique_ptr <int[]> ptr(new int[pn + un + (quot != 0 ? 0 : quot_n)]);

        int* revp = ptr.get(), *qmul = revp + pn;
        if(quot == 0) quot = qmul + un;
        reverse_poly(revp, P, pn);
        divide_inverse(quot, quot_n, revp, pn, inv);
        multiply(qmul, Q, rn, quot, tn);
        subtract(rem, P, rn, qmul, rn);
    }
}

namespace bbl{ /// Black box linear algebra
    using namespace pol;

    int mod_inverse(int x){
        int u = 1, v = 0, t = 0, a = x, b = MOD;
        while (b){
            t = a / b;
            a -= (t * b), u -= (t * v);
            swap(a, b), swap(u, v);
        }
        return (u + MOD) % MOD;
    }

    int convolution(const int* A, const int* B, int n){
        int i = 0, j = 0;
        unsigned long long res = 0;
        for (i = 0; (i + MOD_THRESHOLD) <= n; res %= MOD){
            for (j = 0; j < MOD_THRESHOLD; j++, i++) res += (unsigned long long)A[i] * B[i];
        }

        for (j = 0; i < n; i++) res += (unsigned long long)A[i] * B[i];
        return res % MOD;
    }

    /// Berlekamp Massey algorithm in O(n ^ 2)
    /// Finds the shortest linear recurrence that will generate the sequence S and returns it in C
    /// S[i] * C[l - 1] + S[i + 1] * C[l - 2] + ... + S[j] * C[0] = 0

    int berlekamp_massey(vector <int> S, vector <int>& C){ /// hash = 768118
        assert((S.size() % 2) == 0);

        int n = S.size();
        C.assign(n + 1, 0);
        vector <int> T, B(n + 1, 0);
        reverse(S.begin(), S.end());

        C[0] = 1, B[0] = 1;
        int i, j, k, d, x, l = 0, m = 1, b = 1, deg = 0;

        for (i = 0; i < n; i++){
            d = S[n - i - 1];
            if (l > 0) d = (d + convolution(&C[1], &S[n - i], l)) % MOD;
            if (d == 0) m++;
            else{
                if (l * 2 <= i) T.assign(C.begin(), C.begin() + l + 1);
                x = (((long long)mod_inverse(b) * (MOD - d)) % MOD + MOD) % MOD;

                for (j = 0; j <= deg; j++){
                    C[m + j] = (C[m + j] + (unsigned long long)x * B[j]) % MOD;
                }
                if (l * 2 <= i){
                    B.swap(T);
                    deg = B.size() - 1;
                    b = d, m = 1, l = i - l + 1;
                }
                else m++;
            }
        }

        C.resize(l + 1);
        return l;
    }

    vector <int> recurrence_coefficients(const vector <int>& recurrence, long long k){ /// hash = 713914
        polynomial p, res;
        int n = recurrence.size();

        p.resize(n + 1), p.set(n, 1);
        for (int i = 0; i < n; i++) p.set(i, recurrence[i]);

        vector <int> v;
        res = polynomial(0, 1).power(p, k);
        for (int i = 0; i < n && i < res.size(); i++) v.push_back(res.coefficient[i]);
        return v;
    }

    vector <int> interpolate(const vector<int> &base_sequence, const vector<int> &polynomial, long long k, int n){ /// hash = 347802
        int i, j, len = polynomial.size() - 1;
        vector <int> recurrence(len);
        for (i = 0; i < len; i++) recurrence[i] = polynomial[i];
        vector <int> coefficient = recurrence_coefficients(recurrence, k);

        vector <int> res;
        len = min(len, (int)coefficient.size());
        len = min(len, (int)base_sequence.size());
        for (j = 0; j < n; j++){
            long long r = 0;
            for (i = 0; i < len; i++){
                assert((i + j) < base_sequence.size());
                r = (r + (long long)coefficient[i] * base_sequence[i + j]) % MOD;
            }
            res.push_back(r);
        }
        return res;
    }
}

/// Returns consecutive n terms of the recurrence starting from the k'th term
/// MOD must be prime and greater than 2
/// 0.5s for n <= 4000, 4.25s for n <= 16000

vector <int> interpolate(vector <int>& recurrence, long long k, int n){
    using namespace bbl;
    assert(recurrence.size() && (recurrence.size() % 2) == 0);

    vector <int> polynomial;
    int l = berlekamp_massey(recurrence, polynomial);
	reverse(polynomial.begin(), polynomial.begin() + l + 1);
    return interpolate(recurrence, polynomial, k, n);
}

/// Returns the k'th term of the recurrence

int interpolate(vector <int>& recurrence, long long k){
    vector <int> res = interpolate(recurrence, k, 1);
    return res[0];
}

const int SEQ_LIM = 69;
inline LL solve(LL n, LL c, LL k) {
    auto sequence = getSequence(SEQ_LIM, c, k);
    if(n <= SEQ_LIM) return sequence[n];
    return interpolate(sequence, n);
}

int main() {
//    assert(freopen("input.txt", "r", stdin));
//    assert(freopen("alter_out.txt", "w", stdout));

    clock_t st = clock();

    int test, kase=1;
    LL n, c, k;

    assert(scanf("%d", &test) == 1);
    while(test--) {
        assert(scanf("%lld %lld %lld", &n, &c, &k) == 3);
        printf("Case %d: %lld\n", kase++, solve(n, c, k));
    }

    clock_t en = clock();
    fprintf(stderr, "%0.3f sec\n", (double)(en-st)/(double)CLOCKS_PER_SEC);

    return 0;
}
