#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
#define M 1000005

constexpr uint64_t mod = (1ull<<61) - 1;
uint64_t modmul(uint64_t a, uint64_t b){
	uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	uint64_t ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod) + (ret>>61);
	ret = (ret & mod) + (ret>>61);
	return ret-1;
}
uint64_t modsum(uint64_t a, uint64_t b){
	ull x = a+b;
	if(a+b >= mod) x -= mod;
	return x;
}
uint64_t doMod(ull x)
{
    if(x >= mod) x -= mod;
    return x;
}

const ll B1 = 104723;
const ll B2 = 104729;
const ll MOD1 = 1000000007;
const ll MOD2 = 100000007;

ll pb1[M], pb2[M];

void init()
{
    pb1[0] = pb2[0] = 1;
    for(int i = 1; i < M; i++) pb1[i] = (pb1[i-1]*B1)%MOD1, pb2[i] = (pb2[i-1]*B2)%MOD2;
}

struct myHash
{
    ll h1, h2;

    myHash(): h1(0), h2(0) {}
    myHash(ll h1, ll h2): h1(h1%MOD1), h2(h2%MOD2) {}
    myHash add(ll v1, ll v2) { return myHash(h1*B1+v1, h2*B2+v2); }
    myHash operator-(const myHash& rhs) { return myHash(h1-rhs.h1+MOD1, h2-rhs.h2+MOD2); }
    bool operator==(const myHash& rhs) const { return make_pair(h1, h2) == make_pair(rhs.h1, rhs.h2); }
    bool operator<(const myHash& rhs) const { return make_pair(h1, h2) < make_pair(rhs.h1, rhs.h2); }
};

ostream& operator<<(ostream& dout, myHash h)
{
    return dout<<"h1 = "<<h.h1<<", h2 = "<<h.h2;
}

vector<myHash> getAll(string str)
{
    int n = str.size();
    vector<myHash>ans(n);

    myHash h;
    for(int i = 0; i < str.size(); i++) h = h.add(str[i], str[i]), ans[i] = h;

    return ans;
}

myHash getTot(string str)
{
    if(str.size() == 0) return myHash();

    vector<myHash>shob = getAll(str);
    return shob[shob.size()-1];
}

myHash getRange(const vector<myHash>& shob, int l, int r)
{
    myHash lft = l? shob[l-1]: myHash();
    myHash rht = shob[r];

    lft = myHash(lft.h1*pb1[r-l+1], lft.h2*pb2[r-l+1]);
    return rht-lft;
}

struct gpHash
{
    ll operator()(myHash h) const { return h.h1*1000000000+h.h2; } // return h.h1^1023240101 in case of single hashing
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();

    gp_hash_table<myHash, int, gpHash>ma;

    return 0;
}

