struct pnt{
  int x, y, idx;
  bool operator<(const pnt &p)const{
    return pi(x, y) < pi(p.x, p.y);
  }
}a[5005];
struct line{
    int dx, dy, i1, i2;
};
vector<line> v;
int n, rev[5005];
lint p, q;
LL ccw(pnt a, pnt b, pnt c){
    int dx1 = b.x - a.x;
    int dy1 = b.y - a.y;
    int dx2 = c.x - a.x;
    int dy2 = c.y - a.y;
    return abs(1ll * dx1 * dy2 - 1ll * dy1 * dx2);
}
void solve(int c1, int c2, LL l){
    ans = max(ans, ccw(a[c1], a[c2], a[0]));
    ans = max(ans, ccw(a[c1], a[c2], a[n-1]));
}
int main(){
    cin >> n;
    for(int i=0; i<n;i++) cin >> a[i].x >> a[i].y;
    sort(a, a+n);
    for(int i=0; i < n;i++) a[i].idx = rev[i] = i;
    for(int i=0; i<n; i++)
      for(int j=i+1; j<n; j++)
        v.pb({a[j].x-a[i].x,a[j].y-a[i].y,
                              a[i].idx,a[j].idx});

    sort(v.begin(), v.end(), [&]
         (const line &a, const line &b){
        LL cw = 1ll*a.dx*b.dy - 1ll * b.dx * a.dy;
        if(cw != 0) return cw > 0;
        return pi(a.i1, a.i2) < pi(b.i1, b.i2);
    });
    LL ret = 0;
    for(int i=0; i<v.size(); i++){
        int c1 = rev[v[i].i1], c2 = rev[v[i].i2];
        if(c1 > c2) swap(c1, c2);
        solve(c1, c2, p);
        swap(a[c1], a[c2]);
        swap(rev[v[i].i1], rev[v[i].i2]);
    }
}