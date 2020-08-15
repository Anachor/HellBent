#include<bits/stdc++.h>
using namespace std;

typedef double T;

struct PT {
  T x, y;
  PT() {}
  PT(T x, T y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (T c)     const { return PT(x*c,   y*c  ); }
  PT operator / (T c)     const { return PT(x/c,   y/c  ); }
  bool operator < (PT A)       const { return make_pair(x, y) < make_pair(A.x, A.y);}

};

T dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
T dist2(PT p, PT q)   { return dot(p-q,p-q); }
T cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")";
}

PT dir;
bool half(PT p){
    return cross(dir, p) < 0 || (cross(dir, p) == 0 && dot(dir, p) > 0);
}

bool polarComp(PT p, PT q) {
    return make_tuple(half(p), 0) < make_tuple(half(q), cross(p, q));
}

void process(vector<PT> &P) {
    int mnid = 0;
    for (int i=0; i<P.size(); i++)
        if (P[i] < P[mnid])
            mnid = i;
    rotate(P.begin(), P.begin()+mnid, P.end());
}


vector<PT> MinkowskiSum(vector<PT> A, vector<PT> B){
    process(A);
    process(B);

    int n = A.size(), m = B.size();
    vector<PT> P(n), Q(m);
    for(int i = 0; i < n; i++) P[i] = A[(i+1)%n] - A[i];
    for(int i = 0; i < m; i++) Q[i] = B[(i+1)%m] - B[i];

    dir = PT(0, -1);
    vector<PT> C(n+m+1);
    merge(P.begin(), P.end(), Q.begin(), Q.end(), C.begin()+1, polarComp);
    C[0] = A[0] + B[0];

    for(int i = 1; i < C.size(); i++) C[i] = C[i] + C[i-1];
    C.pop_back();
    return C;
}


///Begin
vector<PT> input() {
    int n;
    cin>>n;
    vector<PT> ans(n);

    for (int i=0; i<n; i++) cin>>ans[i].x>>ans[i].y;
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout<<setprecision(10)<<fixed;

    int t;
    cin>>t;

    while (t--) {
        double x;
        cin>>x;
        x = x/180.0*acos(-1);
        double k = 0.5/tan(x/2);

        vector<PT> A = input();
        vector<PT> B = input();

        for (PT &P: A) {
            P = PT(P.x/2-k*P.y, P.y/2+k*P.x);
        }

        for (PT &P: B) {
            P = PT(P.x/2+k*P.y, P.y/2-k*P.x);
        }

        vector<PT> S = MinkowskiSum(A, B);

        double ans = 0;
        for (int i=0; i<S.size(); i++)  {
            ans += cross(S[i], S[(i+1)%S.size()]);
        }
        cout<<setprecision(10)<<fixed<<abs(ans/2.0)<<endl;
    }
}
