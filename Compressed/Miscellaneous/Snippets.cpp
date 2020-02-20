/// Random
mt19937_64 rng(chrono::steady_clock
              ::now().time_since_epoch().count());
shuffle(V.begin(), V.end(), rng);
int x = uniform_int_distribution<int>(l, r)(rng);

/// bit manipulation
number of leading zeros: __builtin_clz(x)
number of trailing zeros: __builtin_ctz(x)
number of set bits : __builtin_popcountll(x)
bitset : bs._Find_first(),bs._Find_next(15)

///subset(3^n)
for(int i = mask; i > 0; i = ((i-1) & mask))

/// ordered set
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree <int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update > ordered_set;
  find_by_order(k): itr to kth largest 0 indexed
  order_of_key(val): no of items in set < val

/// 2D Partial Sum : update (x1,y1) to (x2,y2) +x
a[x1][y1]+=x; a[x1][y2+1]-=x;
a[x2+1][y1]-=x;a[x2+1][y2+1]+=x;
recons: a[x][y] += a[x-1][y]+a[x][y-1]-a[x-1][y-1]

/// __int128:
__int128 x = 1e12; x = x * x + 1000;
while(x) {res.pb(x%10 + '0'); x/= 10;}

/// split a string by space
string str="abc def  gh",buf;stringstream ss(str);
while(ss >> buf) cout << buf << endl;

/// ntt mod :
998244353 = 119 * 2^23 + 1 , primitive root = 3
985661441 = 235 * 2^22 + 1 , primitive root = 3
1012924417 = 483 * 2^21 + 1 , primitive root = 5

/// MO on tree
case-1: lca(u,v) == u , [ST(u), ST(v)]
case-2: otherws, [EN(u), ST(v)]+[ST(lca), ST(lca)]
