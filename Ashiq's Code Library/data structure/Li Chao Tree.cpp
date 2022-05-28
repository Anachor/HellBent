#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 100;
LL MAXY = 1e9;

struct line{ LL m,c; }tr[N];
int ch[N][2], tot;

LL val(line l, LL x){ return l.m*x + l.c;}
void init(int cn) {
  ch[cn][0] = ch[cn][1] = -1;
}
/// to add line caLL(new line,0,MIN_X,MAX_X)
void add_line(int cn, int b, int e, line l){
  if(tot==0){ tr[0] = l; init(0); tot++; return;}
  if(l.m == tr[cn].m && l.c == tr[cn].c) return;
  int m = (b + e)>>1;
  bool lft = val(l, b) < val(tr[cn], b);
  bool mid = val(l, m) < val(tr[cn], m);
  bool rgt = val(l, e) < val(tr[cn], e);
  if(lft == rgt){ if(lft) tr[cn] = l; return;}
  if(mid) swap(tr[cn], l);
  if(b==e) return;
  else if(lft != mid){
    if(ch[cn][0] == -1){
      tr[tot] = l; init(tot); ch[cn][0] = tot++;
      return;
    }
    add_line(ch[cn][0], b, m, l);
  }
  else{
    if(ch[cn][1] == -1){
        tr[tot] = l; init(tot); ch[cn][1] = tot++;
        return;
    }
    add_line(ch[cn][1],m+1,e,l);
  }
}
/// call  get(0,1,MAX_X,x)
LL get(int cn, int b, int e, LL x){
  if(cn==-1) return MAXY;
  int m = (b + e)>>1;
  if(b==e) return val(tr[cn],x);
  if(x <= m) return min(val(tr[cn],x),get(ch[cn][0],b,m,x));
  return min(val(tr[cn],x),get(ch[cn][1],m+1,e,x));
}

int main() {

}
