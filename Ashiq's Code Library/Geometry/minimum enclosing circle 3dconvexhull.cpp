#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <complex>
#include <utility>
#include <cctype>
#include <list>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define FORALL(i,a,b) for(int i=(a);i<=(b);++i)
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FORB(i,a,b) for(int i=(a);i>=(b);--i)

typedef long long ll;
typedef long double ld;

typedef pair<ll,int> plli;
typedef pair<int,int> pii;
typedef map<int,int> mii;

#define pb push_back
#define mp make_pair

#define EPS (1e-8)
#define MAXN 1005
#define sign(x) (((x)>EPS)-((x)<(-EPS)))

const ld PI = atan2(0,-1);

// 3d vector (can degenerate to 2d when z=0)
#define T ld
struct vec {
  T x,y,z;    //coordinates/data
  vec(T xx, T yy, T zz=0.){ x=xx;y=yy;z=zz; }
  vec() { x=y=z=0;}

  // vector ops
  vec& operator=(const vec& b) { x=b.x; y=b.y; z=b.z; return *this; }
  vec operator+(const vec& b) const { return vec(x+b.x, y+b.y, z+b.z); }
  vec operator-(const vec& b) const { return vec(x-b.x, y-b.y, z-b.z); }
  T operator*(const vec& b) const { return x*b.x + y*b.y + z*b.z; }
  vec operator^(const vec& b) const { return vec(y*b.z - z*b.y,
                                           z*b.x - x*b.z,
                                           x*b.y - y*b.x); }
  // scalar mult
  vec operator*(T k) const { return vec(x*k,y*k,z*k); }
  vec operator/(T k) const { return vec(x/k,y/k,z/k); }
  vec operator-() const { return vec(-x,-y,-z); }  // negation

  T sqlen() const { return (*this) * (*this); }

  bool operator<(const vec& other) const {
    if (x < other.x) return true;
    if (x > other.x) return false;
    if (y < other.y) return true;
    if (y > other.y) return false;
    if (z < other.z) return true;
    if (z > other.z) return false;
    return false;
  }
};
vec operator*(T k, vec v) { return v*k; }
ostream& operator<<(ostream& out, const vec& v) {
  return out << "(" << v.x << "," << v.y << "," << v.z <<")";
}
#undef T

#define INSIDE (-1)
#define ON (0)
#define OUTSIDE (1)

typedef vector<vec> edge;
typedef vector<vec> face;
typedef vector<face> hull;

bool eq(ld a, ld b) {
  return abs(b-a) <= EPS;
}

ld len(vec a) {
  return sqrtl(a.sqlen());
}

int side(vec a, vec b, vec c, vec x) {
  vec norm = (b-a) ^ (c-a);
  vec me = x-a;
  return sign(me * norm);
}

bool is_colinear(vec a, vec b, vec c) {
  vec u = b-a, v = c-a;
  vec w = u^v;
  return eq(w.sqlen(),0);
}

vec projection(vec a, vec b, vec c, vec x) {
  if (side(a,b,c,x) == ON) return x;
  vec norm = (b-a) ^ (c-a);
  vec ans = x - norm * ((norm * (x-a)) / (norm * norm));
  assert(side(a,b,c,ans) == ON);
  return ans;
}

/// O(n^2log(n))

hull find_hull(vec* P, int N) {
  random_shuffle(P, P+N);

  // Find 4 non-degenerate points (make a tetrahedron)
  FORALL(j,2,N-1) if (!is_colinear(P[0],P[1],P[j])) { swap(P[j], P[2]); break; }
  FORALL(j,3,N-1) if (side(P[0],P[1],P[2],P[j]) != 0) { swap(P[j], P[3]); break; }

  // Canonicalize them
  if (side(P[0],P[1],P[2],P[3]) == OUTSIDE) swap(P[0], P[1]);
  assert(side(P[0],P[1],P[2],P[3]) == INSIDE);
  assert(side(P[0],P[3],P[1],P[2]) == INSIDE);
  assert(side(P[0],P[2],P[3],P[1]) == INSIDE);
  assert(side(P[3],P[2],P[1],P[0]) == INSIDE);

  hull H{
    {P[0],P[1],P[2]},
    {P[0],P[3],P[1]},
    {P[0],P[2],P[3]},
    {P[3],P[2],P[1]}
  };

  auto make_degrees = [&](const hull& H) {
    map<edge,int> ans;
    for (const auto & f : H) {
      assert(f.size() == 3);
      FOR(i,3) {
        vec a = f[i];
        vec b = f[(i+1)%3];
        ans[{a,b}]++;
      }
    }

    return ans;
  };

  // incrementally add points
  FORALL(j,4,N-1) {
    hull H2; H2.reserve(H.size());
    vector<face> plane;

    for (const auto & f : H) {
      int s = side(f[0],f[1],f[2],P[j]);
      if (s == INSIDE || s == ON) H2.pb(f);
    }

    // For any edge that now only has 1 incident face (it's other face deleted)
    // add a new face with this vertex and that edge.
    map<edge, int> D = make_degrees(H2);
    const auto tmp = H2;
    for (const auto & f : tmp) {
      assert(f.size() == 3);
      FOR(i,3) {
        vec a = f[i];
        vec b = f[(i+1)%3];
        int d = D[{a,b}] + D[{b,a}];
        assert(d == 1 || d == 2);
        if (d==1) {
          // add a new face
          H2.pb({a, P[j], b});
        }
      }
    }

    H = H2;
  }

  // sanity check that this is at least mostly a hull :)
  for (const auto & f : H) {
    FOR(i,N) {
      int s = side(f[0],f[1],f[2],P[i]);
      assert(s == INSIDE || s == ON);
    }
  }

  // sanity check that this figure is closed
  map<edge, int> D = make_degrees(H);
  for (const auto & f : H) {
    assert(f.size() == 3);
    FOR(i,3) {
      vec a = f[i];
      vec b = f[(i+1)%3];
      int d = D[{a,b}] + D[{b,a}];
      assert(d == 2);
    }
  }

  return H;
}

// line stuff
bool on (vec a, vec b, vec x) {
  return eq(len(x-a) + len(x-b), len(a-b));
}

// find the intersection point of ab with cd
vec isect(vec a, vec b, vec c, vec d) {
  vec u = (b-a), v = (d-c), z = (c-a);
  vec vz = v^z, vu = v^u;
  ld s = len(vz) / len(vu) * sign(vz*vu);
  return a + u*s;
}

typedef pair<vec, ld> circle_t;

bool in_circle(const vec& v, const circle_t& C) {
  return len(v - C.first) <= C.second + EPS;
}

circle_t better(circle_t A, circle_t B) {
  if (A.second < B.second) return A;
  return B;
}

circle_t find_circle(vec a) { return {a, 0}; }
circle_t find_circle(vec a, vec b) { return { (a+b)/2, len(a-b) / 2 }; }
circle_t find_circle(vec a, vec b, vec c, bool force_on = false) {
  vec u = (b-a), v = (c-a);
  vec norm = u ^ v;
  vec uperp = u^norm, vperp = v^norm;
  vec ab = (a+b)/2, ac = (a+c)/2;

  if (is_colinear(a,b,c)) {
    if (on(a,b,c)) return { (a+b)/2, len(a-b) / 2 };
    if (on(a,c,b)) return { (a+c)/2, len(a-c) / 2 };
    if (on(c,b,a)) return { (c+b)/2, len(c-b) / 2 };
    assert(false);
  }

  vec ans = isect(ab, ab + uperp, ac, ac + vperp);
  assert(eq(len(ans-a), len(ans-b)));
  assert(eq(len(ans-a), len(ans-c)));

  circle_t C = { ans, (len(ans-a) + len(ans-b) + len(ans-c)) / 3.0l };
  assert(in_circle(a, C) && eq(len(ans-a), C.second));
  assert(in_circle(b, C) && eq(len(ans-b), C.second));
  assert(in_circle(c, C) && eq(len(ans-c), C.second));

  if (force_on) return C;

  circle_t C_ab = find_circle(a,b);
  circle_t C_bc = find_circle(b,c);
  circle_t C_ac = find_circle(a,c);

  if (in_circle(c, C_ab)) C = better(C, C_ab);
  if (in_circle(a, C_bc)) C = better(C, C_bc);
  if (in_circle(b, C_ac)) C = better(C, C_ac);

  assert(in_circle(a,C));
  assert(in_circle(b,C));
  assert(in_circle(c,C));

  return C;
}

/// minimum enclosing circle- expected runtime- O(N)

// Find circle of N points. K of them (the last K) are guaranteed
// to be on the boundary.
circle_t find_circle(vec* P, int N, int K) {
  if (K >= 3) {
    assert(K == 3);
    assert(!is_colinear(P[N-1],P[N-2],P[N-3]));
    assert(side(P[N-1],P[N-2],P[N-3],P[0]) == ON);
    auto C = find_circle(P[N-1],P[N-2],P[N-3],true);
    return C;
  }

  if (N == 1) return find_circle(P[0]);
  if (N == 2) return find_circle(P[0],P[1]);
  assert(K < N);

  // pick a random point, remove it, recurse.
  // with very high probability, that recursed circle is the optimal circle
  // if not, we just try again (and this point is added to the K set)
  int i = rand()%(N-K);

  swap(P[i], P[N-1-K]); swap(P[N-1-K], P[N-1]); // hack: avoid deleting back K
  auto C = find_circle(P, N-1, K);
  swap(P[N-1-K], P[N-1]); swap(P[i], P[N-1-K]);

  if (in_circle(P[i],C)) return C;

  // Didn't work, that's fine. Add it to our K-set ("boundary set") and try again
  swap(P[i], P[N-1-K]);
  C = find_circle(P, N, K+1);
  swap(P[i], P[N-1-K]);

  return C;
}

vec P[MAXN];
vec F[MAXN];
vec tmp[MAXN];
int main() {
  int N,x,y,z;
  scanf("%d",&N);
  FOR(i,N) {
    scanf("%d%d%d",&x,&y,&z);
    P[i] = vec(x,y,z);
  }

  // Find the convex hull
  hull H = find_hull(P,N);

  // Now try all cylinders with bases aligned with faces of the hull
  ld ans = 1000000000000000.;
  for (const auto & f : H) {
    assert(f.size() == 3);
    vec norm = (f[1] - f[0]) ^ (f[2] - f[0]);

    ld height = 0;
    FOR(i,N) height = max(height, abs((P[i] - f[0])*norm));
    height /= len(norm);

    FOR(i,N) F[i] = projection(f[0],f[1],f[2],P[i]);
    auto C = find_circle(F,N,0);
    ld r = C.second;

    FOR(i,N) assert(in_circle(F[i], C));      // sanity check, everyone should be in the circle
    ans = min(ans, PI * r * r * height);
  }

  cout << fixed << setprecision(8) << ans << endl;
}
