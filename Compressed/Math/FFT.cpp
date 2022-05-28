struct FFT {
struct node {
  double x,y;
  node() {}
  node(double a, double b): x(a), y(b) {}
  node operator+(node a)const
                      {return node(x+a.x,y+a.y);}
  node operator-(node a)const
                      {return node(x-a.x,y-a.y);}
  node operator*(node a)const
    {return node(x*a.x-y*a.y,x*a.y+a.x*y);}
};
int M; vector<node> A, B, w[2]; vector<int>rev;
const long double pi = acos(-1);
void init(int n) {
  M = 1; while(M < n) M <<= 1; M <<= 1;
  A.resize(M); B.resize(M); w[0] = w[1] = rev = B;
  for (int i=0; i<M; i++) {
    int j=i,y=0;
    for (int x=1; x<M; x<<=1,j>>=1) (y<<=1)+=j&1;
    rev[i]=y;
  }
  for (int i=0; i<M; i++) {
    w[0][i] = node( cos(2*pi*i/M),sin(2*pi*i/M));
    w[1][i] = node( cos(2*pi*i/M),-sin(2*pi*i/M));
  }
}
void ftransform( vector<node> &A, int p ) {
  for (int i=0; i<M; i++)
    if (i<rev[i])   swap(A[i],A[rev[i]]);
  for (int i=1; i<M; i<<=1)
    for (int j=0,t=M/(i<<1); j<M; j+=i<<1)
      for (int k=0,l=0; k<i; k++,l+=t) {
        node x=w[p][l]*A[i+j+k], y=A[j+k];
        A[j+k]=y+x; A[j+k+i]=y-x;
      }
  if (p)  for (int i=0; i<M; i++) A[i].x/=M;
}
void multiply(VI &P, VI &Q, VI &res) {
  init(max(P.size(),Q.size()));
  for(int i=0; i<M; i++)
    A[i].x=A[i].y=B[i].x=B[i].y=0;
  for(int i = 0; i < P.size(); i++) A[i].x = P[i];
  for(int i = 0; i < Q.size(); i++) B[i].x = Q[i];
  ftransform(A,0); ftransform(B,0);
  for (int k=0; k<M; k++) A[k] = A[k]*B[k];
  ftransform(A,1);
  res.resize(M);
  for( int i=0; i<M; i++)  res[i] = round(A[i].x);
}
///use long double in fft if RT >= 13
const int RT = 15;   ///Upto M <= 4^RT
vector<LL>anymod(vector<LL>&a,vector<LL>&b,LL mod){
  init(max(a.size(),b.size())); node Z(0, 0);
  vector<node>al(M,Z),ar(M,Z),bl(M,Z),br(M,Z);
  for (int i=0; i<a.size(); i++) {
    LL k = a[i]%mod; al[i] = node(k >> RT, 0);
    ar[i] = node(k & ((1<<RT)-1), 0);
  }
  for (int i=0; i<b.size(); i++) {
    LL k = b[i]%mod; bl[i] = node(k >>RT, 0);
    br[i] = node(k & ((1<<RT)-1), 0);
  }
  ftransform(al, 0); ftransform(ar, 0);
  ftransform(bl, 0); ftransform(br, 0);
  for (int i=0; i<M; i++) {
    node ll = al[i] * bl[i], lr = al[i] * br[i];
    node rl = ar[i] * bl[i], rr = ar[i] * br[i];
    al[i] = ll; ar[i] = lr;
    bl[i] = rl; br[i] = rr;
  }
  ftransform(al, true); ftransform(ar, true);
  ftransform(bl, true); ftransform(br, true);
  vector<LL> ans(M);
  for (int i=0; i<M; i++) {
    LL right = round(br[i].x);
    right %= mod;
    LL mid=round(round(bl[i].x) + round(ar[i].x));
    mid = ((mid%mod)<<RT)%mod;
    LL left=round(al[i].x);
    left = ((left%mod)<<(2*RT))%mod;
    ans[i] = (left+mid+right)%mod;
  }
  return ans;
}
};
