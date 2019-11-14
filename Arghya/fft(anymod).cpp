//fft with any mod
//be careful in choosing MAXN , it should be double of next power of 2 of your needed n
//example, here n is 131072 = 2^17 , so MAXN is 2^19 ( double of 2^18 )
// if n was 10, then MAXN = 32 suffices


#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define sf scanf
#define pf printf
#define pb push_back
#define mp make_pair
#define PI ( acos(-1.0) )
#define IN freopen("dichromatic.in","r",stdin)
#define OUT freopen("dichromatic.out","w",stdout)
#define FOR(i,a,b) for(i=a ; i<=b ; i++)
#define DBG pf("Hi\n")
#define INF 1000000000
#define i64 long long int
#define eps (1e-8)
#define xx first
#define yy second
#define ln 17
#define off 2
#define sq(x)  ((x)*(x))

using namespace __gnu_pbds;
using namespace std ;

typedef tree< i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef pair<i64, i64> pii;

#define MAX 131073
#define MAXN 524288
#define MOD 258280327
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace fft{
    int len, last = -1, step = 0, rev[MAXN];

	struct complx{
        double real, img;

        inline complx(){
            real = img = 0.0;
        }

        inline complx conjugate(){
            return complx(real, -img);
        }

        inline complx(double x){
            real = x, img = 0.0;
        }

        inline complx(double x, double y){
            real = x, img = y;
        }

        inline complx operator + (complx other){
            return complx(real + other.real, img + other.img);
        }

        inline complx operator - (complx other){
            return complx(real - other.real, img - other.img);
        }

        inline complx operator * (complx other){
            return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
        }
    } u[MAXN], v[MAXN], f[MAXN], g[MAXN], dp[MAXN];

    void build(int& a, int *A, int& b, int* B){
        while (a > 1 && A[a - 1] == 0) a--;
        while (b > 1 && B[b - 1] == 0) b--;

	    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
        for (int i = a; i < len; i++) A[i] = 0;
        for (int i = b; i < len; i++) B[i] = 0;

		if (!step++){
            dp[1] = complx(1);
            for (int i = 1; (1 << i) < MAXN; i++){
                double theta = (2.0 * acos(0.0)) / (1 << i);
                complx mul = complx(cos(theta), sin(theta));

                int lim = 1 << i;
                for (int j = lim >> 1; j < lim; j++){
                    dp[2 * j] = dp[j];
                    dp[2 * j + 1] = dp[j] * mul;
                }
            }
        }

        if (last != len){
            last = len;
            int bit = (32 - __builtin_clz(len) - (__builtin_popcount(len) == 1));
            for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (bit - 1));
        }
	}

	void transform_unrolled(complx *in, complx *out, complx* ar){
	    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
	    for (int k = 1; k < len; k <<= 1){
            for (int i = 0; i < len; i += (k << 1)){
                complx z, *a = out + i, *b = out + i + k, *c = ar + k;
                if (k == 1){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }

                for (int j = 0; j < k && k > 1; j += 2, a++, b++, c++){
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                    a++, b++, c++;
                    z = (*b) * (*c);
                    *b = *a - z, *a = *a + z;
                }
            }
	    }
	}

	bool equals(int a, int* A, int b, int* B){
        if (a != b) return false;
        for (a = 0; a < b && A[a] == B[a]; a++){}
        return (a == b);
	}

	int mod_multiply(int a, int* A, int b, int* B, int mod){
	    build(a, A, b, B);
	    int flag = equals(a, A, b, B);
	    for (int i = 0; i < len; i++) A[i] %= mod, B[i] %= mod;
	    for (int i = 0; i < len; i++) u[i] = complx(A[i] & 32767, A[i] >> 15);
	    for (int i = 0; i < len; i++) v[i] = complx(B[i] & 32767, B[i] >> 15);

		transform_unrolled(u, f, dp);
		for (int i = 0; i < len; i++) g[i] = f[i];
		if (!flag) transform_unrolled(v, g, dp);

		for (int i = 0; i < len; i++){
            int j = (len - 1) & (len - i);
            complx c1 = f[j].conjugate(), c2 = g[j].conjugate();

            complx a1 = (f[i] + c1) * complx(0.5, 0);
			complx a2 = (f[i] - c1) * complx(0, -0.5);
			complx b1 = (g[i] + c2) * complx(0.5 / len, 0);
			complx b2 = (g[i] - c2) * complx(0, -0.5 / len);
			v[j] = a1 * b2 + a2 * b1;
			u[j] = a1 * b1 + a2 * b2 * complx(0, 1);
		}
		transform_unrolled(u, f, dp);
		transform_unrolled(v, g, dp);

        long long x, y, z;
		for (int i = 0; i < len; i++){
            x = f[i].real + 0.5, y = g[i].real + 0.5, z = f[i].img + 0.5;
            A[i] = (x + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
		}
		return a + b - 1;
	}
}

int black[17][MAXN] , red[17][MAXN] , ans[MAXN] ;
int dp[MAXN] ;

int main()
{
    IN ;
    OUT ;
    black[0][0] = 1 ; red[0][0] = 1 ; red[0][1] = 1 ;
    black[1][1] = 1 ; black[1][2] = 2 ; black[1][3] = 1 ;
    red[1][3] = 1 ; red[1][4] = 4 ; red[1][5] = 6 ; red[1][6] = 4 ; red[1][7] = 1 ;

    for(int i=2;  i<=16 ; i++)
    {
     //   printf("%d\n",i) ;
        for(int j=0 ; j<MAX ; j++) dp[j] = (red[i-1][j]+black[i-1][j])%MOD ;
        fft::mod_multiply(MAX,dp,MAX,dp,MOD) ;
        for(int j=1 ; j<MAX ; j++) black[i][j] = dp[j-1] ;
        for(int j=0 ; j<MAX ; j++) dp[j] = black[i][j] ;
        fft::mod_multiply(MAX,dp,MAX,dp,MOD) ;
        for(int j=0 ; j<MAX ; j++) red[i][j] = dp[j-1] ;
 //       for(int j=0 ; j<10 ; j++) printf("%d: %d %d\n",j,black[i][j],red[i][j]) ;
    }

    int t , h ;
    scanf("%d %d",&t,&h) ;

    for(int i=0 ; i<MAX ; i++)
    {
        for(int j=0 ; j<=h ; j++) ans[i] = (ans[i] + black[j][i]+red[j][i])%MOD ;
        ans[i] = (ans[i]%MOD + MOD)%MOD ;
    }

    for(int i=0 ; i<t ; i++)
    {
        int n ;
        scanf("%d",&n) ;
        printf("%d\n",ans[n] ) ;
    }

    return 0 ;
}